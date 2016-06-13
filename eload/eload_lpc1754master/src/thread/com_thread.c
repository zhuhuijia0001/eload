#include <rtthread.h>
#include <stdint.h>
#include "type.h"
#include "packet.h"

#include "app_cfg.h"

#include "slave_com.h"

#include "trace.h"

#include "parameter.h"
#include "global.h"

#include "com_thread.h"
#include "msg_thread.h"

/* port polling interval */
#define PORT_POLL_INTERVAL    20

static rt_mq_t s_payload_queue = RT_NULL;

/* message queue len */
#define PKT_MSG_QUEUE_LEN    4

static void packet_receive_callback(uint8_t *payload, uint16_t payload_size)
{
	RT_ASSERT(s_payload_queue != RT_NULL);
	
	rt_mq_send(s_payload_queue, payload, payload_size);
}

/* communication status */
typedef enum
{
	COM_STATUS_POLLING = 0,

	COM_STATUS_ONE_CHANNEL,

	COM_STATUS_BROADCAST
} COM_STATUS;

static uint32_t s_cur_voltage[CHANNEL_COUNT];

uint32_t get_cur_voltage(int channel)

{
	return s_cur_voltage[channel];
}

static uint32_t s_cur_current[CHANNEL_COUNT];

uint32_t get_cur_current(int channel)
{
	return s_cur_current[channel];
}

