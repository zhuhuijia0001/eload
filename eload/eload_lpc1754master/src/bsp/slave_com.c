#include <rthw.h>
#include <rtthread.h>

#include <stdint.h>

#include "dev_slave_uart.h"

#include "slave_com.h"

#include "packet.h"

#define  MAX_RECV_INTERVAL   20

static rt_device_t s_dev_slave_com = RT_NULL;

static slave_com_port s_cur_com_port = SLAVE_PORT_NONE;

static rt_timer_t s_timer = RT_NULL;

static void (*s_receive_callback)(uint8_t *payload, uint16_t payload_size) = RT_NULL;

typedef enum
{
	RECV_STATUS_IDLE = 0,
	
	RECV_STATUS_HEADER,
	
	RECV_STATUS_SUM,
	
	RECV_STATUS_PAYLOAD_LEN,
	
	RECV_STATUS_PAYLOAD
} recv_status;

typedef struct 
{
	uint8_t  recv_buffer[MAX_RECV_PACKET_SIZE];
	
	uint16_t recv_ptr;
	
	recv_status status;
} recv_struct;

static recv_struct s_recv_struct = 
{
	.recv_ptr      = 0,
	
	.status        = RECV_STATUS_IDLE	
};

static uint16_t s_left = 0;

static uint8_t s_sum  = 0;

static rt_tick_t s_tick = 0;

static rt_err_t data_receive_indicate(rt_device_t dev, rt_size_t size)
{
	/* parse packet */
	uint8_t ch;
	
	RT_ASSERT(s_dev_slave_com != RT_NULL);
	
	RT_ASSERT(s_timer != RT_NULL);
	RT_ASSERT(s_tick > 0);
	
	while (size--)
	{
		rt_device_read(s_dev_slave_com, 0, &ch, 1);

		if (s_recv_struct.status == RECV_STATUS_IDLE)
		{
			if (ch == (uint8_t)PACKET_HEADER)
			{
				s_recv_struct.recv_buffer[s_recv_struct.recv_ptr++] = ch;
				
				s_recv_struct.status = RECV_STATUS_HEADER;
				
				rt_timer_control(s_timer, RT_TIMER_CTRL_SET_TIME, &s_tick);
				rt_timer_start(s_timer);
			}
		}
		else if (s_recv_struct.status == RECV_STATUS_HEADER)
		{
			if (ch == (uint8_t)(PACKET_HEADER >> 8))
			{
				s_recv_struct.recv_buffer[s_recv_struct.recv_ptr++] = ch;
				
				s_recv_struct.status = RECV_STATUS_SUM;
				
				rt_timer_stop(s_timer);
				rt_timer_control(s_timer, RT_TIMER_CTRL_SET_TIME, &s_tick);
				rt_timer_start(s_timer);
			}
			else
			{
				s_recv_struct.status = RECV_STATUS_IDLE;
				
				s_recv_struct.recv_ptr = 0;
				
				rt_timer_stop(s_timer);
			}
		}
		else if (s_recv_struct.status == RECV_STATUS_SUM)
		{
			s_recv_struct.recv_buffer[s_recv_struct.recv_ptr++] = ch;
				
			s_recv_struct.status = RECV_STATUS_PAYLOAD_LEN;
			
			s_left = sizeof(uint16_t);
			
			rt_timer_stop(s_timer);
			rt_timer_control(s_timer, RT_TIMER_CTRL_SET_TIME, &s_tick);
			rt_timer_start(s_timer);
		}
		else if (s_recv_struct.status == RECV_STATUS_PAYLOAD_LEN)
		{
			s_recv_struct.recv_buffer[s_recv_struct.recv_ptr++] = ch;
			
			s_left--;
			
			if (s_left > 0)
			{
				rt_timer_stop(s_timer);
				rt_timer_control(s_timer, RT_TIMER_CTRL_SET_TIME, &s_tick);
				rt_timer_start(s_timer);
			}
			else
			{
				/* validate length */
				uint16_t payload_len;
				payload_len = (ch << 8) | s_recv_struct.recv_buffer[s_recv_struct.recv_ptr - 2];
				
				if (payload_len + sizeof(PACKET) - 1 <= MAX_RECV_PACKET_SIZE)
				{
					s_recv_struct.status = RECV_STATUS_PAYLOAD;
					
					s_sum = 0;
					
					s_left = payload_len;
					
					rt_timer_stop(s_timer);
					rt_timer_control(s_timer, RT_TIMER_CTRL_SET_TIME, &s_tick);
					rt_timer_start(s_timer);
				}
				else
				{
					/* invalid length */
					s_recv_struct.status = RECV_STATUS_IDLE;
				
					s_recv_struct.recv_ptr = 0;	
					
					rt_timer_stop(s_timer);
				}
			}
		}
		else if (s_recv_struct.status == RECV_STATUS_PAYLOAD)
		{
			s_recv_struct.recv_buffer[s_recv_struct.recv_ptr++] = ch;
			
			s_sum ^= ch;
			
			s_left--;
			
			if (s_left > 0)
			{
				rt_timer_stop(s_timer);
				rt_timer_control(s_timer, RT_TIMER_CTRL_SET_TIME, &s_tick);
				rt_timer_start(s_timer);
			}
			else
			{
				/* check sum */
				PACKET *packet = (PACKET *)s_recv_struct.recv_buffer;
				if (packet->sum == s_sum)
				{
					if (s_receive_callback != RT_NULL)
					{
						s_receive_callback(packet->payload, packet->payload_size);
					}
				}
				
				s_recv_struct.status = RECV_STATUS_IDLE;
				
				s_recv_struct.recv_ptr = 0;	

				rt_timer_stop(s_timer);
			}
		}
	}
	
	return RT_EOK;
}

static void timer_callback(void *parameter)
{
	/* receive timeout */
	rt_ubase_t level = rt_hw_interrupt_disable();

	s_recv_struct.status = RECV_STATUS_IDLE;			
	s_recv_struct.recv_ptr = 0;	

	rt_hw_interrupt_enable(level);
}

void salve_com_init(void)
{
	dev_slave_uart_init();
	
	s_dev_slave_com = rt_device_find("uart3");
	RT_ASSERT(s_dev_slave_com != RT_NULL);
	
	s_tick = rt_tick_from_millisecond(MAX_RECV_INTERVAL);
	s_timer = rt_timer_create("comtimer", timer_callback, RT_NULL, s_tick, RT_TIMER_FLAG_ONE_SHOT/* | RT_TIMER_FLAG_SOFT_TIMER */);
	
	RT_ASSERT(s_timer != RT_NULL);
	
	rt_device_set_rx_indicate(s_dev_slave_com, data_receive_indicate);
	
	rt_device_open(s_dev_slave_com, RT_DEVICE_OFLAG_RDWR);	
}

uint16_t slave_com_write(slave_com_port port, const uint8_t *buffer, uint16_t size)
{
	RT_ASSERT(s_dev_slave_com != RT_NULL);
	
	if (port != s_cur_com_port)
	{
		uint32_t com_port = port;
		rt_device_control(s_dev_slave_com, CMD_SLAVE_UART_SWITCH_CHANNEL, &com_port);
		
		s_cur_com_port = port;
	}
	
	return rt_device_write(s_dev_slave_com, 0, buffer, size);
}

void slave_com_set_read_callback(void (*fn)(uint8_t *payload, uint16_t payload_size))
{
	s_receive_callback = fn;
}

