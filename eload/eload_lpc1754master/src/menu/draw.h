#ifndef _DRAW_H_
#define _DRAW_H_

#include "parameter.h"

#include "global.h"

/* color config */
#define SCREEN_BACK_COLOR   COLOR_BLACK

#define RDONLY_FORE_COLOR   COLOR_YELLOW

#define EDITABLE_FORE_COLOR COLOR_WHITE

#define FOCUS_BACK_COLOR    COLOR_MAGENTA

#define EDIT_BACK_COLOR     COLOR_BLUE

#define HIGHLIGHT_COLOR     COLOR_RED

#define CAPTION_COLOR       COLOR_CYAN


/* welcome */
#define WELCOME_PIC_LEFT    285
#define WELCOME_PIC_TOP     50

#define WELCOME_STR_LEFT    100
#define WELCOME_STR_TOP     350

extern void draw_welcome_menu(void);

/* main menu */
#define MAIN_MENU_ITEM_LEFT        250

#define MAIN_MENU_ITEM_TOP_SYNTH   50
#define MAIN_MENU_ITEM_TOP_CV      130
#define MAIN_MENU_ITEM_TOP_CC      210
#define MAIN_MENU_ITEM_TOP_CR      290
#define MAIN_MENU_ITEM_TOP_CHANNEL 370

extern void draw_main_items(void);
extern void draw_normal_main_item_cv_mode(void);
extern void draw_focus_main_item_cv_mode(void);
extern void draw_normal_main_item_cc_mode(void);
extern void draw_focus_main_item_cc_mode(void);
extern void draw_normal_main_item_cr_mode(void);
extern void draw_focus_main_item_cr_mode(void);
extern void draw_normal_main_item_synth_test(void);
extern void draw_focus_main_item_synth_test(void);
extern void draw_normal_main_item_channel_set(void);
extern void draw_focus_main_item_channel_set(void);


#define SYNTH_TEST_SETTING_CAPTION_LEFT     150
#define SYNTH_TEST_SETTING_CAPTION_TOP      10

#define SYNTH_TEST_SETTING_GROUP_LEFT    500
#define SYNTH_TEST_SETTING_GROUP_TOP     10

#define SYNTH_TEST_CAPTION_LEFT     (SYNTH_TEST_SETTING_CAPTION_LEFT - 120)
#define SYNTH_TEST_CAPTION_TOP      SYNTH_TEST_SETTING_CAPTION_TOP

#define SYNTH_TEST_GROUP_LEFT    (SYNTH_TEST_SETTING_GROUP_LEFT - 120)
#define SYNTH_TEST_GROUP_TOP     SYNTH_TEST_SETTING_GROUP_TOP

#define SYNTH_TEST_LEFT         700
#define SYNTH_TEST_TOP          25

#define SYNTH_TEST_BIND_LEFT        3
#define SYNTH_TEST_BIND_TOP         77
#define SYNTH_TEST_BIND_RIGHT       851
#define SYNTH_TEST_BIND_BOTTOM      477

#define SYNTH_TEST_BIND_HORZ_1_TOP  172
#define SYNTH_TEST_BIND_HORZ_2_TOP  272
#define SYNTH_TEST_BIND_HORZ_3_TOP  372

#define SYNTH_TEST_BIND_VERT_LEFT   420     

#define SYNTH_TEST_ITEM_STEP_LEFT_1    10
#define SYNTH_TEST_ITEM_TYPE_LEFT_1    200
#define SYNTH_TEST_ITEM_RESULT_LEFT_1  350
#define SYNTH_TEST_ITEM_ON_OFF_LEFT_1  10
#define SYNTH_TEST_ITEM_SETTING_LEFT_1 200

#define SYNTH_TEST_ITEM_STEP_LEFT_2    430
#define SYNTH_TEST_ITEM_TYPE_LEFT_2    620
#define SYNTH_TEST_ITEM_RESULT_LEFT_2  770
#define SYNTH_TEST_ITEM_ON_OFF_LEFT_2  430
#define SYNTH_TEST_ITEM_SETTING_LEFT_2 620

#define SYNTH_TEST_ITEM_1_STEP_LEFT    SYNTH_TEST_ITEM_STEP_LEFT_1
#define SYNTH_TEST_ITEM_1_STEP_TOP     80
#define SYNTH_TEST_ITEM_1_TYPE_LEFT    SYNTH_TEST_ITEM_TYPE_LEFT_1
#define SYNTH_TEST_ITEM_1_TYPE_TOP     80
#define SYNTH_TEST_ITEM_1_RESULT_LEFT  SYNTH_TEST_ITEM_RESULT_LEFT_1
#define SYNTH_TEST_ITEM_1_RESULT_TOP   80
#define SYNTH_TEST_ITEM_1_ON_OFF_LEFT  SYNTH_TEST_ITEM_ON_OFF_LEFT_1
#define SYNTH_TEST_ITEM_1_ON_OFF_TOP   130
#define SYNTH_TEST_ITEM_1_SETTING_LEFT SYNTH_TEST_ITEM_SETTING_LEFT_1
#define SYNTH_TEST_ITEM_1_SETTING_TOP  130

#define SYNTH_TEST_ITEM_1_AC_LEFT      SYNTH_TEST_ITEM_1_STEP_LEFT
#define SYNTH_TEST_ITEM_1_AC_COLON_LEFT  140
#define SYNTH_TEST_ITEM_1_AC_VAL_LEFT  150
#define SYNTH_TEST_ITEM_1_AC_UNIT_LEFT 195
#define SYNTH_TEST_ITEM_1_AC_TOP       (SYNTH_TEST_ITEM_1_STEP_TOP + 33)  

#define SYNTH_TEST_ITEM_1_VOLTAGE_LEFT     SYNTH_TEST_ITEM_1_STEP_LEFT
#define SYNTH_TEST_ITEM_1_VOLTAGE_COLON_LEFT  75
#define SYNTH_TEST_ITEM_1_VOLTAGE_VAL_LEFT  130
#define SYNTH_TEST_ITEM_1_VOLTAGE_UNIT_LEFT 195
#define SYNTH_TEST_ITEM_1_VOLTAGE_TOP       (SYNTH_TEST_ITEM_1_AC_TOP + 33) 

#define SYNTH_TEST_ITEM_1_CURRENT_LEFT     (SYNTH_TEST_ITEM_1_VOLTAGE_LEFT + 210)
#define SYNTH_TEST_ITEM_1_CURRENT_COLON_LEFT  (SYNTH_TEST_ITEM_1_VOLTAGE_COLON_LEFT + 210)
#define SYNTH_TEST_ITEM_1_CURRENT_VAL_LEFT  (SYNTH_TEST_ITEM_1_VOLTAGE_VAL_LEFT + 210)
#define SYNTH_TEST_ITEM_1_CURRENT_UNIT_LEFT (SYNTH_TEST_ITEM_1_VOLTAGE_UNIT_LEFT + 210)
#define SYNTH_TEST_ITEM_1_CURRENT_TOP       SYNTH_TEST_ITEM_1_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_1_OC_LEFT        SYNTH_TEST_ITEM_1_VOLTAGE_LEFT
#define SYNTH_TEST_ITEM_1_OC_COLON_LEFT  SYNTH_TEST_ITEM_1_VOLTAGE_COLON_LEFT
#define SYNTH_TEST_ITEM_1_OC_VAL_LEFT    SYNTH_TEST_ITEM_1_VOLTAGE_VAL_LEFT
#define SYNTH_TEST_ITEM_1_OC_UNIT_LEFT   SYNTH_TEST_ITEM_1_VOLTAGE_UNIT_LEFT
#define SYNTH_TEST_ITEM_1_OC_TOP         SYNTH_TEST_ITEM_1_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_1_SHORT_LEFT        SYNTH_TEST_ITEM_1_VOLTAGE_LEFT
#define SYNTH_TEST_ITEM_1_SHORT_COLON_LEFT  SYNTH_TEST_ITEM_1_VOLTAGE_COLON_LEFT
#define SYNTH_TEST_ITEM_1_SHORT_VAL_LEFT    SYNTH_TEST_ITEM_1_VOLTAGE_VAL_LEFT
#define SYNTH_TEST_ITEM_1_SHORT_UNIT_LEFT   SYNTH_TEST_ITEM_1_VOLTAGE_UNIT_LEFT
#define SYNTH_TEST_ITEM_1_SHORT_TOP         SYNTH_TEST_ITEM_1_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_2_STEP_LEFT    SYNTH_TEST_ITEM_STEP_LEFT_1
#define SYNTH_TEST_ITEM_2_STEP_TOP     180
#define SYNTH_TEST_ITEM_2_TYPE_LEFT    SYNTH_TEST_ITEM_TYPE_LEFT_1
#define SYNTH_TEST_ITEM_2_TYPE_TOP     180
#define SYNTH_TEST_ITEM_2_RESULT_LEFT  SYNTH_TEST_ITEM_RESULT_LEFT_1
#define SYNTH_TEST_ITEM_2_RESULT_TOP   180
#define SYNTH_TEST_ITEM_2_ON_OFF_LEFT  SYNTH_TEST_ITEM_ON_OFF_LEFT_1
#define SYNTH_TEST_ITEM_2_ON_OFF_TOP   230
#define SYNTH_TEST_ITEM_2_SETTING_LEFT SYNTH_TEST_ITEM_SETTING_LEFT_1
#define SYNTH_TEST_ITEM_2_SETTING_TOP  230

#define SYNTH_TEST_ITEM_2_AC_LEFT      SYNTH_TEST_ITEM_2_STEP_LEFT
#define SYNTH_TEST_ITEM_2_AC_COLON_LEFT  140
#define SYNTH_TEST_ITEM_2_AC_VAL_LEFT  150
#define SYNTH_TEST_ITEM_2_AC_UNIT_LEFT 195
#define SYNTH_TEST_ITEM_2_AC_TOP       (SYNTH_TEST_ITEM_2_STEP_TOP + 33)  

#define SYNTH_TEST_ITEM_2_VOLTAGE_LEFT     SYNTH_TEST_ITEM_2_STEP_LEFT
#define SYNTH_TEST_ITEM_2_VOLTAGE_COLON_LEFT  75
#define SYNTH_TEST_ITEM_2_VOLTAGE_VAL_LEFT  130
#define SYNTH_TEST_ITEM_2_VOLTAGE_UNIT_LEFT 195
#define SYNTH_TEST_ITEM_2_VOLTAGE_TOP       (SYNTH_TEST_ITEM_2_AC_TOP + 33) 