/* com port thread */
static void com_thread_entry(void *parameter)
{
	rt_err_t ret;

	/* payload receive */
	uint8_t payload[MAX_RECV_PACKET_SIZE - (sizeof(PACKET) - 1)];
	
	uint8_t packet_buffer[MAX_SEND_PACKET_SIZE];
	
	uint16_t packet_len;
	
	slave_com_port cur_port;

	rt_tick_t  tick;
	
	TEST_CMD  test_cmd;
	
	COM_STATUS com_status;

	TEST_CONTENT test_content;

	uint16_t  refresh_counter = 0;

	const uint16_t MAX_REFRESH_COUNT = 10;
	
	slave_com_set_read_callback(packet_receive_callback);
	salve_com_init();

	/* get adjust parameter first */
	packet_len = build_get_adjust_value_cmd_packet(packet_buffer, sizeof(packet_buffer));

	cur_port = SLAVE_PORT_0;

	RT_ASSERT(s_payload_queue != RT_NULL);
	while (cur_port < SLAVE_PORT_COUNT)
	{
		slave_com_write(cur_port, packet_buffer, packet_len);
		
		/* wait for replay */
		ret = rt_mq_recv(s_payload_queue, payload, sizeof(payload), rt_tick_from_millisecond(PORT_POLL_INTERVAL));
		if (ret == RT_EOK)
		{
			PAYLOAD_CMD_GET_ADJUST_VALUE_RET *adjust_param_payload = (PAYLOAD_CMD_GET_ADJUST_VALUE_RET *)payload;
			if (adjust_param_payload->cmd == CMD_GET_ADJUST_VALUE)
			{
				g_channel_adjust_value[cur_port].measure_voltage = adjust_param_payload->measure_voltage;
				g_channel_adjust_value[cur_port].actual_voltage  = adjust_param_payload->actual_voltage;
				g_channel_adjust_value[cur_port].measure_current = adjust_param_payload->measure_current;
				g_channel_adjust_value[cur_port].actual_current  = adjust_param_payload->actual_current;
			}
		}

		cur_port++;		
	}

	/* start test */
	cur_port = SLAVE_PORT_0;
	
	packet_len = build_poll_cmd_packet(packet_buffer, sizeof(packet_buffer));
				
	com_status = COM_STATUS_POLLING;
	
	while (RT_TRUE)
	{
		/* get cmd from UI */
		ret = test_cmd_query(&test_cmd, RT_WAITING_NO);
		if (ret == RT_EOK)
		{
			/* got a cmd */
			switch (test_cmd.test_type)
			{
			case TEST_TYPE_CV_MODE:
				packet_len = build_cv_mode_cmd_packet(packet_buffer, sizeof(packet_buffer), 
													test_cmd.test_config.cv_mode_config.voltage_val);

				if (test_cmd.channel == SLAVE_PORT_ALL)
				{
					com_status = COM_STATUS_BROADCAST;
					
					cur_port = SLAVE_PORT_0;
				}
				else
				{
					com_status = COM_STATUS_ONE_CHANNEL;

					cur_port = test_cmd.channel;
				}
				
				break;
			
			case TEST_TYPE_CC_MODE:
				packet_len = build_cc_mode_cmd_packet(packet_buffer, sizeof(packet_buffer), 
													test_cmd.test_config.cc_mode_config.current_val);

				if (test_cmd.channel == SLAVE_PORT_ALL)
				{
					com_status = COM_STATUS_BROADCAST;
					
					cur_port = SLAVE_PORT_0;
				}
				else
				{
					com_status = COM_STATUS_ONE_CHANNEL;

					cur_port = test_cmd.channel;
				}
				
				break;
			
			case TEST_TYPE_CR_MODE:
				packet_len = build_cr_mode_cmd_packet(packet_buffer, sizeof(packet_buffer), 
													test_cmd.test_config.cr_mode_config.resist_val);

				if (test_cmd.channel == SLAVE_PORT_ALL)
				{
					com_status = COM_STATUS_BROADCAST;
					
					cur_port = SLAVE_PORT_0;
				}
				else
				{
					com_status = COM_STATUS_ONE_CHANNEL;

					cur_port = test_cmd.channel;
				}
				
				break;

			case TEST_TYPE_EMPTY_LOAD_TEST:
				packet_len = build_empty_load_test_cmd_packet(packet_buffer, sizeof(packet_buffer), 
													test_cmd.test_config.empty_load_test_config.duration,
													test_cmd.test_config.empty_load_test_config.ac_upper,
													test_cmd.test_config.empty_load_test_config.voltage_lower,
													test_cmd.test_config.empty_load_test_config.voltage_upper);

				if (test_cmd.channel == SLAVE_PORT_ALL)
				{
					com_status = COM_STATUS_BROADCAST;
					
					cur_port = SLAVE_PORT_0;
				}
				else
				{
					com_status = COM_STATUS_ONE_CHANNEL;

					cur_port = test_cmd.channel;
				}
				
				break;

			case TEST_TYPE_CV_TEST:
				packet_len = build_cv_test_cmd_packet(packet_buffer, sizeof(packet_buffer),
													test_cmd.test_config.cv_test_config.test_category,
													test_cmd.test_config.cv_test_config.voltage_level,
													test_cmd.test_config.cv_test_config.voltage_val,
													test_cmd.test_config.cv_test_config.duration,
													test_cmd.test_config.cv_test_config.ac_upper,
													test_cmd.test_config.cv_test_config.current_lower,
													test_cmd.test_config.cv_test_config.current_upper);

				if (test_cmd.channel == SLAVE_PORT_ALL)
				{
					com_status = COM_STATUS_BROADCAST;
					
					cur_port = SLAVE_PORT_0;
				}
				else
				{
					com_status = COM_STATUS_ONE_CHANNEL;

					cur_port = test_cmd.channel;
				}
				
				break;

			case TEST_TYPE_CC_TEST:
				packet_len = build_cc_test_cmd_packet(packet_buffer, sizeof(packet_buffer),
													test_cmd.test_config.cc_test_config.test_category,
													test_cmd.test_config.cc_test_config.voltage_level,
													test_cmd.test_config.cc_test_config.current_val,
													test_cmd.test_config.cc_test_config.duration,
													test_cmd.test_config.cc_test_config.ac_upper,
													test_cmd.test_config.cc_test_config.voltage_lower,
													test_cmd.test_config.cc_test_config.voltage_upper);

				if (test_cmd.channel == SLAVE_PORT_ALL)
				{
					com_status = COM_STATUS_BROADCAST;
					
					cur_port = SLAVE_PORT_0;
				}
				else
				{
					com_status = COM_STATUS_ONE_CHANNEL;

					cur_port = test_cmd.channel;
				}

				break;

			case TEST_TYPE_CR_TEST:
				packet_len = build_cr_test_cmd_packet(packet_buffer, sizeof(packet_buffer),
													test_cmd.test_config.cr_test_config.test_category,
													test_cmd.test_config.cr_test_config.voltage_level,
													test_cmd.test_config.cr_test_config.resist_val,
													test_cmd.test_config.cr_test_config.duration,
													test_cmd.test_config.cr_test_config.ac_upper,
													test_cmd.test_config.cr_test_config.voltage_lower,
													test_cmd.test_config.cr_test_config.voltage_upper,
													test_cmd.test_config.cr_test_config.current_lower,
													test_cmd.test_config.cr_test_config.current_upper);

				if (test_cmd.channel == SLAVE_PORT_ALL)
				{
					com_status = COM_STATUS_BROADCAST;
					
					cur_port = SLAVE_PORT_0;
				}
				else
				{
					com_status = COM_STATUS_ONE_CHANNEL;

					cur_port = test_cmd.channel;
				}
				
				break;

			case TEST_TYPE_OVER_CURRENT_TEST:
				packet_len = build_over_current_test_cmd_packet(packet_buffer, sizeof(packet_buffer),
													test_cmd.test_config.over_current_test_config.test_category,
													test_cmd.test_config.over_current_test_config.voltage_level,
													test_cmd.test_config.over_current_test_config.interval,
													test_cmd.test_config.over_current_test_config.ac_upper,
													test_cmd.test_config.over_current_test_config.current_upper);
	
				if (test_cmd.channel == SLAVE_PORT_ALL)
				{
					com_status = COM_STATUS_BROADCAST;
					
					cur_port = SLAVE_PORT_0;
				}
				else
				{
					com_status = COM_STATUS_ONE_CHANNEL;

					cur_port = test_cmd.channel;
				}
				
				break;

			case TEST_TYPE_SHORT_TEST:
				packet_len = build_short_test_cmd_packet(packet_buffer, sizeof(packet_buffer),
													test_cmd.test_config.short_test_config.test_category,
													test_cmd.test_config.short_test_config.voltage_level,
													test_cmd.test_config.short_test_config.duration,
													test_cmd.test_config.short_test_config.ac_upper,
													test_cmd.test_config.short_test_config.current_upper);

				if (test_cmd.channel == SLAVE_PORT_ALL)
				{
					com_status = COM_STATUS_BROADCAST;
					
					cur_port = SLAVE_PORT_0;
				}
				else
				{
					com_status = COM_STATUS_ONE_CHANNEL;

					cur_port = test_cmd.channel;
				}
				
				break;

			case TEST_TYPE_DISCHARGE_TEST:
				packet_len = build_discharge_test_cmd_packet(packet_buffer, sizeof(packet_buffer),
													test_cmd.test_config.discharge_test_config.current_val,
													test_cmd.test_config.discharge_test_config.duration);

				if (test_cmd.channel == SLAVE_PORT_ALL)
				{
					com_status = COM_STATUS_BROADCAST;
					
					cur_port = SLAVE_PORT_0;
				}
				else
				{
					com_status = COM_STATUS_ONE_CHANNEL;

					cur_port = test_cmd.channel;
				}
				
				break;
				
			case TEST_TYPE_NONE:
				packet_len = build_stop_cmd_packet(packet_buffer, sizeof(packet_buffer));

				if (test_cmd.channel == SLAVE_PORT_ALL)
				{
					com_status = COM_STATUS_BROADCAST;
					
					cur_port = SLAVE_PORT_0;
				}
				else
				{
					com_status = COM_STATUS_ONE_CHANNEL;

					cur_port = test_cmd.channel;
				}
				
				break;

			case TEST_TYPE_SET_ADJUST_VALUE:
				packet_len = build_set_adjust_value_cmd_packet(packet_buffer, sizeof(packet_buffer), 
															test_cmd.test_config.adjust_value_config.measure_voltage, 
															test_cmd.test_config.adjust_value_config.actual_voltage,
															test_cmd.test_config.adjust_value_config.measure_current,
															test_cmd.test_config.adjust_value_config.actual_current);

				if (test_cmd.channel == SLAVE_PORT_ALL)
				{
					com_status = COM_STATUS_BROADCAST;
					
					cur_port = SLAVE_PORT_0;
				}
				else
				{
					com_status = COM_STATUS_ONE_CHANNEL;

					cur_port = test_cmd.channel;
				}
				
				break;
				
			default:
				RT_ASSERT(RT_FALSE);
			
				packet_len = 0;
			
				break;
			}
		}

#if 0
		int i;
		/* send command */
		TRACE("packet len:%d\n", packet_len);
			
		for (i = 0; i < packet_len; i++)
		{
			TRACE("0x%02X ", packet_buffer[i]);
		}
		TRACE("\n");			
#endif

		slave_com_write(cur_port, packet_buffer, packet_len);
		
		/* wait for replay */
		RT_ASSERT(s_payload_queue != RT_NULL);
		tick = rt_tick_get();
		ret = rt_mq_recv(s_payload_queue, payload, sizeof(payload), rt_tick_from_millisecond(PORT_POLL_INTERVAL));
		if (ret == RT_EOK)
		{
#if 0
			/* get reply successfully */
			TRACE("get replay from port %d OK\n", cur_port);
				
			for (i = 0; i < sizeof(payload); i++)
			{
				TRACE("0x%02X ", payload[i]);
			}
			TRACE("\n");				
#endif
			g_channel_status[cur_port] = CHANNEL_ONLINE;
			
			if (com_status == COM_STATUS_POLLING)
			{
				/* get value */
				PAYLOAD_CMD_POLL_RET *poll_payload = (PAYLOAD_CMD_POLL_RET *)payload;

				s_cur_voltage[cur_port] = poll_payload->voltage;
				s_cur_current[cur_port] = poll_payload->current;
				
				if (poll_payload->test_type == TEST_TYPE_CV_MODE
					|| poll_payload->test_type == TEST_TYPE_CC_MODE
					|| poll_payload->test_type == TEST_TYPE_CR_MODE
					|| poll_payload->test_type == TEST_TYPE_NONE)
				{
					if (cur_port == SLAVE_PORT_0)
					{
						/* only update port 0 */
						refresh_counter++;
						if (refresh_counter == MAX_REFRESH_COUNT)
						{
							test_content.channel = cur_port;
							test_content.test_type = poll_payload->test_type;
							test_content.test_status = poll_payload->test_status;
							test_content.ac_current = poll_payload->ac;
							test_content.voltage = poll_payload->voltage;
							test_content.current = poll_payload->current;
							refresh_test_content(&test_content);

							refresh_counter = 0;
						}
					}
				}

				if (poll_payload->test_type == TEST_TYPE_EMPTY_LOAD_TEST
					|| poll_payload->test_type == TEST_TYPE_CV_TEST
					|| poll_payload->test_type == TEST_TYPE_CC_TEST
					|| poll_payload->test_type == TEST_TYPE_CR_TEST
					|| poll_payload->test_type == TEST_TYPE_OVER_CURRENT_TEST
					|| poll_payload->test_type == TEST_TYPE_SHORT_TEST
					|| poll_payload->test_type == TEST_TYPE_DISCHARGE_TEST
					|| poll_payload->test_type == TEST_TYPE_NONE)
				{
					test_content.channel    = cur_port;
					test_content.test_type  = poll_payload->test_type;
					test_content.test_status = poll_payload->test_status;
					test_content.ac_current = poll_payload->ac;
					test_content.voltage    = poll_payload->voltage;
					test_content.current    = poll_payload->current;
				
					test_content_notify(&test_content);
				}
			}
			
			tick = rt_tick_from_millisecond(PORT_POLL_INTERVAL) - (rt_tick_get() - tick);
			if (tick > 0)
			{
				/* delay the left tick */
				rt_thread_delay(tick);
			}
		}
		else
		{
#if 0
			/* timeout, the device does not exist */
			TRACE("get replay from port %d timeout\n", cur_port);
#endif
			g_channel_status[cur_port] = CHANNEL_OFFLINE;

			if (com_status == COM_STATUS_POLLING)
			{
				/* get value */
				if (cur_port == SLAVE_PORT_0)
				{
					/* only update port 0 */
					refresh_counter++;
					if (refresh_counter == MAX_REFRESH_COUNT)
					{
						test_content.channel = cur_port;
						test_content.test_type = TEST_TYPE_NONE;
						test_content.test_status = TEST_STATUS_IDLE;
						test_content.ac_current = 0;
						test_content.voltage = 0;
						test_content.current = 0;
						refresh_test_content(&test_content);
					
						refresh_counter = 0;
					}		
				}
			}	
		}

		/* next slave port */
		if (com_status == COM_STATUS_ONE_CHANNEL)
		{
			packet_len = build_poll_cmd_packet(packet_buffer, sizeof(packet_buffer));

			com_status = COM_STATUS_POLLING;
		}

		cur_port++;
		if (cur_port == SLAVE_PORT_COUNT)
		{
			if (com_status == COM_STATUS_BROADCAST)
			{
				/* user cmd sending complete, prepare the polling packet */
				packet_len = build_poll_cmd_packet(packet_buffer, sizeof(packet_buffer));
				
				com_status = COM_STATUS_POLLING;
			}
			
			cur_port = SLAVE_PORT_0;
		}
	}
}

void start_com_thread(void)
{
	rt_thread_t tid;
	
	s_payload_queue = rt_mq_create("comqueue", MAX_RECV_PACKET_SIZE - (sizeof(PACKET) - 1), PKT_MSG_QUEUE_LEN, RT_IPC_FLAG_FIFO);
	RT_ASSERT(s_payload_queue != RT_NULL);
	
	tid = rt_thread_create("com", com_thread_entry, RT_NULL, 512, COM_THREAD_PRIORITY, 10);
	RT_ASSERT(tid != RT_NULL);

	rt_thread_startup(tid);
}

