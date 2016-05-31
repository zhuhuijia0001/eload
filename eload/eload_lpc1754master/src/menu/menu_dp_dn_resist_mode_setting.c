#include <stdint.h>
#include "type.h"
#include "key_define.h"

#include "menu_op.h"
#include "menu.h"

#include "lcd.h"
#include "draw.h"

#include "beeper.h"

static void key_handler(void *msg)
{

}

static void init_callback(void *msg)
{

}

static void destroy_callback(void *msg)
{

}

BEGIN_MENU_HANDLER(MENU_ID_USB_DP_DN_RESIST_MODE_SETTING)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()

