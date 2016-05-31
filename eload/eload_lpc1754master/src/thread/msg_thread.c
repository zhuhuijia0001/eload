#include <rtthread.h>
#include <stdint.h>

#include "menu_op.h"
#include "key.h"

#include "parameter.h"
#include "global.h"

#include "msg_thread.h"

typedef struct
{
	MSG_ID msg_id;
	
	void *msg;
} MSG;

#define MSG_QUEUE_LEN   8

#define SAMPLE_INTERVAL    1000ul

static rt_mq_t s_msg_queue = RT_NULL;

static void key_thread_entry(void *parameter)
{
	key_t key;
	
	MSG msg;
	
	RT_ASSERT(s_msg_queue != RT_NULL);
	
	while (RT_TRUE)
	{
		key = key_get();
		
		msg.msg_id = MSG_ID_KEY;
		msg.msg    = (void *)key;
		
		rt_mq_send(s_msg_queue, &msg, sizeof(msg));
	}
}

void refresh_test_content(TEST_CONTENT *test_content)
{
	MSG msg;
	
	msg.msg_id = MSG_ID_REFRESH;
	msg.msg    = test_content;
	
	RT_ASSERT(s_msg_queue != RT_NULL);
	rt_mq_send(s_msg_queue, &msg, sizeof(msg));
}

void refresh_test_result(TEST_RESULT * synth_test_result)
{
	MSG msg;
	
	msg.msg_id = MSG_ID_SYNTH_TEST;
	msg.msg    = synth_test_result;
	
	RT_ASSERT(s_msg_queue != RT_NULL);
	rt_mq_send(s_msg_queue, &msg, sizeof(msg));
}

int start_menu_session(void)
{
	rt_thread_t tid;
	
	s_msg_queue = rt_mq_create("msgqueue", sizeof(MSG), MSG_QUEUE_LEN, RT_IPC_FLAG_FIFO);
	RT_ASSERT(s_msg_queue != RT_NULL);
	
	tid = rt_thread_create("keythread", key_thread_entry, RT_NULL, 512, 11, 10);

	RT_ASSERT(tid != RT_NULL);
	rt_thread_startup(tid);
	
	return 0;
}

int wait_for_menu_msg(MSG_ID *pId, void **pMsg)
{
	MSG msg;
	
	rt_err_t ret;
	
	RT_ASSERT(s_msg_queue != RT_NULL);
	
	/* get message */
	ret = rt_mq_recv(s_msg_queue, &msg, sizeof(msg), RT_WAITING_FOREVER);
	if (ret == RT_EOK)
	{
		if (pId != RT_NULL)
		{
			*pId = msg.msg_id;
		}
		
		if (pMsg != RT_NULL)
		{
			*pMsg = msg.msg;
		}
		
		return 0;
	}
	
	return -1;
}