#define SYNTH_TEST_ITEM_2_CURRENT_LEFT     (SYNTH_TEST_ITEM_2_VOLTAGE_LEFT + 210)
#define SYNTH_TEST_ITEM_2_CURRENT_COLON_LEFT  (SYNTH_TEST_ITEM_2_VOLTAGE_COLON_LEFT + 210)
#define SYNTH_TEST_ITEM_2_CURRENT_VAL_LEFT  (SYNTH_TEST_ITEM_2_VOLTAGE_VAL_LEFT + 210)
#define SYNTH_TEST_ITEM_2_CURRENT_UNIT_LEFT (SYNTH_TEST_ITEM_2_VOLTAGE_UNIT_LEFT + 210)
#define SYNTH_TEST_ITEM_2_CURRENT_TOP       SYNTH_TEST_ITEM_2_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_2_OC_LEFT        SYNTH_TEST_ITEM_2_VOLTAGE_LEFT
#define SYNTH_TEST_ITEM_2_OC_COLON_LEFT  (SYNTH_TEST_ITEM_2_VOLTAGE_COLON_LEFT + 32)
#define SYNTH_TEST_ITEM_2_OC_VAL_LEFT    (SYNTH_TEST_ITEM_2_VOLTAGE_VAL_LEFT + 32)
#define SYNTH_TEST_ITEM_2_OC_UNIT_LEFT   (SYNTH_TEST_ITEM_2_VOLTAGE_UNIT_LEFT + 32)
#define SYNTH_TEST_ITEM_2_OC_TOP         SYNTH_TEST_ITEM_2_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_2_SHORT_LEFT        SYNTH_TEST_ITEM_2_VOLTAGE_LEFT
#define SYNTH_TEST_ITEM_2_SHORT_COLON_LEFT  (SYNTH_TEST_ITEM_2_VOLTAGE_LEFT + 130)
#define SYNTH_TEST_ITEM_2_SHORT_VAL_LEFT    (SYNTH_TEST_ITEM_2_VOLTAGE_LEFT + 190)
#define SYNTH_TEST_ITEM_2_SHORT_UNIT_LEFT   (SYNTH_TEST_ITEM_2_VOLTAGE_LEFT + 240)
#define SYNTH_TEST_ITEM_2_SHORT_TOP         SYNTH_TEST_ITEM_2_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_3_STEP_LEFT    SYNTH_TEST_ITEM_STEP_LEFT_1
#define SYNTH_TEST_ITEM_3_STEP_TOP     280
#define SYNTH_TEST_ITEM_3_TYPE_LEFT    SYNTH_TEST_ITEM_TYPE_LEFT_1
#define SYNTH_TEST_ITEM_3_TYPE_TOP     280
#define SYNTH_TEST_ITEM_3_RESULT_LEFT  SYNTH_TEST_ITEM_RESULT_LEFT_1
#define SYNTH_TEST_ITEM_3_RESULT_TOP   280
#define SYNTH_TEST_ITEM_3_ON_OFF_LEFT  SYNTH_TEST_ITEM_ON_OFF_LEFT_1
#define SYNTH_TEST_ITEM_3_ON_OFF_TOP   330
#define SYNTH_TEST_ITEM_3_SETTING_LEFT SYNTH_TEST_ITEM_SETTING_LEFT_1
#define SYNTH_TEST_ITEM_3_SETTING_TOP  330

#define SYNTH_TEST_ITEM_3_AC_LEFT      SYNTH_TEST_ITEM_3_STEP_LEFT
#define SYNTH_TEST_ITEM_3_AC_COLON_LEFT  140
#define SYNTH_TEST_ITEM_3_AC_VAL_LEFT  150
#define SYNTH_TEST_ITEM_3_AC_UNIT_LEFT 195
#define SYNTH_TEST_ITEM_3_AC_TOP       (SYNTH_TEST_ITEM_3_STEP_TOP + 33)  

#define SYNTH_TEST_ITEM_3_VOLTAGE_LEFT     SYNTH_TEST_ITEM_3_STEP_LEFT
#define SYNTH_TEST_ITEM_3_VOLTAGE_COLON_LEFT  75
#define SYNTH_TEST_ITEM_3_VOLTAGE_VAL_LEFT  130
#define SYNTH_TEST_ITEM_3_VOLTAGE_UNIT_LEFT 195
#define SYNTH_TEST_ITEM_3_VOLTAGE_TOP       (SYNTH_TEST_ITEM_3_AC_TOP + 33) 

#define SYNTH_TEST_ITEM_3_CURRENT_LEFT     (SYNTH_TEST_ITEM_3_VOLTAGE_LEFT + 210)
#define SYNTH_TEST_ITEM_3_CURRENT_COLON_LEFT  (SYNTH_TEST_ITEM_3_VOLTAGE_COLON_LEFT + 210)
#define SYNTH_TEST_ITEM_3_CURRENT_VAL_LEFT  (SYNTH_TEST_ITEM_3_VOLTAGE_VAL_LEFT + 210)
#define SYNTH_TEST_ITEM_3_CURRENT_UNIT_LEFT (SYNTH_TEST_ITEM_3_VOLTAGE_UNIT_LEFT + 210)
#define SYNTH_TEST_ITEM_3_CURRENT_TOP       SYNTH_TEST_ITEM_3_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_3_OC_LEFT        SYNTH_TEST_ITEM_3_VOLTAGE_LEFT
#define SYNTH_TEST_ITEM_3_OC_COLON_LEFT  (SYNTH_TEST_ITEM_3_VOLTAGE_COLON_LEFT + 32)
#define SYNTH_TEST_ITEM_3_OC_VAL_LEFT    (SYNTH_TEST_ITEM_3_VOLTAGE_VAL_LEFT + 32)
#define SYNTH_TEST_ITEM_3_OC_UNIT_LEFT   (SYNTH_TEST_ITEM_3_VOLTAGE_UNIT_LEFT + 32)
#define SYNTH_TEST_ITEM_3_OC_TOP         SYNTH_TEST_ITEM_3_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_3_SHORT_LEFT        SYNTH_TEST_ITEM_3_VOLTAGE_LEFT
#define SYNTH_TEST_ITEM_3_SHORT_COLON_LEFT  (SYNTH_TEST_ITEM_3_VOLTAGE_LEFT + 130)
#define SYNTH_TEST_ITEM_3_SHORT_VAL_LEFT    (SYNTH_TEST_ITEM_3_VOLTAGE_LEFT + 190)
#define SYNTH_TEST_ITEM_3_SHORT_UNIT_LEFT   (SYNTH_TEST_ITEM_3_VOLTAGE_LEFT + 240)
#define SYNTH_TEST_ITEM_3_SHORT_TOP         SYNTH_TEST_ITEM_3_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_4_STEP_LEFT    SYNTH_TEST_ITEM_STEP_LEFT_1
#define SYNTH_TEST_ITEM_4_STEP_TOP     380
#define SYNTH_TEST_ITEM_4_TYPE_LEFT    SYNTH_TEST_ITEM_TYPE_LEFT_1
#define SYNTH_TEST_ITEM_4_TYPE_TOP     380
#define SYNTH_TEST_ITEM_4_RESULT_LEFT  SYNTH_TEST_ITEM_RESULT_LEFT_1
#define SYNTH_TEST_ITEM_4_RESULT_TOP   380
#define SYNTH_TEST_ITEM_4_ON_OFF_LEFT  SYNTH_TEST_ITEM_ON_OFF_LEFT_1
#define SYNTH_TEST_ITEM_4_ON_OFF_TOP   430
#define SYNTH_TEST_ITEM_4_SETTING_LEFT SYNTH_TEST_ITEM_SETTING_LEFT_1
#define SYNTH_TEST_ITEM_4_SETTING_TOP  430

#define SYNTH_TEST_ITEM_4_AC_LEFT      SYNTH_TEST_ITEM_4_STEP_LEFT
#define SYNTH_TEST_ITEM_4_AC_COLON_LEFT  140
#define SYNTH_TEST_ITEM_4_AC_VAL_LEFT  150
#define SYNTH_TEST_ITEM_4_AC_UNIT_LEFT 195
#define SYNTH_TEST_ITEM_4_AC_TOP       (SYNTH_TEST_ITEM_4_STEP_TOP + 33)  

#define SYNTH_TEST_ITEM_4_VOLTAGE_LEFT     SYNTH_TEST_ITEM_4_STEP_LEFT
#define SYNTH_TEST_ITEM_4_VOLTAGE_COLON_LEFT  75
#define SYNTH_TEST_ITEM_4_VOLTAGE_VAL_LEFT  130
#define SYNTH_TEST_ITEM_4_VOLTAGE_UNIT_LEFT 195
#define SYNTH_TEST_ITEM_4_VOLTAGE_TOP       (SYNTH_TEST_ITEM_4_AC_TOP + 33) 

#define SYNTH_TEST_ITEM_4_CURRENT_LEFT     (SYNTH_TEST_ITEM_4_VOLTAGE_LEFT + 210)
#define SYNTH_TEST_ITEM_4_CURRENT_COLON_LEFT  (SYNTH_TEST_ITEM_4_VOLTAGE_COLON_LEFT + 210)
#define SYNTH_TEST_ITEM_4_CURRENT_VAL_LEFT  (SYNTH_TEST_ITEM_4_VOLTAGE_VAL_LEFT + 210)
#define SYNTH_TEST_ITEM_4_CURRENT_UNIT_LEFT (SYNTH_TEST_ITEM_4_VOLTAGE_UNIT_LEFT + 210)
#define SYNTH_TEST_ITEM_4_CURRENT_TOP       SYNTH_TEST_ITEM_4_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_4_OC_LEFT        SYNTH_TEST_ITEM_4_VOLTAGE_LEFT
#define SYNTH_TEST_ITEM_4_OC_COLON_LEFT  (SYNTH_TEST_ITEM_4_VOLTAGE_COLON_LEFT + 32)
#define SYNTH_TEST_ITEM_4_OC_VAL_LEFT    (SYNTH_TEST_ITEM_4_VOLTAGE_VAL_LEFT + 32)
#define SYNTH_TEST_ITEM_4_OC_UNIT_LEFT   (SYNTH_TEST_ITEM_4_VOLTAGE_UNIT_LEFT + 32)
#define SYNTH_TEST_ITEM_4_OC_TOP         SYNTH_TEST_ITEM_4_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_4_SHORT_LEFT        SYNTH_TEST_ITEM_4_VOLTAGE_LEFT
#define SYNTH_TEST_ITEM_4_SHORT_COLON_LEFT  (SYNTH_TEST_ITEM_4_VOLTAGE_LEFT + 130)
#define SYNTH_TEST_ITEM_4_SHORT_VAL_LEFT    (SYNTH_TEST_ITEM_4_VOLTAGE_LEFT + 190)
#define SYNTH_TEST_ITEM_4_SHORT_UNIT_LEFT   (SYNTH_TEST_ITEM_4_VOLTAGE_LEFT + 240)
#define SYNTH_TEST_ITEM_4_SHORT_TOP         SYNTH_TEST_ITEM_4_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_5_STEP_LEFT    SYNTH_TEST_ITEM_STEP_LEFT_2
#define SYNTH_TEST_ITEM_5_STEP_TOP     80
#define SYNTH_TEST_ITEM_5_TYPE_LEFT    SYNTH_TEST_ITEM_TYPE_LEFT_2
#define SYNTH_TEST_ITEM_5_TYPE_TOP     80
#define SYNTH_TEST_ITEM_5_RESULT_LEFT  SYNTH_TEST_ITEM_RESULT_LEFT_2
#define SYNTH_TEST_ITEM_5_RESULT_TOP   80
#define SYNTH_TEST_ITEM_5_ON_OFF_LEFT  SYNTH_TEST_ITEM_ON_OFF_LEFT_2
#define SYNTH_TEST_ITEM_5_ON_OFF_TOP   130
#define SYNTH_TEST_ITEM_5_SETTING_LEFT SYNTH_TEST_ITEM_SETTING_LEFT_2
#define SYNTH_TEST_ITEM_5_SETTING_TOP  130

