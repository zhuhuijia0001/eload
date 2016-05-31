#include <rtthread.h>
#include <stdint.h>

#include "protocol.h"

#include "global.h"

TEST_CONTENT  g_test_content;

OVER_CURRENT_TEST_RESULT g_over_current_test_result;

rt_sem_t  g_sem_test_content = RT_NULL;

#define  CMD_QUEUE_LEN     4

rt_mq_t   g_test_cmd_queue = RT_NULL;

void global_variable_init(void)
{
	g_test_content.test_type = TEST_TYPE_NONE;
	g_test_content.test_status = TEST_STATUS_IDLE;
	g_test_content.ac_current = 0;
	g_test_content.voltage    = 0;
	g_test_content.current    = 0;

	g_over_current_test_result.over_current_test_current = 0;
	g_over_current_test_result.over_current_test_voltage = 0;
	g_over_current_test_result.over_current_test_ac = 0;
	
	g_sem_test_content = rt_sem_create("content", 1, RT_IPC_FLAG_FIFO);
	RT_ASSERT(g_sem_test_content != RT_NULL);
	
	g_test_cmd_queue = rt_mq_create("cmdqueue", sizeof(TEST_CMD), CMD_QUEUE_LEN, RT_IPC_FLAG_FIFO);
	RT_ASSERT(g_test_cmd_queue != RT_NULL);
}

