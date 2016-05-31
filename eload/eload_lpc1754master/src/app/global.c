
#include <rtthread.h>
#include <stdint.h>
#include "type.h"

#include "protocol.h"
#include "parameter.h"
#include "global.h"

CHANNEL_STATUS  g_channel_status[CHANNEL_COUNT];

ADJUST_VALUE g_channel_adjust_value[CHANNEL_COUNT];

#define  CMD_QUEUE_LEN     8

static rt_mq_t   s_test_cmd_queue = RT_NULL;

/* test content msg queue */
#define TEST_CONTENT_MSG_SIZE         8

static rt_mq_t s_test_content_queue = RT_NULL;

void global_variable_init(void)
{
	int i;

	for (i = 0; i < CHANNEL_COUNT; i++)
	{
		g_channel_status[i] = CHANNEL_OFFLINE;

		g_channel_adjust_value[i].measure_voltage = 1;
		g_channel_adjust_value[i].actual_voltage  = 1;
		g_channel_adjust_value[i].measure_current = 1;
		g_channel_adjust_value[i].actual_current  = 1;
	}
	
	s_test_cmd_queue = rt_mq_create("cmdqueue", sizeof(TEST_CMD), CMD_QUEUE_LEN, RT_IPC_FLAG_FIFO);
	RT_ASSERT(s_test_cmd_queue != RT_NULL);

	s_test_content_queue = rt_mq_create("content", sizeof(TEST_CONTENT), TEST_CONTENT_MSG_SIZE, RT_IPC_FLAG_FIFO);
	RT_ASSERT(s_test_content_queue != RT_NULL);
}

void test_cmd_notify(TEST_CMD *test_cmd)
{
	RT_ASSERT(s_test_cmd_queue != RT_NULL);
	rt_mq_send(s_test_cmd_queue, test_cmd, sizeof(TEST_CMD));	
}

int test_cmd_query(TEST_CMD *test_cmd, int timeout)
{
	int ret;
	
	RT_ASSERT(s_test_cmd_queue != RT_NULL);
	ret = rt_mq_recv(s_test_cmd_queue, test_cmd, sizeof(TEST_CMD), timeout);
	
	return ret;
}

void test_content_notify(TEST_CONTENT *test_content)
{
	RT_ASSERT(s_test_content_queue != RT_NULL);
	rt_mq_send(s_test_content_queue, test_content, sizeof(TEST_CONTENT));	
}

int test_content_query(TEST_CONTENT *test_content, int timeout)
{
	int ret;
	
	RT_ASSERT(s_test_content_queue != RT_NULL);
	ret = rt_mq_recv(s_test_content_queue, test_content, sizeof(TEST_CONTENT), timeout);
	
	return ret;
}

uint32_t measure_to_actual_voltage(int port, uint32_t measure_voltage)
{
	uint32_t actual_voltage = measure_voltage * g_channel_adjust_value[port].actual_voltage / g_channel_adjust_value[port].measure_voltage;

	return actual_voltage;
}

uint32_t actual_to_measure_voltage(int port, uint32_t actual_voltage)
{
	uint32_t measure_voltage = actual_voltage * g_channel_adjust_value[port].measure_voltage / g_channel_adjust_value[port].actual_voltage;

	return measure_voltage;
}

uint32_t measure_to_actual_current(int port, uint32_t measure_current)
{
	uint32_t actual_current = measure_current * g_channel_adjust_value[port].actual_current / g_channel_adjust_value[port].measure_current;

	return actual_current;
}

uint32_t actual_to_measure_current(int port, uint32_t actual_current)
{
	uint32_t measure_current = actual_current * g_channel_adjust_value[port].measure_current / g_channel_adjust_value[port].actual_current;

	return measure_current;
}