#define SYNTH_TEST_ITEM_5_AC_LEFT      SYNTH_TEST_ITEM_5_STEP_LEFT
#define SYNTH_TEST_ITEM_5_AC_COLON_LEFT  (SYNTH_TEST_ITEM_5_STEP_LEFT + 130)
#define SYNTH_TEST_ITEM_5_AC_VAL_LEFT  (SYNTH_TEST_ITEM_5_STEP_LEFT + 140)
#define SYNTH_TEST_ITEM_5_AC_UNIT_LEFT (SYNTH_TEST_ITEM_5_STEP_LEFT + 185)
#define SYNTH_TEST_ITEM_5_AC_TOP       (SYNTH_TEST_ITEM_5_STEP_TOP + 33)  

#define SYNTH_TEST_ITEM_5_VOLTAGE_LEFT     SYNTH_TEST_ITEM_5_STEP_LEFT
#define SYNTH_TEST_ITEM_5_VOLTAGE_COLON_LEFT  (SYNTH_TEST_ITEM_5_VOLTAGE_LEFT + 65)
#define SYNTH_TEST_ITEM_5_VOLTAGE_VAL_LEFT  (SYNTH_TEST_ITEM_5_VOLTAGE_LEFT + 120)
#define SYNTH_TEST_ITEM_5_VOLTAGE_UNIT_LEFT (SYNTH_TEST_ITEM_5_VOLTAGE_LEFT + 185)
#define SYNTH_TEST_ITEM_5_VOLTAGE_TOP       (SYNTH_TEST_ITEM_5_AC_TOP + 33) 

#define SYNTH_TEST_ITEM_5_CURRENT_LEFT     (SYNTH_TEST_ITEM_5_VOLTAGE_LEFT + 210)
#define SYNTH_TEST_ITEM_5_CURRENT_COLON_LEFT  (SYNTH_TEST_ITEM_5_VOLTAGE_COLON_LEFT + 210)
#define SYNTH_TEST_ITEM_5_CURRENT_VAL_LEFT  (SYNTH_TEST_ITEM_5_VOLTAGE_VAL_LEFT + 210)
#define SYNTH_TEST_ITEM_5_CURRENT_UNIT_LEFT (SYNTH_TEST_ITEM_5_VOLTAGE_UNIT_LEFT + 210)
#define SYNTH_TEST_ITEM_5_CURRENT_TOP       SYNTH_TEST_ITEM_5_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_5_OC_LEFT        SYNTH_TEST_ITEM_5_VOLTAGE_LEFT
#define SYNTH_TEST_ITEM_5_OC_COLON_LEFT  (SYNTH_TEST_ITEM_5_VOLTAGE_COLON_LEFT + 32)
#define SYNTH_TEST_ITEM_5_OC_VAL_LEFT    (SYNTH_TEST_ITEM_5_VOLTAGE_VAL_LEFT + 32)
#define SYNTH_TEST_ITEM_5_OC_UNIT_LEFT   (SYNTH_TEST_ITEM_5_VOLTAGE_UNIT_LEFT + 32)
#define SYNTH_TEST_ITEM_5_OC_TOP         SYNTH_TEST_ITEM_5_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_5_SHORT_LEFT        SYNTH_TEST_ITEM_5_VOLTAGE_LEFT
#define SYNTH_TEST_ITEM_5_SHORT_COLON_LEFT  (SYNTH_TEST_ITEM_5_VOLTAGE_LEFT + 130)
#define SYNTH_TEST_ITEM_5_SHORT_VAL_LEFT    (SYNTH_TEST_ITEM_5_VOLTAGE_LEFT + 190)
#define SYNTH_TEST_ITEM_5_SHORT_UNIT_LEFT   (SYNTH_TEST_ITEM_5_VOLTAGE_LEFT + 240)
#define SYNTH_TEST_ITEM_5_SHORT_TOP         SYNTH_TEST_ITEM_5_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_6_STEP_LEFT    SYNTH_TEST_ITEM_STEP_LEFT_2
#define SYNTH_TEST_ITEM_6_STEP_TOP     180
#define SYNTH_TEST_ITEM_6_TYPE_LEFT    SYNTH_TEST_ITEM_TYPE_LEFT_2
#define SYNTH_TEST_ITEM_6_TYPE_TOP     180
#define SYNTH_TEST_ITEM_6_RESULT_LEFT  SYNTH_TEST_ITEM_RESULT_LEFT_2
#define SYNTH_TEST_ITEM_6_RESULT_TOP   180
#define SYNTH_TEST_ITEM_6_ON_OFF_LEFT  SYNTH_TEST_ITEM_ON_OFF_LEFT_2
#define SYNTH_TEST_ITEM_6_ON_OFF_TOP   230
#define SYNTH_TEST_ITEM_6_SETTING_LEFT SYNTH_TEST_ITEM_SETTING_LEFT_2
#define SYNTH_TEST_ITEM_6_SETTING_TOP  230

#define SYNTH_TEST_ITEM_6_AC_LEFT      SYNTH_TEST_ITEM_6_STEP_LEFT
#define SYNTH_TEST_ITEM_6_AC_COLON_LEFT  (SYNTH_TEST_ITEM_6_STEP_LEFT + 130)
#define SYNTH_TEST_ITEM_6_AC_VAL_LEFT  (SYNTH_TEST_ITEM_6_STEP_LEFT + 140)
#define SYNTH_TEST_ITEM_6_AC_UNIT_LEFT (SYNTH_TEST_ITEM_6_STEP_LEFT + 185)
#define SYNTH_TEST_ITEM_6_AC_TOP       (SYNTH_TEST_ITEM_6_STEP_TOP + 33)  

#define SYNTH_TEST_ITEM_6_VOLTAGE_LEFT     SYNTH_TEST_ITEM_6_STEP_LEFT
#define SYNTH_TEST_ITEM_6_VOLTAGE_COLON_LEFT  (SYNTH_TEST_ITEM_6_VOLTAGE_LEFT + 65)
#define SYNTH_TEST_ITEM_6_VOLTAGE_VAL_LEFT  (SYNTH_TEST_ITEM_6_VOLTAGE_LEFT + 120)
#define SYNTH_TEST_ITEM_6_VOLTAGE_UNIT_LEFT (SYNTH_TEST_ITEM_6_VOLTAGE_LEFT + 185)
#define SYNTH_TEST_ITEM_6_VOLTAGE_TOP       (SYNTH_TEST_ITEM_6_AC_TOP + 33) 

#define SYNTH_TEST_ITEM_6_CURRENT_LEFT     (SYNTH_TEST_ITEM_6_VOLTAGE_LEFT + 210)
#define SYNTH_TEST_ITEM_6_CURRENT_COLON_LEFT  (SYNTH_TEST_ITEM_6_VOLTAGE_COLON_LEFT + 210)
#define SYNTH_TEST_ITEM_6_CURRENT_VAL_LEFT  (SYNTH_TEST_ITEM_6_VOLTAGE_VAL_LEFT + 210)
#define SYNTH_TEST_ITEM_6_CURRENT_UNIT_LEFT (SYNTH_TEST_ITEM_6_VOLTAGE_UNIT_LEFT + 210)
#define SYNTH_TEST_ITEM_6_CURRENT_TOP       SYNTH_TEST_ITEM_6_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_6_OC_LEFT        SYNTH_TEST_ITEM_6_VOLTAGE_LEFT
#define SYNTH_TEST_ITEM_6_OC_COLON_LEFT  (SYNTH_TEST_ITEM_6_VOLTAGE_COLON_LEFT + 32)
#define SYNTH_TEST_ITEM_6_OC_VAL_LEFT    (SYNTH_TEST_ITEM_6_VOLTAGE_VAL_LEFT + 32)
#define SYNTH_TEST_ITEM_6_OC_UNIT_LEFT   (SYNTH_TEST_ITEM_6_VOLTAGE_UNIT_LEFT + 32)
#define SYNTH_TEST_ITEM_6_OC_TOP         SYNTH_TEST_ITEM_6_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_6_SHORT_LEFT        SYNTH_TEST_ITEM_6_VOLTAGE_LEFT
#define SYNTH_TEST_ITEM_6_SHORT_COLON_LEFT  (SYNTH_TEST_ITEM_6_VOLTAGE_LEFT + 130)
#define SYNTH_TEST_ITEM_6_SHORT_VAL_LEFT    (SYNTH_TEST_ITEM_6_VOLTAGE_LEFT + 190)
#define SYNTH_TEST_ITEM_6_SHORT_UNIT_LEFT   (SYNTH_TEST_ITEM_6_VOLTAGE_LEFT + 240)
#define SYNTH_TEST_ITEM_6_SHORT_TOP         SYNTH_TEST_ITEM_6_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_7_STEP_LEFT    SYNTH_TEST_ITEM_STEP_LEFT_2
#define SYNTH_TEST_ITEM_7_STEP_TOP     280
#define SYNTH_TEST_ITEM_7_TYPE_LEFT    SYNTH_TEST_ITEM_TYPE_LEFT_2
#define SYNTH_TEST_ITEM_7_TYPE_TOP     280
#define SYNTH_TEST_ITEM_7_RESULT_LEFT  SYNTH_TEST_ITEM_RESULT_LEFT_2
#define SYNTH_TEST_ITEM_7_RESULT_TOP   280
#define SYNTH_TEST_ITEM_7_ON_OFF_LEFT  SYNTH_TEST_ITEM_ON_OFF_LEFT_2
#define SYNTH_TEST_ITEM_7_ON_OFF_TOP   330
#define SYNTH_TEST_ITEM_7_SETTING_LEFT SYNTH_TEST_ITEM_SETTING_LEFT_2
#define SYNTH_TEST_ITEM_7_SETTING_TOP  330

#define SYNTH_TEST_ITEM_7_AC_LEFT      SYNTH_TEST_ITEM_7_STEP_LEFT
#define SYNTH_TEST_ITEM_7_AC_COLON_LEFT  (SYNTH_TEST_ITEM_7_STEP_LEFT + 130)
#define SYNTH_TEST_ITEM_7_AC_VAL_LEFT  (SYNTH_TEST_ITEM_7_STEP_LEFT + 140)
#define SYNTH_TEST_ITEM_7_AC_UNIT_LEFT (SYNTH_TEST_ITEM_7_STEP_LEFT + 185)
#define SYNTH_TEST_ITEM_7_AC_TOP       (SYNTH_TEST_ITEM_7_STEP_TOP + 33)  

#define SYNTH_TEST_ITEM_7_VOLTAGE_LEFT     SYNTH_TEST_ITEM_7_STEP_LEFT
#define SYNTH_TEST_ITEM_7_VOLTAGE_COLON_LEFT  (SYNTH_TEST_ITEM_7_VOLTAGE_LEFT + 65)
#define SYNTH_TEST_ITEM_7_VOLTAGE_VAL_LEFT  (SYNTH_TEST_ITEM_7_VOLTAGE_LEFT + 120)
#define SYNTH_TEST_ITEM_7_VOLTAGE_UNIT_LEFT (SYNTH_TEST_ITEM_7_VOLTAGE_LEFT + 185)
#define SYNTH_TEST_ITEM_7_VOLTAGE_TOP       (SYNTH_TEST_ITEM_7_AC_TOP + 33) 

