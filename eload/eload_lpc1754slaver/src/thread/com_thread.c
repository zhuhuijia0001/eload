#include <rtthread.h>
#include <stdint.h>

#include "type.h"

#include "packet.h"
#include "app_cfg.h"

#include "com_port.h"

#include "parameter.h"
#include "global.h"

#include "com_thread.h"

#include "trace.h"

static rt_mq_t s_payload_queue = RT_NULL;

/* message queue len */
#define MSG_QUEUE_LEN    4

static void packet_receive_callback(uint8_t *payload, uint16_t payload_size)
{
	RT_ASSERT(s_payload_queue != RT_NULL);
	
	rt_mq_send(s_payload_queue, payload, payload_size);
}

/* ac offset value */
static uint32_t s_ac_offset_value = 0;

static void com_thread_entry(void *parameter)
{
	rt_err_t ret;
	
	uint8_t payload[MAX_RECV_PACKET_SIZE - (sizeof(PACKET) - 1)];
	
	uint8_t packet_buffer[MAX_SEND_PACKET_SIZE];

	uint16_t packet_len;
	
	TEST_CMD  test_cmd;
	
	uint32_t voltage, current, ac;
	
	uint8_t test_type;
	uint8_t test_status;
	
	com_port_set_read_callback(packet_receive_callback);
	
	com_port_init();
	
	while (RT_TRUE)
	{
		/* wait for payload */
		RT_ASSERT(s_payload_queue != RT_NULL);
		ret = rt_mq_recv(s_payload_queue, payload, sizeof(payload), RT_WAITING_FOREVER);
		if (ret == RT_EOK)
		{
			/* do cmd */
			uint8_t cmd = payload[0];
			
			switch (cmd)
			{
			case CMD_CV_MODE:
				{
					PAYLOAD_CMD_CV_MODE *payload_cv_mode = (PAYLOAD_CMD_CV_MODE *)payload;
					
					TRACE("CMD_CV_MODE\n");
				
					packet_len = build_cv_mode_cmd_ret_packet(packet_buffer, sizeof(packet_buffer), RESULT_OK);
					if (packet_len != PACKET_TOO_LONG)
					{
						/* reply */
						com_port_write(packet_buffer, packet_len);
					}
				
					/* notify work thread */
					test_cmd.test_type = TEST_TYPE_CV_MODE;
					test_cmd.test_config.cv_mode_config.voltage_val = payload_cv_mode->voltage_val;
					
					RT_ASSERT(g_test_cmd_queue != RT_NULL);
					rt_mq_send(g_test_cmd_queue, &test_cmd, sizeof(test_cmd));
				}
				
				break;
			
			case CMD_CC_MODE:
				{
					PAYLOAD_CMD_CC_MODE *payload_cc_mode = (PAYLOAD_CMD_CC_MODE *)payload;
					
					TRACE("CMD_CC_MODE\n");
				
					packet_len = build_cc_mode_cmd_ret_packet(packet_buffer, sizeof(packet_buffer), RESULT_OK);
					if (packet_len != PACKET_TOO_LONG)
					{
						/* reply */
						com_port_write(packet_buffer, packet_len);
					}

					/* notify work thread */
					test_cmd.test_type = TEST_TYPE_CC_MODE;
					test_cmd.test_config.cc_mode_config.current_val = payload_cc_mode->current_val;
					
					RT_ASSERT(g_test_cmd_queue != RT_NULL);
					rt_mq_send(g_test_cmd_queue, &test_cmd, sizeof(test_cmd));					
				}
				
				break;
			
			case CMD_CR_MODE:
				{
					PAYLOAD_CMD_CR_MODE *payload_cr_mode = (PAYLOAD_CMD_CR_MODE *)payload;
					
					TRACE("CMD_CR_MODE\n");
				
					packet_len = build_cr_mode_cmd_ret_packet(packet_buffer, sizeof(packet_buffer), RESULT_OK);
					if (packet_len != PACKET_TOO_LONG)
					{
						/* reply */
						com_port_write(packet_buffer, packet_len);
					}
				
					/* notify work thread */
					test_cmd.test_type = TEST_TYPE_CR_MODE;
					test_cmd.test_config.cr_mode_config.resist_val = payload_cr_mode->resist_val;
					
					RT_ASSERT(g_test_cmd_queue != RT_NULL);
					rt_mq_send(g_test_cmd_queue, &test_cmd, sizeof(test_cmd));	
				}
				
				break;

			case CMD_CV_TEST:
				{
					PAYLOAD_CMD_CV_TEST *payload_cv_test = (PAYLOAD_CMD_CV_TEST *)payload;

					TRACE("CMD_CV_TEST\n");

					packet_len = build_cv_test_cmd_ret_packet(packet_buffer, sizeof(packet_buffer), RESULT_OK);
					if (packet_len != PACKET_TOO_LONG)
					{
						/* reply */
						com_port_write(packet_buffer, packet_len);
					}

					/* notify work thread */
					test_cmd.test_type = TEST_TYPE_CV_TEST;

					test_cmd.test_config.cv_test_config.test_category = payload_cv_test->test_category;
					test_cmd.test_config.cv_test_config.voltage_level = payload_cv_test->voltage_level;
					test_cmd.test_config.cv_test_config.voltage_val = payload_cv_test->voltage_val;
					test_cmd.test_config.cv_test_config.duration = payload_cv_test->duration;
					test_cmd.test_config.cv_test_config.ac_upper = payload_cv_test->ac_upper;
					test_cmd.test_config.cv_test_config.current_lower = payload_cv_test->current_lower;
					test_cmd.test_config.cv_test_config.current_upper = payload_cv_test->current_upper;


					RT_ASSERT(g_test_cmd_queue != RT_NULL);
					rt_mq_send(g_test_cmd_queue, &test_cmd, sizeof(test_cmd));	
				}

				break;

			case CMD_CC_TEST:
				{
					PAYLOAD_CMD_CC_TEST *payload_cc_test = (PAYLOAD_CMD_CC_TEST *)payload;

					TRACE("CMD_CC_TEST\n");

					packet_len = build_cc_test_cmd_ret_packet(packet_buffer, sizeof(packet_buffer), RESULT_OK);
					if (packet_len != PACKET_TOO_LONG)
					{
						/* reply */
						com_port_write(packet_buffer, packet_len);
					}

					/* notify work thread */
					test_cmd.test_type = TEST_TYPE_CC_TEST;

					test_cmd.test_config.cc_test_config.test_category = payload_cc_test->test_category;
					test_cmd.test_config.cc_test_config.voltage_level = payload_cc_test->voltage_level;
					test_cmd.test_config.cc_test_config.current_val = payload_cc_test->current_val;
					test_cmd.test_config.cc_test_config.duration = payload_cc_test->duration;
					test_cmd.test_config.cc_test_config.ac_upper = payload_cc_test->ac_upper;
					test_cmd.test_config.cc_test_config.voltage_lower = payload_cc_test->voltage_lower;
					test_cmd.test_config.cc_test_config.voltage_upper = payload_cc_test->voltage_upper;


					RT_ASSERT(g_test_cmd_queue != RT_NULL);
					rt_mq_send(g_test_cmd_queue, &test_cmd, sizeof(test_cmd));	
				}

				break;

			case CMD_CR_TEST:
				{
					PAYLOAD_CMD_CR_TEST *payload_cr_test = (PAYLOAD_CMD_CR_TEST *)payload;

					TRACE("CMD_CR_TEST\n");

					packet_len = build_cr_test_cmd_ret_packet(packet_buffer, sizeof(packet_buffer), RESULT_OK);
					if (packet_len != PACKET_TOO_LONG)
					{
						/* reply */
						com_port_write(packet_buffer, packet_len);
					}

					/* notify work thread */
					test_cmd.test_type = TEST_TYPE_CR_TEST;

					test_cmd.test_config.cr_test_config.test_category = payload_cr_test->test_category;
					test_cmd.test_config.cr_test_config.voltage_level = payload_cr_test->voltage_level;
					test_cmd.test_config.cr_test_config.resist_val = payload_cr_test->resist_val;
					test_cmd.test_config.cr_test_config.duration = payload_cr_test->duration;
					test_cmd.test_config.cr_test_config.ac_upper = payload_cr_test->ac_upper;
					test_cmd.test_config.cr_test_config.voltage_lower = payload_cr_test->voltage_lower;
					test_cmd.test_config.cr_test_config.voltage_upper = payload_cr_test->voltage_upper;
					test_cmd.test_config.cr_test_config.current_lower = payload_cr_test->current_lower;
					test_cmd.test_config.cr_test_config.current_upper = payload_cr_test->current_upper;


					RT_ASSERT(g_test_cmd_queue != RT_NULL);
					rt_mq_send(g_test_cmd_queue, &test_cmd, sizeof(test_cmd));	
				}

				break;

			case CMD_EMPTY_LOAD_TEST:
				{
					PAYLOAD_CMD_EMPTY_LOAD_TEST *payload_empty_load_test = (PAYLOAD_CMD_EMPTY_LOAD_TEST *)payload;

					TRACE("CMD_EMPTY_LOAD_TEST\n");

					packet_len = build_empty_load_test_cmd_ret_packet(packet_buffer, sizeof(packet_buffer), RESULT_OK);
					if (packet_len != PACKET_TOO_LONG)
					{
						/* reply */
						com_port_write(packet_buffer, packet_len);
					}

					/* notify work thread */
					test_cmd.test_type = TEST_TYPE_EMPTY_LOAD_TEST;
					
					test_cmd.test_config.empty_load_test_config.duration = payload_empty_load_test->duration;
					test_cmd.test_config.empty_load_test_config.ac_upper = payload_empty_load_test->ac_upper;
					test_cmd.test_config.empty_load_test_config.voltage_lower = payload_empty_load_test->voltage_lower;
					test_cmd.test_config.empty_load_test_config.voltage_upper = payload_empty_load_test->voltage_upper;


					RT_ASSERT(g_test_cmd_queue != RT_NULL);
					rt_mq_send(g_test_cmd_queue, &test_cmd, sizeof(test_cmd));	
				}

				break;

			case CMD_OVER_CURRENT_TEST:
				{
					PAYLOAD_CMD_OVER_CURRENT_TEST *payload_over_current_test = (PAYLOAD_CMD_OVER_CURRENT_TEST *)payload;

					TRACE("CMD_OVER_CURRENT_TEST\n");

					packet_len = build_over_current_test_cmd_ret_packet(packet_buffer, sizeof(packet_buffer), RESULT_OK);
					if (packet_len != PACKET_TOO_LONG)
					{
						/* reply */
						com_port_write(packet_buffer, packet_len);
					}

					/* notify work thread */
					test_cmd.test_type = TEST_TYPE_OVER_CURRENT_TEST;

					test_cmd.test_config.over_current_test_config.test_category = payload_over_current_test->test_category;
					test_cmd.test_config.over_current_test_config.voltage_level = payload_over_current_test->voltage_level;
					test_cmd.test_config.over_current_test_config.interval = payload_over_current_test->interval;
					test_cmd.test_config.over_current_test_config.ac_upper = payload_over_current_test->ac_upper;
					test_cmd.test_config.over_current_test_config.current_upper = payload_over_current_test->current_upper;

					RT_ASSERT(g_test_cmd_queue != RT_NULL);
					rt_mq_send(g_test_cmd_queue, &test_cmd, sizeof(test_cmd));	
				}

				break;

			case CMD_SHORT_TEST:
				{
					PAYLOAD_CMD_SHORT_TEST *payload_short_test = (PAYLOAD_CMD_SHORT_TEST *)payload;

					TRACE("CMD_SHORT_TEST\n");

					packet_len = build_short_test_cmd_ret_packet(packet_buffer, sizeof(packet_buffer), RESULT_OK);
					if (packet_len != PACKET_TOO_LONG)
					{
						/* reply */
						com_port_write(packet_buffer, packet_len);
					}

					/* notify work thread */
					test_cmd.test_type = TEST_TYPE_SHORT_TEST;

					test_cmd.test_config.short_test_config.test_category = payload_short_test->test_category;
					test_cmd.test_config.short_test_config.voltage_level = payload_short_test->voltage_level;
					test_cmd.test_config.short_test_config.duration = payload_short_test->duration;
					test_cmd.test_config.short_test_config.ac_upper = payload_short_test->ac_upper;
					test_cmd.test_config.short_test_config.current_upper = payload_short_test->current_upper;

					RT_ASSERT(g_test_cmd_queue != RT_NULL);
					rt_mq_send(g_test_cmd_queue, &test_cmd, sizeof(test_cmd));	
				}

				break;

			case CMD_DISCHARGE_TEST:
				{
					PAYLOAD_CMD_DISCHARGE_TEST *payload_discharge_test = (PAYLOAD_CMD_DISCHARGE_TEST *)payload;

					TRACE("CMD_DISCHARGE_TEST\n");

					packet_len = build_discharge_test_cmd_ret_packet(packet_buffer, sizeof(packet_buffer), RESULT_OK);
					if (packet_len != PACKET_TOO_LONG)
					{
						/* reply */
						com_port_write(packet_buffer, packet_len);
					}

					/* notify work thread */
					test_cmd.test_type = TEST_TYPE_DISCHARGE_TEST;
					
					test_cmd.test_config.discharge_test_config.duration = payload_discharge_test->duration;
					test_cmd.test_config.discharge_test_config.current_val = payload_discharge_test->current_val;

					RT_ASSERT(g_test_cmd_queue != RT_NULL);
					rt_mq_send(g_test_cmd_queue, &test_cmd, sizeof(test_cmd));	
				}

				break;
				
			case CMD_STOP:
				{
					TRACE("CMD_STOP\n");
				
					packet_len = build_stop_cmd_ret_packet(packet_buffer, sizeof(packet_buffer), RESULT_OK);
					if (packet_len != PACKET_TOO_LONG)
					{
						/* reply */
						com_port_write(packet_buffer, packet_len);
					}
				
					/* notify work thread */
					test_cmd.test_type     = TEST_TYPE_NONE;
					
					RT_ASSERT(g_test_cmd_queue != RT_NULL);
					rt_mq_send(g_test_cmd_queue, &test_cmd, sizeof(test_cmd));
				}
				
				break;
				
			case CMD_POLL:
				/* get value */
				RT_ASSERT(g_sem_test_content != RT_NULL);
				rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);

				if (g_test_content.test_type == TEST_TYPE_OVER_CURRENT_TEST
					&& g_test_content.test_status == TEST_STATUS_NORMAL)
				{
					current = g_over_current_test_result.over_current_test_current;

					voltage = g_over_current_test_result.over_current_test_voltage;

					if (g_over_current_test_result.over_current_test_ac > s_ac_offset_value)
					{
						ac = g_over_current_test_result.over_current_test_ac - s_ac_offset_value;
					}
					else
					{
						ac = 0;
					}
				}
				else
				{
					current = g_test_content.current;

					voltage = g_test_content.voltage;

					if (g_test_content.ac_current > s_ac_offset_value)
					{
						ac = g_test_content.ac_current - s_ac_offset_value;
					}
					else
					{
						ac = 0;
					}
				}
				
				test_type   = g_test_content.test_type;
				test_status = g_test_content.test_status;
				rt_sem_release(g_sem_test_content);
				
				packet_len = build_poll_cmd_ret_packet(packet_buffer, sizeof(packet_buffer), test_type, test_status, ac, voltage, current);
				if (packet_len != PACKET_TOO_LONG)
				{
					/* reply */
					com_port_write(packet_buffer, packet_len);
				}
				
				break;

			case CMD_SET_ADJUST_VALUE:
				{
					PAYLOAD_CMD_SET_ADJUST_VALUE *payload_set_adjust_value = (PAYLOAD_CMD_SET_ADJUST_VALUE *)payload;

					ADJUST_PARAMETER.measure_voltage = payload_set_adjust_value->measure_voltage;
					ADJUST_PARAMETER.actual_voltage  = payload_set_adjust_value->actual_voltage;
					ADJUST_PARAMETER.measure_current = payload_set_adjust_value->measure_current;
					ADJUST_PARAMETER.actual_current  = payload_set_adjust_value->actual_current;
					
					save_parameter();
				}
				
				break;

			case CMD_GET_ADJUST_VALUE:
				TRACE("get adjust\n");
				packet_len = build_get_adjust_value_cmd_ret_packet(packet_buffer, sizeof(packet_buffer), ADJUST_PARAMETER.measure_voltage, ADJUST_PARAMETER.actual_voltage, 
																		ADJUST_PARAMETER.measure_current, ADJUST_PARAMETER.actual_current);
				if (packet_len != PACKET_TOO_LONG)
				{
					/* reply */
					com_port_write(packet_buffer, packet_len);

					TRACE("get adjust value ret:measure voltage:%d,actual voltage:%d,measure current:%d,actual current:%d\n", 
							ADJUST_PARAMETER.measure_voltage, ADJUST_PARAMETER.actual_voltage, ADJUST_PARAMETER.measure_current, ADJUST_PARAMETER.actual_current);
				}

				RT_ASSERT(g_sem_test_content != RT_NULL);
				
				rt_sem_take(g_sem_test_content, RT_WAITING_FOREVER);
				s_ac_offset_value = g_test_content.ac_current;
				rt_sem_release(g_sem_test_content);

				/* notify work thread */
				test_cmd.test_type     = TEST_TYPE_NONE;
					
				RT_ASSERT(g_test_cmd_queue != RT_NULL);
				rt_mq_send(g_test_cmd_queue, &test_cmd, sizeof(test_cmd));
				
				break;
				
			default:
				
				break;
			}
		}
	}
}

void start_com_thread(void)
{
	rt_thread_t tid;

	s_payload_queue = rt_mq_create("comqueue", MAX_RECV_PACKET_SIZE - (sizeof(PACKET) - 1), MSG_QUEUE_LEN, RT_IPC_FLAG_FIFO);
	RT_ASSERT(s_payload_queue != RT_NULL);
	
	tid = rt_thread_create("com", com_thread_entry, RT_NULL, 512, COM_THREAD_PRIORITY, 10);

	RT_ASSERT(tid != RT_NULL);
	rt_thread_startup(tid);
}

