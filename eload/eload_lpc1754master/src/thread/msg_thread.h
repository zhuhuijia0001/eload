#ifndef _MSG_THREAD_H_
#define _MSG_THREAD_H_

#include "menu_op.h"

int start_menu_session(void);

void refresh_test_content(TEST_CONTENT *test_content);

/* send test result to UI */
void refresh_test_result(TEST_RESULT * synth_test_result);

int wait_for_menu_msg(MSG_ID *pId, void **pMsg);

#endif