#define SYNTH_TEST_ITEM_7_CURRENT_LEFT     (SYNTH_TEST_ITEM_7_VOLTAGE_LEFT + 210)
#define SYNTH_TEST_ITEM_7_CURRENT_COLON_LEFT  (SYNTH_TEST_ITEM_7_VOLTAGE_COLON_LEFT + 210)
#define SYNTH_TEST_ITEM_7_CURRENT_VAL_LEFT  (SYNTH_TEST_ITEM_7_VOLTAGE_VAL_LEFT + 210)
#define SYNTH_TEST_ITEM_7_CURRENT_UNIT_LEFT (SYNTH_TEST_ITEM_7_VOLTAGE_UNIT_LEFT + 210)
#define SYNTH_TEST_ITEM_7_CURRENT_TOP       SYNTH_TEST_ITEM_7_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_7_OC_LEFT        SYNTH_TEST_ITEM_7_VOLTAGE_LEFT
#define SYNTH_TEST_ITEM_7_OC_COLON_LEFT  (SYNTH_TEST_ITEM_7_VOLTAGE_COLON_LEFT + 32)
#define SYNTH_TEST_ITEM_7_OC_VAL_LEFT    (SYNTH_TEST_ITEM_7_VOLTAGE_VAL_LEFT + 32)
#define SYNTH_TEST_ITEM_7_OC_UNIT_LEFT   (SYNTH_TEST_ITEM_7_VOLTAGE_UNIT_LEFT + 32)
#define SYNTH_TEST_ITEM_7_OC_TOP         SYNTH_TEST_ITEM_7_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_7_SHORT_LEFT        SYNTH_TEST_ITEM_7_VOLTAGE_LEFT
#define SYNTH_TEST_ITEM_7_SHORT_COLON_LEFT  (SYNTH_TEST_ITEM_7_VOLTAGE_LEFT + 130)
#define SYNTH_TEST_ITEM_7_SHORT_VAL_LEFT    (SYNTH_TEST_ITEM_7_VOLTAGE_LEFT + 190)
#define SYNTH_TEST_ITEM_7_SHORT_UNIT_LEFT   (SYNTH_TEST_ITEM_7_VOLTAGE_LEFT + 240)
#define SYNTH_TEST_ITEM_7_SHORT_TOP         SYNTH_TEST_ITEM_7_VOLTAGE_TOP

#define SYNTH_TEST_ITEM_8_STEP_LEFT    SYNTH_TEST_ITEM_STEP_LEFT_2
#define SYNTH_TEST_ITEM_8_STEP_TOP     380
#define SYNTH_TEST_ITEM_8_TYPE_LEFT    SYNTH_TEST_ITEM_TYPE_LEFT_2
#define SYNTH_TEST_ITEM_8_TYPE_TOP     380
#define SYNTH_TEST_ITEM_8_RESULT_LEFT  SYNTH_TEST_ITEM_RESULT_LEFT_2
#define SYNTH_TEST_ITEM_8_RESULT_TOP   380
#define SYNTH_TEST_ITEM_8_ON_OFF_LEFT  SYNTH_TEST_ITEM_ON_OFF_LEFT_2
#define SYNTH_TEST_ITEM_8_ON_OFF_TOP   430
#define SYNTH_TEST_ITEM_8_SETTING_LEFT SYNTH_TEST_ITEM_SETTING_LEFT_2
#define SYNTH_TEST_ITEM_8_SETTING_TOP  430

#define SYNTH_TEST_ITEM_8_AC_LEFT      SYNTH_TEST_ITEM_8_STEP_LEFT
#define SYNTH_TEST_ITEM_8_AC_COLON_LEFT  (SYNTH_TEST_ITEM_8_STEP_LEFT + 130)
#define SYNTH_TEST_ITEM_8_AC_VAL_LEFT  (SYNTH_TEST_ITEM_8_STEP_LEFT + 140)
#define SYNTH_TEST_ITEM_8_AC_UNIT_LEFT (SYNTH_TEST_ITEM_8_STEP_LEFT + 185)
#define SYNTH_TEST_ITEM_8_AC_TOP       (SYNTH_TEST_ITEM_8_STEP_TOP + 33)  

#define SYNTH_TEST_CONTACT_PHONE_LEFT  530
#define SYNTH_TEST_CONTACT_PHONE_TOP   (SYNTH_TEST_SETTING_CAPTION_TOP + 20)

#define SYNTH_TEST_PHONE_NUMBER_LEFT   680
#define SYNTH_TEST_PHONE_NUMBER_TOP    SYNTH_TEST_CONTACT_PHONE_TOP + 5

#define MODE_CAPTION_LEFT    250
#define MODE_CAPTION_TOP     10

#define MODE_SET_LEFT        200
#define MODE_SET_TOP         110

#define MODE_COLON_LEFT      400

#define MODE_AC_LEFT         200
#define MODE_AC_TOP          190

#define MODE_VOLTAGE_LEFT    200
#define MODE_VOLTAGE_TOP     270

#define MODE_CURRENT_LEFT    200
#define MODE_CURRENT_TOP     350

#define MODE_VAL_LEFT        450

#define MODE_UNIT_LEFT       600

/* digit len */
#define STEP_VAL_INTEGER_LEN      2
#define STEP_VAL_DECIMAL_LEN      0

#define CHANNEL_VAL_INTEGER_LEN   2
#define CHANNEL_VAL_DECIMAL_LEN   0

#define VOLTAGE_VAL_INTEGER_LEN   2
#define VOLTAGE_VAL_DECIMAL_LEN   2

#define CURRENT_VAL_INTEGER_LEN   1
#define CURRENT_VAL_DECIMAL_LEN   2

#define RESIST_VAL_INTEGER_LEN    3
#define RESIST_VAL_DECIMAL_LEN    1

#define AC_VAL_INTEGER_LEN    3
#define AC_VAL_DECIMAL_LEN    1

#define TIME_VAL_INTEGER_LEN      3
#define TIME_VAL_DECIMAL_LEN      1

#define INTERVAL_VAL_INTEGER_LEN   2
#define INTERVAL_VAL_DECIMAL_LEN   1

#define POWER_ON_COUNT_VAL_INTEGER_LEN  4

#define EDIT_VAL_SIZE   5

/* synth test setting */
extern void draw_synth_test_setting_caption(void);

extern void draw_qc_20_test_setting_caption(void);

extern void draw_test_setting_menu_const(void);

extern void draw_synth_test_setting_menu(const SYNTH_TEST_SETTING *synth_test_setting);

extern void draw_QC_20_test_setting_menu(const QC_20_TEST_SETTING *qc_20_test_setting);

extern void draw_normal_test_setting_group(uint32_t group);

extern void draw_focus_test_setting_group(uint32_t group);

extern void draw_edit_test_setting_group(uint32_t group);

extern void draw_test_group(uint32_t group);

extern void draw_normal_test(void);

extern void draw_focus_test(void);

extern void draw_normal_test_item_1_setting(void);

extern void draw_focus_test_item_1_setting(void);

extern void draw_normal_synth_item_2_type(SYNTH_TEST_TYPE type);

extern void draw_focus_synth_item_2_type(SYNTH_TEST_TYPE type);

extern void draw_edit_synth_item_2_type(SYNTH_TEST_TYPE type);

extern void draw_normal_qc_20_item_2_type(QC_20_TEST_TYPE type);

extern void draw_focus_qc_20_item_2_type(QC_20_TEST_TYPE type);

extern void draw_edit_qc_20_item_2_type(QC_20_TEST_TYPE type);

extern void draw_normal_mtk_item_2_type(MTK_TEST_TYPE type);

extern void draw_focus_mtk_item_2_type(MTK_TEST_TYPE type);

extern void draw_edit_mtk_item_2_type(MTK_TEST_TYPE type);

extern void draw_normal_test_item_2_on_off(OPTION_ON_OFF on_off);

extern void draw_focus_test_item_2_on_off(OPTION_ON_OFF on_off);

extern void draw_edit_test_item_2_on_off(OPTION_ON_OFF on_off);

extern void draw_normal_test_item_2_setting(void);

extern void draw_focus_test_item_2_setting(void);

extern void draw_normal_synth_item_3_type(SYNTH_TEST_TYPE type);

extern void draw_focus_synth_item_3_type(SYNTH_TEST_TYPE type);

extern void draw_edit_synth_item_3_type(SYNTH_TEST_TYPE type);

extern void draw_normal_qc_20_item_3_type(QC_20_TEST_TYPE type);

extern void draw_focus_qc_20_item_3_type(QC_20_TEST_TYPE type);

extern void draw_normal_mtk_item_3_type(MTK_TEST_TYPE type);

extern void draw_focus_mtk_item_3_type(MTK_TEST_TYPE type);

extern void draw_edit_mtk_item_3_type(MTK_TEST_TYPE type);

extern void draw_edit_qc_20_item_3_type(QC_20_TEST_TYPE type);

extern void draw_normal_test_item_3_on_off(OPTION_ON_OFF on_off);

extern void draw_focus_test_item_3_on_off(OPTION_ON_OFF on_off);

extern void draw_edit_test_item_3_on_off(OPTION_ON_OFF on_off);

extern void draw_normal_test_item_3_setting(void);

extern void draw_focus_test_item_3_setting(void);

extern void draw_normal_synth_item_4_type(SYNTH_TEST_TYPE type);

extern void draw_focus_synth_item_4_type(SYNTH_TEST_TYPE type);

extern void draw_edit_synth_item_4_type(SYNTH_TEST_TYPE type);

extern void draw_normal_qc_20_item_4_type(QC_20_TEST_TYPE type);

extern void draw_focus_qc_20_item_4_type(QC_20_TEST_TYPE type);

extern void draw_edit_qc_20_item_4_type(QC_20_TEST_TYPE type);

extern void draw_normal_mtk_item_4_type(MTK_TEST_TYPE type);

extern void draw_focus_mtk_item_4_type(MTK_TEST_TYPE type);

extern void draw_edit_mtk_item_4_type(MTK_TEST_TYPE type);

extern void draw_normal_test_item_4_on_off(OPTION_ON_OFF on_off);

extern void draw_focus_test_item_4_on_off(OPTION_ON_OFF on_off);

extern void draw_edit_test_item_4_on_off(OPTION_ON_OFF on_off);

extern void draw_normal_test_item_4_setting(void);

extern void draw_focus_test_item_4_setting(void);

extern void draw_normal_synth_item_5_type(SYNTH_TEST_TYPE type);

extern void draw_focus_synth_item_5_type(SYNTH_TEST_TYPE type);

extern void draw_edit_synth_item_5_type(SYNTH_TEST_TYPE type);

extern void draw_normal_qc_20_item_5_type(QC_20_TEST_TYPE type);

extern void draw_focus_qc_20_item_5_type(QC_20_TEST_TYPE type);

extern void draw_edit_qc_20_item_5_type(QC_20_TEST_TYPE type);

extern void draw_normal_mtk_item_5_type(MTK_TEST_TYPE type);

extern void draw_focus_mtk_item_5_type(MTK_TEST_TYPE type);

extern void draw_edit_mtk_item_5_type(MTK_TEST_TYPE type);

extern void draw_normal_test_item_5_on_off(OPTION_ON_OFF on_off);

