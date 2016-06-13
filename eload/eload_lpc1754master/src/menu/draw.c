#include <stdint.h>
#include "rtthread.h"
#include "type.h"

#include "utility.h"

#include "menu_string.h"
#include "draw.h"

#include "lcd.h"

/* picture id */
#define PIC_ID_WELCOME        1

#define PIC_ID_OK             2

#define PIC_ID_FAIL           3

/* picture size */
#define PIC_RESULT_WIDTH      45

#define PIC_RESULT_HEIGHT     45

/* welcome */
void draw_welcome_menu(void)
{	
	lcd_clear(SCREEN_BACK_COLOR);
	
	lcd_display_pic(WELCOME_PIC_LEFT, WELCOME_PIC_TOP, PIC_ID_WELCOME);
	
	lcd_display_string(WELCOME_STR_LEFT, WELCOME_STR_TOP, str_welcome, RDONLY_FORE_COLOR, FONT_64);
}

/* main menu */
void draw_normal_main_item_cv_mode(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(MAIN_MENU_ITEM_LEFT, MAIN_MENU_ITEM_TOP_CV, str_cv_mode, RDONLY_FORE_COLOR, FONT_64);
}

void draw_focus_main_item_cv_mode(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(MAIN_MENU_ITEM_LEFT, MAIN_MENU_ITEM_TOP_CV, str_cv_mode, RDONLY_FORE_COLOR, FONT_64);
}

void draw_normal_main_item_cc_mode(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(MAIN_MENU_ITEM_LEFT, MAIN_MENU_ITEM_TOP_CC, str_cc_mode, RDONLY_FORE_COLOR, FONT_64);
}

void draw_focus_main_item_cc_mode(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(MAIN_MENU_ITEM_LEFT, MAIN_MENU_ITEM_TOP_CC, str_cc_mode, RDONLY_FORE_COLOR, FONT_64);
}

void draw_normal_main_item_cr_mode(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(MAIN_MENU_ITEM_LEFT, MAIN_MENU_ITEM_TOP_CR, str_cr_mode, RDONLY_FORE_COLOR, FONT_64);
}

void draw_focus_main_item_cr_mode(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(MAIN_MENU_ITEM_LEFT, MAIN_MENU_ITEM_TOP_CR, str_cr_mode, RDONLY_FORE_COLOR, FONT_64);
}

void draw_normal_main_item_synth_test(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(MAIN_MENU_ITEM_LEFT, MAIN_MENU_ITEM_TOP_SYNTH, str_synth_test, RDONLY_FORE_COLOR, FONT_64);
}

void draw_focus_main_item_synth_test(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(MAIN_MENU_ITEM_LEFT, MAIN_MENU_ITEM_TOP_SYNTH, str_synth_test, RDONLY_FORE_COLOR, FONT_64);
}

void draw_normal_main_item_channel_set(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(MAIN_MENU_ITEM_LEFT, MAIN_MENU_ITEM_TOP_CHANNEL, str_channel_set, RDONLY_FORE_COLOR, FONT_64);
}

void draw_focus_main_item_channel_set(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(MAIN_MENU_ITEM_LEFT, MAIN_MENU_ITEM_TOP_CHANNEL, str_channel_set, RDONLY_FORE_COLOR, FONT_64);
}


void draw_main_items(void)
{
	draw_normal_main_item_synth_test();
	
	draw_normal_main_item_cv_mode();

	draw_normal_main_item_cc_mode();

	draw_normal_main_item_cr_mode();

	draw_normal_main_item_channel_set();
}

#define ASCII_FONT_24_WIDTH    10

#define ASCII_FONT_32_WIDTH    12

#define ASCII_FONT_48_WIDTH    24

#define ASCII_FONT_64_WIDTH    32

static uint16_t get_font_width(lcd_font font)
{
	uint16_t width;
	
	switch (font)
	{
	case FONT_24:
		width = ASCII_FONT_24_WIDTH;
	
		break;
	
	case FONT_32:
		width = ASCII_FONT_32_WIDTH;
	
		break;
	
	case FONT_48:
		width = ASCII_FONT_48_WIDTH;
		
		break;
	
	case FONT_64:
		width = ASCII_FONT_64_WIDTH;
	
		break;
	
	default:
		width = 0;
	
		break;
	}
	
	return width;
}

static const char *const s_synth_test_type_name[] = 
{
	[SYNTH_TEST_EMPTY_LOAD]   = str_empty_load_test,
	
	[SYNTH_TEST_CV]           = str_cv_test,
	
	[SYNTH_TEST_CC]           = str_cc_test,
	
	[SYNTH_TEST_CR]           = str_cr_test,
	
	[SYNTH_TEST_OVER_CURRENT] = str_over_current_test,
	
	[SYNTH_TEST_SHORT]        = str_short_test,
	
	[SYNTH_TEST_DISCHARGE]    = str_discharge_test
};

static const char *const s_qc_20_test_type_name[] = 
{
	[QC_20_TEST_EMPTY_LOAD]   = str_empty_load_test,
	
	[QC_20_5V_TEST_CV]        = str_5v_cv_test,
	
	[QC_20_5V_TEST_CC]        = str_5v_cc_test,
	
	[QC_20_5V_TEST_CR]        = str_5v_cr_test,
	
	[QC_20_5V_TEST_OVER_CURRENT] = str_5v_over_current_test,
	
	[QC_20_5V_TEST_SHORT]     = str_5v_short_test,

	[QC_20_9V_TEST_CV]        = str_9v_cv_test,
	
	[QC_20_9V_TEST_CC]        = str_9v_cc_test,
	
	[QC_20_9V_TEST_CR]        = str_9v_cr_test,
	
	[QC_20_9V_TEST_OVER_CURRENT] = str_9v_over_current_test,
	
	[QC_20_9V_TEST_SHORT]     = str_9v_short_test,

	[QC_20_12V_TEST_CV]        = str_12v_cv_test,
	
	[QC_20_12V_TEST_CC]        = str_12v_cc_test,
	
	[QC_20_12V_TEST_CR]        = str_12v_cr_test,
	
	[QC_20_12V_TEST_OVER_CURRENT] = str_12v_over_current_test,
	
	[QC_20_12V_TEST_SHORT]     = str_12v_short_test,

	[QC_20_20V_TEST_CV]        = str_20v_cv_test,
	
	[QC_20_20V_TEST_CC]        = str_20v_cc_test,
	
	[QC_20_20V_TEST_CR]        = str_20v_cr_test,
	
	[QC_20_20V_TEST_OVER_CURRENT] = str_20v_over_current_test,
	
	[QC_20_20V_TEST_SHORT]     = str_20v_short_test,
	
	[QC_20_TEST_DISCHARGE]    = str_discharge_test
};

static const char *const s_mtk_test_type_name[] = 
{
	[MTK_TEST_EMPTY_LOAD]   = str_empty_load_test,
	
	[MTK_5V_TEST_CV]        = str_5v_cv_test,
	
	[MTK_5V_TEST_CC]        = str_5v_cc_test,
	
	[MTK_5V_TEST_CR]        = str_5v_cr_test,
	
	[MTK_5V_TEST_OVER_CURRENT] = str_5v_over_current_test,
	
	[MTK_5V_TEST_SHORT]     = str_5v_short_test,

	[MTK_9V_TEST_CV]        = str_9v_cv_test,
	
	[MTK_9V_TEST_CC]        = str_9v_cc_test,
	
	[MTK_9V_TEST_CR]        = str_9v_cr_test,
	
	[MTK_9V_TEST_OVER_CURRENT] = str_9v_over_current_test,
	
	[MTK_9V_TEST_SHORT]     = str_9v_short_test,

	[MTK_12V_TEST_CV]        = str_12v_cv_test,
	
	[MTK_12V_TEST_CC]        = str_12v_cc_test,
	
	[MTK_12V_TEST_CR]        = str_12v_cr_test,
	
	[MTK_12V_TEST_OVER_CURRENT] = str_12v_over_current_test,
	
	[MTK_12V_TEST_SHORT]     = str_12v_short_test,

	[MTK_20V_TEST_CV]        = str_20v_cv_test,
	
	[MTK_20V_TEST_CC]        = str_20v_cc_test,
	
	[MTK_20V_TEST_CR]        = str_20v_cr_test,
	
	[MTK_20V_TEST_OVER_CURRENT] = str_20v_over_current_test,
	
	[MTK_20V_TEST_SHORT]     = str_20v_short_test,
	
	[MTK_TEST_DISCHARGE]    = str_discharge_test
};

static const char *const s_OPTION_ON_OFF_name[] = 
{
	[OPTION_ON]  = str_on,
	
	[OPTION_OFF] = str_off
};

