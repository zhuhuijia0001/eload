#include "rtthread.h"
#include "stdint.h"
#include "trace.h"

#include "menu_op.h"
#include "menu.h"

/* menu */
typedef struct
{
	MENU_ID  menu_id;
	
	void (*pMsg_handler)(MSG_ID id, void *msg);

#ifdef RT_DEBUG
	const char *strID;
#endif
} MENU;


#ifdef RT_DEBUG
#define DEF_MENU(id)						\
static const MENU s_menu_##id = 			\
{											\
	.menu_id      = id,                     \
	.pMsg_handler = menu_##id##_handler,	\
	.strID        = #id						\
}
#else
#define DEF_MENU(id)						\
static const MENU s_menu_##id = 			\
{											\
	.menu_id      = id,                     \
	.pMsg_handler = menu_##id##_handler     \
}
#endif

#define MENU_ITEM(id)	[##id##] = &s_menu_##id

static const MENU *s_cur_menu = RT_NULL;

/* define menus */
DEF_MENU(MENU_ID_WELCOME);

DEF_MENU(MENU_ID_MAIN);

DEF_MENU(MENU_ID_CV_MODE);
DEF_MENU(MENU_ID_CC_MODE);
DEF_MENU(MENU_ID_CR_MODE);

DEF_MENU(MENU_ID_SYNTH_TEST_SETTING);

DEF_MENU(MENU_ID_CHANNEL_SETTING);

DEF_MENU(MENU_ID_SYNTH_TEST);

DEF_MENU(MENU_ID_EMPTY_LOAD_SETTING);

DEF_MENU(MENU_ID_USB_DP_DN_DIVIDE_MODE_SETTING);
DEF_MENU(MENU_ID_USB_DP_DN_SHORT_MODE_SETTING);
DEF_MENU(MENU_ID_USB_DP_DN_RESIST_MODE_SETTING);

DEF_MENU(MENU_ID_CC_SETTING);
DEF_MENU(MENU_ID_CV_SETTING);
DEF_MENU(MENU_ID_CR_SETTING);

DEF_MENU(MENU_ID_OVER_CURRENT_SETTING);
DEF_MENU(MENU_ID_SHORT_SETTING);
DEF_MENU(MENU_ID_DISCHARGE_SETTING);

DEF_MENU(MENU_ID_FACTORY_MODE);
DEF_MENU(MENU_ID_ADJUST);
DEF_MENU(MENU_ID_PRIVILEGE);
DEF_MENU(MENU_ID_LIFE);
DEF_MENU(MENU_ID_PHONE_SETTING);

static const MENU *const s_menu_arr[MENU_ID_COUNT] = 
{
	MENU_ITEM(MENU_ID_WELCOME),
	
	MENU_ITEM(MENU_ID_MAIN),

	MENU_ITEM(MENU_ID_CV_MODE),
	MENU_ITEM(MENU_ID_CC_MODE),
	MENU_ITEM(MENU_ID_CR_MODE),
	
	MENU_ITEM(MENU_ID_SYNTH_TEST_SETTING),

	MENU_ITEM(MENU_ID_CHANNEL_SETTING),
	
	MENU_ITEM(MENU_ID_SYNTH_TEST),
	
	MENU_ITEM(MENU_ID_EMPTY_LOAD_SETTING),

	MENU_ITEM(MENU_ID_USB_DP_DN_DIVIDE_MODE_SETTING),
	MENU_ITEM(MENU_ID_USB_DP_DN_SHORT_MODE_SETTING),
	MENU_ITEM(MENU_ID_USB_DP_DN_RESIST_MODE_SETTING),
	
	MENU_ITEM(MENU_ID_CC_SETTING),
	MENU_ITEM(MENU_ID_CV_SETTING),
	MENU_ITEM(MENU_ID_CR_SETTING),
	
	MENU_ITEM(MENU_ID_OVER_CURRENT_SETTING),
	MENU_ITEM(MENU_ID_SHORT_SETTING),
	MENU_ITEM(MENU_ID_DISCHARGE_SETTING),
	
	MENU_ITEM(MENU_ID_FACTORY_MODE),
	MENU_ITEM(MENU_ID_ADJUST),
	MENU_ITEM(MENU_ID_PRIVILEGE),
	MENU_ITEM(MENU_ID_LIFE),
	MENU_ITEM(MENU_ID_PHONE_SETTING),
};

void switch_to_menu(MENU_ID id)
{
	const MENU *old_menu = s_cur_menu;
	
	MENU_ID old_id = MENU_ID_NONE;
	
	s_cur_menu = s_menu_arr[id];
	
	TRACE("switch to menu:%s\r\n", s_cur_menu->strID);
	
	if (old_menu != RT_NULL)
	{		
		old_menu->pMsg_handler(MSG_ID_DESTROY, (void *)id);
		
		old_id = old_menu->menu_id;
	}
	
	s_cur_menu->pMsg_handler(MSG_ID_INIT, (void *)old_id);
}

MENU_ID get_cur_menu_id(void)
{
	if (s_cur_menu != RT_NULL)
	{
		return s_cur_menu->menu_id;
	}
	
	return MENU_ID_NONE;
}

void process_cur_menu_msg(MSG_ID id, void *msg)
{
	if (s_cur_menu != RT_NULL)
	{
		s_cur_menu->pMsg_handler(id, msg);
	}
}

void init_menu(void)
{
	switch_to_menu(MENU_ID_WELCOME);
}