extern void draw_focus_test_item_5_on_off(OPTION_ON_OFF on_off);

extern void draw_edit_test_item_5_on_off(OPTION_ON_OFF on_off);

extern void draw_normal_test_item_5_setting(void);

extern void draw_focus_test_item_5_setting(void);

extern void draw_normal_synth_item_6_type(SYNTH_TEST_TYPE type);

extern void draw_focus_synth_item_6_type(SYNTH_TEST_TYPE type);

extern void draw_edit_synth_item_6_type(SYNTH_TEST_TYPE type);

extern void draw_normal_qc_20_item_6_type(QC_20_TEST_TYPE type);

extern void draw_focus_qc_20_item_6_type(QC_20_TEST_TYPE type);

extern void draw_edit_qc_20_item_6_type(QC_20_TEST_TYPE type);

extern void draw_normal_mtk_item_6_type(MTK_TEST_TYPE type);

extern void draw_focus_mtk_item_6_type(MTK_TEST_TYPE type);

extern void draw_edit_mtk_item_6_type(MTK_TEST_TYPE type);

extern void draw_normal_test_item_6_on_off(OPTION_ON_OFF on_off);

extern void draw_focus_test_item_6_on_off(OPTION_ON_OFF on_off);

extern void draw_edit_test_item_6_on_off(OPTION_ON_OFF on_off);

extern void draw_normal_test_item_6_setting(void);

extern void draw_focus_test_item_6_setting(void);

extern void draw_normal_synth_item_7_type(SYNTH_TEST_TYPE type);

extern void draw_focus_synth_item_7_type(SYNTH_TEST_TYPE type);

extern void draw_edit_synth_item_7_type(SYNTH_TEST_TYPE type);

extern void draw_normal_qc_20_item_7_type(QC_20_TEST_TYPE type);

extern void draw_focus_qc_20_item_7_type(QC_20_TEST_TYPE type);

extern void draw_edit_qc_20_item_7_type(QC_20_TEST_TYPE type);

extern void draw_normal_mtk_item_7_type(MTK_TEST_TYPE type);

extern void draw_focus_mtk_item_7_type(MTK_TEST_TYPE type);

extern void draw_edit_mtk_item_7_type(MTK_TEST_TYPE type);

extern void draw_normal_test_item_7_on_off(OPTION_ON_OFF on_off);

extern void draw_focus_test_item_7_on_off(OPTION_ON_OFF on_off);

extern void draw_edit_test_item_7_on_off(OPTION_ON_OFF on_off);

extern void draw_normal_test_item_7_setting(void);

extern void draw_focus_test_item_7_setting(void);

extern void draw_normal_test_item_8_on_off(OPTION_ON_OFF on_off);

extern void draw_focus_test_item_8_on_off(OPTION_ON_OFF on_off);

extern void draw_edit_test_item_8_on_off(OPTION_ON_OFF on_off);

extern void draw_normal_test_item_8_setting(void);

extern void draw_focus_test_item_8_setting(void);

/* synth test */
extern void draw_synth_test_caption(void);

extern void draw_qc_20_test_caption(void);

extern void draw_test_menu_const(void);

extern void draw_synth_test_menu(const SYNTH_TEST_SETTING *synth_test_setting);

extern void draw_qc_20_test_menu(const QC_20_TEST_SETTING *qc_20_test_setting);

extern void draw_synth_test_phone_number(const PHONE_NUMBER *phone_number);

extern void draw_synth_test_step_1_ac(uint32_t uA);
extern void clear_synth_test_step_1_ac(void);
extern void draw_synth_test_step_1_voltage(uint32_t mV);
extern void clear_synth_test_step_1_voltage(void);
extern void draw_synth_test_step_1_OK(void);
extern void draw_synth_test_step_1_fail(void);
extern void clear_synth_test_step_1_result(void);

extern void draw_synth_test_step_2_ac(uint32_t uA);
extern void clear_synth_test_step_2_ac(void);
extern void draw_synth_test_step_2_voltage(uint32_t mV);
extern void clear_synth_test_step_2_voltage(void);
extern void draw_synth_test_step_2_current(uint32_t mA);
extern void clear_synth_test_step_2_current(void);

extern void draw_synth_test_step_2_oc(uint32_t mA);
extern void clear_synth_test_step_2_oc(void);
extern void draw_synth_test_step_2_short(uint32_t mA);
extern void clear_synth_test_step_2_short(void);
extern void draw_synth_test_step_2_OK(void);
extern void draw_synth_test_step_2_fail(void);
extern void clear_synth_test_step_2_result(void);

extern void draw_synth_test_step_3_ac(uint32_t uA);
extern void clear_synth_test_step_3_ac(void);
extern void draw_synth_test_step_3_voltage(uint32_t mV);
extern void clear_synth_test_step_3_voltage(void);
extern void draw_synth_test_step_3_current(uint32_t mA);
extern void clear_synth_test_step_3_current(void);

extern void draw_synth_test_step_3_oc(uint32_t mA);
extern void clear_synth_test_step_3_oc(void);
extern void draw_synth_test_step_3_short(uint32_t mA);
extern void clear_synth_test_step_3_short(void);
extern void draw_synth_test_step_3_OK(void);
extern void draw_synth_test_step_3_fail(void);
extern void clear_synth_test_step_3_result(void);

extern void draw_synth_test_step_4_ac(uint32_t uA);
extern void clear_synth_test_step_4_ac(void);
extern void draw_synth_test_step_4_voltage(uint32_t mV);
extern void clear_synth_test_step_4_voltage(void);
extern void draw_synth_test_step_4_current(uint32_t mA);
extern void clear_synth_test_step_4_current(void);
extern void draw_synth_test_step_4_oc(uint32_t mA);
extern void clear_synth_test_step_4_oc(void);
extern void draw_synth_test_step_4_short(uint32_t mA);
extern void clear_synth_test_step_4_short(void);
extern void draw_synth_test_step_4_OK(void);
extern void draw_synth_test_step_4_fail(void);
extern void clear_synth_test_step_4_result(void);

extern void draw_synth_test_step_5_ac(uint32_t uA);
extern void clear_synth_test_step_5_ac(void);
extern void draw_synth_test_step_5_voltage(uint32_t mV);
extern void clear_synth_test_step_5_voltage(void);
extern void draw_synth_test_step_5_current(uint32_t mA);
extern void clear_synth_test_step_5_current(void);
extern void draw_synth_test_step_5_oc(uint32_t mA);
extern void clear_synth_test_step_5_oc(void);
extern void draw_synth_test_step_5_short(uint32_t mA);
extern void clear_synth_test_step_5_short(void);
extern void draw_synth_test_step_5_OK(void);
extern void draw_synth_test_step_5_fail(void);
extern void clear_synth_test_step_5_result(void);

extern void draw_synth_test_step_6_ac(uint32_t uA);
extern void clear_synth_test_step_6_ac(void);
extern void draw_synth_test_step_6_voltage(uint32_t mV);
extern void clear_synth_test_step_6_voltage(void);
extern void draw_synth_test_step_6_current(uint32_t mA);
extern void clear_synth_test_step_6_current(void);
extern void draw_synth_test_step_6_oc(uint32_t mA);
extern void clear_synth_test_step_6_oc(void);
extern void draw_synth_test_step_6_short(uint32_t mA);
extern void clear_synth_test_step_6_short(void);
extern void draw_synth_test_step_6_OK(void);
extern void draw_synth_test_step_6_fail(void);
extern void clear_synth_test_step_6_result(void);

extern void draw_synth_test_step_7_ac(uint32_t uA);
extern void clear_synth_test_step_7_ac(void);
extern void draw_synth_test_step_7_voltage(uint32_t mV);
extern void clear_synth_test_step_7_voltage(void);
extern void draw_synth_test_step_7_current(uint32_t mA);
extern void clear_synth_test_step_7_current(void);
extern void draw_synth_test_step_7_oc(uint32_t mA);
extern void clear_synth_test_step_7_oc(void);
extern void draw_synth_test_step_7_short(uint32_t mA);
extern void clear_synth_test_step_7_short(void);
extern void draw_synth_test_step_7_OK(void);
extern void draw_synth_test_step_7_fail(void);
extern void clear_synth_test_step_7_result(void);

extern void draw_synth_test_step_8_OK(void);
extern void clear_synth_test_step_8_result(void);

/* cv mode */
extern void draw_cv_mode_menu(void);

extern void draw_focus_voltage_val(uint32_t mV);

extern void draw_edit_voltage_val(uint32_t mV);

/* cc mode */
extern void draw_cc_mode_menu(void);

extern void draw_focus_current_val(uint32_t mA);

extern void draw_edit_current_val(uint32_t mA);

/* cr mode */
extern void draw_cr_mode_menu(void);

extern void draw_focus_resist_val(uint32_t mO);

extern void draw_edit_resist_val(uint32_t mO);

extern void draw_ac_val(uint32_t uA);

extern void draw_voltage_val(uint32_t mV);

extern void draw_current_val(uint32_t mA);


/* empty load setting */
#define EMPTY_LOAD_SETTING_CAPTION_LEFT   250
#define EMPTY_LOAD_SETTING_CAPTION_TOP    10

#define EMPTY_LOAD_SETTING_TIME_LEFT     150
#define EMPTY_LOAD_SETTING_TIME_TOP      110
#define EMPTY_LOAD_SETTING_TIME_UNIT_LEFT 550

#define EMPTY_LOAD_SETTING_AC_LEFT       150
#define EMPTY_LOAD_SETTING_AC_TOP        190
#define EMPTY_LOAD_SETTING_AC_UNIT_LEFT  550

#define EMPTY_LOAD_SETTING_VOLTAGE_RANGE_LEFT  150
#define EMPTY_LOAD_SETTING_VOLTAGE_RANGE_TOP   270
#define EMPTY_LOAD_SETTING_VOLTAGE_RANGE_UNIT_LEFT   740

#define EMPTY_LOAD_SETTING_USB_DP_DN_LEFT    10
#define EMPTY_LOAD_SETTING_USB_DP_DN_TOP     350

#define EMPTY_LOAD_SETTING_USB_DP_DN_NODE_LEFT  420

#define EMPTY_LOAD_DP_DN_ON_OFF_LEFT       420
#define EMPTY_LOAD_DP_DN_ON_OFF_TOP        430

#define EMPTY_LOAD_DP_DN_SETTING_LEFT      550
#define EMPTY_LOAD_DP_DN_SETTING_TOP       EMPTY_LOAD_DP_DN_ON_OFF_TOP

#define EMPTY_LOAD_SETTING_VOLTAGE_RANGE_HYPHON  550

#define EMPTY_LOAD_SETTING_COLON_LEFT    350

#define EMPTY_LOAD_SETTING_LESS_THAN_LEFT    380

#define EMPTY_LOAD_SETTING_EDIT_TIME_LEFT     420

#define EMPTY_LOAD_SETTING_EDIT_AC_LEFT       420

#define EMPTY_LOAD_SETTING_EDIT_VOLTAGE_FROM_LEFT  420

#define EMPTY_LOAD_SETTING_EDIT_VOLTAGE_TO_LEFT    620

extern void draw_empty_load_setting_menu(void);

extern void draw_normal_empty_load_setting_time(uint32_t ms);