void draw_synth_test_setting_caption(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	/* caption */
	lcd_display_string(SYNTH_TEST_SETTING_CAPTION_LEFT, SYNTH_TEST_SETTING_CAPTION_TOP, str_synth_test_group, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_test_setting_caption(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	/* caption */
	lcd_display_string(SYNTH_TEST_SETTING_CAPTION_LEFT, SYNTH_TEST_SETTING_CAPTION_TOP, str_qc_20_test_group, CAPTION_COLOR, FONT_64);
}

void draw_test_setting_menu_const(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	/* test */
	lcd_display_string(SYNTH_TEST_LEFT, SYNTH_TEST_TOP, str_test, EDITABLE_FORE_COLOR, FONT_48);
	
	/* bind line */
	lcd_draw_rectangle(SYNTH_TEST_BIND_LEFT, SYNTH_TEST_BIND_TOP, SYNTH_TEST_BIND_RIGHT, SYNTH_TEST_BIND_BOTTOM, RDONLY_FORE_COLOR);
	lcd_draw_line(SYNTH_TEST_BIND_LEFT, SYNTH_TEST_BIND_HORZ_1_TOP, SYNTH_TEST_BIND_RIGHT, SYNTH_TEST_BIND_HORZ_1_TOP, RDONLY_FORE_COLOR);
	lcd_draw_line(SYNTH_TEST_BIND_LEFT, SYNTH_TEST_BIND_HORZ_2_TOP, SYNTH_TEST_BIND_RIGHT, SYNTH_TEST_BIND_HORZ_2_TOP, RDONLY_FORE_COLOR);
	lcd_draw_line(SYNTH_TEST_BIND_LEFT, SYNTH_TEST_BIND_HORZ_3_TOP, SYNTH_TEST_BIND_RIGHT, SYNTH_TEST_BIND_HORZ_3_TOP, RDONLY_FORE_COLOR);
	
	lcd_draw_line(SYNTH_TEST_BIND_VERT_LEFT, SYNTH_TEST_BIND_TOP, SYNTH_TEST_BIND_VERT_LEFT, SYNTH_TEST_BIND_BOTTOM, RDONLY_FORE_COLOR);
	
	/* first step */
	lcd_display_string(SYNTH_TEST_ITEM_1_STEP_LEFT, SYNTH_TEST_ITEM_1_STEP_TOP, str_first_step, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_1_TYPE_LEFT, SYNTH_TEST_ITEM_1_TYPE_TOP, str_empty_load_test, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_1_ON_OFF_LEFT, SYNTH_TEST_ITEM_1_ON_OFF_TOP, str_on, RDONLY_FORE_COLOR, FONT_32);
	lcd_display_string(SYNTH_TEST_ITEM_1_SETTING_LEFT, SYNTH_TEST_ITEM_1_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
	
	/* second step */
	lcd_display_string(SYNTH_TEST_ITEM_2_STEP_LEFT, SYNTH_TEST_ITEM_2_STEP_TOP, str_second_step, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_2_SETTING_LEFT, SYNTH_TEST_ITEM_2_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);

	/* third step */
	lcd_display_string(SYNTH_TEST_ITEM_3_STEP_LEFT, SYNTH_TEST_ITEM_3_STEP_TOP, str_third_step, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_3_SETTING_LEFT, SYNTH_TEST_ITEM_3_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
	
	/* forth step */
	lcd_display_string(SYNTH_TEST_ITEM_4_STEP_LEFT, SYNTH_TEST_ITEM_4_STEP_TOP, str_forth_step, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_4_SETTING_LEFT, SYNTH_TEST_ITEM_4_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
	
	/* fifth step */
	lcd_display_string(SYNTH_TEST_ITEM_5_STEP_LEFT, SYNTH_TEST_ITEM_5_STEP_TOP, str_fifth_step, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_5_SETTING_LEFT, SYNTH_TEST_ITEM_5_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
	
	/* sixth step */
	lcd_display_string(SYNTH_TEST_ITEM_6_STEP_LEFT, SYNTH_TEST_ITEM_6_STEP_TOP, str_sixth_step, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_6_SETTING_LEFT, SYNTH_TEST_ITEM_6_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
	
	/* seventh step */
	lcd_display_string(SYNTH_TEST_ITEM_7_STEP_LEFT, SYNTH_TEST_ITEM_7_STEP_TOP, str_seventh_step, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_7_SETTING_LEFT, SYNTH_TEST_ITEM_7_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
	
	/* eighth step */
	lcd_display_string(SYNTH_TEST_ITEM_8_STEP_LEFT, SYNTH_TEST_ITEM_8_STEP_TOP, str_eighth_step, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_8_TYPE_LEFT, SYNTH_TEST_ITEM_8_TYPE_TOP, str_discharge_test, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_8_SETTING_LEFT, SYNTH_TEST_ITEM_8_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_setting_menu(const SYNTH_TEST_SETTING *synth_test_setting)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	/* second step */
	lcd_display_string(SYNTH_TEST_ITEM_2_TYPE_LEFT, SYNTH_TEST_ITEM_2_TYPE_TOP, s_synth_test_type_name[synth_test_setting->synth_normal_test_setting[0].test_type], 
						EDITABLE_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_2_ON_OFF_LEFT, SYNTH_TEST_ITEM_2_ON_OFF_TOP, s_OPTION_ON_OFF_name[synth_test_setting->synth_normal_test_setting[0].on_off], 
						EDITABLE_FORE_COLOR, FONT_32);

	/* third step */
	lcd_display_string(SYNTH_TEST_ITEM_3_TYPE_LEFT, SYNTH_TEST_ITEM_3_TYPE_TOP, s_synth_test_type_name[synth_test_setting->synth_normal_test_setting[1].test_type], 
						EDITABLE_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_3_ON_OFF_LEFT, SYNTH_TEST_ITEM_3_ON_OFF_TOP, s_OPTION_ON_OFF_name[synth_test_setting->synth_normal_test_setting[1].on_off], 
						EDITABLE_FORE_COLOR, FONT_32);
	
	/* forth step */
	lcd_display_string(SYNTH_TEST_ITEM_4_TYPE_LEFT, SYNTH_TEST_ITEM_4_TYPE_TOP, s_synth_test_type_name[synth_test_setting->synth_normal_test_setting[2].test_type], 
						EDITABLE_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_4_ON_OFF_LEFT, SYNTH_TEST_ITEM_4_ON_OFF_TOP, s_OPTION_ON_OFF_name[synth_test_setting->synth_normal_test_setting[2].on_off], 
						EDITABLE_FORE_COLOR, FONT_32);

	/* fifth step */
	lcd_display_string(SYNTH_TEST_ITEM_5_TYPE_LEFT, SYNTH_TEST_ITEM_5_TYPE_TOP, s_synth_test_type_name[synth_test_setting->synth_normal_test_setting[3].test_type], 
						EDITABLE_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_5_ON_OFF_LEFT, SYNTH_TEST_ITEM_5_ON_OFF_TOP, s_OPTION_ON_OFF_name[synth_test_setting->synth_normal_test_setting[3].on_off], 
						EDITABLE_FORE_COLOR, FONT_32);

	/* sixth step */
	lcd_display_string(SYNTH_TEST_ITEM_6_TYPE_LEFT, SYNTH_TEST_ITEM_6_TYPE_TOP, s_synth_test_type_name[synth_test_setting->synth_normal_test_setting[4].test_type], 
						EDITABLE_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_6_ON_OFF_LEFT, SYNTH_TEST_ITEM_6_ON_OFF_TOP, s_OPTION_ON_OFF_name[synth_test_setting->synth_normal_test_setting[4].on_off], 
						EDITABLE_FORE_COLOR, FONT_32);

	/* seventh step */
	lcd_display_string(SYNTH_TEST_ITEM_7_TYPE_LEFT, SYNTH_TEST_ITEM_7_TYPE_TOP, s_synth_test_type_name[synth_test_setting->synth_normal_test_setting[5].test_type], 
						EDITABLE_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_7_ON_OFF_LEFT, SYNTH_TEST_ITEM_7_ON_OFF_TOP, s_OPTION_ON_OFF_name[synth_test_setting->synth_normal_test_setting[5].on_off], 
						EDITABLE_FORE_COLOR, FONT_32);

	/* eighth step */
	lcd_display_string(SYNTH_TEST_ITEM_8_ON_OFF_LEFT, SYNTH_TEST_ITEM_8_ON_OFF_TOP, s_OPTION_ON_OFF_name[synth_test_setting->discharge_test_setting.on_off], 
						EDITABLE_FORE_COLOR, FONT_32);	
}

void draw_QC_20_test_setting_menu(const QC_20_TEST_SETTING *qc_20_test_setting)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	/* second step */
	lcd_display_string(SYNTH_TEST_ITEM_2_TYPE_LEFT, SYNTH_TEST_ITEM_2_TYPE_TOP, s_qc_20_test_type_name[qc_20_test_setting->qc_20_normal_test_setting[0].test_type], 
						EDITABLE_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_2_ON_OFF_LEFT, SYNTH_TEST_ITEM_2_ON_OFF_TOP, s_OPTION_ON_OFF_name[qc_20_test_setting->qc_20_normal_test_setting[0].on_off], 
						EDITABLE_FORE_COLOR, FONT_32);

	/* third step */
	lcd_display_string(SYNTH_TEST_ITEM_3_TYPE_LEFT, SYNTH_TEST_ITEM_3_TYPE_TOP, s_qc_20_test_type_name[qc_20_test_setting->qc_20_normal_test_setting[1].test_type], 
						EDITABLE_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_3_ON_OFF_LEFT, SYNTH_TEST_ITEM_3_ON_OFF_TOP, s_OPTION_ON_OFF_name[qc_20_test_setting->qc_20_normal_test_setting[1].on_off], 
						EDITABLE_FORE_COLOR, FONT_32);
	
	/* forth step */
	lcd_display_string(SYNTH_TEST_ITEM_4_TYPE_LEFT, SYNTH_TEST_ITEM_4_TYPE_TOP, s_qc_20_test_type_name[qc_20_test_setting->qc_20_normal_test_setting[2].test_type], 
						EDITABLE_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_4_ON_OFF_LEFT, SYNTH_TEST_ITEM_4_ON_OFF_TOP, s_OPTION_ON_OFF_name[qc_20_test_setting->qc_20_normal_test_setting[2].on_off], 
						EDITABLE_FORE_COLOR, FONT_32);

	/* fifth step */
	lcd_display_string(SYNTH_TEST_ITEM_5_TYPE_LEFT, SYNTH_TEST_ITEM_5_TYPE_TOP, s_qc_20_test_type_name[qc_20_test_setting->qc_20_normal_test_setting[3].test_type], 
						EDITABLE_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_5_ON_OFF_LEFT, SYNTH_TEST_ITEM_5_ON_OFF_TOP, s_OPTION_ON_OFF_name[qc_20_test_setting->qc_20_normal_test_setting[3].on_off], 
						EDITABLE_FORE_COLOR, FONT_32);

	/* sixth step */
	lcd_display_string(SYNTH_TEST_ITEM_6_TYPE_LEFT, SYNTH_TEST_ITEM_6_TYPE_TOP, s_qc_20_test_type_name[qc_20_test_setting->qc_20_normal_test_setting[4].test_type], 
						EDITABLE_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_6_ON_OFF_LEFT, SYNTH_TEST_ITEM_6_ON_OFF_TOP, s_OPTION_ON_OFF_name[qc_20_test_setting->qc_20_normal_test_setting[4].on_off], 
						EDITABLE_FORE_COLOR, FONT_32);

	/* seventh step */
	lcd_display_string(SYNTH_TEST_ITEM_7_TYPE_LEFT, SYNTH_TEST_ITEM_7_TYPE_TOP, s_qc_20_test_type_name[qc_20_test_setting->qc_20_normal_test_setting[5].test_type], 
						EDITABLE_FORE_COLOR, FONT_48);
	lcd_display_string(SYNTH_TEST_ITEM_7_ON_OFF_LEFT, SYNTH_TEST_ITEM_7_ON_OFF_TOP, s_OPTION_ON_OFF_name[qc_20_test_setting->qc_20_normal_test_setting[5].on_off], 
						EDITABLE_FORE_COLOR, FONT_32);

	/* eighth step */
	lcd_display_string(SYNTH_TEST_ITEM_8_ON_OFF_LEFT, SYNTH_TEST_ITEM_8_ON_OFF_TOP, s_OPTION_ON_OFF_name[qc_20_test_setting->discharge_test_setting.on_off], 
						EDITABLE_FORE_COLOR, FONT_32);
}

/* draw group */
void draw_normal_test_setting_group(uint32_t group)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(SYNTH_TEST_SETTING_GROUP_LEFT, SYNTH_TEST_SETTING_GROUP_TOP, group, STEP_VAL_INTEGER_LEN, 0, STEP_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_64);	
}

void draw_focus_test_setting_group(uint32_t group)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(SYNTH_TEST_SETTING_GROUP_LEFT, SYNTH_TEST_SETTING_GROUP_TOP, group, STEP_VAL_INTEGER_LEN, 0, STEP_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_64);
}

void draw_edit_test_setting_group(uint32_t group)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(SYNTH_TEST_SETTING_GROUP_LEFT, SYNTH_TEST_SETTING_GROUP_TOP, group, STEP_VAL_INTEGER_LEN, 0, STEP_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_64);
}

void draw_normal_test(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(SYNTH_TEST_LEFT, SYNTH_TEST_TOP, str_test, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_focus_test(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(SYNTH_TEST_LEFT, SYNTH_TEST_TOP, str_test, EDITABLE_FORE_COLOR, FONT_48);
}

/* draw first step */
/* setting */
void draw_normal_test_item_1_setting(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(SYNTH_TEST_ITEM_1_SETTING_LEFT, SYNTH_TEST_ITEM_1_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
}

void draw_focus_test_item_1_setting(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(SYNTH_TEST_ITEM_1_SETTING_LEFT, SYNTH_TEST_ITEM_1_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
}

/* draw second step type */
void draw_normal_synth_item_2_type(SYNTH_TEST_TYPE type)
{
	if (type < SYNTH_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_2_TYPE_LEFT, SYNTH_TEST_ITEM_2_TYPE_TOP, s_synth_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_synth_item_2_type(SYNTH_TEST_TYPE type)
{
	if (type < SYNTH_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_2_TYPE_LEFT, SYNTH_TEST_ITEM_2_TYPE_TOP, s_synth_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_edit_synth_item_2_type(SYNTH_TEST_TYPE type)
{
	if (type < SYNTH_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_2_TYPE_LEFT, SYNTH_TEST_ITEM_2_TYPE_TOP, s_synth_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_normal_qc_20_item_2_type(QC_20_TEST_TYPE type)
{
	if (type < QC_20_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_2_TYPE_LEFT, SYNTH_TEST_ITEM_2_TYPE_TOP, s_qc_20_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_qc_20_item_2_type(QC_20_TEST_TYPE type)
{
	if (type < QC_20_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_2_TYPE_LEFT, SYNTH_TEST_ITEM_2_TYPE_TOP, s_qc_20_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_edit_qc_20_item_2_type(QC_20_TEST_TYPE type)
{
	if (type < QC_20_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_2_TYPE_LEFT, SYNTH_TEST_ITEM_2_TYPE_TOP, s_qc_20_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_normal_mtk_item_2_type(MTK_TEST_TYPE type)
{
	if (type < MTK_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_2_TYPE_LEFT, SYNTH_TEST_ITEM_2_TYPE_TOP, s_mtk_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_mtk_item_2_type(MTK_TEST_TYPE type)
{
	if (type < MTK_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_2_TYPE_LEFT, SYNTH_TEST_ITEM_2_TYPE_TOP, s_mtk_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_edit_mtk_item_2_type(MTK_TEST_TYPE type)
{
	if (type < MTK_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_2_TYPE_LEFT, SYNTH_TEST_ITEM_2_TYPE_TOP, s_mtk_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}


/* draw second step on/off */
void draw_normal_test_item_2_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_2_ON_OFF_LEFT, SYNTH_TEST_ITEM_2_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}
}

void draw_focus_test_item_2_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_2_ON_OFF_LEFT, SYNTH_TEST_ITEM_2_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}	
}

void draw_edit_test_item_2_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_2_ON_OFF_LEFT, SYNTH_TEST_ITEM_2_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}	
}

/* draw second setting */
void draw_normal_test_item_2_setting(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(SYNTH_TEST_ITEM_2_SETTING_LEFT, SYNTH_TEST_ITEM_2_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
}

void draw_focus_test_item_2_setting(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(SYNTH_TEST_ITEM_2_SETTING_LEFT, SYNTH_TEST_ITEM_2_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
}

/* draw third step type */
void draw_normal_synth_item_3_type(SYNTH_TEST_TYPE type)
{
	if (type < SYNTH_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_3_TYPE_LEFT, SYNTH_TEST_ITEM_3_TYPE_TOP, s_synth_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_synth_item_3_type(SYNTH_TEST_TYPE type)
{
	if (type < SYNTH_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_3_TYPE_LEFT, SYNTH_TEST_ITEM_3_TYPE_TOP, s_synth_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_edit_synth_item_3_type(SYNTH_TEST_TYPE type)
{
	if (type < SYNTH_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_3_TYPE_LEFT, SYNTH_TEST_ITEM_3_TYPE_TOP, s_synth_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_normal_qc_20_item_3_type(QC_20_TEST_TYPE type)
{
	if (type < QC_20_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_3_TYPE_LEFT, SYNTH_TEST_ITEM_3_TYPE_TOP, s_qc_20_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_qc_20_item_3_type(QC_20_TEST_TYPE type)
{
	if (type < QC_20_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_3_TYPE_LEFT, SYNTH_TEST_ITEM_3_TYPE_TOP, s_qc_20_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_edit_qc_20_item_3_type(QC_20_TEST_TYPE type)
{
	if (type < QC_20_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_3_TYPE_LEFT, SYNTH_TEST_ITEM_3_TYPE_TOP, s_qc_20_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_normal_mtk_item_3_type(MTK_TEST_TYPE type)
{
	if (type < MTK_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_3_TYPE_LEFT, SYNTH_TEST_ITEM_3_TYPE_TOP, s_mtk_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_mtk_item_3_type(MTK_TEST_TYPE type)
{
	if (type < MTK_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_3_TYPE_LEFT, SYNTH_TEST_ITEM_3_TYPE_TOP, s_mtk_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_edit_mtk_item_3_type(MTK_TEST_TYPE type)
{
	if (type < MTK_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_3_TYPE_LEFT, SYNTH_TEST_ITEM_3_TYPE_TOP, s_mtk_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

/* draw third step on/off */
void draw_normal_test_item_3_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_3_ON_OFF_LEFT, SYNTH_TEST_ITEM_3_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}
}

void draw_focus_test_item_3_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_3_ON_OFF_LEFT, SYNTH_TEST_ITEM_3_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}	
}

void draw_edit_test_item_3_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_3_ON_OFF_LEFT, SYNTH_TEST_ITEM_3_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}	
}

/* draw third setting */
void draw_normal_test_item_3_setting(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(SYNTH_TEST_ITEM_3_SETTING_LEFT, SYNTH_TEST_ITEM_3_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
}

void draw_focus_test_item_3_setting(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(SYNTH_TEST_ITEM_3_SETTING_LEFT, SYNTH_TEST_ITEM_3_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
}

/* draw forth step type */
void draw_normal_synth_item_4_type(SYNTH_TEST_TYPE type)
{
	if (type < SYNTH_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_4_TYPE_LEFT, SYNTH_TEST_ITEM_4_TYPE_TOP, s_synth_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_synth_item_4_type(SYNTH_TEST_TYPE type)
{
	if (type < SYNTH_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_4_TYPE_LEFT, SYNTH_TEST_ITEM_4_TYPE_TOP, s_synth_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_edit_synth_item_4_type(SYNTH_TEST_TYPE type)
{
	if (type < SYNTH_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_4_TYPE_LEFT, SYNTH_TEST_ITEM_4_TYPE_TOP, s_synth_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_normal_qc_20_item_4_type(QC_20_TEST_TYPE type)
{
	if (type < QC_20_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_4_TYPE_LEFT, SYNTH_TEST_ITEM_4_TYPE_TOP, s_qc_20_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_qc_20_item_4_type(QC_20_TEST_TYPE type)
{
	if (type < QC_20_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_4_TYPE_LEFT, SYNTH_TEST_ITEM_4_TYPE_TOP, s_qc_20_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_edit_qc_20_item_4_type(QC_20_TEST_TYPE type)
{
	if (type < QC_20_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_4_TYPE_LEFT, SYNTH_TEST_ITEM_4_TYPE_TOP, s_qc_20_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_normal_mtk_item_4_type(MTK_TEST_TYPE type)
{
	if (type < MTK_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_4_TYPE_LEFT, SYNTH_TEST_ITEM_4_TYPE_TOP, s_mtk_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_mtk_item_4_type(MTK_TEST_TYPE type)
{
	if (type < MTK_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_4_TYPE_LEFT, SYNTH_TEST_ITEM_4_TYPE_TOP, s_mtk_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_edit_mtk_item_4_type(MTK_TEST_TYPE type)
{
	if (type < MTK_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_4_TYPE_LEFT, SYNTH_TEST_ITEM_4_TYPE_TOP, s_mtk_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

/* draw forth step on/off */
void draw_normal_test_item_4_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_4_ON_OFF_LEFT, SYNTH_TEST_ITEM_4_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}
}

void draw_focus_test_item_4_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_4_ON_OFF_LEFT, SYNTH_TEST_ITEM_4_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}	
}

void draw_edit_test_item_4_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_4_ON_OFF_LEFT, SYNTH_TEST_ITEM_4_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}	
}

/* draw forth setting */
void draw_normal_test_item_4_setting(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(SYNTH_TEST_ITEM_4_SETTING_LEFT, SYNTH_TEST_ITEM_4_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
}

void draw_focus_test_item_4_setting(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(SYNTH_TEST_ITEM_4_SETTING_LEFT, SYNTH_TEST_ITEM_4_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
}

/* draw fifth step type */
void draw_normal_synth_item_5_type(SYNTH_TEST_TYPE type)
{
	if (type < SYNTH_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_5_TYPE_LEFT, SYNTH_TEST_ITEM_5_TYPE_TOP, s_synth_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_synth_item_5_type(SYNTH_TEST_TYPE type)
{
	if (type < SYNTH_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_5_TYPE_LEFT, SYNTH_TEST_ITEM_5_TYPE_TOP, s_synth_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_edit_synth_item_5_type(SYNTH_TEST_TYPE type)
{
	if (type < SYNTH_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_5_TYPE_LEFT, SYNTH_TEST_ITEM_5_TYPE_TOP, s_synth_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_normal_qc_20_item_5_type(QC_20_TEST_TYPE type)
{
	if (type < QC_20_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_5_TYPE_LEFT, SYNTH_TEST_ITEM_5_TYPE_TOP, s_qc_20_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_qc_20_item_5_type(QC_20_TEST_TYPE type)
{
	if (type < QC_20_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_5_TYPE_LEFT, SYNTH_TEST_ITEM_5_TYPE_TOP, s_qc_20_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_edit_qc_20_item_5_type(QC_20_TEST_TYPE type)
{
	if (type < QC_20_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_5_TYPE_LEFT, SYNTH_TEST_ITEM_5_TYPE_TOP, s_qc_20_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_normal_mtk_item_5_type(MTK_TEST_TYPE type)
{
	if (type < MTK_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_5_TYPE_LEFT, SYNTH_TEST_ITEM_5_TYPE_TOP, s_mtk_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_mtk_item_5_type(MTK_TEST_TYPE type)
{
	if (type < MTK_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_5_TYPE_LEFT, SYNTH_TEST_ITEM_5_TYPE_TOP, s_mtk_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_edit_mtk_item_5_type(MTK_TEST_TYPE type)
{
	if (type < MTK_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_5_TYPE_LEFT, SYNTH_TEST_ITEM_5_TYPE_TOP, s_mtk_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

/* draw fifth step on/off */
void draw_normal_test_item_5_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_5_ON_OFF_LEFT, SYNTH_TEST_ITEM_5_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}
}

void draw_focus_test_item_5_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_5_ON_OFF_LEFT, SYNTH_TEST_ITEM_5_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}	
}

void draw_edit_test_item_5_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_5_ON_OFF_LEFT, SYNTH_TEST_ITEM_5_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}	
}

/* draw fifth setting */
void draw_normal_test_item_5_setting(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(SYNTH_TEST_ITEM_5_SETTING_LEFT, SYNTH_TEST_ITEM_5_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
}

void draw_focus_test_item_5_setting(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(SYNTH_TEST_ITEM_5_SETTING_LEFT, SYNTH_TEST_ITEM_5_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
}

/* draw sixth step type */
void draw_normal_synth_item_6_type(SYNTH_TEST_TYPE type)
{
	if (type < SYNTH_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_6_TYPE_LEFT, SYNTH_TEST_ITEM_6_TYPE_TOP, s_synth_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_synth_item_6_type(SYNTH_TEST_TYPE type)
{
	if (type < SYNTH_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_6_TYPE_LEFT, SYNTH_TEST_ITEM_6_TYPE_TOP, s_synth_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_edit_synth_item_6_type(SYNTH_TEST_TYPE type)
{
	if (type < SYNTH_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_6_TYPE_LEFT, SYNTH_TEST_ITEM_6_TYPE_TOP, s_synth_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_normal_qc_20_item_6_type(QC_20_TEST_TYPE type)
{
	if (type < QC_20_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_6_TYPE_LEFT, SYNTH_TEST_ITEM_6_TYPE_TOP, s_qc_20_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_qc_20_item_6_type(QC_20_TEST_TYPE type)
{
	if (type < QC_20_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_6_TYPE_LEFT, SYNTH_TEST_ITEM_6_TYPE_TOP, s_qc_20_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_edit_qc_20_item_6_type(QC_20_TEST_TYPE type)
{
	if (type < QC_20_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_6_TYPE_LEFT, SYNTH_TEST_ITEM_6_TYPE_TOP, s_qc_20_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_normal_mtk_item_6_type(MTK_TEST_TYPE type)
{
	if (type < MTK_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_6_TYPE_LEFT, SYNTH_TEST_ITEM_6_TYPE_TOP, s_mtk_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_mtk_item_6_type(MTK_TEST_TYPE type)
{
	if (type < MTK_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_6_TYPE_LEFT, SYNTH_TEST_ITEM_6_TYPE_TOP, s_mtk_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_edit_mtk_item_6_type(MTK_TEST_TYPE type)
{
	if (type < MTK_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_6_TYPE_LEFT, SYNTH_TEST_ITEM_6_TYPE_TOP, s_mtk_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

/* draw sixth step on/off */
void draw_normal_test_item_6_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_6_ON_OFF_LEFT, SYNTH_TEST_ITEM_6_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}
}

void draw_focus_test_item_6_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_6_ON_OFF_LEFT, SYNTH_TEST_ITEM_6_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}	
}

void draw_edit_test_item_6_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_6_ON_OFF_LEFT, SYNTH_TEST_ITEM_6_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}	
}

/* draw sixth setting */
void draw_normal_test_item_6_setting(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(SYNTH_TEST_ITEM_6_SETTING_LEFT, SYNTH_TEST_ITEM_6_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
}

void draw_focus_test_item_6_setting(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(SYNTH_TEST_ITEM_6_SETTING_LEFT, SYNTH_TEST_ITEM_6_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
}

/* draw seventh step type */
void draw_normal_synth_item_7_type(SYNTH_TEST_TYPE type)
{
	if (type < SYNTH_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_7_TYPE_LEFT, SYNTH_TEST_ITEM_7_TYPE_TOP, s_synth_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_synth_item_7_type(SYNTH_TEST_TYPE type)
{
	if (type < SYNTH_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_7_TYPE_LEFT, SYNTH_TEST_ITEM_7_TYPE_TOP, s_synth_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_edit_synth_item_7_type(SYNTH_TEST_TYPE type)
{
	if (type < SYNTH_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_7_TYPE_LEFT, SYNTH_TEST_ITEM_7_TYPE_TOP, s_synth_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_normal_qc_20_item_7_type(QC_20_TEST_TYPE type)
{
	if (type < QC_20_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_7_TYPE_LEFT, SYNTH_TEST_ITEM_7_TYPE_TOP, s_qc_20_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_qc_20_item_7_type(QC_20_TEST_TYPE type)
{
	if (type < QC_20_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_7_TYPE_LEFT, SYNTH_TEST_ITEM_7_TYPE_TOP, s_qc_20_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_edit_qc_20_item_7_type(QC_20_TEST_TYPE type)
{
	if (type < QC_20_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_7_TYPE_LEFT, SYNTH_TEST_ITEM_7_TYPE_TOP, s_qc_20_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_normal_mtk_item_7_type(MTK_TEST_TYPE type)
{
	if (type < MTK_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_7_TYPE_LEFT, SYNTH_TEST_ITEM_7_TYPE_TOP, s_mtk_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_mtk_item_7_type(MTK_TEST_TYPE type)
{
	if (type < MTK_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_7_TYPE_LEFT, SYNTH_TEST_ITEM_7_TYPE_TOP, s_mtk_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_edit_mtk_item_7_type(MTK_TEST_TYPE type)
{
	if (type < MTK_TEST_TYPE_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_7_TYPE_LEFT, SYNTH_TEST_ITEM_7_TYPE_TOP, s_mtk_test_type_name[type], EDITABLE_FORE_COLOR, FONT_48);
	}	
}


/* draw seventh step on/off */
void draw_normal_test_item_7_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_7_ON_OFF_LEFT, SYNTH_TEST_ITEM_7_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}
}

void draw_focus_test_item_7_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_7_ON_OFF_LEFT, SYNTH_TEST_ITEM_7_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}	
}

void draw_edit_test_item_7_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_7_ON_OFF_LEFT, SYNTH_TEST_ITEM_7_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}	
}

/* draw seventh setting */
void draw_normal_test_item_7_setting(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(SYNTH_TEST_ITEM_7_SETTING_LEFT, SYNTH_TEST_ITEM_7_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
}

void draw_focus_test_item_7_setting(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(SYNTH_TEST_ITEM_7_SETTING_LEFT, SYNTH_TEST_ITEM_7_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
}

/* draw eighth step on/off */
void draw_normal_test_item_8_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_8_ON_OFF_LEFT, SYNTH_TEST_ITEM_8_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}
}

void draw_focus_test_item_8_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_8_ON_OFF_LEFT, SYNTH_TEST_ITEM_8_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}	
}

void draw_edit_test_item_8_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(SYNTH_TEST_ITEM_8_ON_OFF_LEFT, SYNTH_TEST_ITEM_8_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_32);
	}	
}

/* draw eighth setting */
void draw_normal_test_item_8_setting(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(SYNTH_TEST_ITEM_8_SETTING_LEFT, SYNTH_TEST_ITEM_8_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
}

void draw_focus_test_item_8_setting(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(SYNTH_TEST_ITEM_8_SETTING_LEFT, SYNTH_TEST_ITEM_8_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_32);
}

/* synth test */
void draw_synth_test_caption(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	/* caption */
	lcd_display_string(SYNTH_TEST_CAPTION_LEFT, SYNTH_TEST_CAPTION_TOP, str_synth_test_group, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_test_caption(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	/* caption */
	lcd_display_string(SYNTH_TEST_CAPTION_LEFT, SYNTH_TEST_CAPTION_TOP, str_qc_20_test_group, CAPTION_COLOR, FONT_64);
}

void draw_test_group(uint32_t group)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(SYNTH_TEST_GROUP_LEFT, SYNTH_TEST_GROUP_TOP, group, STEP_VAL_INTEGER_LEN, 0, STEP_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_64);	
}

void draw_test_menu_const(void)
{
	/* first step */
	lcd_display_string(SYNTH_TEST_ITEM_1_STEP_LEFT, SYNTH_TEST_ITEM_1_STEP_TOP, str_first_step, RDONLY_FORE_COLOR, FONT_32);
	lcd_display_string(SYNTH_TEST_ITEM_1_TYPE_LEFT, SYNTH_TEST_ITEM_1_TYPE_TOP, str_empty_load_test, EDITABLE_FORE_COLOR, FONT_32);

	/* ac */
	lcd_display_string(SYNTH_TEST_ITEM_1_AC_LEFT, SYNTH_TEST_ITEM_1_AC_TOP, str_ac_current, CAPTION_COLOR, FONT_32);
	lcd_display_ascii_char(SYNTH_TEST_ITEM_1_AC_COLON_LEFT, SYNTH_TEST_ITEM_1_AC_TOP, ':', CAPTION_COLOR, FONT_32);
	lcd_display_string(SYNTH_TEST_ITEM_1_AC_UNIT_LEFT, SYNTH_TEST_ITEM_1_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_32);

	/* voltage */
	lcd_display_string(SYNTH_TEST_ITEM_1_VOLTAGE_LEFT, SYNTH_TEST_ITEM_1_VOLTAGE_TOP, str_voltage, CAPTION_COLOR, FONT_32);
	lcd_display_ascii_char(SYNTH_TEST_ITEM_1_VOLTAGE_COLON_LEFT, SYNTH_TEST_ITEM_1_VOLTAGE_TOP, ':', CAPTION_COLOR, FONT_32);
	lcd_display_ascii_char(SYNTH_TEST_ITEM_1_VOLTAGE_UNIT_LEFT, SYNTH_TEST_ITEM_1_VOLTAGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_32);
	
	/* second step */
	lcd_display_string(SYNTH_TEST_ITEM_2_STEP_LEFT, SYNTH_TEST_ITEM_2_STEP_TOP, str_second_step, RDONLY_FORE_COLOR, FONT_32);

	/* third step */
	lcd_display_string(SYNTH_TEST_ITEM_3_STEP_LEFT, SYNTH_TEST_ITEM_3_STEP_TOP, str_third_step, RDONLY_FORE_COLOR, FONT_32);
	
	/* forth step */
	lcd_display_string(SYNTH_TEST_ITEM_4_STEP_LEFT, SYNTH_TEST_ITEM_4_STEP_TOP, str_forth_step, RDONLY_FORE_COLOR, FONT_32);
	
	/* fifth step */
	lcd_display_string(SYNTH_TEST_ITEM_5_STEP_LEFT, SYNTH_TEST_ITEM_5_STEP_TOP, str_fifth_step, RDONLY_FORE_COLOR, FONT_32);
	
	/* sixth step */
	lcd_display_string(SYNTH_TEST_ITEM_6_STEP_LEFT, SYNTH_TEST_ITEM_6_STEP_TOP, str_sixth_step, RDONLY_FORE_COLOR, FONT_32);
	
	/* seventh step */
	lcd_display_string(SYNTH_TEST_ITEM_7_STEP_LEFT, SYNTH_TEST_ITEM_7_STEP_TOP, str_seventh_step, RDONLY_FORE_COLOR, FONT_32);
	
	/* eighth step */
	lcd_display_string(SYNTH_TEST_ITEM_8_STEP_LEFT, SYNTH_TEST_ITEM_8_STEP_TOP, str_eighth_step, RDONLY_FORE_COLOR, FONT_32);
	lcd_display_string(SYNTH_TEST_ITEM_8_TYPE_LEFT, SYNTH_TEST_ITEM_8_TYPE_TOP, str_discharge_test, EDITABLE_FORE_COLOR, FONT_32);

}

static void draw_synth_test_item_2(const SYNTH_NORMAL_TEST_SETTING *synth_normal_test_setting)
{
	if (synth_normal_test_setting->on_off == OPTION_ON)
	{
		/* ac */
		lcd_display_string(SYNTH_TEST_ITEM_2_AC_LEFT, SYNTH_TEST_ITEM_2_AC_TOP, str_ac_current, CAPTION_COLOR, FONT_32);
		lcd_display_ascii_char(SYNTH_TEST_ITEM_2_AC_COLON_LEFT, SYNTH_TEST_ITEM_2_AC_TOP, ':', CAPTION_COLOR, FONT_32);
		lcd_display_string(SYNTH_TEST_ITEM_2_AC_UNIT_LEFT, SYNTH_TEST_ITEM_2_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_32);
		
		switch (synth_normal_test_setting->test_type)
		{
		case SYNTH_TEST_CV:

		case SYNTH_TEST_CC:

		case SYNTH_TEST_CR:
			/* voltage */
			lcd_display_string(SYNTH_TEST_ITEM_2_VOLTAGE_LEFT, SYNTH_TEST_ITEM_2_VOLTAGE_TOP, str_voltage, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_2_VOLTAGE_COLON_LEFT, SYNTH_TEST_ITEM_2_VOLTAGE_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_2_VOLTAGE_UNIT_LEFT, SYNTH_TEST_ITEM_2_VOLTAGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_32);

			/* current */
			lcd_display_string(SYNTH_TEST_ITEM_2_CURRENT_LEFT, SYNTH_TEST_ITEM_2_CURRENT_TOP, str_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_2_CURRENT_COLON_LEFT, SYNTH_TEST_ITEM_2_CURRENT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_2_CURRENT_UNIT_LEFT, SYNTH_TEST_ITEM_2_CURRENT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case SYNTH_TEST_OVER_CURRENT:
			/* over current */
			lcd_display_string(SYNTH_TEST_ITEM_2_OC_LEFT, SYNTH_TEST_ITEM_2_OC_TOP, str_over_current_val, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_2_OC_COLON_LEFT, SYNTH_TEST_ITEM_2_OC_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_2_OC_UNIT_LEFT, SYNTH_TEST_ITEM_2_OC_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case SYNTH_TEST_SHORT:
			/* short current */
			lcd_display_string(SYNTH_TEST_ITEM_2_SHORT_LEFT, SYNTH_TEST_ITEM_2_SHORT_TOP, str_short_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_2_SHORT_COLON_LEFT, SYNTH_TEST_ITEM_2_SHORT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_2_SHORT_UNIT_LEFT, SYNTH_TEST_ITEM_2_SHORT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		default:
			break;
		}
	}
	else
	{
		lcd_display_string(SYNTH_TEST_ITEM_2_AC_LEFT, SYNTH_TEST_ITEM_2_AC_TOP, str_off, CAPTION_COLOR, FONT_32);
	}
	
}

static void draw_synth_test_item_3(const SYNTH_NORMAL_TEST_SETTING *synth_normal_test_setting)
{
	if (synth_normal_test_setting->on_off == OPTION_ON)
	{
		/* ac */
		lcd_display_string(SYNTH_TEST_ITEM_3_AC_LEFT, SYNTH_TEST_ITEM_3_AC_TOP, str_ac_current, CAPTION_COLOR, FONT_32);
		lcd_display_ascii_char(SYNTH_TEST_ITEM_3_AC_COLON_LEFT, SYNTH_TEST_ITEM_3_AC_TOP, ':', CAPTION_COLOR, FONT_32);
		lcd_display_string(SYNTH_TEST_ITEM_3_AC_UNIT_LEFT, SYNTH_TEST_ITEM_3_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_32);
			
		switch (synth_normal_test_setting->test_type)
		{
		case SYNTH_TEST_CV:

		case SYNTH_TEST_CC:

		case SYNTH_TEST_CR:
			/* voltage */
			lcd_display_string(SYNTH_TEST_ITEM_3_VOLTAGE_LEFT, SYNTH_TEST_ITEM_3_VOLTAGE_TOP, str_voltage, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_3_VOLTAGE_COLON_LEFT, SYNTH_TEST_ITEM_3_VOLTAGE_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_3_VOLTAGE_UNIT_LEFT, SYNTH_TEST_ITEM_3_VOLTAGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_32);
		
			/* current */
			lcd_display_string(SYNTH_TEST_ITEM_3_CURRENT_LEFT, SYNTH_TEST_ITEM_3_CURRENT_TOP, str_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_3_CURRENT_COLON_LEFT, SYNTH_TEST_ITEM_3_CURRENT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_3_CURRENT_UNIT_LEFT, SYNTH_TEST_ITEM_3_CURRENT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);

			break;

		case SYNTH_TEST_OVER_CURRENT:
			/* over current */
			lcd_display_string(SYNTH_TEST_ITEM_3_OC_LEFT, SYNTH_TEST_ITEM_3_OC_TOP, str_over_current_val, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_3_OC_COLON_LEFT, SYNTH_TEST_ITEM_3_OC_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_3_OC_UNIT_LEFT, SYNTH_TEST_ITEM_3_OC_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case SYNTH_TEST_SHORT:
			/* short current */
			lcd_display_string(SYNTH_TEST_ITEM_3_SHORT_LEFT, SYNTH_TEST_ITEM_3_SHORT_TOP, str_short_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_3_SHORT_COLON_LEFT, SYNTH_TEST_ITEM_3_SHORT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_3_SHORT_UNIT_LEFT, SYNTH_TEST_ITEM_3_SHORT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		default:
			break;
		}

	}
	else
	{
		lcd_display_string(SYNTH_TEST_ITEM_3_AC_LEFT, SYNTH_TEST_ITEM_3_AC_TOP, str_off, CAPTION_COLOR, FONT_32);
	}
}

static void draw_synth_test_item_4(const SYNTH_NORMAL_TEST_SETTING *synth_normal_test_setting)
{
	if (synth_normal_test_setting->on_off == OPTION_ON)
	{
		/* ac */
		lcd_display_string(SYNTH_TEST_ITEM_4_AC_LEFT, SYNTH_TEST_ITEM_4_AC_TOP, str_ac_current, CAPTION_COLOR, FONT_32);
		lcd_display_ascii_char(SYNTH_TEST_ITEM_4_AC_COLON_LEFT, SYNTH_TEST_ITEM_4_AC_TOP, ':', CAPTION_COLOR, FONT_32);
		lcd_display_string(SYNTH_TEST_ITEM_4_AC_UNIT_LEFT, SYNTH_TEST_ITEM_4_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_32);
			
		switch (synth_normal_test_setting->test_type)
		{
		case SYNTH_TEST_CV:

		case SYNTH_TEST_CC:

		case SYNTH_TEST_CR:
			/* voltage */
			lcd_display_string(SYNTH_TEST_ITEM_4_VOLTAGE_LEFT, SYNTH_TEST_ITEM_4_VOLTAGE_TOP, str_voltage, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_4_VOLTAGE_COLON_LEFT, SYNTH_TEST_ITEM_4_VOLTAGE_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_4_VOLTAGE_UNIT_LEFT, SYNTH_TEST_ITEM_4_VOLTAGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_32);

			/* current */
			lcd_display_string(SYNTH_TEST_ITEM_4_CURRENT_LEFT, SYNTH_TEST_ITEM_4_CURRENT_TOP, str_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_4_CURRENT_COLON_LEFT, SYNTH_TEST_ITEM_4_CURRENT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_4_CURRENT_UNIT_LEFT, SYNTH_TEST_ITEM_4_CURRENT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case SYNTH_TEST_OVER_CURRENT:
			/* over current */
			lcd_display_string(SYNTH_TEST_ITEM_4_OC_LEFT, SYNTH_TEST_ITEM_4_OC_TOP, str_over_current_val, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_4_OC_COLON_LEFT, SYNTH_TEST_ITEM_4_OC_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_4_OC_UNIT_LEFT, SYNTH_TEST_ITEM_4_OC_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case SYNTH_TEST_SHORT:
			/* short current */
			lcd_display_string(SYNTH_TEST_ITEM_4_SHORT_LEFT, SYNTH_TEST_ITEM_4_SHORT_TOP, str_short_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_4_SHORT_COLON_LEFT, SYNTH_TEST_ITEM_4_SHORT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_4_SHORT_UNIT_LEFT, SYNTH_TEST_ITEM_4_SHORT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		default:
			break;
		}
	}
	else
	{
		lcd_display_string(SYNTH_TEST_ITEM_4_AC_LEFT, SYNTH_TEST_ITEM_4_AC_TOP, str_off, CAPTION_COLOR, FONT_32);
	}
}

static void draw_synth_test_item_5(const SYNTH_NORMAL_TEST_SETTING *synth_normal_test_setting)
{
	if (synth_normal_test_setting->on_off == OPTION_ON)
	{
		/* ac */
		lcd_display_string(SYNTH_TEST_ITEM_5_AC_LEFT, SYNTH_TEST_ITEM_5_AC_TOP, str_ac_current, CAPTION_COLOR, FONT_32);
		lcd_display_ascii_char(SYNTH_TEST_ITEM_5_AC_COLON_LEFT, SYNTH_TEST_ITEM_5_AC_TOP, ':', CAPTION_COLOR, FONT_32);
		lcd_display_string(SYNTH_TEST_ITEM_5_AC_UNIT_LEFT, SYNTH_TEST_ITEM_5_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_32);
			
		switch (synth_normal_test_setting->test_type)
		{
		case SYNTH_TEST_CV:
			
		case SYNTH_TEST_CC:
			
		case SYNTH_TEST_CR:
			/* voltage */
			lcd_display_string(SYNTH_TEST_ITEM_5_VOLTAGE_LEFT, SYNTH_TEST_ITEM_5_VOLTAGE_TOP, str_voltage, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_5_VOLTAGE_COLON_LEFT, SYNTH_TEST_ITEM_5_VOLTAGE_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_5_VOLTAGE_UNIT_LEFT, SYNTH_TEST_ITEM_5_VOLTAGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_32);
		
			/* current */
			lcd_display_string(SYNTH_TEST_ITEM_5_CURRENT_LEFT, SYNTH_TEST_ITEM_5_CURRENT_TOP, str_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_5_CURRENT_COLON_LEFT, SYNTH_TEST_ITEM_5_CURRENT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_5_CURRENT_UNIT_LEFT, SYNTH_TEST_ITEM_5_CURRENT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
				
			break;

		case SYNTH_TEST_OVER_CURRENT:
			/* over current */
			lcd_display_string(SYNTH_TEST_ITEM_5_OC_LEFT, SYNTH_TEST_ITEM_5_OC_TOP, str_over_current_val, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_5_OC_COLON_LEFT, SYNTH_TEST_ITEM_5_OC_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_5_OC_UNIT_LEFT, SYNTH_TEST_ITEM_5_OC_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case SYNTH_TEST_SHORT:
			/* short current */
			lcd_display_string(SYNTH_TEST_ITEM_5_SHORT_LEFT, SYNTH_TEST_ITEM_5_SHORT_TOP, str_short_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_5_SHORT_COLON_LEFT, SYNTH_TEST_ITEM_5_SHORT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_5_SHORT_UNIT_LEFT, SYNTH_TEST_ITEM_5_SHORT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		default:
			break;
		}
	}
	else
	{
		lcd_display_string(SYNTH_TEST_ITEM_5_AC_LEFT, SYNTH_TEST_ITEM_5_AC_TOP, str_off, CAPTION_COLOR, FONT_32);
	}
}

static void draw_synth_test_item_6(const SYNTH_NORMAL_TEST_SETTING *synth_normal_test_setting)
{
	if (synth_normal_test_setting->on_off == OPTION_ON)
	{
		/* ac */
		lcd_display_string(SYNTH_TEST_ITEM_6_AC_LEFT, SYNTH_TEST_ITEM_6_AC_TOP, str_ac_current, CAPTION_COLOR, FONT_32);
		lcd_display_ascii_char(SYNTH_TEST_ITEM_6_AC_COLON_LEFT, SYNTH_TEST_ITEM_6_AC_TOP, ':', CAPTION_COLOR, FONT_32);
		lcd_display_string(SYNTH_TEST_ITEM_6_AC_UNIT_LEFT, SYNTH_TEST_ITEM_6_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_32);
			
		switch (synth_normal_test_setting->test_type)
		{
		case SYNTH_TEST_CV:
			
		case SYNTH_TEST_CC:
			
		case SYNTH_TEST_CR:
			/* voltage */
			lcd_display_string(SYNTH_TEST_ITEM_6_VOLTAGE_LEFT, SYNTH_TEST_ITEM_6_VOLTAGE_TOP, str_voltage, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_6_VOLTAGE_COLON_LEFT, SYNTH_TEST_ITEM_6_VOLTAGE_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_6_VOLTAGE_UNIT_LEFT, SYNTH_TEST_ITEM_6_VOLTAGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_32);
		
			/* current */
			lcd_display_string(SYNTH_TEST_ITEM_6_CURRENT_LEFT, SYNTH_TEST_ITEM_6_CURRENT_TOP, str_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_6_CURRENT_COLON_LEFT, SYNTH_TEST_ITEM_6_CURRENT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_6_CURRENT_UNIT_LEFT, SYNTH_TEST_ITEM_6_CURRENT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
				
			break;

		case SYNTH_TEST_OVER_CURRENT:
			/* over current */
			lcd_display_string(SYNTH_TEST_ITEM_6_OC_LEFT, SYNTH_TEST_ITEM_6_OC_TOP, str_over_current_val, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_6_OC_COLON_LEFT, SYNTH_TEST_ITEM_6_OC_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_6_OC_UNIT_LEFT, SYNTH_TEST_ITEM_6_OC_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case SYNTH_TEST_SHORT:
			/* short current */
			lcd_display_string(SYNTH_TEST_ITEM_6_SHORT_LEFT, SYNTH_TEST_ITEM_6_SHORT_TOP, str_short_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_6_SHORT_COLON_LEFT, SYNTH_TEST_ITEM_6_SHORT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_6_SHORT_UNIT_LEFT, SYNTH_TEST_ITEM_6_SHORT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		default:
			break;
		}
	}
	else
	{
		lcd_display_string(SYNTH_TEST_ITEM_6_AC_LEFT, SYNTH_TEST_ITEM_6_AC_TOP, str_off, CAPTION_COLOR, FONT_32);
	}	
}

static void draw_synth_test_item_7(const SYNTH_NORMAL_TEST_SETTING *synth_normal_test_setting)
{
	if (synth_normal_test_setting->on_off == OPTION_ON)
	{
		/* ac */
		lcd_display_string(SYNTH_TEST_ITEM_7_AC_LEFT, SYNTH_TEST_ITEM_7_AC_TOP, str_ac_current, CAPTION_COLOR, FONT_32);
		lcd_display_ascii_char(SYNTH_TEST_ITEM_7_AC_COLON_LEFT, SYNTH_TEST_ITEM_7_AC_TOP, ':', CAPTION_COLOR, FONT_32);
		lcd_display_string(SYNTH_TEST_ITEM_7_AC_UNIT_LEFT, SYNTH_TEST_ITEM_7_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_32);
			
		switch (synth_normal_test_setting->test_type)
		{
		case SYNTH_TEST_CV:
			
		case SYNTH_TEST_CC:
			
		case SYNTH_TEST_CR:
			/* voltage */
			lcd_display_string(SYNTH_TEST_ITEM_7_VOLTAGE_LEFT, SYNTH_TEST_ITEM_7_VOLTAGE_TOP, str_voltage, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_7_VOLTAGE_COLON_LEFT, SYNTH_TEST_ITEM_7_VOLTAGE_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_7_VOLTAGE_UNIT_LEFT, SYNTH_TEST_ITEM_7_VOLTAGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_32);
		
			/* current */
			lcd_display_string(SYNTH_TEST_ITEM_7_CURRENT_LEFT, SYNTH_TEST_ITEM_7_CURRENT_TOP, str_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_7_CURRENT_COLON_LEFT, SYNTH_TEST_ITEM_7_CURRENT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_7_CURRENT_UNIT_LEFT, SYNTH_TEST_ITEM_7_CURRENT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
				
			break;

		case SYNTH_TEST_OVER_CURRENT:
			/* over current */
			lcd_display_string(SYNTH_TEST_ITEM_7_OC_LEFT, SYNTH_TEST_ITEM_7_OC_TOP, str_over_current_val, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_7_OC_COLON_LEFT, SYNTH_TEST_ITEM_7_OC_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_7_OC_UNIT_LEFT, SYNTH_TEST_ITEM_7_OC_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case SYNTH_TEST_SHORT:
			/* short current */
			lcd_display_string(SYNTH_TEST_ITEM_7_SHORT_LEFT, SYNTH_TEST_ITEM_7_SHORT_TOP, str_short_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_7_SHORT_COLON_LEFT, SYNTH_TEST_ITEM_7_SHORT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_7_SHORT_UNIT_LEFT, SYNTH_TEST_ITEM_7_SHORT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		default:
			break;
		}
	}
	else
	{
		lcd_display_string(SYNTH_TEST_ITEM_7_AC_LEFT, SYNTH_TEST_ITEM_7_AC_TOP, str_off, CAPTION_COLOR, FONT_32);
	}	
}

static void draw_test_discharge(const DISCHARGE_TEST_SETTING *synth_discharge_test_setting)
{
	if (synth_discharge_test_setting->on_off == OPTION_ON)
	{
		lcd_display_string(SYNTH_TEST_ITEM_8_AC_LEFT, SYNTH_TEST_ITEM_8_AC_TOP, str_on, CAPTION_COLOR, FONT_32);
	}
	else
	{
		lcd_display_string(SYNTH_TEST_ITEM_8_AC_LEFT, SYNTH_TEST_ITEM_8_AC_TOP, str_off, CAPTION_COLOR, FONT_32);
	}	
}

void draw_synth_test_menu(const SYNTH_TEST_SETTING *synth_test_setting)
{
	/* second step */
	lcd_display_string(SYNTH_TEST_ITEM_2_TYPE_LEFT, SYNTH_TEST_ITEM_2_TYPE_TOP, s_synth_test_type_name[synth_test_setting->synth_normal_test_setting[0].test_type], 
						EDITABLE_FORE_COLOR, FONT_32);
	draw_synth_test_item_2(&synth_test_setting->synth_normal_test_setting[0]);
	
	/* third step */
	lcd_display_string(SYNTH_TEST_ITEM_3_TYPE_LEFT, SYNTH_TEST_ITEM_3_TYPE_TOP, s_synth_test_type_name[synth_test_setting->synth_normal_test_setting[1].test_type], 
						EDITABLE_FORE_COLOR, FONT_32);
	draw_synth_test_item_3(&synth_test_setting->synth_normal_test_setting[1]);
	
	/* forth step */
	lcd_display_string(SYNTH_TEST_ITEM_4_TYPE_LEFT, SYNTH_TEST_ITEM_4_TYPE_TOP, s_synth_test_type_name[synth_test_setting->synth_normal_test_setting[2].test_type], 
						EDITABLE_FORE_COLOR, FONT_32);
	draw_synth_test_item_4(&synth_test_setting->synth_normal_test_setting[2]);

	/* add a validate cmd */
	lcd_validate_cmd();
	
	/* fifth step */
	lcd_display_string(SYNTH_TEST_ITEM_5_TYPE_LEFT, SYNTH_TEST_ITEM_5_TYPE_TOP, s_synth_test_type_name[synth_test_setting->synth_normal_test_setting[3].test_type], 
						EDITABLE_FORE_COLOR, FONT_32);
	draw_synth_test_item_5(&synth_test_setting->synth_normal_test_setting[3]);
	
	/* sixth step */
	lcd_display_string(SYNTH_TEST_ITEM_6_TYPE_LEFT, SYNTH_TEST_ITEM_6_TYPE_TOP, s_synth_test_type_name[synth_test_setting->synth_normal_test_setting[4].test_type], 
						EDITABLE_FORE_COLOR, FONT_32);
	draw_synth_test_item_6(&synth_test_setting->synth_normal_test_setting[4]);

	/* seventh step */
	lcd_display_string(SYNTH_TEST_ITEM_7_TYPE_LEFT, SYNTH_TEST_ITEM_7_TYPE_TOP, s_synth_test_type_name[synth_test_setting->synth_normal_test_setting[5].test_type], 
						EDITABLE_FORE_COLOR, FONT_32);
	draw_synth_test_item_7(&synth_test_setting->synth_normal_test_setting[5]);

	/* discharge step */
	draw_test_discharge(&synth_test_setting->discharge_test_setting);
}


static void draw_qc_20_test_item_2(const QC_20_NORMAL_TEST_SETTING *qc_20_normal_test_setting)
{
	if (qc_20_normal_test_setting->on_off == OPTION_ON)
	{
		/* ac */
		lcd_display_string(SYNTH_TEST_ITEM_2_AC_LEFT, SYNTH_TEST_ITEM_2_AC_TOP, str_ac_current, CAPTION_COLOR, FONT_32);
		lcd_display_ascii_char(SYNTH_TEST_ITEM_2_AC_COLON_LEFT, SYNTH_TEST_ITEM_2_AC_TOP, ':', CAPTION_COLOR, FONT_32);
		lcd_display_string(SYNTH_TEST_ITEM_2_AC_UNIT_LEFT, SYNTH_TEST_ITEM_2_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_32);
		
		switch (qc_20_normal_test_setting->test_type)
		{
		case QC_20_5V_TEST_CV:
		case QC_20_5V_TEST_CC:
		case QC_20_5V_TEST_CR:

		case QC_20_9V_TEST_CV:
		case QC_20_9V_TEST_CC:
		case QC_20_9V_TEST_CR:

		case QC_20_12V_TEST_CV:
		case QC_20_12V_TEST_CC:
		case QC_20_12V_TEST_CR:

		case QC_20_20V_TEST_CV:
		case QC_20_20V_TEST_CC:
		case QC_20_20V_TEST_CR:
			/* voltage */
			lcd_display_string(SYNTH_TEST_ITEM_2_VOLTAGE_LEFT, SYNTH_TEST_ITEM_2_VOLTAGE_TOP, str_voltage, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_2_VOLTAGE_COLON_LEFT, SYNTH_TEST_ITEM_2_VOLTAGE_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_2_VOLTAGE_UNIT_LEFT, SYNTH_TEST_ITEM_2_VOLTAGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_32);

			/* current */
			lcd_display_string(SYNTH_TEST_ITEM_2_CURRENT_LEFT, SYNTH_TEST_ITEM_2_CURRENT_TOP, str_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_2_CURRENT_COLON_LEFT, SYNTH_TEST_ITEM_2_CURRENT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_2_CURRENT_UNIT_LEFT, SYNTH_TEST_ITEM_2_CURRENT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case QC_20_5V_TEST_OVER_CURRENT:
		case QC_20_9V_TEST_OVER_CURRENT:
		case QC_20_12V_TEST_OVER_CURRENT:
		case QC_20_20V_TEST_OVER_CURRENT:
			/* over current */
			lcd_display_string(SYNTH_TEST_ITEM_2_OC_LEFT, SYNTH_TEST_ITEM_2_OC_TOP, str_over_current_val, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_2_OC_COLON_LEFT, SYNTH_TEST_ITEM_2_OC_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_2_OC_UNIT_LEFT, SYNTH_TEST_ITEM_2_OC_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case QC_20_5V_TEST_SHORT:
		case QC_20_9V_TEST_SHORT:
		case QC_20_12V_TEST_SHORT:
		case QC_20_20V_TEST_SHORT:
			/* short current */
			lcd_display_string(SYNTH_TEST_ITEM_2_SHORT_LEFT, SYNTH_TEST_ITEM_2_SHORT_TOP, str_short_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_2_SHORT_COLON_LEFT, SYNTH_TEST_ITEM_2_SHORT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_2_SHORT_UNIT_LEFT, SYNTH_TEST_ITEM_2_SHORT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		default:
			break;
		}
	}
	else
	{
		lcd_display_string(SYNTH_TEST_ITEM_2_AC_LEFT, SYNTH_TEST_ITEM_2_AC_TOP, str_off, CAPTION_COLOR, FONT_32);
	}
	
}

static void draw_qc_20_test_item_3(const QC_20_NORMAL_TEST_SETTING *qc_20_normal_test_setting)
{
	if (qc_20_normal_test_setting->on_off == OPTION_ON)
	{
		/* ac */
		lcd_display_string(SYNTH_TEST_ITEM_3_AC_LEFT, SYNTH_TEST_ITEM_3_AC_TOP, str_ac_current, CAPTION_COLOR, FONT_32);
		lcd_display_ascii_char(SYNTH_TEST_ITEM_3_AC_COLON_LEFT, SYNTH_TEST_ITEM_3_AC_TOP, ':', CAPTION_COLOR, FONT_32);
		lcd_display_string(SYNTH_TEST_ITEM_3_AC_UNIT_LEFT, SYNTH_TEST_ITEM_3_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_32);
		
		switch (qc_20_normal_test_setting->test_type)
		{
		case QC_20_5V_TEST_CV:
		case QC_20_5V_TEST_CC:
		case QC_20_5V_TEST_CR:

		case QC_20_9V_TEST_CV:
		case QC_20_9V_TEST_CC:
		case QC_20_9V_TEST_CR:

		case QC_20_12V_TEST_CV:
		case QC_20_12V_TEST_CC:
		case QC_20_12V_TEST_CR:

		case QC_20_20V_TEST_CV:
		case QC_20_20V_TEST_CC:
		case QC_20_20V_TEST_CR:
			/* voltage */
			lcd_display_string(SYNTH_TEST_ITEM_3_VOLTAGE_LEFT, SYNTH_TEST_ITEM_3_VOLTAGE_TOP, str_voltage, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_3_VOLTAGE_COLON_LEFT, SYNTH_TEST_ITEM_3_VOLTAGE_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_3_VOLTAGE_UNIT_LEFT, SYNTH_TEST_ITEM_3_VOLTAGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_32);

			/* current */
			lcd_display_string(SYNTH_TEST_ITEM_3_CURRENT_LEFT, SYNTH_TEST_ITEM_3_CURRENT_TOP, str_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_3_CURRENT_COLON_LEFT, SYNTH_TEST_ITEM_3_CURRENT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_3_CURRENT_UNIT_LEFT, SYNTH_TEST_ITEM_3_CURRENT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case QC_20_5V_TEST_OVER_CURRENT:
		case QC_20_9V_TEST_OVER_CURRENT:
		case QC_20_12V_TEST_OVER_CURRENT:
		case QC_20_20V_TEST_OVER_CURRENT:
			/* over current */
			lcd_display_string(SYNTH_TEST_ITEM_3_OC_LEFT, SYNTH_TEST_ITEM_3_OC_TOP, str_over_current_val, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_3_OC_COLON_LEFT, SYNTH_TEST_ITEM_3_OC_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_3_OC_UNIT_LEFT, SYNTH_TEST_ITEM_3_OC_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case QC_20_5V_TEST_SHORT:
		case QC_20_9V_TEST_SHORT:
		case QC_20_12V_TEST_SHORT:
		case QC_20_20V_TEST_SHORT:
			/* short current */
			lcd_display_string(SYNTH_TEST_ITEM_3_SHORT_LEFT, SYNTH_TEST_ITEM_3_SHORT_TOP, str_short_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_3_SHORT_COLON_LEFT, SYNTH_TEST_ITEM_3_SHORT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_3_SHORT_UNIT_LEFT, SYNTH_TEST_ITEM_3_SHORT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		default:
			break;
		}
	}
	else
	{
		lcd_display_string(SYNTH_TEST_ITEM_3_AC_LEFT, SYNTH_TEST_ITEM_3_AC_TOP, str_off, CAPTION_COLOR, FONT_32);
	}
	
}

static void draw_qc_20_test_item_4(const QC_20_NORMAL_TEST_SETTING *qc_20_normal_test_setting)
{
	if (qc_20_normal_test_setting->on_off == OPTION_ON)
	{
		/* ac */
		lcd_display_string(SYNTH_TEST_ITEM_4_AC_LEFT, SYNTH_TEST_ITEM_4_AC_TOP, str_ac_current, CAPTION_COLOR, FONT_32);
		lcd_display_ascii_char(SYNTH_TEST_ITEM_4_AC_COLON_LEFT, SYNTH_TEST_ITEM_4_AC_TOP, ':', CAPTION_COLOR, FONT_32);
		lcd_display_string(SYNTH_TEST_ITEM_4_AC_UNIT_LEFT, SYNTH_TEST_ITEM_4_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_32);
		
		switch (qc_20_normal_test_setting->test_type)
		{
		case QC_20_5V_TEST_CV:
		case QC_20_5V_TEST_CC:
		case QC_20_5V_TEST_CR:

		case QC_20_9V_TEST_CV:
		case QC_20_9V_TEST_CC:
		case QC_20_9V_TEST_CR:

		case QC_20_12V_TEST_CV:
		case QC_20_12V_TEST_CC:
		case QC_20_12V_TEST_CR:

		case QC_20_20V_TEST_CV:
		case QC_20_20V_TEST_CC:
		case QC_20_20V_TEST_CR:
			/* voltage */
			lcd_display_string(SYNTH_TEST_ITEM_4_VOLTAGE_LEFT, SYNTH_TEST_ITEM_4_VOLTAGE_TOP, str_voltage, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_4_VOLTAGE_COLON_LEFT, SYNTH_TEST_ITEM_4_VOLTAGE_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_4_VOLTAGE_UNIT_LEFT, SYNTH_TEST_ITEM_4_VOLTAGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_32);

			/* current */
			lcd_display_string(SYNTH_TEST_ITEM_4_CURRENT_LEFT, SYNTH_TEST_ITEM_4_CURRENT_TOP, str_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_4_CURRENT_COLON_LEFT, SYNTH_TEST_ITEM_4_CURRENT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_4_CURRENT_UNIT_LEFT, SYNTH_TEST_ITEM_4_CURRENT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case QC_20_5V_TEST_OVER_CURRENT:
		case QC_20_9V_TEST_OVER_CURRENT:
		case QC_20_12V_TEST_OVER_CURRENT:
		case QC_20_20V_TEST_OVER_CURRENT:
			/* over current */
			lcd_display_string(SYNTH_TEST_ITEM_4_OC_LEFT, SYNTH_TEST_ITEM_4_OC_TOP, str_over_current_val, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_4_OC_COLON_LEFT, SYNTH_TEST_ITEM_4_OC_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_4_OC_UNIT_LEFT, SYNTH_TEST_ITEM_4_OC_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case QC_20_5V_TEST_SHORT:
		case QC_20_9V_TEST_SHORT:
		case QC_20_12V_TEST_SHORT:
		case QC_20_20V_TEST_SHORT:
			/* short current */
			lcd_display_string(SYNTH_TEST_ITEM_4_SHORT_LEFT, SYNTH_TEST_ITEM_4_SHORT_TOP, str_short_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_4_SHORT_COLON_LEFT, SYNTH_TEST_ITEM_4_SHORT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_4_SHORT_UNIT_LEFT, SYNTH_TEST_ITEM_4_SHORT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		default:
			break;
		}
	}
	else
	{
		lcd_display_string(SYNTH_TEST_ITEM_4_AC_LEFT, SYNTH_TEST_ITEM_4_AC_TOP, str_off, CAPTION_COLOR, FONT_32);
	}
	
}

static void draw_qc_20_test_item_5(const QC_20_NORMAL_TEST_SETTING *qc_20_normal_test_setting)
{
	if (qc_20_normal_test_setting->on_off == OPTION_ON)
	{
		/* ac */
		lcd_display_string(SYNTH_TEST_ITEM_5_AC_LEFT, SYNTH_TEST_ITEM_5_AC_TOP, str_ac_current, CAPTION_COLOR, FONT_32);
		lcd_display_ascii_char(SYNTH_TEST_ITEM_5_AC_COLON_LEFT, SYNTH_TEST_ITEM_5_AC_TOP, ':', CAPTION_COLOR, FONT_32);
		lcd_display_string(SYNTH_TEST_ITEM_5_AC_UNIT_LEFT, SYNTH_TEST_ITEM_5_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_32);
		
		switch (qc_20_normal_test_setting->test_type)
		{
		case QC_20_5V_TEST_CV:
		case QC_20_5V_TEST_CC:
		case QC_20_5V_TEST_CR:

		case QC_20_9V_TEST_CV:
		case QC_20_9V_TEST_CC:
		case QC_20_9V_TEST_CR:

		case QC_20_12V_TEST_CV:
		case QC_20_12V_TEST_CC:
		case QC_20_12V_TEST_CR:

		case QC_20_20V_TEST_CV:
		case QC_20_20V_TEST_CC:
		case QC_20_20V_TEST_CR:
			/* voltage */
			lcd_display_string(SYNTH_TEST_ITEM_5_VOLTAGE_LEFT, SYNTH_TEST_ITEM_5_VOLTAGE_TOP, str_voltage, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_5_VOLTAGE_COLON_LEFT, SYNTH_TEST_ITEM_5_VOLTAGE_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_5_VOLTAGE_UNIT_LEFT, SYNTH_TEST_ITEM_5_VOLTAGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_32);

			/* current */
			lcd_display_string(SYNTH_TEST_ITEM_5_CURRENT_LEFT, SYNTH_TEST_ITEM_5_CURRENT_TOP, str_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_5_CURRENT_COLON_LEFT, SYNTH_TEST_ITEM_5_CURRENT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_5_CURRENT_UNIT_LEFT, SYNTH_TEST_ITEM_5_CURRENT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case QC_20_5V_TEST_OVER_CURRENT:
		case QC_20_9V_TEST_OVER_CURRENT:
		case QC_20_12V_TEST_OVER_CURRENT:
		case QC_20_20V_TEST_OVER_CURRENT:
			/* over current */
			lcd_display_string(SYNTH_TEST_ITEM_5_OC_LEFT, SYNTH_TEST_ITEM_5_OC_TOP, str_over_current_val, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_5_OC_COLON_LEFT, SYNTH_TEST_ITEM_5_OC_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_5_OC_UNIT_LEFT, SYNTH_TEST_ITEM_5_OC_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case QC_20_5V_TEST_SHORT:
		case QC_20_9V_TEST_SHORT:
		case QC_20_12V_TEST_SHORT:
		case QC_20_20V_TEST_SHORT:
			/* short current */
			lcd_display_string(SYNTH_TEST_ITEM_5_SHORT_LEFT, SYNTH_TEST_ITEM_5_SHORT_TOP, str_short_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_5_SHORT_COLON_LEFT, SYNTH_TEST_ITEM_5_SHORT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_5_SHORT_UNIT_LEFT, SYNTH_TEST_ITEM_5_SHORT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		default:
			break;
		}
	}
	else
	{
		lcd_display_string(SYNTH_TEST_ITEM_5_AC_LEFT, SYNTH_TEST_ITEM_5_AC_TOP, str_off, CAPTION_COLOR, FONT_32);
	}
	
}

static void draw_qc_20_test_item_6(const QC_20_NORMAL_TEST_SETTING *qc_20_normal_test_setting)
{
	if (qc_20_normal_test_setting->on_off == OPTION_ON)
	{
		/* ac */
		lcd_display_string(SYNTH_TEST_ITEM_6_AC_LEFT, SYNTH_TEST_ITEM_6_AC_TOP, str_ac_current, CAPTION_COLOR, FONT_32);
		lcd_display_ascii_char(SYNTH_TEST_ITEM_6_AC_COLON_LEFT, SYNTH_TEST_ITEM_6_AC_TOP, ':', CAPTION_COLOR, FONT_32);
		lcd_display_string(SYNTH_TEST_ITEM_6_AC_UNIT_LEFT, SYNTH_TEST_ITEM_6_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_32);
		
		switch (qc_20_normal_test_setting->test_type)
		{
		case QC_20_5V_TEST_CV:
		case QC_20_5V_TEST_CC:
		case QC_20_5V_TEST_CR:

		case QC_20_9V_TEST_CV:
		case QC_20_9V_TEST_CC:
		case QC_20_9V_TEST_CR:

		case QC_20_12V_TEST_CV:
		case QC_20_12V_TEST_CC:
		case QC_20_12V_TEST_CR:

		case QC_20_20V_TEST_CV:
		case QC_20_20V_TEST_CC:
		case QC_20_20V_TEST_CR:
			/* voltage */
			lcd_display_string(SYNTH_TEST_ITEM_6_VOLTAGE_LEFT, SYNTH_TEST_ITEM_6_VOLTAGE_TOP, str_voltage, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_6_VOLTAGE_COLON_LEFT, SYNTH_TEST_ITEM_6_VOLTAGE_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_6_VOLTAGE_UNIT_LEFT, SYNTH_TEST_ITEM_6_VOLTAGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_32);

			/* current */
			lcd_display_string(SYNTH_TEST_ITEM_6_CURRENT_LEFT, SYNTH_TEST_ITEM_6_CURRENT_TOP, str_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_6_CURRENT_COLON_LEFT, SYNTH_TEST_ITEM_6_CURRENT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_6_CURRENT_UNIT_LEFT, SYNTH_TEST_ITEM_6_CURRENT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case QC_20_5V_TEST_OVER_CURRENT:
		case QC_20_9V_TEST_OVER_CURRENT:
		case QC_20_12V_TEST_OVER_CURRENT:
		case QC_20_20V_TEST_OVER_CURRENT:
			/* over current */
			lcd_display_string(SYNTH_TEST_ITEM_6_OC_LEFT, SYNTH_TEST_ITEM_6_OC_TOP, str_over_current_val, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_6_OC_COLON_LEFT, SYNTH_TEST_ITEM_6_OC_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_6_OC_UNIT_LEFT, SYNTH_TEST_ITEM_6_OC_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case QC_20_5V_TEST_SHORT:
		case QC_20_9V_TEST_SHORT:
		case QC_20_12V_TEST_SHORT:
		case QC_20_20V_TEST_SHORT:
			/* short current */
			lcd_display_string(SYNTH_TEST_ITEM_6_SHORT_LEFT, SYNTH_TEST_ITEM_6_SHORT_TOP, str_short_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_6_SHORT_COLON_LEFT, SYNTH_TEST_ITEM_6_SHORT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_6_SHORT_UNIT_LEFT, SYNTH_TEST_ITEM_6_SHORT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		default:
			break;
		}
	}
	else
	{
		lcd_display_string(SYNTH_TEST_ITEM_6_AC_LEFT, SYNTH_TEST_ITEM_6_AC_TOP, str_off, CAPTION_COLOR, FONT_32);
	}
	
}

static void draw_qc_20_test_item_7(const QC_20_NORMAL_TEST_SETTING *qc_20_normal_test_setting)
{
	if (qc_20_normal_test_setting->on_off == OPTION_ON)
	{
		/* ac */
		lcd_display_string(SYNTH_TEST_ITEM_7_AC_LEFT, SYNTH_TEST_ITEM_7_AC_TOP, str_ac_current, CAPTION_COLOR, FONT_32);
		lcd_display_ascii_char(SYNTH_TEST_ITEM_7_AC_COLON_LEFT, SYNTH_TEST_ITEM_7_AC_TOP, ':', CAPTION_COLOR, FONT_32);
		lcd_display_string(SYNTH_TEST_ITEM_7_AC_UNIT_LEFT, SYNTH_TEST_ITEM_7_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_32);
		
		switch (qc_20_normal_test_setting->test_type)
		{
		case QC_20_5V_TEST_CV:
		case QC_20_5V_TEST_CC:
		case QC_20_5V_TEST_CR:

		case QC_20_9V_TEST_CV:
		case QC_20_9V_TEST_CC:
		case QC_20_9V_TEST_CR:

		case QC_20_12V_TEST_CV:
		case QC_20_12V_TEST_CC:
		case QC_20_12V_TEST_CR:

		case QC_20_20V_TEST_CV:
		case QC_20_20V_TEST_CC:
		case QC_20_20V_TEST_CR:
			/* voltage */
			lcd_display_string(SYNTH_TEST_ITEM_7_VOLTAGE_LEFT, SYNTH_TEST_ITEM_7_VOLTAGE_TOP, str_voltage, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_7_VOLTAGE_COLON_LEFT, SYNTH_TEST_ITEM_7_VOLTAGE_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_7_VOLTAGE_UNIT_LEFT, SYNTH_TEST_ITEM_7_VOLTAGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_32);

			/* current */
			lcd_display_string(SYNTH_TEST_ITEM_7_CURRENT_LEFT, SYNTH_TEST_ITEM_7_CURRENT_TOP, str_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_7_CURRENT_COLON_LEFT, SYNTH_TEST_ITEM_7_CURRENT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_7_CURRENT_UNIT_LEFT, SYNTH_TEST_ITEM_7_CURRENT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case QC_20_5V_TEST_OVER_CURRENT:
		case QC_20_9V_TEST_OVER_CURRENT:
		case QC_20_12V_TEST_OVER_CURRENT:
		case QC_20_20V_TEST_OVER_CURRENT:
			/* over current */
			lcd_display_string(SYNTH_TEST_ITEM_7_OC_LEFT, SYNTH_TEST_ITEM_7_OC_TOP, str_over_current_val, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_7_OC_COLON_LEFT, SYNTH_TEST_ITEM_7_OC_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_7_OC_UNIT_LEFT, SYNTH_TEST_ITEM_7_OC_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		case QC_20_5V_TEST_SHORT:
		case QC_20_9V_TEST_SHORT:
		case QC_20_12V_TEST_SHORT:
		case QC_20_20V_TEST_SHORT:
			/* short current */
			lcd_display_string(SYNTH_TEST_ITEM_7_SHORT_LEFT, SYNTH_TEST_ITEM_7_SHORT_TOP, str_short_current, CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_7_SHORT_COLON_LEFT, SYNTH_TEST_ITEM_7_SHORT_TOP, ':', CAPTION_COLOR, FONT_32);
			lcd_display_ascii_char(SYNTH_TEST_ITEM_7_SHORT_UNIT_LEFT, SYNTH_TEST_ITEM_7_SHORT_TOP, 'A', RDONLY_FORE_COLOR, FONT_32);
			
			break;

		default:
			break;
		}
	}
	else
	{
		lcd_display_string(SYNTH_TEST_ITEM_7_AC_LEFT, SYNTH_TEST_ITEM_7_AC_TOP, str_off, CAPTION_COLOR, FONT_32);
	}
	
}

void draw_qc_20_test_menu(const QC_20_TEST_SETTING *qc_20_test_setting)
{
	/* second step */
	lcd_display_string(SYNTH_TEST_ITEM_2_TYPE_LEFT, SYNTH_TEST_ITEM_2_TYPE_TOP, s_qc_20_test_type_name[qc_20_test_setting->qc_20_normal_test_setting[0].test_type], 
						EDITABLE_FORE_COLOR, FONT_32);
	draw_qc_20_test_item_2(&qc_20_test_setting->qc_20_normal_test_setting[0]);
	
	/* third step */
	lcd_display_string(SYNTH_TEST_ITEM_3_TYPE_LEFT, SYNTH_TEST_ITEM_3_TYPE_TOP, s_qc_20_test_type_name[qc_20_test_setting->qc_20_normal_test_setting[1].test_type], 
						EDITABLE_FORE_COLOR, FONT_32);
	draw_qc_20_test_item_3(&qc_20_test_setting->qc_20_normal_test_setting[1]);
	
	/* forth step */
	lcd_display_string(SYNTH_TEST_ITEM_4_TYPE_LEFT, SYNTH_TEST_ITEM_4_TYPE_TOP, s_qc_20_test_type_name[qc_20_test_setting->qc_20_normal_test_setting[2].test_type], 
						EDITABLE_FORE_COLOR, FONT_32);
	draw_qc_20_test_item_4(&qc_20_test_setting->qc_20_normal_test_setting[2]);

	/* add a validate cmd */
	lcd_validate_cmd();
	
	/* fifth step */
	lcd_display_string(SYNTH_TEST_ITEM_5_TYPE_LEFT, SYNTH_TEST_ITEM_5_TYPE_TOP, s_qc_20_test_type_name[qc_20_test_setting->qc_20_normal_test_setting[3].test_type], 
						EDITABLE_FORE_COLOR, FONT_32);
	draw_qc_20_test_item_5(&qc_20_test_setting->qc_20_normal_test_setting[3]);
	
	/* sixth step */
	lcd_display_string(SYNTH_TEST_ITEM_6_TYPE_LEFT, SYNTH_TEST_ITEM_6_TYPE_TOP, s_qc_20_test_type_name[qc_20_test_setting->qc_20_normal_test_setting[4].test_type], 
						EDITABLE_FORE_COLOR, FONT_32);
	draw_qc_20_test_item_6(&qc_20_test_setting->qc_20_normal_test_setting[4]);

	/* seventh step */
	lcd_display_string(SYNTH_TEST_ITEM_7_TYPE_LEFT, SYNTH_TEST_ITEM_7_TYPE_TOP, s_qc_20_test_type_name[qc_20_test_setting->qc_20_normal_test_setting[5].test_type], 
						EDITABLE_FORE_COLOR, FONT_32);
	draw_qc_20_test_item_7(&qc_20_test_setting->qc_20_normal_test_setting[5]);

	/* discharge step */
	draw_test_discharge(&qc_20_test_setting->discharge_test_setting);
}


void draw_synth_test_phone_number(const PHONE_NUMBER *phone_number)
{
	char phone[PHONE_NUMBER_LEN + 1];
	rt_memcpy(phone, phone_number->phone_number, PHONE_NUMBER_LEN);
	phone[PHONE_NUMBER_LEN] = '\0';
	
	lcd_display_string(SYNTH_TEST_CONTACT_PHONE_LEFT, SYNTH_TEST_CONTACT_PHONE_TOP, str_contact_phone, CAPTION_COLOR, FONT_32);

	lcd_display_string(SYNTH_TEST_PHONE_NUMBER_LEFT, SYNTH_TEST_PHONE_NUMBER_TOP, phone, CAPTION_COLOR, FONT_32); 
}

static const uint32_t s_number_divider[] = 
{
	[1] = 100,
	[2] = 10,
	[3] = 1
};


void draw_synth_test_step_1_ac(uint32_t uA)
{
	lcd_display_number(SYNTH_TEST_ITEM_1_AC_VAL_LEFT, SYNTH_TEST_ITEM_1_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_1_ac(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_1_AC_VAL_LEFT, SYNTH_TEST_ITEM_1_AC_TOP, "   ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_1_voltage(uint32_t mV)
{
	lcd_display_number(SYNTH_TEST_ITEM_1_VOLTAGE_VAL_LEFT, SYNTH_TEST_ITEM_1_VOLTAGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_1_voltage(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_1_VOLTAGE_VAL_LEFT, SYNTH_TEST_ITEM_1_VOLTAGE_TOP, "     ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_1_OK(void)
{
	lcd_display_pic(SYNTH_TEST_ITEM_1_RESULT_LEFT, SYNTH_TEST_ITEM_1_RESULT_TOP, PIC_ID_OK);
}

void draw_synth_test_step_1_fail(void)
{
	lcd_display_pic(SYNTH_TEST_ITEM_1_RESULT_LEFT, SYNTH_TEST_ITEM_1_RESULT_TOP, PIC_ID_FAIL);
}

void clear_synth_test_step_1_result(void)
{
	lcd_fill_rectangle(SYNTH_TEST_ITEM_1_RESULT_LEFT, SYNTH_TEST_ITEM_1_RESULT_TOP, 
					SYNTH_TEST_ITEM_1_RESULT_LEFT + PIC_RESULT_WIDTH,
					SYNTH_TEST_ITEM_1_RESULT_TOP + PIC_RESULT_HEIGHT, SCREEN_BACK_COLOR);
}

void draw_synth_test_step_2_ac(uint32_t uA)
{
	lcd_display_number(SYNTH_TEST_ITEM_2_AC_VAL_LEFT, SYNTH_TEST_ITEM_2_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_2_ac(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_2_AC_VAL_LEFT, SYNTH_TEST_ITEM_2_AC_TOP, "   ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_2_voltage(uint32_t mV)
{
	lcd_display_number(SYNTH_TEST_ITEM_2_VOLTAGE_VAL_LEFT, SYNTH_TEST_ITEM_2_VOLTAGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_2_voltage(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_2_VOLTAGE_VAL_LEFT, SYNTH_TEST_ITEM_2_VOLTAGE_TOP, "     ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_2_current(uint32_t mA)
{
	lcd_display_number(SYNTH_TEST_ITEM_2_CURRENT_VAL_LEFT, SYNTH_TEST_ITEM_2_CURRENT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_2_current(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_2_CURRENT_VAL_LEFT, SYNTH_TEST_ITEM_2_CURRENT_TOP, "    ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_2_oc(uint32_t mA)
{
	lcd_display_number(SYNTH_TEST_ITEM_2_OC_VAL_LEFT, SYNTH_TEST_ITEM_2_OC_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_2_oc(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_2_OC_VAL_LEFT, SYNTH_TEST_ITEM_2_OC_TOP, "    ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_2_short(uint32_t mA)
{
	lcd_display_number(SYNTH_TEST_ITEM_2_SHORT_VAL_LEFT, SYNTH_TEST_ITEM_2_SHORT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_2_short(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_2_SHORT_VAL_LEFT, SYNTH_TEST_ITEM_2_SHORT_TOP, "    ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_2_OK(void)
{
	lcd_display_pic(SYNTH_TEST_ITEM_2_RESULT_LEFT, SYNTH_TEST_ITEM_2_RESULT_TOP, PIC_ID_OK);
}

void draw_synth_test_step_2_fail(void)
{
	lcd_display_pic(SYNTH_TEST_ITEM_2_RESULT_LEFT, SYNTH_TEST_ITEM_2_RESULT_TOP, PIC_ID_FAIL);
}

void clear_synth_test_step_2_result(void)
{
	lcd_fill_rectangle(SYNTH_TEST_ITEM_2_RESULT_LEFT, SYNTH_TEST_ITEM_2_RESULT_TOP, 
					SYNTH_TEST_ITEM_2_RESULT_LEFT + PIC_RESULT_WIDTH,
					SYNTH_TEST_ITEM_2_RESULT_TOP + PIC_RESULT_HEIGHT, SCREEN_BACK_COLOR);
}

void draw_synth_test_step_3_ac(uint32_t uA)
{
	lcd_display_number(SYNTH_TEST_ITEM_3_AC_VAL_LEFT, SYNTH_TEST_ITEM_3_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_3_ac(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_3_AC_VAL_LEFT, SYNTH_TEST_ITEM_3_AC_TOP, "   ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_3_voltage(uint32_t mV)
{
	lcd_display_number(SYNTH_TEST_ITEM_3_VOLTAGE_VAL_LEFT, SYNTH_TEST_ITEM_3_VOLTAGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_3_voltage(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_3_VOLTAGE_VAL_LEFT, SYNTH_TEST_ITEM_3_VOLTAGE_TOP, "     ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_3_current(uint32_t mA)
{
	lcd_display_number(SYNTH_TEST_ITEM_3_CURRENT_VAL_LEFT, SYNTH_TEST_ITEM_3_CURRENT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_3_current(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_3_CURRENT_VAL_LEFT, SYNTH_TEST_ITEM_3_CURRENT_TOP, "    ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_3_oc(uint32_t mA)
{
	lcd_display_number(SYNTH_TEST_ITEM_3_OC_VAL_LEFT, SYNTH_TEST_ITEM_3_OC_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_3_oc(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_3_OC_VAL_LEFT, SYNTH_TEST_ITEM_3_OC_TOP, "    ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_3_short(uint32_t mA)
{
	lcd_display_number(SYNTH_TEST_ITEM_3_SHORT_VAL_LEFT, SYNTH_TEST_ITEM_3_SHORT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_3_short(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_3_SHORT_VAL_LEFT, SYNTH_TEST_ITEM_3_SHORT_TOP, "    ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_3_OK(void)
{
	lcd_display_pic(SYNTH_TEST_ITEM_3_RESULT_LEFT, SYNTH_TEST_ITEM_3_RESULT_TOP, PIC_ID_OK);
}

void draw_synth_test_step_3_fail(void)
{
	lcd_display_pic(SYNTH_TEST_ITEM_3_RESULT_LEFT, SYNTH_TEST_ITEM_3_RESULT_TOP, PIC_ID_FAIL);
}

void clear_synth_test_step_3_result(void)
{
	lcd_fill_rectangle(SYNTH_TEST_ITEM_3_RESULT_LEFT, SYNTH_TEST_ITEM_3_RESULT_TOP, 
					SYNTH_TEST_ITEM_3_RESULT_LEFT + PIC_RESULT_WIDTH,
					SYNTH_TEST_ITEM_3_RESULT_TOP + PIC_RESULT_HEIGHT, SCREEN_BACK_COLOR);
}

void draw_synth_test_step_4_ac(uint32_t uA)
{
	lcd_display_number(SYNTH_TEST_ITEM_4_AC_VAL_LEFT, SYNTH_TEST_ITEM_4_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_4_ac(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_4_AC_VAL_LEFT, SYNTH_TEST_ITEM_4_AC_TOP, "   ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_4_voltage(uint32_t mV)
{
	lcd_display_number(SYNTH_TEST_ITEM_4_VOLTAGE_VAL_LEFT, SYNTH_TEST_ITEM_4_VOLTAGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_4_voltage(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_4_VOLTAGE_VAL_LEFT, SYNTH_TEST_ITEM_4_VOLTAGE_TOP, "     ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_4_current(uint32_t mA)
{
	lcd_display_number(SYNTH_TEST_ITEM_4_CURRENT_VAL_LEFT, SYNTH_TEST_ITEM_4_CURRENT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_4_current(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_4_CURRENT_VAL_LEFT, SYNTH_TEST_ITEM_4_CURRENT_TOP, "    ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_4_oc(uint32_t mA)
{
	lcd_display_number(SYNTH_TEST_ITEM_4_OC_VAL_LEFT, SYNTH_TEST_ITEM_4_OC_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_4_oc(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_4_OC_VAL_LEFT, SYNTH_TEST_ITEM_4_OC_TOP, "    ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_4_short(uint32_t mA)
{
	lcd_display_number(SYNTH_TEST_ITEM_4_SHORT_VAL_LEFT, SYNTH_TEST_ITEM_4_SHORT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_4_short(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_4_SHORT_VAL_LEFT, SYNTH_TEST_ITEM_4_SHORT_TOP, "    ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_4_OK(void)
{
	lcd_display_pic(SYNTH_TEST_ITEM_4_RESULT_LEFT, SYNTH_TEST_ITEM_4_RESULT_TOP, PIC_ID_OK);
}

void draw_synth_test_step_4_fail(void)
{
	lcd_display_pic(SYNTH_TEST_ITEM_4_RESULT_LEFT, SYNTH_TEST_ITEM_4_RESULT_TOP, PIC_ID_FAIL);
}

void clear_synth_test_step_4_result(void)
{
	lcd_fill_rectangle(SYNTH_TEST_ITEM_4_RESULT_LEFT, SYNTH_TEST_ITEM_4_RESULT_TOP, 
					SYNTH_TEST_ITEM_4_RESULT_LEFT + PIC_RESULT_WIDTH,
					SYNTH_TEST_ITEM_4_RESULT_TOP + PIC_RESULT_HEIGHT, SCREEN_BACK_COLOR);
}

void draw_synth_test_step_5_ac(uint32_t uA)
{
	lcd_display_number(SYNTH_TEST_ITEM_5_AC_VAL_LEFT, SYNTH_TEST_ITEM_5_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, false, true, EDITABLE_FORE_COLOR, FONT_32);
}


void clear_synth_test_step_5_ac(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_5_AC_VAL_LEFT, SYNTH_TEST_ITEM_5_AC_TOP, "   ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_5_voltage(uint32_t mV)
{
	lcd_display_number(SYNTH_TEST_ITEM_5_VOLTAGE_VAL_LEFT, SYNTH_TEST_ITEM_5_VOLTAGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_5_voltage(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_5_VOLTAGE_VAL_LEFT, SYNTH_TEST_ITEM_5_VOLTAGE_TOP, "     ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_5_current(uint32_t mA)
{
	lcd_display_number(SYNTH_TEST_ITEM_5_CURRENT_VAL_LEFT, SYNTH_TEST_ITEM_5_CURRENT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_5_current(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_5_CURRENT_VAL_LEFT, SYNTH_TEST_ITEM_5_CURRENT_TOP, "    ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_5_oc(uint32_t mA)
{
	lcd_display_number(SYNTH_TEST_ITEM_5_OC_VAL_LEFT, SYNTH_TEST_ITEM_5_OC_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_5_oc(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_5_OC_VAL_LEFT, SYNTH_TEST_ITEM_5_OC_TOP, "    ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_5_short(uint32_t mA)
{
	lcd_display_number(SYNTH_TEST_ITEM_5_SHORT_VAL_LEFT, SYNTH_TEST_ITEM_5_SHORT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_5_short(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_5_SHORT_VAL_LEFT, SYNTH_TEST_ITEM_5_SHORT_TOP, "    ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_5_OK(void)
{
	lcd_display_pic(SYNTH_TEST_ITEM_5_RESULT_LEFT, SYNTH_TEST_ITEM_5_RESULT_TOP, PIC_ID_OK);
}

void draw_synth_test_step_5_fail(void)
{
	lcd_display_pic(SYNTH_TEST_ITEM_5_RESULT_LEFT, SYNTH_TEST_ITEM_5_RESULT_TOP, PIC_ID_FAIL);
}

void clear_synth_test_step_5_result(void)
{
	lcd_fill_rectangle(SYNTH_TEST_ITEM_5_RESULT_LEFT, SYNTH_TEST_ITEM_5_RESULT_TOP, 
					SYNTH_TEST_ITEM_5_RESULT_LEFT + PIC_RESULT_WIDTH,
					SYNTH_TEST_ITEM_5_RESULT_TOP + PIC_RESULT_HEIGHT, SCREEN_BACK_COLOR);
}

void draw_synth_test_step_6_ac(uint32_t uA)
{
	lcd_display_number(SYNTH_TEST_ITEM_6_AC_VAL_LEFT, SYNTH_TEST_ITEM_6_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_6_ac(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_6_AC_VAL_LEFT, SYNTH_TEST_ITEM_6_AC_TOP, "   ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_6_voltage(uint32_t mV)
{
	lcd_display_number(SYNTH_TEST_ITEM_6_VOLTAGE_VAL_LEFT, SYNTH_TEST_ITEM_6_VOLTAGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_6_voltage(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_6_VOLTAGE_VAL_LEFT, SYNTH_TEST_ITEM_6_VOLTAGE_TOP, "     ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_6_current(uint32_t mA)
{
	lcd_display_number(SYNTH_TEST_ITEM_6_CURRENT_VAL_LEFT, SYNTH_TEST_ITEM_6_CURRENT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_6_current(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_6_CURRENT_VAL_LEFT, SYNTH_TEST_ITEM_6_CURRENT_TOP, "    ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_6_oc(uint32_t mA)
{
	lcd_display_number(SYNTH_TEST_ITEM_6_OC_VAL_LEFT, SYNTH_TEST_ITEM_6_OC_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_6_oc(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_6_OC_VAL_LEFT, SYNTH_TEST_ITEM_6_OC_TOP, "    ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_6_short(uint32_t mA)
{
	lcd_display_number(SYNTH_TEST_ITEM_6_SHORT_VAL_LEFT, SYNTH_TEST_ITEM_6_SHORT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_6_short(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_6_SHORT_VAL_LEFT, SYNTH_TEST_ITEM_6_SHORT_TOP, "    ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_6_OK(void)
{
	lcd_display_pic(SYNTH_TEST_ITEM_6_RESULT_LEFT, SYNTH_TEST_ITEM_6_RESULT_TOP, PIC_ID_OK);
}

void draw_synth_test_step_6_fail(void)
{
	lcd_display_pic(SYNTH_TEST_ITEM_6_RESULT_LEFT, SYNTH_TEST_ITEM_6_RESULT_TOP, PIC_ID_FAIL);
}

void clear_synth_test_step_6_result(void)
{
	lcd_fill_rectangle(SYNTH_TEST_ITEM_6_RESULT_LEFT, SYNTH_TEST_ITEM_6_RESULT_TOP, 
					SYNTH_TEST_ITEM_6_RESULT_LEFT + PIC_RESULT_WIDTH,
					SYNTH_TEST_ITEM_6_RESULT_TOP + PIC_RESULT_HEIGHT, SCREEN_BACK_COLOR);
}

void draw_synth_test_step_7_ac(uint32_t uA)
{
	lcd_display_number(SYNTH_TEST_ITEM_7_AC_VAL_LEFT, SYNTH_TEST_ITEM_7_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_7_ac(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_7_AC_VAL_LEFT, SYNTH_TEST_ITEM_7_AC_TOP, "   ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_7_voltage(uint32_t mV)
{
	lcd_display_number(SYNTH_TEST_ITEM_7_VOLTAGE_VAL_LEFT, SYNTH_TEST_ITEM_7_VOLTAGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_7_voltage(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_7_VOLTAGE_VAL_LEFT, SYNTH_TEST_ITEM_7_VOLTAGE_TOP, "     ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_7_current(uint32_t mA)
{
	lcd_display_number(SYNTH_TEST_ITEM_7_CURRENT_VAL_LEFT, SYNTH_TEST_ITEM_7_CURRENT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_7_current(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_7_CURRENT_VAL_LEFT, SYNTH_TEST_ITEM_7_CURRENT_TOP, "    ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_7_oc(uint32_t mA)
{
	lcd_display_number(SYNTH_TEST_ITEM_7_OC_VAL_LEFT, SYNTH_TEST_ITEM_7_OC_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_7_oc(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_7_OC_VAL_LEFT, SYNTH_TEST_ITEM_7_OC_TOP, "    ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_7_short(uint32_t mA)
{
	lcd_display_number(SYNTH_TEST_ITEM_7_SHORT_VAL_LEFT, SYNTH_TEST_ITEM_7_SHORT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, false, true, EDITABLE_FORE_COLOR, FONT_32);
}

void clear_synth_test_step_7_short(void)
{
	lcd_display_string(SYNTH_TEST_ITEM_7_SHORT_VAL_LEFT, SYNTH_TEST_ITEM_7_SHORT_TOP, "    ", EDITABLE_FORE_COLOR, FONT_32);
}

void draw_synth_test_step_7_OK(void)
{
	lcd_display_pic(SYNTH_TEST_ITEM_7_RESULT_LEFT, SYNTH_TEST_ITEM_7_RESULT_TOP, PIC_ID_OK);
}

void draw_synth_test_step_7_fail(void)
{
	lcd_display_pic(SYNTH_TEST_ITEM_7_RESULT_LEFT, SYNTH_TEST_ITEM_7_RESULT_TOP, PIC_ID_FAIL);
}

void clear_synth_test_step_7_result(void)
{
	lcd_fill_rectangle(SYNTH_TEST_ITEM_7_RESULT_LEFT, SYNTH_TEST_ITEM_7_RESULT_TOP, 
					SYNTH_TEST_ITEM_7_RESULT_LEFT + PIC_RESULT_WIDTH,
					SYNTH_TEST_ITEM_7_RESULT_TOP + PIC_RESULT_HEIGHT, SCREEN_BACK_COLOR);
}

void draw_synth_test_step_8_OK(void)
{
	lcd_display_pic(SYNTH_TEST_ITEM_8_RESULT_LEFT, SYNTH_TEST_ITEM_8_RESULT_TOP, PIC_ID_OK);
}

void clear_synth_test_step_8_result(void)
{
	lcd_fill_rectangle(SYNTH_TEST_ITEM_8_RESULT_LEFT, SYNTH_TEST_ITEM_8_RESULT_TOP, 
					SYNTH_TEST_ITEM_8_RESULT_LEFT + PIC_RESULT_WIDTH,
					SYNTH_TEST_ITEM_8_RESULT_TOP + PIC_RESULT_HEIGHT, SCREEN_BACK_COLOR);
}

/* cv mode */
void draw_cv_mode_menu(void)
{
	/* caption */
	lcd_display_string(MODE_CAPTION_LEFT, MODE_CAPTION_TOP, str_cv_mode, CAPTION_COLOR, FONT_64);

	lcd_display_string(MODE_SET_LEFT, MODE_SET_TOP, str_set_voltage, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(MODE_COLON_LEFT, MODE_SET_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	/* V */
	lcd_display_ascii_char(MODE_UNIT_LEFT, MODE_SET_TOP, 'V', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_string(MODE_AC_LEFT, MODE_AC_TOP, str_ac_current, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(MODE_COLON_LEFT, MODE_AC_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	/* mA */
	lcd_display_string(MODE_UNIT_LEFT, MODE_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_string(MODE_VOLTAGE_LEFT, MODE_VOLTAGE_TOP, str_voltage_val, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(MODE_COLON_LEFT, MODE_VOLTAGE_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	/* V */
	lcd_display_ascii_char(MODE_UNIT_LEFT, MODE_VOLTAGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_string(MODE_CURRENT_LEFT, MODE_CURRENT_TOP, str_current_val, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(MODE_COLON_LEFT, MODE_CURRENT_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	/* A */
	lcd_display_ascii_char(MODE_UNIT_LEFT, MODE_CURRENT_TOP, 'A', RDONLY_FORE_COLOR, FONT_48);
}

void draw_focus_voltage_val(uint32_t mV)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(MODE_VAL_LEFT, MODE_SET_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_edit_voltage_val(uint32_t mV)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(MODE_VAL_LEFT, MODE_SET_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

/* cc mode */
void draw_cc_mode_menu(void)
{
	/* caption */
	lcd_display_string(MODE_CAPTION_LEFT, MODE_CAPTION_TOP, str_cc_mode, CAPTION_COLOR, FONT_64);
	
	lcd_display_string(MODE_SET_LEFT, MODE_SET_TOP, str_set_current, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(MODE_COLON_LEFT, MODE_SET_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	/* A */
	lcd_display_ascii_char(MODE_UNIT_LEFT, MODE_SET_TOP, 'A', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_string(MODE_AC_LEFT, MODE_AC_TOP, str_ac_current, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(MODE_COLON_LEFT, MODE_AC_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	/* mA */
	lcd_display_string(MODE_UNIT_LEFT, MODE_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_string(MODE_VOLTAGE_LEFT, MODE_VOLTAGE_TOP, str_voltage_val, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(MODE_COLON_LEFT, MODE_VOLTAGE_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	/* V */
	lcd_display_ascii_char(MODE_UNIT_LEFT, MODE_VOLTAGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_48);
							
	lcd_display_string(MODE_CURRENT_LEFT, MODE_CURRENT_TOP, str_current_val, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(MODE_COLON_LEFT, MODE_CURRENT_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	/* A */
	lcd_display_ascii_char(MODE_UNIT_LEFT, MODE_CURRENT_TOP, 'A', RDONLY_FORE_COLOR, FONT_48);
}

void draw_focus_current_val(uint32_t mA)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(MODE_VAL_LEFT, MODE_SET_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_edit_current_val(uint32_t mA)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(MODE_VAL_LEFT, MODE_SET_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

/* cr mode */
void draw_cr_mode_menu(void)
{
	/* caption */
	lcd_display_string(MODE_CAPTION_LEFT, MODE_CAPTION_TOP, str_cr_mode, CAPTION_COLOR, FONT_64);

	lcd_display_string(MODE_SET_LEFT, MODE_SET_TOP, str_set_resistance, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(MODE_COLON_LEFT, MODE_SET_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	/* omega */
	lcd_display_string(MODE_UNIT_LEFT, MODE_SET_TOP, str_omega, RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_string(MODE_AC_LEFT, MODE_AC_TOP, str_ac_current, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(MODE_COLON_LEFT, MODE_AC_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	/* mA */
	lcd_display_string(MODE_UNIT_LEFT, MODE_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_string(MODE_VOLTAGE_LEFT, MODE_VOLTAGE_TOP, str_voltage_val, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(MODE_COLON_LEFT, MODE_VOLTAGE_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	/* V */
	lcd_display_ascii_char(MODE_UNIT_LEFT, MODE_VOLTAGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_string(MODE_CURRENT_LEFT, MODE_CURRENT_TOP, str_current_val, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(MODE_COLON_LEFT, MODE_CURRENT_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	/* A */
	lcd_display_ascii_char(MODE_UNIT_LEFT, MODE_CURRENT_TOP, 'A', RDONLY_FORE_COLOR, FONT_48);
}

void draw_focus_resist_val(uint32_t mO)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(MODE_VAL_LEFT, MODE_SET_TOP, mO / 1000, RESIST_VAL_INTEGER_LEN, mO % 1000 / s_number_divider[RESIST_VAL_DECIMAL_LEN], RESIST_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_edit_resist_val(uint32_t mO)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(MODE_VAL_LEFT, MODE_SET_TOP, mO / 1000, RESIST_VAL_INTEGER_LEN, mO % 1000 / s_number_divider[RESIST_VAL_DECIMAL_LEN], RESIST_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_ac_val(uint32_t uA)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(MODE_VAL_LEFT, MODE_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, uA % 1000 / s_number_divider[AC_VAL_DECIMAL_LEN], AC_VAL_DECIMAL_LEN, 
						false, true, RDONLY_FORE_COLOR, FONT_48);
}

void draw_voltage_val(uint32_t mV)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);

	lcd_display_number(MODE_VAL_LEFT, MODE_VOLTAGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, RDONLY_FORE_COLOR, FONT_48);
}

void draw_current_val(uint32_t mA)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(MODE_VAL_LEFT, MODE_CURRENT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, RDONLY_FORE_COLOR, FONT_48);
}

/* empty load setting */
void draw_empty_load_setting_menu(void)
{
	/* caption */
	lcd_display_string(EMPTY_LOAD_SETTING_CAPTION_LEFT, EMPTY_LOAD_SETTING_CAPTION_TOP, str_empty_load_test_caption, CAPTION_COLOR, FONT_64);

	/* test duration */
	lcd_display_string(EMPTY_LOAD_SETTING_TIME_LEFT, EMPTY_LOAD_SETTING_TIME_TOP, str_test_time, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(EMPTY_LOAD_SETTING_COLON_LEFT, EMPTY_LOAD_SETTING_TIME_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	/* ac */
	lcd_display_string(EMPTY_LOAD_SETTING_AC_LEFT, EMPTY_LOAD_SETTING_AC_TOP, str_ac_current, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(EMPTY_LOAD_SETTING_COLON_LEFT, EMPTY_LOAD_SETTING_AC_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(EMPTY_LOAD_SETTING_LESS_THAN_LEFT, EMPTY_LOAD_SETTING_AC_TOP, '<', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_string(EMPTY_LOAD_SETTING_AC_UNIT_LEFT, EMPTY_LOAD_SETTING_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_48);

	/* voltage range */
	lcd_display_string(EMPTY_LOAD_SETTING_VOLTAGE_RANGE_LEFT, EMPTY_LOAD_SETTING_VOLTAGE_RANGE_TOP, str_voltage_range, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(EMPTY_LOAD_SETTING_COLON_LEFT, EMPTY_LOAD_SETTING_VOLTAGE_RANGE_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(EMPTY_LOAD_SETTING_VOLTAGE_RANGE_HYPHON, EMPTY_LOAD_SETTING_VOLTAGE_RANGE_TOP, '-', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(EMPTY_LOAD_SETTING_VOLTAGE_RANGE_UNIT_LEFT, EMPTY_LOAD_SETTING_VOLTAGE_RANGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_48);	

	/* usb d+/d- detect */
	lcd_display_string(EMPTY_LOAD_SETTING_USB_DP_DN_LEFT, EMPTY_LOAD_SETTING_USB_DP_DN_TOP, str_usb_dp_dn_detect, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(EMPTY_LOAD_SETTING_COLON_LEFT, EMPTY_LOAD_SETTING_USB_DP_DN_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_string(EMPTY_LOAD_DP_DN_SETTING_LEFT, EMPTY_LOAD_DP_DN_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_48);
}

static void draw_empty_load_setting_time(uint32_t ms)
{
	if (ms == AUTOMATIC_TIME)
	{
		lcd_display_string(EMPTY_LOAD_SETTING_EDIT_TIME_LEFT, EMPTY_LOAD_SETTING_TIME_TOP, str_automatic, EDITABLE_FORE_COLOR, FONT_48);

		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(EMPTY_LOAD_SETTING_TIME_UNIT_LEFT, EMPTY_LOAD_SETTING_TIME_TOP, "  ", RDONLY_FORE_COLOR, FONT_48);
	}
	else
	{
		lcd_display_number(EMPTY_LOAD_SETTING_EDIT_TIME_LEFT, EMPTY_LOAD_SETTING_TIME_TOP, ms / 1000, TIME_VAL_INTEGER_LEN, ms % 1000 / s_number_divider[TIME_VAL_DECIMAL_LEN], TIME_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);

		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(EMPTY_LOAD_SETTING_TIME_UNIT_LEFT, EMPTY_LOAD_SETTING_TIME_TOP, str_second, RDONLY_FORE_COLOR, FONT_48);
	}
}

void draw_normal_empty_load_setting_time(uint32_t ms)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);

	draw_empty_load_setting_time(ms);
}

void draw_focus_empty_load_setting_time(uint32_t ms)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	draw_empty_load_setting_time(ms);		
}

void draw_edit_empty_load_setting_time(uint32_t ms)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	draw_empty_load_setting_time(ms);	
}

void draw_normal_empty_load_setting_ac(uint32_t uA)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(EMPTY_LOAD_SETTING_EDIT_AC_LEFT, EMPTY_LOAD_SETTING_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_focus_empty_load_setting_ac(uint32_t uA)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(EMPTY_LOAD_SETTING_EDIT_AC_LEFT, EMPTY_LOAD_SETTING_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_edit_empty_load_setting_ac(uint32_t uA)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(EMPTY_LOAD_SETTING_EDIT_AC_LEFT, EMPTY_LOAD_SETTING_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_normal_empty_load_setting_voltage_from(uint32_t mV)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(EMPTY_LOAD_SETTING_EDIT_VOLTAGE_FROM_LEFT, EMPTY_LOAD_SETTING_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_focus_empty_load_setting_voltage_from(uint32_t mV)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(EMPTY_LOAD_SETTING_EDIT_VOLTAGE_FROM_LEFT, EMPTY_LOAD_SETTING_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_edit_empty_load_setting_voltage_from(uint32_t mV)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(EMPTY_LOAD_SETTING_EDIT_VOLTAGE_FROM_LEFT, EMPTY_LOAD_SETTING_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_normal_empty_load_setting_voltage_to(uint32_t mV)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(EMPTY_LOAD_SETTING_EDIT_VOLTAGE_TO_LEFT, EMPTY_LOAD_SETTING_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_focus_empty_load_setting_voltage_to(uint32_t mV)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(EMPTY_LOAD_SETTING_EDIT_VOLTAGE_TO_LEFT, EMPTY_LOAD_SETTING_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_edit_empty_load_setting_voltage_to(uint32_t mV)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(EMPTY_LOAD_SETTING_EDIT_VOLTAGE_TO_LEFT, EMPTY_LOAD_SETTING_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

static const char *const s_dp_dn_mode_name[] = 
{
	[VOLTAGE_DIVIDE_MODE] = str_voltage_divide_mode,

	[SHORT_MODE]          = str_short_mode,

	[SHORT_RESIST_MODE]   = str_resist_mode
};

void draw_normal_empty_load_dp_dn_mode(USB_DP_DN_MODE mode)
{
	if (mode < DP_DN_MODE_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(EMPTY_LOAD_SETTING_USB_DP_DN_NODE_LEFT, EMPTY_LOAD_SETTING_USB_DP_DN_TOP, s_dp_dn_mode_name[mode], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_empty_load_dp_dn_mode(USB_DP_DN_MODE mode)
{
	if (mode < DP_DN_MODE_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(EMPTY_LOAD_SETTING_USB_DP_DN_NODE_LEFT, EMPTY_LOAD_SETTING_USB_DP_DN_TOP, s_dp_dn_mode_name[mode], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_edit_empty_load_dp_dn_mode(USB_DP_DN_MODE mode)
{
	if (mode < DP_DN_MODE_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(EMPTY_LOAD_SETTING_USB_DP_DN_NODE_LEFT, EMPTY_LOAD_SETTING_USB_DP_DN_TOP, s_dp_dn_mode_name[mode], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_normal_empty_load_dp_dn_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(EMPTY_LOAD_DP_DN_ON_OFF_LEFT, EMPTY_LOAD_DP_DN_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_empty_load_dp_dn_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(EMPTY_LOAD_DP_DN_ON_OFF_LEFT, EMPTY_LOAD_DP_DN_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_edit_empty_load_dp_dn_on_off(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(EMPTY_LOAD_DP_DN_ON_OFF_LEFT, EMPTY_LOAD_DP_DN_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_normal_empty_load_dp_dn_setting(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(EMPTY_LOAD_DP_DN_SETTING_LEFT, EMPTY_LOAD_DP_DN_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_focus_empty_load_dp_dn_setting(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	

	lcd_display_string(EMPTY_LOAD_DP_DN_SETTING_LEFT, EMPTY_LOAD_DP_DN_SETTING_TOP, str_enter_setting, EDITABLE_FORE_COLOR, FONT_48);
}
/* usb D+/D- divide mode */
void draw_dp_dn_divide_mode_menu(void)
{
	/* caption */
	lcd_set_back_color(SCREEN_BACK_COLOR);

	lcd_display_string(DP_DN_SETTING_CAPTION_LEFT, DP_DN_SETTING_CAPTION_TOP, str_usb_dp_dn_detect_setting,
				CAPTION_COLOR, FONT_64);

	/* divide mode */
	lcd_display_string(DP_DN_DIVIDE_MODE_LEFT, DP_DN_DIVIDE_MODE_TOP, str_voltage_divide_mode,
				RDONLY_FORE_COLOR, FONT_48);

	/* d+ range */
	lcd_display_string(DP_VOLTAGE_RANGE_LEFT, DP_VOLTAGE_RANGE_TOP, str_dp_voltage_range, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(DP_DN_DIVIDE_MODE_COLON_LEFT, DP_VOLTAGE_RANGE_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(DP_DN_DIVIDE_MODE_HYPHON_LEFT, DP_VOLTAGE_RANGE_TOP, '-', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(DP_DN_DIVIDE_MODE_UNIT_LEFT, DP_VOLTAGE_RANGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_48);	
	

	/* d- range */
	lcd_display_string(DN_VOLTAGE_RANGE_LEFT, DN_VOLTAGE_RANGE_TOP, str_dn_voltage_range, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(DP_DN_DIVIDE_MODE_COLON_LEFT, DN_VOLTAGE_RANGE_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(DP_DN_DIVIDE_MODE_HYPHON_LEFT, DN_VOLTAGE_RANGE_TOP, '-', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(DP_DN_DIVIDE_MODE_UNIT_LEFT, DN_VOLTAGE_RANGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_48);	
}

void draw_normal_divide_mode_dp_voltage_from(uint32_t mV)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);

	lcd_display_number(DP_DN_DIVIDE_MODE_EDIT_VOLTAGE_FROM_LEFT, DP_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_focus_divide_mode_dp_voltage_from(uint32_t mV)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);

	lcd_display_number(DP_DN_DIVIDE_MODE_EDIT_VOLTAGE_FROM_LEFT, DP_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_edit_divide_mode_dp_voltage_from(uint32_t mV)
{
	lcd_set_back_color(EDIT_BACK_COLOR);

	lcd_display_number(DP_DN_DIVIDE_MODE_EDIT_VOLTAGE_FROM_LEFT, DP_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_normal_divide_mode_dp_voltage_to(uint32_t mV)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);

	lcd_display_number(DP_DN_DIVIDE_MODE_EDIT_VOLTAGE_TO_LEFT, DP_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_focus_divide_mode_dp_voltage_to(uint32_t mV)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);

	lcd_display_number(DP_DN_DIVIDE_MODE_EDIT_VOLTAGE_TO_LEFT, DP_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_edit_divide_mode_dp_voltage_to(uint32_t mV)
{
	lcd_set_back_color(EDIT_BACK_COLOR);

	lcd_display_number(DP_DN_DIVIDE_MODE_EDIT_VOLTAGE_TO_LEFT, DP_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_normal_divide_mode_dn_voltage_from(uint32_t mV)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);

	lcd_display_number(DP_DN_DIVIDE_MODE_EDIT_VOLTAGE_FROM_LEFT, DN_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_focus_divide_mode_dn_voltage_from(uint32_t mV)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);

	lcd_display_number(DP_DN_DIVIDE_MODE_EDIT_VOLTAGE_FROM_LEFT, DN_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_edit_divide_mode_dn_voltage_from(uint32_t mV)
{
	lcd_set_back_color(EDIT_BACK_COLOR);

	lcd_display_number(DP_DN_DIVIDE_MODE_EDIT_VOLTAGE_FROM_LEFT, DN_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_normal_divide_mode_dn_voltage_to(uint32_t mV)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);

	lcd_display_number(DP_DN_DIVIDE_MODE_EDIT_VOLTAGE_TO_LEFT, DN_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_focus_divide_mode_dn_voltage_to(uint32_t mV)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);

	lcd_display_number(DP_DN_DIVIDE_MODE_EDIT_VOLTAGE_TO_LEFT, DN_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_edit_divide_mode_dn_voltage_to(uint32_t mV)
{
	lcd_set_back_color(EDIT_BACK_COLOR);

	lcd_display_number(DP_DN_DIVIDE_MODE_EDIT_VOLTAGE_TO_LEFT, DN_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

/* cc setting */
void draw_synth_cc_setting_caption(void)
{
	lcd_display_string(CC_SETTING_CAPTION_LEFT, CC_SETTING_CAPTION_TOP, str_cc_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_5v_cc_setting_caption(void)
{
	lcd_display_string(CC_SETTING_CAPTION_LEFT, CC_SETTING_CAPTION_TOP, str_5v_cc_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_9v_cc_setting_caption(void)
{
	lcd_display_string(CC_SETTING_CAPTION_LEFT, CC_SETTING_CAPTION_TOP, str_9v_cc_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_12v_cc_setting_caption(void)
{
	lcd_display_string(CC_SETTING_CAPTION_LEFT, CC_SETTING_CAPTION_TOP, str_12v_cc_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_20v_cc_setting_caption(void)
{
	lcd_display_string(CC_SETTING_CAPTION_LEFT, CC_SETTING_CAPTION_TOP, str_20v_cc_setting, CAPTION_COLOR, FONT_64);
}

void draw_cc_setting_menu(void)
{
	/* test time */
	lcd_display_string(CC_SETTING_TIME_LEFT, CC_SETTING_TIME_TOP, str_test_time, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(CC_SETTING_COLON_LEFT, CC_SETTING_TIME_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	/* ac */
	lcd_display_string(CC_SETTING_AC_LEFT, CC_SETTING_AC_TOP, str_ac_current, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(CC_SETTING_COLON_LEFT, CC_SETTING_AC_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(CC_SETTING_LESS_THAN_LEFT, CC_SETTING_AC_TOP, '<', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_string(CC_SETTING_AC_UNIT_LEFT, CC_SETTING_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_48);

	/* cc val */
	lcd_display_string(CC_SETTING_CC_VAL_LEFT, CC_SETTING_CC_VAL_TOP, str_cc_val, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(CC_SETTING_COLON_LEFT, CC_SETTING_CC_VAL_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(CC_SETTING_CC_VAL_UNIT_LEFT, CC_SETTING_CC_VAL_TOP, 'A', RDONLY_FORE_COLOR, FONT_48);

	/* voltage range */
	lcd_display_string(CC_SETTING_VOLTAGE_RANGE_LEFT, CC_SETTING_VOLTAGE_RANGE_TOP, str_voltage_range, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(CC_SETTING_COLON_LEFT, CC_SETTING_VOLTAGE_RANGE_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(CC_SETTING_VOLTAGE_RANGE_HYPHON, CC_SETTING_VOLTAGE_RANGE_TOP, '-', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(CC_SETTING_VOLTAGE_RANGE_UNIT_LEFT, CC_SETTING_VOLTAGE_RANGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_48);
}

static void draw_cc_setting_time(uint32_t ms)
{
	if (ms == AUTOMATIC_TIME)
	{
		lcd_display_string(CC_SETTING_EDIT_TIME_LEFT, CC_SETTING_TIME_TOP, str_automatic, EDITABLE_FORE_COLOR, FONT_48);

		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(CC_SETTING_TIME_UNIT_LEFT, CC_SETTING_TIME_TOP, "  ", RDONLY_FORE_COLOR, FONT_48);
	}
	else
	{
		lcd_display_number(CC_SETTING_EDIT_TIME_LEFT, CC_SETTING_TIME_TOP, ms / 1000, TIME_VAL_INTEGER_LEN, ms % 1000 / s_number_divider[TIME_VAL_DECIMAL_LEN], TIME_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);

		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(CC_SETTING_TIME_UNIT_LEFT, CC_SETTING_TIME_TOP, str_second, RDONLY_FORE_COLOR, FONT_48);
	}
}

void draw_normal_cc_setting_time(uint32_t ms)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	draw_cc_setting_time(ms);
}

void draw_focus_cc_setting_time(uint32_t ms)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	draw_cc_setting_time(ms);
}

void draw_edit_cc_setting_time(uint32_t ms)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	draw_cc_setting_time(ms);
}

void draw_normal_cc_setting_ac(uint32_t uA)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(CC_SETTING_EDIT_AC_LEFT, CC_SETTING_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_focus_cc_setting_ac(uint32_t uA)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(CC_SETTING_EDIT_AC_LEFT, CC_SETTING_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_edit_cc_setting_ac(uint32_t uA)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(CC_SETTING_EDIT_AC_LEFT, CC_SETTING_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_normal_cc_setting_cc(uint32_t mA)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(CC_SETTING_EDIT_CC_VAL_LEFT, CC_SETTING_CC_VAL_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_focus_cc_setting_cc(uint32_t mA)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(CC_SETTING_EDIT_CC_VAL_LEFT, CC_SETTING_CC_VAL_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_edit_cc_setting_cc(uint32_t mA)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(CC_SETTING_EDIT_CC_VAL_LEFT, CC_SETTING_CC_VAL_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_normal_cc_setting_voltage_from(uint32_t mV)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(CC_SETTING_EDIT_VOLTAGE_FROM_LEFT, CC_SETTING_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_focus_cc_setting_voltage_from(uint32_t mV)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(CC_SETTING_EDIT_VOLTAGE_FROM_LEFT, CC_SETTING_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_edit_cc_setting_voltage_from(uint32_t mV)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(CC_SETTING_EDIT_VOLTAGE_FROM_LEFT, CC_SETTING_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_normal_cc_setting_voltage_to(uint32_t mV)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(CC_SETTING_EDIT_VOLTAGE_TO_LEFT, CC_SETTING_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_focus_cc_setting_voltage_to(uint32_t mV)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(CC_SETTING_EDIT_VOLTAGE_TO_LEFT, CC_SETTING_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_edit_cc_setting_voltage_to(uint32_t mV)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(CC_SETTING_EDIT_VOLTAGE_TO_LEFT, CC_SETTING_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

/* cv setting */
void draw_synth_cv_setting_caption(void)
{
	/* caption */
	lcd_display_string(CV_SETTING_CAPTION_LEFT, CV_SETTING_CAPTION_TOP, str_cv_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_5v_cv_setting_caption(void)
{
	/* caption */
	lcd_display_string(CV_SETTING_CAPTION_LEFT, CV_SETTING_CAPTION_TOP, str_5v_cv_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_9v_cv_setting_caption(void)
{
	/* caption */
	lcd_display_string(CV_SETTING_CAPTION_LEFT, CV_SETTING_CAPTION_TOP, str_9v_cv_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_12v_cv_setting_caption(void)
{
	/* caption */
	lcd_display_string(CV_SETTING_CAPTION_LEFT, CV_SETTING_CAPTION_TOP, str_12v_cv_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_20v_cv_setting_caption(void)
{
	/* caption */
	lcd_display_string(CV_SETTING_CAPTION_LEFT, CV_SETTING_CAPTION_TOP, str_20v_cv_setting, CAPTION_COLOR, FONT_64);
}

void draw_cv_setting_menu(void)
{
	/* test time */
	lcd_display_string(CV_SETTING_TIME_LEFT, CV_SETTING_TIME_TOP, str_test_time, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(CV_SETTING_COLON_LEFT, CV_SETTING_TIME_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	/* ac */
	lcd_display_string(CV_SETTING_AC_LEFT, CV_SETTING_AC_TOP, str_ac_current, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(CV_SETTING_COLON_LEFT, CV_SETTING_AC_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(CC_SETTING_LESS_THAN_LEFT, CC_SETTING_AC_TOP, '<', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_string(CV_SETTING_AC_UNIT_LEFT, CV_SETTING_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_48);

	/* cv val */
	lcd_display_string(CV_SETTING_CV_VAL_LEFT, CV_SETTING_CV_VAL_TOP, str_cv_val, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(CV_SETTING_COLON_LEFT, CV_SETTING_CV_VAL_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_string(CV_SETTING_CV_VAL_UNIT_LEFT, CV_SETTING_CV_VAL_TOP, "V", RDONLY_FORE_COLOR, FONT_48);

	/* current range */
	lcd_display_string(CV_SETTING_CURRENT_RANGE_LEFT, CV_SETTING_CURRENT_RANGE_TOP, str_current_range, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(CV_SETTING_COLON_LEFT, CV_SETTING_CURRENT_RANGE_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	/* - */
	lcd_display_ascii_char(CV_SETTING_CURRENT_RANGE_HYPHON, CV_SETTING_CURRENT_RANGE_TOP, '-', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_ascii_char(CV_SETTING_CURRENT_RANGE_UNIT_LEFT, CV_SETTING_CURRENT_RANGE_TOP, 'A', RDONLY_FORE_COLOR, FONT_48);
}

static void draw_cv_setting_time(uint32_t ms)
{
	if (ms == AUTOMATIC_TIME)
	{
		lcd_display_string(CV_SETTING_EDIT_TIME_LEFT, CV_SETTING_TIME_TOP, str_automatic, EDITABLE_FORE_COLOR, FONT_48);

		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(CV_SETTING_TIME_UNIT_LEFT, CV_SETTING_TIME_TOP, "  ", RDONLY_FORE_COLOR, FONT_48);
	}
	else
	{
		lcd_display_number(CV_SETTING_EDIT_TIME_LEFT, CV_SETTING_TIME_TOP, ms / 1000, TIME_VAL_INTEGER_LEN, ms % 1000 / s_number_divider[TIME_VAL_DECIMAL_LEN], TIME_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);

		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(CV_SETTING_TIME_UNIT_LEFT, CV_SETTING_TIME_TOP, str_second, RDONLY_FORE_COLOR, FONT_48);
	}
}

void draw_normal_cv_setting_time(uint32_t ms)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	draw_cv_setting_time(ms);
}

void draw_focus_cv_setting_time(uint32_t ms)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	draw_cv_setting_time(ms);
}

void draw_edit_cv_setting_time(uint32_t ms)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	draw_cv_setting_time(ms);
}

void draw_normal_cv_setting_ac(uint32_t uA)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(CV_SETTING_EDIT_AC_LEFT, CV_SETTING_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_focus_cv_setting_ac(uint32_t uA)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(CV_SETTING_EDIT_AC_LEFT, CV_SETTING_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_edit_cv_setting_ac(uint32_t uA)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(CV_SETTING_EDIT_AC_LEFT, CV_SETTING_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_normal_cv_setting_cv(uint32_t mV)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(CV_SETTING_EDIT_CV_VAL_LEFT, CV_SETTING_CV_VAL_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_focus_cv_setting_cv(uint32_t mV)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(CV_SETTING_EDIT_CV_VAL_LEFT, CV_SETTING_CV_VAL_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_edit_cv_setting_cv(uint32_t mV)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(CV_SETTING_EDIT_CV_VAL_LEFT, CV_SETTING_CV_VAL_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_normal_cv_setting_current_from(uint32_t mA)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(CV_SETTING_EDIT_CURRENT_FROM_LEFT, CV_SETTING_CURRENT_RANGE_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_focus_cv_setting_current_from(uint32_t mA)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(CV_SETTING_EDIT_CURRENT_FROM_LEFT, CV_SETTING_CURRENT_RANGE_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_edit_cv_setting_current_from(uint32_t mA)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(CV_SETTING_EDIT_CURRENT_FROM_LEFT, CV_SETTING_CURRENT_RANGE_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_normal_cv_setting_current_to(uint32_t mA)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(CV_SETTING_EDIT_CURRENT_TO_LEFT, CV_SETTING_CURRENT_RANGE_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_focus_cv_setting_current_to(uint32_t mA)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(CV_SETTING_EDIT_CURRENT_TO_LEFT, CV_SETTING_CURRENT_RANGE_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_edit_cv_setting_current_to(uint32_t mA)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(CV_SETTING_EDIT_CURRENT_TO_LEFT, CV_SETTING_CURRENT_RANGE_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

/* cr setting */
void draw_synth_cr_setting_caption(void)
{
	/* caption */
	lcd_display_string(CR_SETTING_CAPTION_LEFT, CR_SETTING_CAPTION_TOP, str_cr_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_5v_cr_setting_caption(void)
{
	/* caption */
	lcd_display_string(CR_SETTING_CAPTION_LEFT, CR_SETTING_CAPTION_TOP, str_5v_cr_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_9v_cr_setting_caption(void)
{
	/* caption */
	lcd_display_string(CR_SETTING_CAPTION_LEFT, CR_SETTING_CAPTION_TOP, str_9v_cr_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_12v_cr_setting_caption(void)
{
	/* caption */
	lcd_display_string(CR_SETTING_CAPTION_LEFT, CR_SETTING_CAPTION_TOP, str_12v_cr_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_20v_cr_setting_caption(void)
{
	/* caption */
	lcd_display_string(CR_SETTING_CAPTION_LEFT, CR_SETTING_CAPTION_TOP, str_20v_cr_setting, CAPTION_COLOR, FONT_64);
}

void draw_cr_setting_menu(void)
{
	/* test time */
	lcd_display_string(CR_SETTING_TIME_LEFT, CR_SETTING_TIME_TOP, str_test_time, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(CR_SETTING_COLON_LEFT, CR_SETTING_TIME_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	/* ac */
	lcd_display_string(CR_SETTING_AC_LEFT, CR_SETTING_AC_TOP, str_ac_current, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(CR_SETTING_COLON_LEFT, CR_SETTING_AC_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(CR_SETTING_LESS_THAN_LEFT, CR_SETTING_AC_TOP, '<', RDONLY_FORE_COLOR, FONT_48);
		
	lcd_display_string(CR_SETTING_AC_UNIT_LEFT, CR_SETTING_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_48);

	/* cr */
	lcd_display_string(CR_SETTING_CR_VAL_LEFT, CR_SETTING_CR_VAL_TOP, str_cr_val, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(CR_SETTING_COLON_LEFT, CR_SETTING_CR_VAL_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_string(CR_SETTING_CR_VAL_UNIT_LEFT, CR_SETTING_CR_VAL_TOP, str_omega, RDONLY_FORE_COLOR, FONT_48);

	/* current range */
	lcd_display_string(CR_SETTING_CURRENT_RANGE_LEFT, CR_SETTING_CURRENT_RANGE_TOP, str_current_range, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(CR_SETTING_COLON_LEFT, CR_SETTING_CURRENT_RANGE_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	/* - */
	lcd_display_ascii_char(CR_SETTING_CURRENT_RANGE_HYPHON, CR_SETTING_CURRENT_RANGE_TOP, '-', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_ascii_char(CR_SETTING_CURRENT_RANGE_UNIT_LEFT, CR_SETTING_CURRENT_RANGE_TOP, 'A', RDONLY_FORE_COLOR, FONT_48);

	/* voltage range */
	lcd_display_string(CR_SETTING_VOLTAGE_RANGE_LEFT, CR_SETTING_VOLTAGE_RANGE_TOP, str_voltage_range, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(CR_SETTING_COLON_LEFT, CR_SETTING_VOLTAGE_RANGE_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	/* - */
	lcd_display_ascii_char(CR_SETTING_VOLTAGE_RANGE_HYPHON, CR_SETTING_VOLTAGE_RANGE_TOP, '-', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_ascii_char(CR_SETTING_VOLTAGE_RANGE_UNIT_LEFT, CR_SETTING_VOLTAGE_RANGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_48);
}

static void draw_cr_setting_time(uint32_t ms)
{
	if (ms == AUTOMATIC_TIME)
	{
		lcd_display_string(CR_SETTING_EDIT_TIME_LEFT, CR_SETTING_TIME_TOP, str_automatic, EDITABLE_FORE_COLOR, FONT_48);

		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(CR_SETTING_TIME_UNIT_LEFT, CR_SETTING_TIME_TOP, "  ", RDONLY_FORE_COLOR, FONT_48);
	}
	else
	{
		lcd_display_number(CR_SETTING_EDIT_TIME_LEFT, CR_SETTING_TIME_TOP, ms / 1000, TIME_VAL_INTEGER_LEN, ms % 1000 / s_number_divider[TIME_VAL_DECIMAL_LEN], TIME_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);

		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(CR_SETTING_TIME_UNIT_LEFT, CR_SETTING_TIME_TOP, str_second, RDONLY_FORE_COLOR, FONT_48);
	}
}

void draw_normal_cr_setting_time(uint32_t ms)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	draw_cr_setting_time(ms);
}

void draw_focus_cr_setting_time(uint32_t ms)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	draw_cr_setting_time(ms);
}

void draw_edit_cr_setting_time(uint32_t ms)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	draw_cr_setting_time(ms);
}

void draw_normal_cr_setting_ac(uint32_t uA)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(CR_SETTING_EDIT_AC_LEFT, CR_SETTING_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_focus_cr_setting_ac(uint32_t uA)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(CR_SETTING_EDIT_AC_LEFT, CR_SETTING_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_edit_cr_setting_ac(uint32_t uA)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(CR_SETTING_EDIT_AC_LEFT, CR_SETTING_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_normal_cr_setting_cr(uint32_t mO)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(CR_SETTING_EDIT_CR_VAL_LEFT, CR_SETTING_CR_VAL_TOP, mO / 1000, RESIST_VAL_INTEGER_LEN, mO % 1000 / s_number_divider[RESIST_VAL_DECIMAL_LEN], RESIST_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_focus_cr_setting_cr(uint32_t mO)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(CR_SETTING_EDIT_CR_VAL_LEFT, CR_SETTING_CR_VAL_TOP, mO / 1000, RESIST_VAL_INTEGER_LEN, mO % 1000 / s_number_divider[RESIST_VAL_DECIMAL_LEN], RESIST_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_edit_cr_setting_cr(uint32_t mO)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(CR_SETTING_EDIT_CR_VAL_LEFT, CR_SETTING_CR_VAL_TOP, mO / 1000, RESIST_VAL_INTEGER_LEN, mO % 1000 / s_number_divider[RESIST_VAL_DECIMAL_LEN], RESIST_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_normal_cr_setting_current_from(uint32_t mA)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(CR_SETTING_EDIT_CURRENT_FROM_LEFT, CR_SETTING_CURRENT_RANGE_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_focus_cr_setting_current_from(uint32_t mA)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(CR_SETTING_EDIT_CURRENT_FROM_LEFT, CR_SETTING_CURRENT_RANGE_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_edit_cr_setting_current_from(uint32_t mA)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(CR_SETTING_EDIT_CURRENT_FROM_LEFT, CR_SETTING_CURRENT_RANGE_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_normal_cr_setting_current_to(uint32_t mA)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(CR_SETTING_EDIT_CURRENT_TO_LEFT, CR_SETTING_CURRENT_RANGE_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_focus_cr_setting_current_to(uint32_t mA)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(CR_SETTING_EDIT_CURRENT_TO_LEFT, CR_SETTING_CURRENT_RANGE_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_edit_cr_setting_current_to(uint32_t mA)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(CR_SETTING_EDIT_CURRENT_TO_LEFT, CR_SETTING_CURRENT_RANGE_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_normal_cr_setting_voltage_from(uint32_t mV)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(CR_SETTING_EDIT_VOLTAGE_FROM_LEFT, CR_SETTING_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_focus_cr_setting_voltage_from(uint32_t mV)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(CR_SETTING_EDIT_VOLTAGE_FROM_LEFT, CR_SETTING_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_edit_cr_setting_voltage_from(uint32_t mV)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(CR_SETTING_EDIT_VOLTAGE_FROM_LEFT, CR_SETTING_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_normal_cr_setting_voltage_to(uint32_t mV)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(CR_SETTING_EDIT_VOLTAGE_TO_LEFT, CR_SETTING_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_focus_cr_setting_voltage_to(uint32_t mV)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(CR_SETTING_EDIT_VOLTAGE_TO_LEFT, CR_SETTING_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_edit_cr_setting_voltage_to(uint32_t mV)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(CR_SETTING_EDIT_VOLTAGE_TO_LEFT, CR_SETTING_VOLTAGE_RANGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

/* over current setting */
void draw_synth_oc_setting_caption(void)
{
	/* caption */
	lcd_display_string(OC_SETTING_CAPTION_LEFT, OC_SETTING_CAPTION_TOP, str_over_current_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_5v_oc_setting_caption(void)
{
	/* caption */
	lcd_display_string(OC_SETTING_CAPTION_LEFT, OC_SETTING_CAPTION_TOP, str_5v_over_current_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_9v_oc_setting_caption(void)
{
	/* caption */
	lcd_display_string(OC_SETTING_CAPTION_LEFT, OC_SETTING_CAPTION_TOP, str_9v_over_current_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_12v_oc_setting_caption(void)
{
	/* caption */
	lcd_display_string(OC_SETTING_CAPTION_LEFT, OC_SETTING_CAPTION_TOP, str_12v_over_current_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_20v_oc_setting_caption(void)
{
	/* caption */
	lcd_display_string(OC_SETTING_CAPTION_LEFT, OC_SETTING_CAPTION_TOP, str_20v_over_current_setting, CAPTION_COLOR, FONT_64);
}

void draw_oc_setting_menu(void)
{
	/* test interval */
	lcd_display_string(OC_SETTING_TIME_LEFT, OC_SETTING_TIME_TOP, str_test_interval, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(OC_SETTING_COLON_LEFT, OC_SETTING_TIME_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_string(OC_SETTING_TIME_UNIT_LEFT, OC_SETTING_TIME_TOP, str_second, RDONLY_FORE_COLOR, FONT_48);
	
	/* ac */
	lcd_display_string(OC_SETTING_AC_LEFT, OC_SETTING_AC_TOP, str_ac_current, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(OC_SETTING_COLON_LEFT, OC_SETTING_AC_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(OC_SETTING_LESS_THAN_LEFT, OC_SETTING_AC_TOP, '<', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_string(OC_SETTING_AC_UNIT_LEFT, OC_SETTING_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_48);

	/* over current */
	lcd_display_string(OC_SETTING_OC_VAL_LEFT, OC_SETTING_OC_VAL_TOP, str_over_current_val, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(OC_SETTING_COLON_LEFT, OC_SETTING_OC_VAL_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(OC_SETTING_LESS_THAN_LEFT, OC_SETTING_OC_VAL_TOP, '<', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(OC_SETTING_AC_UNIT_LEFT, OC_SETTING_OC_VAL_TOP, 'A', RDONLY_FORE_COLOR, FONT_48);	
}

void draw_normal_oc_setting_time(uint32_t ms)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(OC_SETTING_EDIT_TIME_LEFT, OC_SETTING_TIME_TOP, ms / 1000, TIME_VAL_INTEGER_LEN, ms % 1000 / s_number_divider[TIME_VAL_DECIMAL_LEN], TIME_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);
}

void draw_focus_oc_setting_time(uint32_t ms)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(OC_SETTING_EDIT_TIME_LEFT, OC_SETTING_TIME_TOP, ms / 1000, TIME_VAL_INTEGER_LEN, ms % 1000 / s_number_divider[TIME_VAL_DECIMAL_LEN], TIME_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_edit_oc_setting_time(uint32_t ms)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(OC_SETTING_EDIT_TIME_LEFT, OC_SETTING_TIME_TOP, ms / 1000, TIME_VAL_INTEGER_LEN, ms % 1000 / s_number_divider[TIME_VAL_DECIMAL_LEN], TIME_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_normal_oc_setting_ac(uint32_t uA)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(OC_SETTING_EDIT_AC_LEFT, OC_SETTING_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_focus_oc_setting_ac(uint32_t uA)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(OC_SETTING_EDIT_AC_LEFT, OC_SETTING_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_edit_oc_setting_ac(uint32_t uA)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(OC_SETTING_EDIT_AC_LEFT, OC_SETTING_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_normal_oc_setting_oc(uint32_t mA)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(OC_SETTING_EDIT_OC_VAL_LEFT, OC_SETTING_OC_VAL_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_focus_oc_setting_oc(uint32_t mA)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(OC_SETTING_EDIT_OC_VAL_LEFT, OC_SETTING_OC_VAL_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_edit_oc_setting_oc(uint32_t mA)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(OC_SETTING_EDIT_OC_VAL_LEFT, OC_SETTING_OC_VAL_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

/* short setting */
void draw_synth_short_setting_caption(void)
{
	/* caption */
	lcd_display_string(SHORT_SETTING_CAPTION_LEFT, SHORT_SETTING_CAPTION_TOP, str_short_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_5v_short_setting_caption(void)
{
	/* caption */
	lcd_display_string(SHORT_SETTING_CAPTION_LEFT, SHORT_SETTING_CAPTION_TOP, str_5v_short_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_9v_short_setting_caption(void)
{
	/* caption */
	lcd_display_string(SHORT_SETTING_CAPTION_LEFT, SHORT_SETTING_CAPTION_TOP, str_9v_short_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_12v_short_setting_caption(void)
{
	/* caption */
	lcd_display_string(SHORT_SETTING_CAPTION_LEFT, SHORT_SETTING_CAPTION_TOP, str_12v_short_setting, CAPTION_COLOR, FONT_64);
}

void draw_qc_20_20v_short_setting_caption(void)
{
	/* caption */
	lcd_display_string(SHORT_SETTING_CAPTION_LEFT, SHORT_SETTING_CAPTION_TOP, str_20v_short_setting, CAPTION_COLOR, FONT_64);
}

void draw_short_setting_menu(void)
{
	/* test time */
	lcd_display_string(SHORT_SETTING_TIME_LEFT, SHORT_SETTING_TIME_TOP, str_test_time, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(SHORT_SETTING_COLON_LEFT, SHORT_SETTING_TIME_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	/* ac */
	lcd_display_string(SHORT_SETTING_AC_LEFT, SHORT_SETTING_AC_TOP, str_ac_current, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(SHORT_SETTING_COLON_LEFT, SHORT_SETTING_AC_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(SHORT_SETTING_LESS_THAN_LEFT, SHORT_SETTING_AC_TOP, '<', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_string(SHORT_SETTING_AC_UNIT_LEFT, SHORT_SETTING_AC_TOP, "mA", RDONLY_FORE_COLOR, FONT_48);

	/* short current */
	lcd_display_string(SHORT_SETTING_SHORT_VAL_LEFT, SHORT_SETTING_SHORT_VAL_TOP, str_short_current, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(SHORT_SETTING_COLON_LEFT, SHORT_SETTING_SHORT_VAL_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(SHORT_SETTING_LESS_THAN_LEFT, SHORT_SETTING_SHORT_VAL_TOP, '<', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_ascii_char(SHORT_SETTING_AC_UNIT_LEFT, SHORT_SETTING_SHORT_VAL_TOP, 'A', RDONLY_FORE_COLOR, FONT_48);	
}

static void draw_short_setting_time(uint32_t ms)
{
	if (ms == AUTOMATIC_TIME)
	{
		lcd_display_string(SHORT_SETTING_EDIT_TIME_LEFT, SHORT_SETTING_TIME_TOP, str_automatic, EDITABLE_FORE_COLOR, FONT_48);

		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SHORT_SETTING_TIME_UNIT_LEFT, SHORT_SETTING_TIME_TOP, "  ", RDONLY_FORE_COLOR, FONT_48);
	}
	else
	{
		lcd_display_number(SHORT_SETTING_EDIT_TIME_LEFT, SHORT_SETTING_TIME_TOP, ms / 1000, TIME_VAL_INTEGER_LEN, ms % 1000 / s_number_divider[TIME_VAL_DECIMAL_LEN], TIME_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);

		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(SHORT_SETTING_TIME_UNIT_LEFT, SHORT_SETTING_TIME_TOP, str_second, RDONLY_FORE_COLOR, FONT_48);
	}
}

void draw_normal_short_setting_time(uint32_t ms)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	draw_short_setting_time(ms);	
}

void draw_focus_short_setting_time(uint32_t ms)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	draw_short_setting_time(ms);
}

void draw_edit_short_setting_time(uint32_t ms)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	draw_short_setting_time(ms);
}

void draw_normal_short_setting_ac(uint32_t uA)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(SHORT_SETTING_EDIT_AC_LEFT, SHORT_SETTING_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_focus_short_setting_ac(uint32_t uA)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(SHORT_SETTING_EDIT_AC_LEFT, SHORT_SETTING_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_edit_short_setting_ac(uint32_t uA)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(SHORT_SETTING_EDIT_AC_LEFT, SHORT_SETTING_AC_TOP, uA / 1000, AC_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_normal_short_setting_short(uint32_t mA)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(SHORT_SETTING_EDIT_SHORT_VAL_LEFT, SHORT_SETTING_SHORT_VAL_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_focus_short_setting_short(uint32_t mA)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(SHORT_SETTING_EDIT_SHORT_VAL_LEFT, SHORT_SETTING_SHORT_VAL_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_edit_short_setting_short(uint32_t mA)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(SHORT_SETTING_EDIT_SHORT_VAL_LEFT, SHORT_SETTING_SHORT_VAL_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_discharge_setting_menu(void)
{
	lcd_display_string(DISCHARGE_SETTING_CAPTION_LEFT, DISCHARGE_SETTING_CAPTION_TOP, str_discharge_setting, CAPTION_COLOR, FONT_64);

	lcd_display_string(DISCHARGE_SETTING_DISCHARGE_CURRENT_LEFT, DISCHARGE_SETTING_DISCHARGE_CURRENT_TOP, str_discharge_current, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(DISCHARGE_SETTING_COLON_LEFT, DISCHARGE_SETTING_DISCHARGE_CURRENT_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(DISCHARGE_SETTING_DISCHARGE_CURRENT_UNIT_LEFT, DISCHARGE_SETTING_DISCHARGE_CURRENT_TOP, 'A', RDONLY_FORE_COLOR, FONT_48);
		
	lcd_display_string(DISCHARGE_SETTING_DISCHARGE_TIME_LEFT, DISCHARGE_SETTING_DISCHARGE_TIME_TOP, str_discharge_time, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(DISCHARGE_SETTING_COLON_LEFT, DISCHARGE_SETTING_DISCHARGE_TIME_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_string(DISCHARGE_SETTING_DISCHARGE_TIME_UNIT_LEFT, DISCHARGE_SETTING_DISCHARGE_TIME_TOP, str_second, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_string(DISCHARGE_SETTING_INDICATE_DELAY_TIME_LEFT, DISCHARGE_SETTING_INDICATE_DELAY_TIME_TOP, str_indicate_delay_time, RDONLY_FORE_COLOR, FONT_48);

	lcd_display_ascii_char(DISCHARGE_SETTING_COLON_LEFT, DISCHARGE_SETTING_INDICATE_DELAY_TIME_TOP, ':', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_string(DISCHARGE_SETTING_INDICATE_DELAY_TIME_UNIT_LEFT, DISCHARGE_SETTING_INDICATE_DELAY_TIME_TOP, str_second, RDONLY_FORE_COLOR, FONT_48);				
}

void draw_normal_discharge_setting_discharge_current(uint32_t mA)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(DISCHARGE_SETTING_EDIT_DISCHARGE_CURRENT_LEFT, DISCHARGE_SETTING_DISCHARGE_CURRENT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_focus_discharge_setting_discharge_current(uint32_t mA)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(DISCHARGE_SETTING_EDIT_DISCHARGE_CURRENT_LEFT, DISCHARGE_SETTING_DISCHARGE_CURRENT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_edit_discharge_setting_discharge_current(uint32_t mA)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(DISCHARGE_SETTING_EDIT_DISCHARGE_CURRENT_LEFT, DISCHARGE_SETTING_DISCHARGE_CURRENT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_normal_discharge_setting_discharge_time(uint32_t ms)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(DISCHARGE_SETTING_EDIT_DISCHARGE_TIME_LEFT, DISCHARGE_SETTING_DISCHARGE_TIME_TOP, ms / 1000, TIME_VAL_INTEGER_LEN, ms % 1000 / s_number_divider[TIME_VAL_DECIMAL_LEN], TIME_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_focus_discharge_setting_discharge_time(uint32_t ms)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(DISCHARGE_SETTING_EDIT_DISCHARGE_TIME_LEFT, DISCHARGE_SETTING_DISCHARGE_TIME_TOP, ms / 1000, TIME_VAL_INTEGER_LEN, ms % 1000 / s_number_divider[TIME_VAL_DECIMAL_LEN], TIME_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_edit_discharge_setting_discharge_time(uint32_t ms)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(DISCHARGE_SETTING_EDIT_DISCHARGE_TIME_LEFT, DISCHARGE_SETTING_DISCHARGE_TIME_TOP, ms / 1000, TIME_VAL_INTEGER_LEN, ms % 1000 / s_number_divider[TIME_VAL_DECIMAL_LEN], TIME_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_normal_discharge_setting_indicate_delay_time(uint32_t ms)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(DISCHARGE_SETTING_EDIT_INDICATE_DELAY_TIME_LEFT, DISCHARGE_SETTING_INDICATE_DELAY_TIME_TOP, ms / 1000, TIME_VAL_INTEGER_LEN, ms % 1000 / s_number_divider[TIME_VAL_DECIMAL_LEN], TIME_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_focus_discharge_setting_indicate_delay_time(uint32_t ms)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(DISCHARGE_SETTING_EDIT_INDICATE_DELAY_TIME_LEFT, DISCHARGE_SETTING_INDICATE_DELAY_TIME_TOP, ms / 1000, TIME_VAL_INTEGER_LEN, ms % 1000 / s_number_divider[TIME_VAL_DECIMAL_LEN], TIME_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_edit_discharge_setting_indicate_delay_time(uint32_t ms)
{
	lcd_set_back_color(EDIT_BACK_COLOR);
	
	lcd_display_number(DISCHARGE_SETTING_EDIT_INDICATE_DELAY_TIME_LEFT, DISCHARGE_SETTING_INDICATE_DELAY_TIME_TOP, ms / 1000, TIME_VAL_INTEGER_LEN, ms % 1000 / s_number_divider[TIME_VAL_DECIMAL_LEN], TIME_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

/* channel setting */
#define FIRST_CHANNEL_LEFT     150
#define CHANNEL_HORZ_INTERVAL  150

#define FIRST_CHANNEL_HEIGHT   100
#define CHANNEL_VERT_INTERVAL  200

#define FIRST_OPTION_LEFT      FIRST_CHANNEL_LEFT
#define FIRST_OPTION_HEIGHT    150

void draw_channel_setting_menu(void)
{
	int i, j;

	char buffer[10];
	
	/* caption */
	lcd_set_back_color(SCREEN_BACK_COLOR);

	lcd_display_string(CHANNEL_SETTING_CAPTION_LEFT, CHANNEL_SETTING_CAPTION_TOP, str_channel_set, CAPTION_COLOR, FONT_64);

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < CHANNEL_COUNT / 2; j++)
		{
			rt_sprintf(buffer, "%s%d", str_channel, i * CHANNEL_COUNT / 2 + j + 1);
			lcd_display_string(FIRST_CHANNEL_LEFT + j * CHANNEL_HORZ_INTERVAL, FIRST_CHANNEL_HEIGHT + i * CHANNEL_VERT_INTERVAL, buffer, RDONLY_FORE_COLOR, FONT_48);
		}
	}
}

void draw_channel_setting_option(OPTION_ON_OFF  on_off[CHANNEL_COUNT], CHANNEL_STATUS status[CHANNEL_COUNT])
{
	int i, j;
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < CHANNEL_COUNT / 2; j++)
		{
			if (status[i * CHANNEL_COUNT / 2 + j] == CHANNEL_ONLINE)
			{
				if (on_off[i * CHANNEL_COUNT / 2 + j] == OPTION_ON)
				{
					lcd_display_string(FIRST_OPTION_LEFT + j * CHANNEL_HORZ_INTERVAL, FIRST_OPTION_HEIGHT + i * CHANNEL_VERT_INTERVAL, str_on, EDITABLE_FORE_COLOR, FONT_48);
				}
				else
				{
					lcd_display_string(FIRST_OPTION_LEFT + j * CHANNEL_HORZ_INTERVAL, FIRST_OPTION_HEIGHT + i * CHANNEL_VERT_INTERVAL, str_off, EDITABLE_FORE_COLOR, FONT_48);
				}
			}
			else
			{
				lcd_display_string(FIRST_OPTION_LEFT + j * CHANNEL_HORZ_INTERVAL, FIRST_OPTION_HEIGHT + i * CHANNEL_VERT_INTERVAL, "N/A", RDONLY_FORE_COLOR, FONT_48);
			}
		}
	}
}

void draw_normal_channel_option(int channel, OPTION_ON_OFF on_off)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);

	if (on_off == OPTION_ON)
	{
		lcd_display_string(FIRST_OPTION_LEFT + channel % (CHANNEL_COUNT / 2) * CHANNEL_HORZ_INTERVAL, 
							FIRST_OPTION_HEIGHT + channel / (CHANNEL_COUNT / 2) * CHANNEL_VERT_INTERVAL, str_on, EDITABLE_FORE_COLOR, FONT_48);
	}
	else
	{
		lcd_display_string(FIRST_OPTION_LEFT + channel % (CHANNEL_COUNT / 2) * CHANNEL_HORZ_INTERVAL, 
							FIRST_OPTION_HEIGHT + channel / (CHANNEL_COUNT / 2) * CHANNEL_VERT_INTERVAL, str_off, EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_focus_channel_option(int channel, OPTION_ON_OFF on_off)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);

	if (on_off == OPTION_ON)
	{
		lcd_display_string(FIRST_OPTION_LEFT + channel % (CHANNEL_COUNT / 2) * CHANNEL_HORZ_INTERVAL, 
							FIRST_OPTION_HEIGHT + channel / (CHANNEL_COUNT / 2) * CHANNEL_VERT_INTERVAL, str_on, EDITABLE_FORE_COLOR, FONT_48);
	}
	else
	{
		lcd_display_string(FIRST_OPTION_LEFT + channel % (CHANNEL_COUNT / 2) * CHANNEL_HORZ_INTERVAL, 
							FIRST_OPTION_HEIGHT + channel / (CHANNEL_COUNT / 2) * CHANNEL_VERT_INTERVAL, str_off, EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_edit_channel_option(int channel, OPTION_ON_OFF on_off)
{
	lcd_set_back_color(EDIT_BACK_COLOR);

	if (on_off == OPTION_ON)
	{
		lcd_display_string(FIRST_OPTION_LEFT + channel % (CHANNEL_COUNT / 2) * CHANNEL_HORZ_INTERVAL, 
							FIRST_OPTION_HEIGHT + channel / (CHANNEL_COUNT / 2) * CHANNEL_VERT_INTERVAL, str_on, EDITABLE_FORE_COLOR, FONT_48);
	}
	else
	{
		lcd_display_string(FIRST_OPTION_LEFT + channel % (CHANNEL_COUNT / 2) * CHANNEL_HORZ_INTERVAL, 
							FIRST_OPTION_HEIGHT + channel / (CHANNEL_COUNT / 2) * CHANNEL_VERT_INTERVAL, str_off, EDITABLE_FORE_COLOR, FONT_48);
	}	
}

/* factory menu */
void draw_factory_menu(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(FACTORY_CAPTION_LEFT, FACTORY_CAPTION_TOP, str_factory_mode, CAPTION_COLOR, FONT_64);
	
	draw_normal_factory_item_adjust();

	draw_normal_factory_item_privilege();

	draw_normal_factory_item_life();

	draw_normal_factory_item_phone();

	draw_normal_factory_item_password();
}

void draw_normal_factory_item_adjust(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(FACTORY_MENU_ITEM_LEFT, FACTORY_MENU_ITEM_TOP_ADJUST, str_device_adjust, RDONLY_FORE_COLOR, FONT_48);
}

void draw_focus_factory_item_adjust(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(FACTORY_MENU_ITEM_LEFT, FACTORY_MENU_ITEM_TOP_ADJUST, str_device_adjust, RDONLY_FORE_COLOR, FONT_48);
}

void draw_normal_factory_item_privilege(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(FACTORY_MENU_ITEM_LEFT, FACTORY_MENU_ITEM_TOP_PRIVILEGE, str_device_privilege, RDONLY_FORE_COLOR, FONT_48);
}

void draw_focus_factory_item_privilege(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(FACTORY_MENU_ITEM_LEFT, FACTORY_MENU_ITEM_TOP_PRIVILEGE, str_device_privilege, RDONLY_FORE_COLOR, FONT_48);
}
void draw_normal_factory_item_life(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(FACTORY_MENU_ITEM_LEFT, FACTORY_MENU_ITEM_TOP_LIFE, str_life_limit, RDONLY_FORE_COLOR, FONT_48);
}

void draw_focus_factory_item_life(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(FACTORY_MENU_ITEM_LEFT, FACTORY_MENU_ITEM_TOP_LIFE, str_life_limit, RDONLY_FORE_COLOR, FONT_48);
}

void draw_normal_factory_item_phone(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(FACTORY_MENU_ITEM_LEFT, FACTORY_MENU_ITEM_TOP_PHONE, str_phone_setting, RDONLY_FORE_COLOR, FONT_48);
}

void draw_focus_factory_item_phone(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(FACTORY_MENU_ITEM_LEFT, FACTORY_MENU_ITEM_TOP_PHONE, str_phone_setting, RDONLY_FORE_COLOR, FONT_48);
}

void draw_normal_factory_item_password(void)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(FACTORY_MENU_ITEM_LEFT, FACTORY_MENU_ITEM_TOP_PASSWORD, str_password_setting, RDONLY_FORE_COLOR, FONT_48);
}

void draw_focus_factory_item_password(void)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(FACTORY_MENU_ITEM_LEFT, FACTORY_MENU_ITEM_TOP_PASSWORD, str_password_setting, RDONLY_FORE_COLOR, FONT_48);
}

/* device adjust menu */
void draw_device_adjust_menu(void)
{
	/* caption */
	lcd_display_string(DEVICE_ADJUST_CAPTION_LEFT, DEVICE_ADJUST_CAPTION_TOP, str_channel_voltage_current_adjust, 
						CAPTION_COLOR, FONT_64);
	
	/* voltage */
	lcd_display_string(VOLTAGE_ADJUST_LEFT, VOLTAGE_ADJUST_TOP, str_voltage_adjust,
						CAPTION_COLOR, FONT_48);
	
	lcd_display_string(DEVICE_MEASURE_VOLTAGE_LEFT, DEVICE_MEASURE_VOLTAGE_TOP, str_device_measure_voltage,
						RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(DEVICE_ADJUST_COLON_LEFT, DEVICE_MEASURE_VOLTAGE_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_ascii_char(DEVICE_ADJUST_UNIT_LEFT, DEVICE_MEASURE_VOLTAGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_48);

	lcd_display_string(DEVICE_ADJUSTED_VOLTAGE_LEFT, DEVICE_ADJUSTED_VOLTAGE_TOP, str_device_adjusted_voltage,
						RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(DEVICE_ADJUST_COLON_LEFT, DEVICE_ADJUSTED_VOLTAGE_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_ascii_char(DEVICE_ADJUST_UNIT_LEFT, DEVICE_ADJUSTED_VOLTAGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_string(ACTUAL_VOLTAGE_LEFT, ACTUAL_VOLTAGE_TOP, str_actual_voltage,
						RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(DEVICE_ADJUST_COLON_LEFT, ACTUAL_VOLTAGE_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_ascii_char(DEVICE_ADJUST_UNIT_LEFT, ACTUAL_VOLTAGE_TOP, 'V', RDONLY_FORE_COLOR, FONT_48);
	
	/* current */
	lcd_display_string(CURRENT_ADJUST_LEFT, CURRENT_ADJUST_TOP, str_current_adjust,
						CAPTION_COLOR, FONT_48);
	
	lcd_display_string(DEVICE_MEASURE_CURRENT_LEFT, DEVICE_MEASURE_CURRENT_TOP, str_device_measure_current,
						RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(DEVICE_ADJUST_COLON_LEFT, DEVICE_MEASURE_CURRENT_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_ascii_char(DEVICE_ADJUST_UNIT_LEFT, DEVICE_MEASURE_CURRENT_TOP, 'A',
						RDONLY_FORE_COLOR, FONT_48);

	lcd_display_string(DEVICE_ADJUSTED_CURRENT_LEFT, DEVICE_ADJUSTED_CURRENT_TOP, str_device_adjusted_current,
						RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(DEVICE_ADJUST_COLON_LEFT, DEVICE_ADJUSTED_CURRENT_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_ascii_char(DEVICE_ADJUST_UNIT_LEFT, DEVICE_ADJUSTED_CURRENT_TOP, 'A',
						RDONLY_FORE_COLOR, FONT_48);
						
	lcd_display_string(ACTUAL_CURRENT_LEFT, ACTUAL_CURRENT_TOP, str_actual_current,
						RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(DEVICE_ADJUST_COLON_LEFT, ACTUAL_CURRENT_TOP, ':', RDONLY_FORE_COLOR, FONT_48);	

	lcd_display_ascii_char(DEVICE_ADJUST_UNIT_LEFT, ACTUAL_CURRENT_TOP, 'A',
						RDONLY_FORE_COLOR, FONT_48);
}

void draw_normal_device_adjust_channel(uint32_t channel)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);

	lcd_display_number(DEVICE_ADJUST_CHANNEL_LEFT, DEVICE_ADJUST_CAPTION_TOP, channel, CHANNEL_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_64);	
}

void draw_focus_device_adjust_channel(uint32_t channel)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);

	lcd_display_number(DEVICE_ADJUST_CHANNEL_LEFT, DEVICE_ADJUST_CAPTION_TOP, channel, CHANNEL_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_64);	
}

void draw_edit_device_adjust_channel(uint32_t channel)
{
	lcd_set_back_color(EDIT_BACK_COLOR);

	lcd_display_number(DEVICE_ADJUST_CHANNEL_LEFT, DEVICE_ADJUST_CAPTION_TOP, channel, CHANNEL_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_64);	
}

void draw_device_adjust_measure_voltage(uint32_t mV)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);

	lcd_display_number(DEVICE_MEASURE_VOLTAGE_VAL_LEFT, DEVICE_MEASURE_VOLTAGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, RDONLY_FORE_COLOR, FONT_48);	
}

void draw_device_adjusted_voltage(uint32_t mV)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);

	lcd_display_number(DEVICE_MEASURE_VOLTAGE_VAL_LEFT, DEVICE_ADJUSTED_VOLTAGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, RDONLY_FORE_COLOR, FONT_48);
}

void draw_normal_device_adjust_actual_voltage(uint32_t mV)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);

	lcd_display_number(DEVICE_EDIT_ACTUAL_VOLTAGE_LEFT, ACTUAL_VOLTAGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_focus_device_adjust_actual_voltage(uint32_t mV)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);

	lcd_display_number(DEVICE_EDIT_ACTUAL_VOLTAGE_LEFT, ACTUAL_VOLTAGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_edit_device_adjust_actual_voltage(uint32_t mV)
{
	lcd_set_back_color(EDIT_BACK_COLOR);

	lcd_display_number(DEVICE_EDIT_ACTUAL_VOLTAGE_LEFT, ACTUAL_VOLTAGE_TOP, mV / 1000, VOLTAGE_VAL_INTEGER_LEN, mV % 1000 / s_number_divider[VOLTAGE_VAL_DECIMAL_LEN], VOLTAGE_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_device_adjust_measure_current(uint32_t mA)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);

	lcd_display_number(DEVICE_MEASURE_CURRENT_VAL_LEFT, DEVICE_MEASURE_CURRENT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, RDONLY_FORE_COLOR, FONT_48);	
}

void draw_device_adjusted_current(uint32_t mA)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);

	lcd_display_number(DEVICE_MEASURE_CURRENT_VAL_LEFT, DEVICE_ADJUSTED_CURRENT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, RDONLY_FORE_COLOR, FONT_48);	
}

void draw_normal_device_adjust_actual_current(uint32_t mA)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);

	lcd_display_number(DEVICE_EDIT_ACTUAL_CURRENT_VAL_LEFT, ACTUAL_CURRENT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_focus_device_adjust_actual_current(uint32_t mA)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);

	lcd_display_number(DEVICE_EDIT_ACTUAL_CURRENT_VAL_LEFT, ACTUAL_CURRENT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

void draw_edit_device_adjust_actual_current(uint32_t mA)
{
	lcd_set_back_color(EDIT_BACK_COLOR);

	lcd_display_number(DEVICE_EDIT_ACTUAL_CURRENT_VAL_LEFT, ACTUAL_CURRENT_TOP, mA / 1000, CURRENT_VAL_INTEGER_LEN, mA % 1000 / s_number_divider[CURRENT_VAL_DECIMAL_LEN], CURRENT_VAL_DECIMAL_LEN, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

/* device privilege menu */
void draw_device_privilege_menu(void)
{
	/* caption */
	lcd_display_string(DEVICE_PRIVILEGE_CAPTION_LEFT, DEVICE_PRIVILEGE_CAPTION_TOP, str_device_privilege, 
						CAPTION_COLOR, FONT_64);
	
	lcd_display_string(QC20_ON_OFF_LEFT, QC20_ON_OFF_TOP, str_QC20_test, 
						RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_ascii_char(DEVICE_PRIVILEGE_COLON_LEFT, QC20_ON_OFF_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_string(MTK_ON_OFF_LEFT, MTK_ON_OFF_TOP, str_MTK_test, 
						RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_ascii_char(DEVICE_PRIVILEGE_COLON_LEFT, MTK_ON_OFF_TOP, ':', RDONLY_FORE_COLOR, FONT_48);	
}

void draw_normal_QC20_item(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(QC20_EDIT_ON_OFF_LEFT, QC20_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], 
						EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_focus_QC20_item(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(QC20_EDIT_ON_OFF_LEFT, QC20_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], 
						EDITABLE_FORE_COLOR, FONT_48);
	}
}

void draw_edit_QC20_item(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(QC20_EDIT_ON_OFF_LEFT, QC20_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], 
						EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_normal_MTK_item(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(SCREEN_BACK_COLOR);
		
		lcd_display_string(MTK_EDIT_ON_OFF_LEFT, MTK_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], 
						EDITABLE_FORE_COLOR, FONT_48);
	}	
}

void draw_focus_MTK_item(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(FOCUS_BACK_COLOR);
		
		lcd_display_string(MTK_EDIT_ON_OFF_LEFT, MTK_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], 
						EDITABLE_FORE_COLOR, FONT_48);
	}		
}

void draw_edit_MTK_item(OPTION_ON_OFF on_off)
{
	if (on_off < OPTION_ON_OFF_COUNT)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		
		lcd_display_string(MTK_EDIT_ON_OFF_LEFT, MTK_ON_OFF_TOP, s_OPTION_ON_OFF_name[on_off], 
						EDITABLE_FORE_COLOR, FONT_48);
	}		
}

/* life limit menu */
void draw_life_limit_menu(void)
{
	/* caption */
	lcd_display_string(LIFE_LIMIT_CAPTION_LEFT, LIFE_LIMIT_CAPTION_TOP, str_life_limit, 
						CAPTION_COLOR, FONT_64);
	
	/* power on count setting */
	lcd_display_string(LIFE_COUNT_SETTING_LEFT, LIFE_COUNT_SETTING_TOP, str_power_on_count_setting, 
						RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(LIFE_LIMIT_SETTING_COLON_LEFT, LIFE_COUNT_SETTING_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_string(LIFE_LIMIT_SETTING_UNIT_LEFT, LIFE_COUNT_SETTING_TOP, str_count, RDONLY_FORE_COLOR, FONT_48);
	
	/* actual power on count */
	lcd_display_string(LIFE_ACTUAL_COUNT_LEFT, LIFE_ACTUAL_COUNT_TOP, str_actual_power_on_count, 
						RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(LIFE_LIMIT_SETTING_COLON_LEFT, LIFE_ACTUAL_COUNT_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_string(LIFE_LIMIT_SETTING_UNIT_LEFT, LIFE_ACTUAL_COUNT_TOP, str_count, RDONLY_FORE_COLOR, FONT_48);	

	/* reminder */
	lcd_display_string(LIFE_LIMIT_REMINDER_LEFT, LIFE_LIMIT_REMINDER_TOP, str_clear_power_on_count_reminder, 
							CAPTION_COLOR, FONT_32);
}

void draw_normal_life_count_setting_item(uint32_t integer)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(LIFE_COUNT_SETTING_EDIT_LEFT, LIFE_COUNT_SETTING_TOP, integer, POWER_ON_COUNT_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_focus_life_count_setting_item(uint32_t integer)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(LIFE_COUNT_SETTING_EDIT_LEFT, LIFE_COUNT_SETTING_TOP, integer, POWER_ON_COUNT_VAL_INTEGER_LEN, 0, 0, 
						false, true, EDITABLE_FORE_COLOR, FONT_48);		
}

#define MAX_EDIT_BUF_LEN   12
static char s_edit_buffer[MAX_EDIT_BUF_LEN + 1];

static uint8_t s_cur_edit_index = 0;

static void number_enter_edit_mode(uint32_t x, uint32_t y, uint32_t integer, uint32_t integer_len, uint32_t decimal, uint32_t decimal_len, lcd_font font)
{
	bool res = number_to_string(s_edit_buffer, sizeof(s_edit_buffer), integer, integer_len, decimal, decimal_len, true, false);
	if (res)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		lcd_display_string(x, y, s_edit_buffer, EDITABLE_FORE_COLOR, font);
		
		s_cur_edit_index = 0;
		
		lcd_display_ascii_char(x + s_cur_edit_index * get_font_width(font), y, s_edit_buffer[s_cur_edit_index], HIGHLIGHT_COLOR, font);
	}
}

static bool number_literal_enter_edit_mode(uint32_t x, uint32_t y, const char *number, uint32_t number_len, lcd_font font)
{
	bool res = literal_number_to_string(s_edit_buffer, sizeof(s_edit_buffer), number, number_len);
	if (res)
	{
		lcd_set_back_color(EDIT_BACK_COLOR);
		lcd_display_string(x, y, s_edit_buffer, EDITABLE_FORE_COLOR, font);
		
		s_cur_edit_index = 0;
		
		lcd_display_ascii_char(x + s_cur_edit_index * get_font_width(font), y, s_edit_buffer[s_cur_edit_index], HIGHLIGHT_COLOR, font);
	}	

	return res;
}

static void number_digit_increase(uint32_t x, uint32_t y, lcd_font font)
{
	uint8_t digit = s_edit_buffer[s_cur_edit_index] - '0';
	digit++;
	digit %= 10;
	s_edit_buffer[s_cur_edit_index] = digit + '0';
	
	lcd_set_back_color(EDIT_BACK_COLOR);

	lcd_display_ascii_char(x + s_cur_edit_index * get_font_width(font), y, s_edit_buffer[s_cur_edit_index], HIGHLIGHT_COLOR, font);
}

static void number_digit_decrease(uint32_t x, uint32_t y, lcd_font font)
{
	uint8_t digit = s_edit_buffer[s_cur_edit_index] - '0';
	digit += 9;
	digit %= 10;
	s_edit_buffer[s_cur_edit_index] = digit + '0';
	
	lcd_set_back_color(EDIT_BACK_COLOR);

	lcd_display_ascii_char(x + s_cur_edit_index * get_font_width(font), y, s_edit_buffer[s_cur_edit_index], HIGHLIGHT_COLOR, font);
}

static void number_prev_digit(uint32_t x, uint32_t y, lcd_font font)
{
	if (s_cur_edit_index == 0)
	{
		return;
	}
	
	s_cur_edit_index--;
	if (s_edit_buffer[s_cur_edit_index] == '.')
	{
		s_cur_edit_index--;
	}
	
	lcd_set_back_color(EDIT_BACK_COLOR);
	lcd_display_string(x, y, s_edit_buffer, EDITABLE_FORE_COLOR, font);

	lcd_display_ascii_char(x + s_cur_edit_index * get_font_width(font), y, s_edit_buffer[s_cur_edit_index], HIGHLIGHT_COLOR, font);	
}

static void number_next_digit(uint32_t x, uint32_t y, lcd_font font)
{
	if (s_edit_buffer[s_cur_edit_index + 1] == '\0')
	{
		return;
	}
	
	s_cur_edit_index++;
	if (s_edit_buffer[s_cur_edit_index] == '.')
	{
		s_cur_edit_index++;
	}
	
	lcd_set_back_color(EDIT_BACK_COLOR);
	lcd_display_string(x, y, s_edit_buffer, EDITABLE_FORE_COLOR, font);

	lcd_display_ascii_char(x + s_cur_edit_index * get_font_width(font), y, s_edit_buffer[s_cur_edit_index], HIGHLIGHT_COLOR, font);	
}

static bool get_edit_val(uint32_t *integer, uint32_t *decimal)
{
	return string_to_number(s_edit_buffer, integer, decimal);
}

void enter_edit_life_count_setting_item(uint32_t integer)
{
	number_enter_edit_mode(LIFE_COUNT_SETTING_EDIT_LEFT, LIFE_COUNT_SETTING_TOP, integer, POWER_ON_COUNT_VAL_INTEGER_LEN, 0, 0,
							FONT_48);	
}

uint32_t get_edit_life_count_setting_item(void)
{
	uint32_t integer;
	uint32_t decimal;
			
	if (get_edit_val(&integer, &decimal))
	{
		return integer;
	}
	
	return (uint32_t)-1;
}

void increase_edit_life_count_setting_digit(void)
{
	number_digit_increase(LIFE_COUNT_SETTING_EDIT_LEFT, LIFE_COUNT_SETTING_TOP, FONT_48);
}

void decrease_edit_life_count_setting_digit(void)
{
	number_digit_decrease(LIFE_COUNT_SETTING_EDIT_LEFT, LIFE_COUNT_SETTING_TOP, FONT_48);
}

void move_prev_edit_life_count_setting_digit(void)
{
	number_prev_digit(LIFE_COUNT_SETTING_EDIT_LEFT, LIFE_COUNT_SETTING_TOP, FONT_48);
}

void move_next_edit_life_count_setting_digit(void)
{
	number_next_digit(LIFE_COUNT_SETTING_EDIT_LEFT, LIFE_COUNT_SETTING_TOP, FONT_48);
}

void draw_normal_life_actual_count_item(uint32_t integer)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(LIFE_ACTUAL_COUNT_VAL_LEFT, LIFE_ACTUAL_COUNT_TOP, integer, POWER_ON_COUNT_VAL_INTEGER_LEN, 0, 0, 
						false, true, RDONLY_FORE_COLOR, FONT_48);	
}

/* phone setting menu */
void draw_phone_setting_menu(void)
{
	/* caption */
	lcd_display_string(PHONE_SETTING_CAPTION_LEFT, PHONE_SETTING_CAPTION_TOP, str_phone_setting, 
						CAPTION_COLOR, FONT_64);
	
	/* default number */
	lcd_display_string(PHONE_SETTING_DEFAULT_NUMBER_LEFT, PHONE_SETTING_DEFAULT_NUMBER_TOP, str_default_phone_number, 
						RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(PHONE_SETTING_COLON_LEFT, PHONE_SETTING_DEFAULT_NUMBER_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	/* customer numer */
	lcd_display_string(PHONE_SETTING_CUSTOMER_NUMBER_LEFT, PHONE_SETTING_CUSTOMER_NUMBER_TOP, str_customer_number, 
						RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(PHONE_SETTING_COLON_LEFT, PHONE_SETTING_CUSTOMER_NUMBER_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	/* customer number power on count */
	lcd_display_string(PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_LEFT, PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_TOP, str_customer_power_on_count, 
						RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(PHONE_SETTING_COLON_LEFT, PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_string(PHONE_SETTING_UNIT_LEFT, PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_TOP, str_count, RDONLY_FORE_COLOR, FONT_48);

	/* actual customer number power on count */
	lcd_display_string(PHONE_SETTING_ACTUAL_POWER_ON_COUNT_LEFT, PHONE_SETTING_ACTUAL_POWER_ON_COUNT_TOP, str_actual_power_on_count, 
						RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(PHONE_SETTING_COLON_LEFT, PHONE_SETTING_ACTUAL_POWER_ON_COUNT_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
	
	lcd_display_string(PHONE_SETTING_UNIT_LEFT, PHONE_SETTING_ACTUAL_POWER_ON_COUNT_TOP, str_count, RDONLY_FORE_COLOR, FONT_48);

	/* reminder */
	lcd_display_string(PHONE_SETTING_REMINDER_LEFT, PHONE_SETTING_REMINDER_TOP, str_clear_power_on_count_reminder, 
							CAPTION_COLOR, FONT_32);
}

void draw_normal_phone_setting_default_number(const PHONE_NUMBER *phone_number)
{
	char phone[PHONE_NUMBER_LEN + 1];
	rt_memcpy(phone, phone_number->phone_number, PHONE_NUMBER_LEN);
	phone[PHONE_NUMBER_LEN] = '\0';
	
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(PHONE_SETTING_DEFAULT_NUMBER_EDIT_LEFT, PHONE_SETTING_DEFAULT_NUMBER_TOP, phone, EDITABLE_FORE_COLOR, FONT_48); 
}

void draw_focus_phone_setting_default_number(const PHONE_NUMBER *phone_number)
{
	char phone[PHONE_NUMBER_LEN + 1];
	rt_memcpy(phone, phone_number->phone_number, PHONE_NUMBER_LEN);
	phone[PHONE_NUMBER_LEN] = '\0';
	
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(PHONE_SETTING_DEFAULT_NUMBER_EDIT_LEFT, PHONE_SETTING_DEFAULT_NUMBER_TOP, phone, EDITABLE_FORE_COLOR, FONT_48); 
}

void enter_edit_phone_setting_default_number(const PHONE_NUMBER *phone_number)
{
	number_literal_enter_edit_mode(PHONE_SETTING_DEFAULT_NUMBER_EDIT_LEFT, PHONE_SETTING_DEFAULT_NUMBER_TOP, phone_number->phone_number, sizeof(phone_number->phone_number), FONT_48);
}

void get_edit_phone_setting_default_number(PHONE_NUMBER *phone_number)
{
	literal_string_to_number(phone_number->phone_number, sizeof(phone_number->phone_number), s_edit_buffer, sizeof(s_edit_buffer));
}

void increase_edit_phone_setting_default_number_digit(void)
{
	number_digit_increase(PHONE_SETTING_DEFAULT_NUMBER_EDIT_LEFT, PHONE_SETTING_DEFAULT_NUMBER_TOP, FONT_48);
}

void decrease_edit_phone_setting_default_number_digit(void)
{
	number_digit_decrease(PHONE_SETTING_DEFAULT_NUMBER_EDIT_LEFT, PHONE_SETTING_DEFAULT_NUMBER_TOP, FONT_48);
}

void move_prev_edit_phone_setting_default_number_digit(void)
{
	number_prev_digit(PHONE_SETTING_DEFAULT_NUMBER_EDIT_LEFT, PHONE_SETTING_DEFAULT_NUMBER_TOP, FONT_48);
}

void move_next_edit_phone_setting_default_number_digit(void)
{
	number_next_digit(PHONE_SETTING_DEFAULT_NUMBER_EDIT_LEFT, PHONE_SETTING_DEFAULT_NUMBER_TOP, FONT_48);
}

void draw_normal_phone_setting_customer_number(const PHONE_NUMBER *phone_number)
{
	char phone[PHONE_NUMBER_LEN + 1];
	rt_memcpy(phone, phone_number->phone_number, PHONE_NUMBER_LEN);
	phone[PHONE_NUMBER_LEN] = '\0';
	
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_string(PHONE_SETTING_CUSTOMER_NUMBER_EDIT_LEFT, PHONE_SETTING_CUSTOMER_NUMBER_TOP, phone, EDITABLE_FORE_COLOR, FONT_48); 	
}

void draw_focus_phone_setting_customer_number(const PHONE_NUMBER *phone_number)
{
	char phone[PHONE_NUMBER_LEN + 1];
	rt_memcpy(phone, phone_number->phone_number, PHONE_NUMBER_LEN);
	phone[PHONE_NUMBER_LEN] = '\0';
	
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(PHONE_SETTING_CUSTOMER_NUMBER_EDIT_LEFT, PHONE_SETTING_CUSTOMER_NUMBER_TOP, phone, EDITABLE_FORE_COLOR, FONT_48); 	
}

void enter_edit_phone_setting_customer_number(const PHONE_NUMBER *phone_number)
{
	number_literal_enter_edit_mode(PHONE_SETTING_CUSTOMER_NUMBER_EDIT_LEFT, PHONE_SETTING_CUSTOMER_NUMBER_TOP, phone_number->phone_number, sizeof(phone_number->phone_number), FONT_48);
}

void get_edit_phone_setting_customer_number(PHONE_NUMBER *phone_number)
{
	literal_string_to_number(phone_number->phone_number, sizeof(phone_number->phone_number), s_edit_buffer, sizeof(s_edit_buffer));
}

void increase_edit_phone_setting_customer_number_digit(void)
{
	number_digit_increase(PHONE_SETTING_CUSTOMER_NUMBER_EDIT_LEFT, PHONE_SETTING_CUSTOMER_NUMBER_TOP, FONT_48);	
}

void decrease_edit_phone_setting_customer_number_digit(void)
{
	number_digit_decrease(PHONE_SETTING_CUSTOMER_NUMBER_EDIT_LEFT, PHONE_SETTING_CUSTOMER_NUMBER_TOP, FONT_48);	
}

void move_prev_edit_phone_setting_customer_number_digit(void)
{
	number_prev_digit(PHONE_SETTING_CUSTOMER_NUMBER_EDIT_LEFT, PHONE_SETTING_CUSTOMER_NUMBER_TOP, FONT_48);
}

void move_next_edit_phone_setting_customer_number_digit(void)
{
	number_next_digit(PHONE_SETTING_CUSTOMER_NUMBER_EDIT_LEFT, PHONE_SETTING_CUSTOMER_NUMBER_TOP, FONT_48);	
}

void draw_normal_phone_setting_customer_power_on_limit(uint32_t integer)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_EDIT_LEFT, PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_TOP, 
						integer, POWER_ON_COUNT_VAL_INTEGER_LEN, 0, 0, false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void draw_focus_phone_setting_customer_power_on_limit(uint32_t integer)
{
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_number(PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_EDIT_LEFT, PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_TOP, 
						integer, POWER_ON_COUNT_VAL_INTEGER_LEN, 0, 0, false, true, EDITABLE_FORE_COLOR, FONT_48);	
}

void enter_edit_phone_setting_customer_power_on_limit(uint32_t integer)
{
	number_enter_edit_mode(PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_EDIT_LEFT, PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_TOP, integer, POWER_ON_COUNT_VAL_INTEGER_LEN, 0, 0,
							FONT_48);	
}

uint16_t get_edit_phone_setting_customer_power_on_limit(void)
{
	uint32_t integer;
	uint32_t decimal;
			
	if (get_edit_val(&integer, &decimal))
	{
		return integer;
	}
	
	return (uint16_t)-1;
}

void increase_edit_phone_setting_customer_power_on_limit_digit(void)
{
	number_digit_increase(PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_EDIT_LEFT, PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_TOP, FONT_48);	
}

void decrease_edit_phone_setting_customer_power_on_limit_digit(void)
{
	number_digit_decrease(PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_EDIT_LEFT, PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_TOP, FONT_48);		
}

void move_prev_edit_phone_setting_customer_power_on_limit_digit(void)
{
	number_prev_digit(PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_EDIT_LEFT, PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_TOP, FONT_48);	
}

void move_next_edit_phone_setting_customer_power_on_limit_digit(void)
{
	number_next_digit(PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_EDIT_LEFT, PHONE_SETTING_CUSTOMER_POWER_ON_COUNT_TOP, FONT_48);	
}

void draw_normal_phone_setting_actual_customer_power_on_count(uint32_t integer)
{
	lcd_set_back_color(SCREEN_BACK_COLOR);
	
	lcd_display_number(PHONE_SETTING_ACTUAL_POWER_ON_COUNT_VAL_LEFT, PHONE_SETTING_ACTUAL_POWER_ON_COUNT_TOP, 
						integer, POWER_ON_COUNT_VAL_INTEGER_LEN, 0, 0, false, true, RDONLY_FORE_COLOR, FONT_48);	
}


/* password setting menu */
void draw_password_setting_menu(void)
{
	/* caption */
	lcd_display_string(PASSWORD_SETTING_CAPTION_LEFT, PASSWORD_SETTING_CAPTION_TOP, str_password_setting, 
						CAPTION_COLOR, FONT_64);
	
	/* password */
	lcd_display_string(PASSWORD_SETTING_LEFT, PASSWORD_SETTING_TOP, str_password, RDONLY_FORE_COLOR, FONT_48);
	lcd_display_ascii_char(PASSWORD_SETTING_COLON_LEFT, PASSWORD_SETTING_TOP, ':', RDONLY_FORE_COLOR, FONT_48);
}

void enter_edit_password(const PASSWORD *password)
{
	number_literal_enter_edit_mode(PASSWORD_EDIT_LEFT, PASSWORD_EDIT_TOP, password->password, sizeof(password->password), FONT_48);
}

void get_edit_password(PASSWORD *password)
{
	literal_string_to_number(password->password, sizeof(password->password), s_edit_buffer, sizeof(s_edit_buffer));
}

void increase_edit_password_digit(void)
{
	number_digit_increase(PASSWORD_EDIT_LEFT, PASSWORD_EDIT_TOP, FONT_48);
}

void decrease_edit_password_digit(void)
{
	number_digit_decrease(PASSWORD_EDIT_LEFT, PASSWORD_EDIT_TOP, FONT_48);
}

void move_prev_edit_password_digit(void)
{
	number_prev_digit(PASSWORD_EDIT_LEFT, PASSWORD_EDIT_TOP, FONT_48);
}

void move_next_edit_password_digit(void)
{
	number_next_digit(PASSWORD_EDIT_LEFT, PASSWORD_EDIT_TOP, FONT_48);
}


/* password menu */
void draw_password_menu(void)
{
	/* caption */
	lcd_display_string(PASSWORD_SETTING_CAPTION_LEFT, PASSWORD_SETTING_CAPTION_TOP, str_input_password, 
						CAPTION_COLOR, FONT_64);
}


void draw_focus_password_setting_password(const PASSWORD *password)
{
	char pwd[PASSWORD_LEN + 1];
	rt_memcpy(pwd, password->password, PASSWORD_LEN);
	pwd[PASSWORD_LEN] = '\0';
	
	lcd_set_back_color(FOCUS_BACK_COLOR);
	
	lcd_display_string(PASSWORD_SETTING_PASSWORD_EDIT_LEFT, PASSWORD_SETTING_TOP, pwd, EDITABLE_FORE_COLOR, FONT_48); 
}


void enter_edit_password_setting_password(const PASSWORD *password)
{
	number_literal_enter_edit_mode(PASSWORD_SETTING_PASSWORD_EDIT_LEFT, PASSWORD_SETTING_TOP, password->password, sizeof(password->password), FONT_48);
}

void get_edit_password_setting_password(PASSWORD *password)
{
	literal_string_to_number(password->password, sizeof(password->password), s_edit_buffer, sizeof(s_edit_buffer));
}

void increase_edit_password_setting_password_digit(void)
{
	number_digit_increase(PASSWORD_SETTING_PASSWORD_EDIT_LEFT, PASSWORD_SETTING_TOP, FONT_48);
}

void decrease_edit_password_setting_password_digit(void)
{
	number_digit_decrease(PASSWORD_SETTING_PASSWORD_EDIT_LEFT, PASSWORD_SETTING_TOP, FONT_48);
}

void move_prev_edit_password_setting_password_digit(void)
{
	number_prev_digit(PASSWORD_SETTING_PASSWORD_EDIT_LEFT, PASSWORD_SETTING_TOP, FONT_48);
}

void move_next_edit_password_setting_password_digit(void)
{
	number_next_digit(PASSWORD_SETTING_PASSWORD_EDIT_LEFT, PASSWORD_SETTING_TOP, FONT_48);
}