extern void draw_focus_empty_load_setting_time(uint32_t ms);

extern void draw_edit_empty_load_setting_time(uint32_t ms);

extern void draw_normal_empty_load_setting_ac(uint32_t uA);

extern void draw_focus_empty_load_setting_ac(uint32_t uA);

extern void draw_edit_empty_load_setting_ac(uint32_t uA);

extern void draw_normal_empty_load_setting_voltage_from(uint32_t mV);

extern void draw_focus_empty_load_setting_voltage_from(uint32_t mV);

extern void draw_edit_empty_load_setting_voltage_from(uint32_t mV);

extern void draw_normal_empty_load_setting_voltage_to(uint32_t mV);

extern void draw_focus_empty_load_setting_voltage_to(uint32_t mV);

extern void draw_edit_empty_load_setting_voltage_to(uint32_t mV);

extern void draw_normal_empty_load_dp_dn_mode(USB_DP_DN_MODE mode);

extern void draw_focus_empty_load_dp_dn_mode(USB_DP_DN_MODE mode);

extern void draw_edit_empty_load_dp_dn_mode(USB_DP_DN_MODE mode);

extern void draw_normal_empty_load_dp_dn_on_off(OPTION_ON_OFF on_off);

extern void draw_focus_empty_load_dp_dn_on_off(OPTION_ON_OFF on_off);

extern void draw_edit_empty_load_dp_dn_on_off(OPTION_ON_OFF on_off);

extern void draw_normal_empty_load_dp_dn_setting(void);

extern void draw_focus_empty_load_dp_dn_setting(void);

/* usb D+/D- divide mode */
#define DP_DN_SETTING_CAPTION_LEFT     150
#define DP_DN_SETTING_CAPTION_TOP      10

#define DP_DN_DIVIDE_MODE_LEFT         330
#define DP_DN_DIVIDE_MODE_TOP          80

#define DP_VOLTAGE_RANGE_LEFT          100
#define DP_VOLTAGE_RANGE_TOP           200

#define DN_VOLTAGE_RANGE_LEFT          100
#define DN_VOLTAGE_RANGE_TOP           300

#define DP_DN_DIVIDE_MODE_COLON_LEFT    350

#define DP_DN_DIVIDE_MODE_HYPHON_LEFT   550

#define DP_DN_DIVIDE_MODE_UNIT_LEFT    740

#define DP_DN_DIVIDE_MODE_EDIT_VOLTAGE_FROM_LEFT  420

#define DP_DN_DIVIDE_MODE_EDIT_VOLTAGE_TO_LEFT    620

extern void draw_dp_dn_divide_mode_menu(void);

extern void draw_normal_divide_mode_dp_voltage_from(uint32_t mV);
extern void draw_focus_divide_mode_dp_voltage_from(uint32_t mV);
extern void draw_edit_divide_mode_dp_voltage_from(uint32_t mV);

extern void draw_normal_divide_mode_dp_voltage_to(uint32_t mV);
extern void draw_focus_divide_mode_dp_voltage_to(uint32_t mV);
extern void draw_edit_divide_mode_dp_voltage_to(uint32_t mV);

extern void draw_normal_divide_mode_dn_voltage_from(uint32_t mV);
extern void draw_focus_divide_mode_dn_voltage_from(uint32_t mV);
extern void draw_edit_divide_mode_dn_voltage_from(uint32_t mV);

extern void draw_normal_divide_mode_dn_voltage_to(uint32_t mV);
extern void draw_focus_divide_mode_dn_voltage_to(uint32_t mV);
extern void draw_edit_divide_mode_dn_voltage_to(uint32_t mV);

/* cc setting */
#define CC_SETTING_CAPTION_LEFT   250
#define CC_SETTING_CAPTION_TOP    10

#define CC_SETTING_TIME_LEFT     150
#define CC_SETTING_TIME_TOP      110
#define CC_SETTING_TIME_UNIT_LEFT 550

#define CC_SETTING_AC_LEFT       150
#define CC_SETTING_AC_TOP        190
#define CC_SETTING_AC_UNIT_LEFT  550

#define CC_SETTING_CC_VAL_LEFT   150
#define CC_SETTING_CC_VAL_TOP    270
#define CC_SETTING_CC_VAL_UNIT_LEFT 550

#define CC_SETTING_VOLTAGE_RANGE_LEFT  150
#define CC_SETTING_VOLTAGE_RANGE_TOP   350
#define CC_SETTING_VOLTAGE_RANGE_UNIT_LEFT   740

#define CC_SETTING_VOLTAGE_RANGE_HYPHON  550

#define CC_SETTING_COLON_LEFT    350

#define CC_SETTING_LESS_THAN_LEFT    380

#define CC_SETTING_EDIT_TIME_LEFT     420

#define CC_SETTING_EDIT_AC_LEFT       420

#define CC_SETTING_EDIT_CC_VAL_LEFT   420

#define CC_SETTING_EDIT_VOLTAGE_FROM_LEFT  420

#define CC_SETTING_EDIT_VOLTAGE_TO_LEFT    620

extern void draw_synth_cc_setting_caption(void);

extern void draw_qc_20_5v_cc_setting_caption(void);

extern void draw_qc_20_9v_cc_setting_caption(void);

extern void draw_qc_20_12v_cc_setting_caption(void);

extern void draw_qc_20_20v_cc_setting_caption(void);

extern void draw_cc_setting_menu(void);

extern void draw_normal_cc_setting_time(uint32_t ms);

extern void draw_focus_cc_setting_time(uint32_t ms);

extern void draw_edit_cc_setting_time(uint32_t ms);

extern void draw_normal_cc_setting_ac(uint32_t uA);

extern void draw_focus_cc_setting_ac(uint32_t uA);

extern void draw_edit_cc_setting_ac(uint32_t uA);

extern void draw_normal_cc_setting_cc(uint32_t mA);

extern void draw_focus_cc_setting_cc(uint32_t mA);

extern void draw_edit_cc_setting_cc(uint32_t mA);

extern void draw_normal_cc_setting_voltage_from(uint32_t mV);

extern void draw_focus_cc_setting_voltage_from(uint32_t mV);

extern void draw_edit_cc_setting_voltage_from(uint32_t mV);

extern void draw_normal_cc_setting_voltage_to(uint32_t mV);

extern void draw_focus_cc_setting_voltage_to(uint32_t mV);

extern void draw_edit_cc_setting_voltage_to(uint32_t mV);

/* cv setting */
#define CV_SETTING_CAPTION_LEFT   CC_SETTING_CAPTION_LEFT
#define CV_SETTING_CAPTION_TOP    CC_SETTING_CAPTION_TOP

#define CV_SETTING_TIME_LEFT     CC_SETTING_TIME_LEFT
#define CV_SETTING_TIME_TOP      CC_SETTING_TIME_TOP
#define CV_SETTING_TIME_UNIT_LEFT CC_SETTING_TIME_UNIT_LEFT

#define CV_SETTING_AC_LEFT       CC_SETTING_AC_LEFT
#define CV_SETTING_AC_TOP        CC_SETTING_AC_TOP
#define CV_SETTING_AC_UNIT_LEFT  CC_SETTING_AC_UNIT_LEFT

#define CV_SETTING_CV_VAL_LEFT   CC_SETTING_CC_VAL_LEFT
#define CV_SETTING_CV_VAL_TOP    CC_SETTING_CC_VAL_TOP
#define CV_SETTING_CV_VAL_UNIT_LEFT CC_SETTING_CC_VAL_UNIT_LEFT

#define CV_SETTING_CURRENT_RANGE_LEFT  CC_SETTING_VOLTAGE_RANGE_LEFT
#define CV_SETTING_CURRENT_RANGE_TOP   CC_SETTING_VOLTAGE_RANGE_TOP
#define CV_SETTING_CURRENT_RANGE_UNIT_LEFT   CC_SETTING_VOLTAGE_RANGE_UNIT_LEFT

#define CV_SETTING_COLON_LEFT    CC_SETTING_COLON_LEFT

#define CV_SETTING_LESS_THAN_LEFT    CC_SETTING_LESS_THAN_LEFT

#define CV_SETTING_CURRENT_RANGE_HYPHON  CC_SETTING_VOLTAGE_RANGE_HYPHON

#define CV_SETTING_EDIT_TIME_LEFT     CC_SETTING_EDIT_TIME_LEFT

#define CV_SETTING_EDIT_AC_LEFT       CC_SETTING_EDIT_AC_LEFT

#define CV_SETTING_EDIT_CV_VAL_LEFT   CC_SETTING_EDIT_CC_VAL_LEFT

#define CV_SETTING_EDIT_CURRENT_FROM_LEFT  CC_SETTING_EDIT_VOLTAGE_FROM_LEFT

#define CV_SETTING_EDIT_CURRENT_TO_LEFT    CC_SETTING_EDIT_VOLTAGE_TO_LEFT

extern void draw_synth_cv_setting_caption(void);

extern void draw_qc_20_5v_cv_setting_caption(void);

extern void draw_qc_20_9v_cv_setting_caption(void);

extern void draw_qc_20_12v_cv_setting_caption(void);

extern void draw_qc_20_20v_cv_setting_caption(void);

extern void draw_cv_setting_menu(void);

extern void draw_normal_cv_setting_time(uint32_t ms);

extern void draw_focus_cv_setting_time(uint32_t ms);

extern void draw_edit_cv_setting_time(uint32_t ms);

extern void draw_normal_cv_setting_ac(uint32_t uA);

extern void draw_focus_cv_setting_ac(uint32_t uA);

extern void draw_edit_cv_setting_ac(uint32_t uA);

extern void draw_normal_cv_setting_cv(uint32_t mV);

extern void draw_focus_cv_setting_cv(uint32_t mV);

extern void draw_edit_cv_setting_cv(uint32_t mV);

extern void draw_normal_cv_setting_current_from(uint32_t mA);

extern void draw_focus_cv_setting_current_from(uint32_t mA);

extern void draw_edit_cv_setting_current_from(uint32_t mA);

extern void draw_normal_cv_setting_current_to(uint32_t mA);

extern void draw_focus_cv_setting_current_to(uint32_t mA);

extern void draw_edit_cv_setting_current_to(uint32_t mA);

/* cr setting */
#define CR_SETTING_CAPTION_LEFT   CC_SETTING_CAPTION_LEFT
#define CR_SETTING_CAPTION_TOP    CC_SETTING_CAPTION_TOP

#define CR_SETTING_TIME_LEFT     CC_SETTING_TIME_LEFT
#define CR_SETTING_TIME_TOP      (CC_SETTING_TIME_TOP - 20)
#define CR_SETTING_TIME_UNIT_LEFT CC_SETTING_TIME_UNIT_LEFT

#define CR_SETTING_AC_LEFT       CC_SETTING_AC_LEFT
#define CR_SETTING_AC_TOP        (CR_SETTING_TIME_TOP + 80)
#define CR_SETTING_AC_UNIT_LEFT  CC_SETTING_AC_UNIT_LEFT

#define CR_SETTING_CR_VAL_LEFT   CC_SETTING_CC_VAL_LEFT
#define CR_SETTING_CR_VAL_TOP    (CR_SETTING_AC_TOP + 80)
#define CR_SETTING_CR_VAL_UNIT_LEFT CC_SETTING_CC_VAL_UNIT_LEFT

#define CR_SETTING_CURRENT_RANGE_LEFT  CC_SETTING_VOLTAGE_RANGE_LEFT
#define CR_SETTING_CURRENT_RANGE_TOP   (CR_SETTING_CR_VAL_TOP + 80)
#define CR_SETTING_CURRENT_RANGE_UNIT_LEFT   CC_SETTING_VOLTAGE_RANGE_UNIT_LEFT

#define CR_SETTING_VOLTAGE_RANGE_LEFT  CC_SETTING_VOLTAGE_RANGE_LEFT
#define CR_SETTING_VOLTAGE_RANGE_TOP   (CR_SETTING_CURRENT_RANGE_TOP + 80)
#define CR_SETTING_VOLTAGE_RANGE_UNIT_LEFT   CC_SETTING_VOLTAGE_RANGE_UNIT_LEFT

#define CR_SETTING_COLON_LEFT    CC_SETTING_COLON_LEFT

#define CR_SETTING_LESS_THAN_LEFT    CC_SETTING_LESS_THAN_LEFT

#define CR_SETTING_CURRENT_RANGE_HYPHON  CC_SETTING_VOLTAGE_RANGE_HYPHON

#define CR_SETTING_VOLTAGE_RANGE_HYPHON  CC_SETTING_VOLTAGE_RANGE_HYPHON

#define CR_SETTING_EDIT_TIME_LEFT     CC_SETTING_EDIT_TIME_LEFT

#define CR_SETTING_EDIT_AC_LEFT       CC_SETTING_EDIT_AC_LEFT

#define CR_SETTING_EDIT_CR_VAL_LEFT   CC_SETTING_EDIT_CC_VAL_LEFT

#define CR_SETTING_EDIT_CURRENT_FROM_LEFT  CC_SETTING_EDIT_VOLTAGE_FROM_LEFT

#define CR_SETTING_EDIT_CURRENT_TO_LEFT    CC_SETTING_EDIT_VOLTAGE_TO_LEFT

#define CR_SETTING_EDIT_VOLTAGE_FROM_LEFT  CR_SETTING_EDIT_CURRENT_FROM_LEFT

#define CR_SETTING_EDIT_VOLTAGE_TO_LEFT    CR_SETTING_EDIT_CURRENT_TO_LEFT

extern void draw_synth_cr_setting_caption(void);

extern void draw_qc_20_5v_cr_setting_caption(void);

extern void draw_qc_20_9v_cr_setting_caption(void);

extern void draw_qc_20_12v_cr_setting_caption(void);

extern void draw_qc_20_20v_cr_setting_caption(void);

extern void draw_cr_setting_menu(void);

extern void draw_normal_cr_setting_time(uint32_t ms);

extern void draw_focus_cr_setting_time(uint32_t ms);

extern void draw_edit_cr_setting_time(uint32_t ms);

extern void draw_normal_cr_setting_ac(uint32_t uA);

extern void draw_focus_cr_setting_ac(uint32_t uA);

extern void draw_edit_cr_setting_ac(uint32_t uA);

extern void draw_normal_cr_setting_cr(uint32_t mO);

extern void draw_focus_cr_setting_cr(uint32_t mO);

extern void draw_edit_cr_setting_cr(uint32_t mO);

extern void draw_normal_cr_setting_current_from(uint32_t mA);

extern void draw_focus_cr_setting_current_from(uint32_t mA);

extern void draw_edit_cr_setting_current_from(uint32_t mA);

extern void draw_normal_cr_setting_current_to(uint32_t mA);

extern void draw_focus_cr_setting_current_to(uint32_t mA);

extern void draw_edit_cr_setting_current_to(uint32_t mA);

extern void draw_normal_cr_setting_voltage_from(uint32_t mV);

extern void draw_focus_cr_setting_voltage_from(uint32_t mV);

extern void draw_edit_cr_setting_voltage_from(uint32_t mV);

extern void draw_normal_cr_setting_voltage_to(uint32_t mV);

extern void draw_focus_cr_setting_voltage_to(uint32_t mV);

extern void draw_edit_cr_setting_voltage_to(uint32_t mV);

/* over current setting */
#define OC_SETTING_CAPTION_LEFT   CC_SETTING_CAPTION_LEFT
#define OC_SETTING_CAPTION_TOP    CC_SETTING_CAPTION_TOP

#define OC_SETTING_TIME_LEFT     (CC_SETTING_TIME_LEFT + 50)
#define OC_SETTING_TIME_TOP      (CC_SETTING_TIME_TOP + 50)
#define OC_SETTING_TIME_UNIT_LEFT (CC_SETTING_TIME_UNIT_LEFT + 50)

#define OC_SETTING_AC_LEFT       OC_SETTING_TIME_LEFT
#define OC_SETTING_AC_TOP        (OC_SETTING_TIME_TOP + 80)
#define OC_SETTING_AC_UNIT_LEFT  OC_SETTING_TIME_UNIT_LEFT

#define OC_SETTING_OC_VAL_LEFT   OC_SETTING_TIME_LEFT
#define OC_SETTING_OC_VAL_TOP    (OC_SETTING_AC_TOP + 80)
#define OC_SETTING_OC_VAL_UNIT_LEFT OC_SETTING_TIME_UNIT_LEFT

#define OC_SETTING_COLON_LEFT    (CC_SETTING_COLON_LEFT + 50)

#define OC_SETTING_LESS_THAN_LEFT    (CC_SETTING_LESS_THAN_LEFT + 50)

#define OC_SETTING_EDIT_TIME_LEFT     (CC_SETTING_EDIT_TIME_LEFT + 50)

#define OC_SETTING_EDIT_AC_LEFT       OC_SETTING_EDIT_TIME_LEFT

#define OC_SETTING_EDIT_OC_VAL_LEFT   OC_SETTING_EDIT_TIME_LEFT

extern void draw_synth_oc_setting_caption(void);

extern void draw_qc_20_5v_oc_setting_caption(void);

extern void draw_qc_20_9v_oc_setting_caption(void);

extern void draw_qc_20_12v_oc_setting_caption(void);

extern void draw_qc_20_20v_oc_setting_caption(void);

extern void draw_oc_setting_menu(void);

extern void draw_normal_oc_setting_time(uint32_t ms);

extern void draw_focus_oc_setting_time(uint32_t ms);

extern void draw_edit_oc_setting_time(uint32_t ms);

extern void draw_normal_oc_setting_ac(uint32_t uA);

extern void draw_focus_oc_setting_ac(uint32_t uA);

extern void draw_edit_oc_setting_ac(uint32_t uA);

extern void draw_normal_oc_setting_oc(uint32_t mA);

extern void draw_focus_oc_setting_oc(uint32_t mA);

extern void draw_edit_oc_setting_oc(uint32_t mA);

/* short setting */
#define SHORT_SETTING_CAPTION_LEFT   CC_SETTING_CAPTION_LEFT
#define SHORT_SETTING_CAPTION_TOP    CC_SETTING_CAPTION_TOP

#define SHORT_SETTING_TIME_LEFT     OC_SETTING_TIME_LEFT
#define SHORT_SETTING_TIME_TOP      (CC_SETTING_TIME_TOP + 50)
#define SHORT_SETTING_TIME_UNIT_LEFT OC_SETTING_TIME_UNIT_LEFT

#define SHORT_SETTING_AC_LEFT       OC_SETTING_AC_LEFT
#define SHORT_SETTING_AC_TOP        (SHORT_SETTING_TIME_TOP + 80)
#define SHORT_SETTING_AC_UNIT_LEFT  OC_SETTING_AC_UNIT_LEFT

#define SHORT_SETTING_SHORT_VAL_LEFT   OC_SETTING_OC_VAL_LEFT
#define SHORT_SETTING_SHORT_VAL_TOP    (SHORT_SETTING_AC_TOP + 80)
#define SHORT_SETTING_SHORT_VAL_UNIT_LEFT OC_SETTING_OC_VAL_UNIT_LEFT

#define SHORT_SETTING_COLON_LEFT    OC_SETTING_COLON_LEFT

#define SHORT_SETTING_LESS_THAN_LEFT    OC_SETTING_LESS_THAN_LEFT

#define SHORT_SETTING_EDIT_TIME_LEFT     OC_SETTING_EDIT_TIME_LEFT

#define SHORT_SETTING_EDIT_AC_LEFT       SHORT_SETTING_EDIT_TIME_LEFT

#define SHORT_SETTING_EDIT_SHORT_VAL_LEFT   SHORT_SETTING_EDIT_TIME_LEFT

extern void draw_synth_short_setting_caption(void);

extern void draw_qc_20_5v_short_setting_caption(void);

extern void draw_qc_20_9v_short_setting_caption(void);

extern void draw_qc_20_12v_short_setting_caption(void);

extern void draw_qc_20_20v_short_setting_caption(void);

extern void draw_short_setting_menu(void);

extern void draw_normal_short_setting_time(uint32_t ms);

extern void draw_focus_short_setting_time(uint32_t ms);

extern void draw_edit_short_setting_time(uint32_t ms);

extern void draw_normal_short_setting_ac(uint32_t uA);

extern void draw_focus_short_setting_ac(uint32_t uA);

extern void draw_edit_short_setting_ac(uint32_t uA);

extern void draw_normal_short_setting_short(uint32_t mA);

extern void draw_focus_short_setting_short(uint32_t mA);

extern void draw_edit_short_setting_short(uint32_t mA);

/* discharge setting */
#define DISCHARGE_SETTING_CAPTION_LEFT   CC_SETTING_CAPTION_LEFT
#define DISCHARGE_SETTING_CAPTION_TOP    CC_SETTING_CAPTION_TOP

#define DISCHARGE_SETTING_DISCHARGE_CURRENT_LEFT  150 
#define DISCHARGE_SETTING_DISCHARGE_CURRENT_TOP   CC_SETTING_TIME_TOP
#define DISCHARGE_SETTING_DISCHARGE_CURRENT_UNIT_LEFT   670


#define DISCHARGE_SETTING_DISCHARGE_TIME_LEFT      150
#define DISCHARGE_SETTING_DISCHARGE_TIME_TOP       (DISCHARGE_SETTING_DISCHARGE_CURRENT_TOP + 100)
#define DISCHARGE_SETTING_DISCHARGE_TIME_UNIT_LEFT 670

#define DISCHARGE_SETTING_INDICATE_DELAY_TIME_LEFT      150
#define DISCHARGE_SETTING_INDICATE_DELAY_TIME_TOP       (DISCHARGE_SETTING_DISCHARGE_TIME_TOP + 100)
#define DISCHARGE_SETTING_INDICATE_DELAY_TIME_UNIT_LEFT 670

#define DISCHARGE_SETTING_COLON_LEFT    500

#define DISCHARGE_SETTING_EDIT_DISCHARGE_CURRENT_LEFT     550

#define DISCHARGE_SETTING_EDIT_AC_CLOSE_TIME_LEFT         550

#define DISCHARGE_SETTING_EDIT_DISCHARGE_TIME_LEFT        550

#define DISCHARGE_SETTING_EDIT_INDICATE_DELAY_TIME_LEFT   550

extern void draw_discharge_setting_menu(void);

extern void draw_normal_discharge_setting_discharge_current(uint32_t mA);

extern void draw_focus_discharge_setting_discharge_current(uint32_t mA);

extern void draw_edit_discharge_setting_discharge_current(uint32_t mA);

extern void draw_normal_discharge_setting_discharge_time(uint32_t ms);

extern void draw_focus_discharge_setting_discharge_time(uint32_t ms);

extern void draw_edit_discharge_setting_discharge_time(uint32_t ms);

extern void draw_normal_discharge_setting_indicate_delay_time(uint32_t ms);

extern void draw_focus_discharge_setting_indicate_delay_time(uint32_t ms);

extern void draw_edit_discharge_setting_indicate_delay_time(uint32_t ms);

#define CHANNEL_SETTING_CAPTION_LEFT    MODE_CAPTION_LEFT
#define CHANNEL_SETTING_CAPTION_TOP     MODE_CAPTION_TOP

/* channel setting */
extern void draw_channel_setting_menu(void);
extern void draw_channel_setting_option(OPTION_ON_OFF  on_off[CHANNEL_COUNT], CHANNEL_STATUS status[CHANNEL_COUNT]);

extern void draw_normal_channel_option(int channel, OPTION_ON_OFF on_off);
extern void draw_focus_channel_option(int channel, OPTION_ON_OFF on_off);
extern void draw_edit_channel_option(int channel, OPTION_ON_OFF on_off);

/* factory mode menu */
#define FACTORY_CAPTION_LEFT                 CC_SETTING_CAPTION_LEFT
#define FACTORY_CAPTION_TOP                  CC_SETTING_CAPTION_TOP

#define FACTORY_MENU_ITEM_LEFT               330
#define FACTORY_MENU_ITEM_TOP_ADJUST         130
#define FACTORY_MENU_ITEM_TOP_PRIVILEGE      (FACTORY_MENU_ITEM_TOP_ADJUST + 80)
#define FACTORY_MENU_ITEM_TOP_LIFE           (FACTORY_MENU_ITEM_TOP_PRIVILEGE + 80)
#define FACTORY_MENU_ITEM_TOP_PHONE          (FACTORY_MENU_ITEM_TOP_LIFE + 80)

extern void draw_factory_menu(void);

extern void draw_normal_factory_item_adjust(void);
extern void draw_focus_factory_item_adjust(void);

extern void draw_normal_factory_item_privilege(void);
extern void draw_focus_factory_item_privilege(void);

extern void draw_normal_factory_item_life(void);
extern void draw_focus_factory_item_life(void);

extern void draw_normal_factory_item_phone(void);
extern void draw_focus_factory_item_phone(void);


/* device adjust menu */
#define DEVICE_ADJUST_CAPTION_LEFT          80
#define DEVICE_ADJUST_CAPTION_TOP           CC_SETTING_CAPTION_TOP

#define DEVICE_ADJUST_CHANNEL_LEFT          145

#define VOLTAGE_ADJUST_LEFT                 150
#define VOLTAGE_ADJUST_TOP                  80

#define DEVICE_MEASURE_VOLTAGE_LEFT         150
#define DEVICE_MEASURE_VOLTAGE_TOP          130

#define DEVICE_ADJUSTED_VOLTAGE_LEFT        150
#define DEVICE_ADJUSTED_VOLTAGE_TOP         180

#define ACTUAL_VOLTAGE_LEFT                 150
#define ACTUAL_VOLTAGE_TOP                  230

#define CURRENT_ADJUST_LEFT                 150
#define CURRENT_ADJUST_TOP                  280

#define DEVICE_MEASURE_CURRENT_LEFT         150
#define DEVICE_MEASURE_CURRENT_TOP          330

#define DEVICE_ADJUSTED_CURRENT_LEFT        150
#define DEVICE_ADJUSTED_CURRENT_TOP         380

#define ACTUAL_CURRENT_LEFT                 150
#define ACTUAL_CURRENT_TOP                  430

#define DEVICE_ADJUST_COLON_LEFT            450

#define DEVICE_ADJUST_UNIT_LEFT             650

#define DEVICE_MEASURE_VOLTAGE_VAL_LEFT     500

#define DEVICE_EDIT_ACTUAL_VOLTAGE_LEFT     500

#define DEVICE_MEASURE_CURRENT_VAL_LEFT     500

#define DEVICE_EDIT_ACTUAL_CURRENT_VAL_LEFT 500

extern void draw_device_adjust_menu(void);

extern void draw_normal_device_adjust_channel(uint32_t channel);
extern void draw_focus_device_adjust_channel(uint32_t channel);
extern void draw_edit_device_adjust_channel(uint32_t channel);

extern void draw_device_adjust_measure_voltage(uint32_t mV);
extern void draw_device_adjusted_voltage(uint32_t mV);

extern void draw_normal_device_adjust_actual_voltage(uint32_t mV);
extern void draw_focus_device_adjust_actual_voltage(uint32_t mV);
extern void draw_edit_device_adjust_actual_voltage(uint32_t mV);

extern void draw_device_adjust_measure_current(uint32_t mA);
extern void draw_device_adjusted_current(uint32_t mA);

extern void draw_normal_device_adjust_actual_current(uint32_t mA);
extern void draw_focus_device_adjust_actual_current(uint32_t mA);
extern void draw_edit_device_adjust_actual_current(uint32_t mA);


/* device privilege menu */
#define DEVICE_PRIVILEGE_CAPTION_LEFT       CC_SETTING_CAPTION_LEFT
#define DEVICE_PRIVILEGE_CAPTION_TOP        CC_SETTING_CAPTION_TOP

#define DEVICE_PRIVILEGE_COLON_LEFT         560

#define QC20_ON_OFF_LEFT                    150
#define QC20_ON_OFF_TOP                     200

#define MTK_ON_OFF_LEFT                     150
#define MTK_ON_OFF_TOP                      300

#define QC20_EDIT_ON_OFF_LEFT               610
#define MTK_EDIT_ON_OFF_LEFT                610

extern void draw_device_privilege_menu(void);

extern void draw_normal_QC20_item(OPTION_ON_OFF on_off);

extern void draw_focus_QC20_item(OPTION_ON_OFF on_off);

extern void draw_edit_QC20_item(OPTION_ON_OFF on_off);

extern void draw_normal_MTK_item(OPTION_ON_OFF on_off);

extern void draw_focus_MTK_item(OPTION_ON_OFF on_off);

extern void draw_edit_MTK_item(OPTION_ON_OFF on_off);

/* life limit menu */
#define LIFE_LIMIT_CAPTION_LEFT             CC_SETTING_CAPTION_LEFT
#define LIFE_LIMIT_CAPTION_TOP              CC_SETTING_CAPTION_TOP

#define LIFE_COUNT_SETTING_LEFT             190
#define LIFE_COUNT_SETTING_TOP              180
      
#define LIFE_ACTUAL_COUNT_LEFT              190
#define LIFE_ACTUAL_COUNT_TOP               280

#define LIFE_LIMIT_SETTING_COLON_LEFT       490

#define LIFE_LIMIT_SETTING_UNIT_LEFT        640

#define LIFE_COUNT_SETTING_EDIT_LEFT        530
#define LIFE_ACTUAL_COUNT_VAL_LEFT          530

#define LIFE_LIMIT_REMINDER_LEFT            450
#define LIFE_LIMIT_REMINDER_TOP             380

extern void draw_life_limit_menu(void);

extern void draw_normal_life_count_setting_item(uint32_t integer);

extern void draw_focus_life_count_setting_item(uint32_t integer);

extern void enter_edit_life_count_setting_item(uint32_t integer);

extern uint32_t get_edit_life_count_setting_item(void);

extern void increase_edit_life_count_setting_digit(void);

extern void decrease_edit_life_count_setting_digit(void);

extern void move_prev_edit_life_count_setting_digit(void);

extern void move_next_edit_life_count_setting_digit(void);

extern void draw_normal_life_actual_count_item(uint32_t integer);

/* phone setting menu */
#define PHONE_SETTING_CAPTION_LEFT          CC_SETTING_CAPTION_LEFT
#define PHONE_SETTING_CAPTION_TOP           CC_SETTING_CAPTION_TOP

#define PHONE_SETTING_DEFAULT_NUMBER_LEFT   100
#define PHONE_SETTING_DEFAULT_NUMBER_TOP    100
      
#define PHONE_SETTING_CUSTOMER_NUMBER_LEFT  100
#define PHONE_SETTING_CUSTOMER_NUMBER_TOP   180

#define PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_LEFT  100
#define PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_TOP   260

#define PHONE_SETTING_ACTUAL_POWER_ON_COUNT_LEFT 100
#define PHONE_SETTING_ACTUAL_POWER_ON_COUNT_TOP  340

#define PHONE_SETTING_COLON_LEFT            490

#define PHONE_SETTING_UNIT_LEFT             640

#define PHONE_SETTING_DEFAULT_NUMBER_EDIT_LEFT  530
#define PHONE_SETTING_CUSTOMER_NUMBER_EDIT_LEFT 530
#define PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_EDIT_LEFT  530
#define PHONE_SETTING_ACTUAL_POWER_ON_COUNT_VAL_LEFT  530

#define PHONE_SETTING_REMINDER_LEFT         450
#define PHONE_SETTING_REMINDER_TOP          420

extern void draw_phone_setting_menu(void);

extern void draw_normal_phone_setting_default_number(const PHONE_NUMBER *phone_number);
extern void draw_focus_phone_setting_default_number(const PHONE_NUMBER *phone_number);

extern void enter_edit_phone_setting_default_number(const PHONE_NUMBER *phone_number);
extern void get_edit_phone_setting_default_number(PHONE_NUMBER *phone_number);
extern void increase_edit_phone_setting_default_number_digit(void);
extern void decrease_edit_phone_setting_default_number_digit(void);
extern void move_prev_edit_phone_setting_default_number_digit(void);
extern void move_next_edit_phone_setting_default_number_digit(void);

extern void draw_normal_phone_setting_customer_number(const PHONE_NUMBER *phone_number);
extern void draw_focus_phone_setting_customer_number(const PHONE_NUMBER *phone_number);

extern void enter_edit_phone_setting_customer_number(const PHONE_NUMBER *phone_number);
extern void get_edit_phone_setting_customer_number(PHONE_NUMBER *phone_number);
extern void increase_edit_phone_setting_customer_number_digit(void);
extern void decrease_edit_phone_setting_customer_number_digit(void);
extern void move_prev_edit_phone_setting_customer_number_digit(void);
extern void move_next_edit_phone_setting_customer_number_digit(void);

extern void draw_normal_phone_setting_customer_power_on_limit(uint32_t integer);
extern void draw_focus_phone_setting_customer_power_on_limit(uint32_t integer);

extern void enter_edit_phone_setting_customer_power_on_limit(uint32_t integer);
extern uint16_t get_edit_phone_setting_customer_power_on_limit(void);
extern void increase_edit_phone_setting_customer_power_on_limit_digit(void);
extern void decrease_edit_phone_setting_customer_power_on_limit_digit(void);
extern void move_prev_edit_phone_setting_customer_power_on_limit_digit(void);
extern void move_next_edit_phone_setting_customer_power_on_limit_digit(void);

extern void draw_normal_phone_setting_actual_customer_power_on_count(uint32_t integer);

#endif
