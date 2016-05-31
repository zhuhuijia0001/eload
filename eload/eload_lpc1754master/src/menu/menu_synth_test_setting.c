#include <stdint.h>
#include "type.h"
#include "key_define.h"

#include "menu_op.h"
#include "menu.h"

#include "lcd.h"
#include "draw.h"

#include "beeper.h"

/* focus item */
typedef enum 
{
	FOCUS_GROUP,
	
	FOCUS_TEST,
	
	FOCUS_ITEM_1_SETTING,
	
	FOCUS_ITEM_2_TYPE,
	FOCUS_ITEM_2_ON_OFF,
	FOCUS_ITEM_2_SETTING,
	
	FOCUS_ITEM_3_TYPE,
	FOCUS_ITEM_3_ON_OFF,
	FOCUS_ITEM_3_SETTING,	

	FOCUS_ITEM_4_TYPE,
	FOCUS_ITEM_4_ON_OFF,
	FOCUS_ITEM_4_SETTING,
	
	FOCUS_ITEM_5_TYPE,
	FOCUS_ITEM_5_ON_OFF,
	FOCUS_ITEM_5_SETTING,
	
	FOCUS_ITEM_6_TYPE,
	FOCUS_ITEM_6_ON_OFF,
	FOCUS_ITEM_6_SETTING,
	
	FOCUS_ITEM_7_TYPE,
	FOCUS_ITEM_7_ON_OFF,
	FOCUS_ITEM_7_SETTING,

	FOCUS_ITEM_8_ON_OFF,
	FOCUS_ITEM_8_SETTING,
	
	FOCUS_NONE,
	FOCUS_COUNT = FOCUS_NONE
} focus_item;

/* edit item */
typedef enum
{
	EDIT_GROUP,
	
	EDIT_ITEM_2_TYPE,
	EDIT_ITEM_2_ON_OFF,

	EDIT_ITEM_3_TYPE,
	EDIT_ITEM_3_ON_OFF,

	EDIT_ITEM_4_TYPE,
	EDIT_ITEM_4_ON_OFF,	
	
	EDIT_ITEM_5_TYPE,
	EDIT_ITEM_5_ON_OFF,
	
	EDIT_ITEM_6_TYPE,
	EDIT_ITEM_6_ON_OFF,
	
	EDIT_ITEM_7_TYPE,
	EDIT_ITEM_7_ON_OFF,

	EDIT_ITEM_8_ON_OFF,
	
	EDIT_NONE,
	
	EDIT_COUNT = EDIT_NONE
} edit_item;


/* focus layout */
static const focus_item s_focus_arr[][4] = 
{
	{ FOCUS_NONE,     FOCUS_GROUP,          FOCUS_NONE,          FOCUS_TEST },

	{ FOCUS_NONE,     FOCUS_NONE,           FOCUS_NONE,          FOCUS_ITEM_5_TYPE },
	{ FOCUS_NONE,     FOCUS_ITEM_1_SETTING, FOCUS_ITEM_5_ON_OFF, FOCUS_ITEM_5_SETTING }, 

	{ FOCUS_NONE,         FOCUS_ITEM_2_TYPE,    FOCUS_NONE,          FOCUS_ITEM_6_TYPE }, 
	{ FOCUS_ITEM_2_ON_OFF,FOCUS_ITEM_2_SETTING, FOCUS_ITEM_6_ON_OFF, FOCUS_ITEM_6_SETTING }, 

	{ FOCUS_NONE,          FOCUS_ITEM_3_TYPE,    FOCUS_NONE,          FOCUS_ITEM_7_TYPE },
	{ FOCUS_ITEM_3_ON_OFF, FOCUS_ITEM_3_SETTING, FOCUS_ITEM_7_ON_OFF, FOCUS_ITEM_7_SETTING }, 
	
	{ FOCUS_NONE,          FOCUS_ITEM_4_TYPE,    FOCUS_NONE, FOCUS_NONE }, 
	{ FOCUS_ITEM_4_ON_OFF, FOCUS_ITEM_4_SETTING, FOCUS_ITEM_8_ON_OFF, FOCUS_ITEM_8_SETTING }
};

static int s_focus_row_index = 0;
static int s_focus_col_index = 0;

static edit_item s_edit_item = EDIT_NONE;

static TEST_CATEGORY s_cur_test_category = TEST_CATEGORY_SYNTH_TEST;

static DEVICE_PRIVILEGE s_device_privilege;

/* test index to type */
static const SYNTH_TEST_TYPE s_synth_test_index_to_type[] = 
{
	[0] = SYNTH_TEST_CV,
	
	[1] = SYNTH_TEST_CC,
	
	[2] = SYNTH_TEST_CR,
	
	[3] = SYNTH_TEST_OVER_CURRENT,
	
	[4] = SYNTH_TEST_SHORT
};

static const QC_20_TEST_TYPE s_qc_20_test_index_to_type[] = 
{
	[0] = QC_20_5V_TEST_CV,

	[1] = QC_20_5V_TEST_CC,

	[2] = QC_20_5V_TEST_CR,

	[3] = QC_20_5V_TEST_OVER_CURRENT,

	[4] = QC_20_5V_TEST_SHORT,


	[5] = QC_20_9V_TEST_CV,

	[6] = QC_20_9V_TEST_CC,

	[7] = QC_20_9V_TEST_CR,

	[8] = QC_20_9V_TEST_OVER_CURRENT,

	[9] = QC_20_9V_TEST_SHORT,


	[10] = QC_20_12V_TEST_CV,

	[11] = QC_20_12V_TEST_CC,

	[12] = QC_20_12V_TEST_CR,

	[13] = QC_20_12V_TEST_OVER_CURRENT,

	[14] = QC_20_12V_TEST_SHORT,


	[15] = QC_20_20V_TEST_CV,

	[16] = QC_20_20V_TEST_CC,

	[17] = QC_20_20V_TEST_CR,

	[18] = QC_20_20V_TEST_OVER_CURRENT,

	[19] = QC_20_20V_TEST_SHORT,
};

static const MTK_TEST_TYPE s_mtk_test_index_to_type[] = 
{
	[0] = MTK_5V_TEST_CV,

	[1] = MTK_5V_TEST_CC,

	[2] = MTK_5V_TEST_CR,

	[3] = MTK_5V_TEST_OVER_CURRENT,

	[4] = MTK_5V_TEST_SHORT,


	[5] = MTK_9V_TEST_CV,

	[6] = MTK_9V_TEST_CC,

	[7] = MTK_9V_TEST_CR,

	[8] = MTK_9V_TEST_OVER_CURRENT,

	[9] = MTK_9V_TEST_SHORT,


	[10] = MTK_12V_TEST_CV,

	[11] = MTK_12V_TEST_CC,

	[12] = MTK_12V_TEST_CR,

	[13] = MTK_12V_TEST_OVER_CURRENT,

	[14] = MTK_12V_TEST_SHORT,


	[15] = MTK_20V_TEST_CV,

	[16] = MTK_20V_TEST_CC,

	[17] = MTK_20V_TEST_CR,

	[18] = MTK_20V_TEST_OVER_CURRENT,

	[19] = MTK_20V_TEST_SHORT,
};

/* test type to index */
static const int s_synth_test_type_to_index[] = 
{
	[SYNTH_TEST_CV] = 0,

	[SYNTH_TEST_CC] = 1,

	[SYNTH_TEST_CR] = 2,

	[SYNTH_TEST_OVER_CURRENT] = 3,

	[SYNTH_TEST_SHORT] = 4
};

static const int s_qc_20_test_type_to_index[] = 
{
	[QC_20_5V_TEST_CV] = 0,

	[QC_20_5V_TEST_CC] = 1,

	[QC_20_5V_TEST_CR] = 2,

	[QC_20_5V_TEST_OVER_CURRENT] = 3,

	[QC_20_5V_TEST_SHORT] = 4,


	[QC_20_9V_TEST_CV] = 5,

	[QC_20_9V_TEST_CC] = 6,

	[QC_20_9V_TEST_CR] = 7,

	[QC_20_9V_TEST_OVER_CURRENT] = 8,

	[QC_20_9V_TEST_SHORT] = 9,


	[QC_20_12V_TEST_CV] = 10,

	[QC_20_12V_TEST_CC] = 11,

	[QC_20_12V_TEST_CR] = 12,

	[QC_20_12V_TEST_OVER_CURRENT] = 13,

	[QC_20_12V_TEST_SHORT] = 14,


	[QC_20_20V_TEST_CV] = 15,

	[QC_20_20V_TEST_CC] = 16,

	[QC_20_20V_TEST_CR] = 17,

	[QC_20_20V_TEST_OVER_CURRENT] = 18,

	[QC_20_20V_TEST_SHORT] = 19,
};

static const int s_mtk_test_type_to_index[] = 
{
	[MTK_5V_TEST_CV] = 0,

	[MTK_5V_TEST_CC] = 1,

	[MTK_5V_TEST_CR] = 2,

	[MTK_5V_TEST_OVER_CURRENT] = 3,

	[MTK_5V_TEST_SHORT] = 4,


	[MTK_9V_TEST_CV] = 5,

	[MTK_9V_TEST_CC] = 6,

	[MTK_9V_TEST_CR] = 7,

	[MTK_9V_TEST_OVER_CURRENT] = 8,

	[MTK_9V_TEST_SHORT] = 9,


	[MTK_12V_TEST_CV] = 10,

	[MTK_12V_TEST_CC] = 11,

	[MTK_12V_TEST_CR] = 12,

	[MTK_12V_TEST_OVER_CURRENT] = 13,

	[MTK_12V_TEST_SHORT] = 14,


	[MTK_20V_TEST_CV] = 15,

	[MTK_20V_TEST_CC] = 16,

	[MTK_20V_TEST_CR] = 17,

	[MTK_20V_TEST_OVER_CURRENT] = 18,

	[MTK_20V_TEST_SHORT] = 19,
};

static int s_cur_test_type_index = 0;


static OPTION_ON_OFF s_cur_option_on_off = OPTION_OFF;

/* synth test setting */
static SYNTH_TEST_SETTING s_synth_test_setting;

/* qc2.0 test setting */
static QC_20_TEST_SETTING s_qc_20_test_setting;

/* mtk test setting */
static MTK_TEST_SETTING s_mtk_test_setting;

/* current group */
static int s_cur_group = 0;

/* test type menu */
static const MENU_ID s_synth_test_type_menu_arr[] = 
{
	[SYNTH_TEST_CV] = MENU_ID_CV_SETTING,

	[SYNTH_TEST_CC] = MENU_ID_CC_SETTING,

	[SYNTH_TEST_CR] = MENU_ID_CR_SETTING,

	[SYNTH_TEST_OVER_CURRENT] = MENU_ID_OVER_CURRENT_SETTING,

	[SYNTH_TEST_SHORT] = MENU_ID_SHORT_SETTING
};

static const MENU_ID s_qc_20_test_type_menu_arr[] = 
{
	[QC_20_5V_TEST_CV] = MENU_ID_CV_SETTING,

	[QC_20_5V_TEST_CC] = MENU_ID_CC_SETTING,

	[QC_20_5V_TEST_CR] = MENU_ID_CR_SETTING,

	[QC_20_5V_TEST_OVER_CURRENT] = MENU_ID_OVER_CURRENT_SETTING,

	[QC_20_5V_TEST_SHORT] = MENU_ID_SHORT_SETTING,


	[QC_20_9V_TEST_CV] = MENU_ID_CV_SETTING,

	[QC_20_9V_TEST_CC] = MENU_ID_CC_SETTING,

	[QC_20_9V_TEST_CR] = MENU_ID_CR_SETTING,

	[QC_20_9V_TEST_OVER_CURRENT] = MENU_ID_OVER_CURRENT_SETTING,

	[QC_20_9V_TEST_SHORT] = MENU_ID_SHORT_SETTING,


	[QC_20_12V_TEST_CV] = MENU_ID_CV_SETTING,

	[QC_20_12V_TEST_CC] = MENU_ID_CC_SETTING,

	[QC_20_12V_TEST_CR] = MENU_ID_CR_SETTING,

	[QC_20_12V_TEST_OVER_CURRENT] = MENU_ID_OVER_CURRENT_SETTING,

	[QC_20_12V_TEST_SHORT] = MENU_ID_SHORT_SETTING,


	[QC_20_20V_TEST_CV] = MENU_ID_CV_SETTING,

	[QC_20_20V_TEST_CC] = MENU_ID_CC_SETTING,

	[QC_20_20V_TEST_CR] = MENU_ID_CR_SETTING,

	[QC_20_20V_TEST_OVER_CURRENT] = MENU_ID_OVER_CURRENT_SETTING,

	[QC_20_20V_TEST_SHORT] = MENU_ID_SHORT_SETTING,
	
};

static const MENU_ID s_mtk_test_type_menu_arr[] = 
{
	[MTK_5V_TEST_CV] = MENU_ID_CV_SETTING,

	[MTK_5V_TEST_CC] = MENU_ID_CC_SETTING,

	[MTK_5V_TEST_CR] = MENU_ID_CR_SETTING,

	[MTK_5V_TEST_OVER_CURRENT] = MENU_ID_OVER_CURRENT_SETTING,

	[MTK_5V_TEST_SHORT] = MENU_ID_SHORT_SETTING,


	[MTK_9V_TEST_CV] = MENU_ID_CV_SETTING,

	[MTK_9V_TEST_CC] = MENU_ID_CC_SETTING,

	[MTK_9V_TEST_CR] = MENU_ID_CR_SETTING,

	[MTK_9V_TEST_OVER_CURRENT] = MENU_ID_OVER_CURRENT_SETTING,

	[MTK_9V_TEST_SHORT] = MENU_ID_SHORT_SETTING,


	[MTK_12V_TEST_CV] = MENU_ID_CV_SETTING,

	[MTK_12V_TEST_CC] = MENU_ID_CC_SETTING,

	[MTK_12V_TEST_CR] = MENU_ID_CR_SETTING,

	[MTK_12V_TEST_OVER_CURRENT] = MENU_ID_OVER_CURRENT_SETTING,

	[MTK_12V_TEST_SHORT] = MENU_ID_SHORT_SETTING,


	[MTK_20V_TEST_CV] = MENU_ID_CV_SETTING,

	[MTK_20V_TEST_CC] = MENU_ID_CC_SETTING,

	[MTK_20V_TEST_CR] = MENU_ID_CR_SETTING,

	[MTK_20V_TEST_OVER_CURRENT] = MENU_ID_OVER_CURRENT_SETTING,

	[MTK_20V_TEST_SHORT] = MENU_ID_SHORT_SETTING,
};

static MENU_ID get_cur_synth_test_type_menu(SYNTH_TEST_TYPE test_type)
{
	if (test_type >= SYNTH_TEST_CV && test_type <= SYNTH_TEST_SHORT)
	{
		return s_synth_test_type_menu_arr[test_type];
	}

	return MENU_ID_NONE;
}

static MENU_ID get_cur_qc_20_test_type_menu(QC_20_TEST_TYPE test_type)
{
	if (test_type >= QC_20_5V_TEST_CV && test_type <= QC_20_20V_TEST_SHORT)
	{
		return s_qc_20_test_type_menu_arr[test_type];
	}

	return MENU_ID_NONE;
}

static MENU_ID get_cur_mtk_test_type_menu(MTK_TEST_TYPE test_type)
{
	if (test_type >= MTK_5V_TEST_CV && test_type <= MTK_20V_TEST_SHORT)
	{
		return s_mtk_test_type_menu_arr[test_type];
	}

	return MENU_ID_NONE;
}

static void load_device_privilege(DEVICE_PRIVILEGE *device_privilege)
{
	load_parameter(STRUCT_OFFSET(PARAMETER, device_privilege), device_privilege, sizeof(*device_privilege));
}

static void load_group_test_setting(TEST_CATEGORY type, int group)
{
	if (type == TEST_CATEGORY_SYNTH_TEST)
	{	
		load_parameter(STRUCT_OFFSET(PARAMETER, synth_test_setting[group]), &s_synth_test_setting, sizeof(s_synth_test_setting));
	}
	else if (type == TEST_CATEGORY_QC_20_TEST)
	{
		load_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group]), &s_qc_20_test_setting, sizeof(s_qc_20_test_setting));
	}
	else if (type == TEST_CATEGORY_MTK_TEST)
	{
		load_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group]), &s_mtk_test_setting, sizeof(s_mtk_test_setting));
	}
}

static void save_synth_test_empty_load_setting(int group)
{
	save_parameter(STRUCT_OFFSET(PARAMETER, synth_test_setting[group].empty_load_test_setting),
					&(s_synth_test_setting.empty_load_test_setting),
					sizeof(s_synth_test_setting.empty_load_test_setting));
}

static void save_synth_test_discharge_setting(int group)
{
	save_parameter(STRUCT_OFFSET(PARAMETER, synth_test_setting[group].discharge_test_setting),
					&s_synth_test_setting.discharge_test_setting,
					sizeof(s_synth_test_setting.discharge_test_setting));
}

static void save_synth_test_type(int group, int step)
{
	save_parameter(STRUCT_OFFSET(PARAMETER, synth_test_setting[group].synth_normal_test_setting[step - 2].test_type),
					&s_synth_test_setting.synth_normal_test_setting[step - 2].test_type,
					sizeof(s_synth_test_setting.synth_normal_test_setting[step - 2].test_type));
}

static void save_synth_test_on_off(int group, int step)
{
	save_parameter(STRUCT_OFFSET(PARAMETER, synth_test_setting[group].synth_normal_test_setting[step - 2].on_off),
					&s_synth_test_setting.synth_normal_test_setting[step - 2].on_off,
					sizeof(s_synth_test_setting.synth_normal_test_setting[step - 2].on_off));
}

static void save_synth_test_cv_setting(int group, int step)
{
	save_parameter(STRUCT_OFFSET(PARAMETER, synth_test_setting[group].synth_normal_test_setting[step - 2].cv_setting),
					&s_synth_test_setting.synth_normal_test_setting[step - 2].cv_setting,
					sizeof(s_synth_test_setting.synth_normal_test_setting[step - 2].cv_setting));
}

static void save_synth_test_cc_setting(int group, int step)
{
	save_parameter(STRUCT_OFFSET(PARAMETER, synth_test_setting[group].synth_normal_test_setting[step - 2].cc_setting),
					&s_synth_test_setting.synth_normal_test_setting[step - 2].cc_setting,
					sizeof(s_synth_test_setting.synth_normal_test_setting[step - 2].cc_setting));
}

static void save_synth_test_cr_setting(int group, int step)
{
	save_parameter(STRUCT_OFFSET(PARAMETER, synth_test_setting[group].synth_normal_test_setting[step - 2].cr_setting),
					&s_synth_test_setting.synth_normal_test_setting[step - 2].cr_setting,
					sizeof(s_synth_test_setting.synth_normal_test_setting[step - 2].cr_setting));
}

static void save_synth_test_over_current_setting(int group, int step)
{
	save_parameter(STRUCT_OFFSET(PARAMETER, synth_test_setting[group].synth_normal_test_setting[step - 2].over_current_test_setting),
					&s_synth_test_setting.synth_normal_test_setting[step - 2].over_current_test_setting,
					sizeof(s_synth_test_setting.synth_normal_test_setting[step - 2].over_current_test_setting));
}

static void save_synth_test_short_setting(int group, int step)
{
	save_parameter(STRUCT_OFFSET(PARAMETER, synth_test_setting[group].synth_normal_test_setting[step - 2].short_test_setting),
					&s_synth_test_setting.synth_normal_test_setting[step - 2].short_test_setting,
					sizeof(s_synth_test_setting.synth_normal_test_setting[step - 2].short_test_setting));
}

static void save_qc_20_test_empty_load_setting(int group)
{
	save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].empty_load_test_setting),
					&(s_qc_20_test_setting.empty_load_test_setting),
					sizeof(s_qc_20_test_setting.empty_load_test_setting));
}

static void save_qc_20_test_discharge_setting(int group)
{
	save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].discharge_test_setting),
					&s_qc_20_test_setting.discharge_test_setting,
					sizeof(s_qc_20_test_setting.discharge_test_setting));
}

static void save_qc_20_test_type(int group, int step)
{
	save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2].test_type),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].test_type,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].test_type));
}

static void save_qc_20_test_on_off(int group, int step)
{
	save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2].on_off),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].on_off,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].on_off));
}

static void save_qc_20_test_cv_setting(int group, int step)
{
	QC_20_TEST_TYPE test_type = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].test_type;
	
	if (test_type == QC_20_5V_TEST_CV)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._5v_cv_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_cv_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_cv_setting));
	}
	else if (test_type == QC_20_9V_TEST_CV)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._9v_cv_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_cv_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_cv_setting));
	}
	else if (test_type == QC_20_12V_TEST_CV)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._12v_cv_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_cv_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_cv_setting));
	}
	else if (test_type == QC_20_20V_TEST_CV)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._20v_cv_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_cv_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_cv_setting));
	}
}

static void save_qc_20_test_cc_setting(int group, int step)
{
	QC_20_TEST_TYPE test_type = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].test_type;
	
	if (test_type == QC_20_5V_TEST_CC)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._5v_cc_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_cc_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_cc_setting));
	}
	else if (test_type == QC_20_9V_TEST_CC)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._9v_cc_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_cc_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_cc_setting));
	}
	else if (test_type == QC_20_12V_TEST_CC)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._12v_cc_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_cc_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_cc_setting));
	}
	else if (test_type == QC_20_20V_TEST_CC)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._20v_cc_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_cc_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_cc_setting));
	}
}

static void save_qc_20_test_cr_setting(int group, int step)
{
	QC_20_TEST_TYPE test_type = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].test_type;
	
	if (test_type == QC_20_5V_TEST_CR)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._5v_cr_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_cr_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_cr_setting));
	}
	else if (test_type == QC_20_9V_TEST_CR)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._9v_cr_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_cr_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_cr_setting));
	}
	else if (test_type == QC_20_12V_TEST_CR)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._12v_cr_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_cr_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_cr_setting));
	}
	else if (test_type == QC_20_20V_TEST_CR)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._20v_cr_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_cr_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_cr_setting));
	}
}

static void save_qc_20_test_over_current_setting(int group, int step)
{
	QC_20_TEST_TYPE test_type = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].test_type;
	
	if (test_type == QC_20_5V_TEST_OVER_CURRENT)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._5v_over_current_test_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_over_current_test_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_over_current_test_setting));
	}
	else if (test_type == QC_20_9V_TEST_OVER_CURRENT)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._9v_over_current_test_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_over_current_test_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_over_current_test_setting));
	}
	else if (test_type == QC_20_12V_TEST_OVER_CURRENT)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._12v_over_current_test_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_over_current_test_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_over_current_test_setting));
	}
	else if (test_type == QC_20_20V_TEST_OVER_CURRENT)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._20v_over_current_test_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_over_current_test_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_over_current_test_setting));
	}
}

static void save_qc_20_test_short_setting(int group, int step)
{
	QC_20_TEST_TYPE test_type = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].test_type;
	
	if (test_type == QC_20_5V_TEST_SHORT)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._5v_short_test_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_short_test_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_short_test_setting));
	}
	else if (test_type == QC_20_9V_TEST_SHORT)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._9v_short_test_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_short_test_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_short_test_setting));
	}
	else if (test_type == QC_20_12V_TEST_SHORT)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._12v_short_test_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_short_test_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_short_test_setting));
	}
	else if (test_type == QC_20_20V_TEST_SHORT)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, qc_20_test_setting[group].qc_20_normal_test_setting[step - 2]._20v_short_test_setting),
					&s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_short_test_setting,
					sizeof(s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_short_test_setting));
	}
}

static void save_mtk_test_empty_load_setting(int group)
{
	save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].empty_load_test_setting),
					&(s_mtk_test_setting.empty_load_test_setting),
					sizeof(s_mtk_test_setting.empty_load_test_setting));
}

static void save_mtk_test_discharge_setting(int group)
{
	save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].discharge_test_setting),
					&s_mtk_test_setting.discharge_test_setting,
					sizeof(s_mtk_test_setting.discharge_test_setting));
}

static void save_mtk_test_type(int group, int step)
{
	save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2].test_type),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2].test_type,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2].test_type));
}

static void save_mtk_test_on_off(int group, int step)
{
	save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2].on_off),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2].on_off,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2].on_off));
}

static void save_mtk_test_cv_setting(int group, int step)
{
	MTK_TEST_TYPE test_type = s_mtk_test_setting.mtk_normal_test_setting[step - 2].test_type;
	
	if (test_type == MTK_5V_TEST_CV)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._5v_cv_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._5v_cv_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._5v_cv_setting));
	}
	else if (test_type == MTK_9V_TEST_CV)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._9v_cv_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._9v_cv_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._9v_cv_setting));
	}
	else if (test_type == MTK_12V_TEST_CV)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._12v_cv_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._12v_cv_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._12v_cv_setting));
	}
	else if (test_type == MTK_20V_TEST_CV)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._20v_cv_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._20v_cv_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._20v_cv_setting));
	}
}

static void save_mtk_test_cc_setting(int group, int step)
{
	MTK_TEST_TYPE test_type = s_mtk_test_setting.mtk_normal_test_setting[step - 2].test_type;
	
	if (test_type == MTK_5V_TEST_CC)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._5v_cc_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._5v_cc_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._5v_cc_setting));
	}
	else if (test_type == MTK_9V_TEST_CC)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._9v_cc_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._9v_cc_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._9v_cc_setting));
	}
	else if (test_type == MTK_12V_TEST_CC)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._12v_cc_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._12v_cc_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._12v_cc_setting));
	}
	else if (test_type == MTK_20V_TEST_CC)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._20v_cc_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._20v_cc_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._20v_cc_setting));
	}
}

static void save_mtk_test_cr_setting(int group, int step)
{
	MTK_TEST_TYPE test_type = s_mtk_test_setting.mtk_normal_test_setting[step - 2].test_type;
	
	if (test_type == MTK_5V_TEST_CR)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._5v_cr_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._5v_cr_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._5v_cr_setting));
	}
	else if (test_type == MTK_9V_TEST_CR)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._9v_cr_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._9v_cr_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._9v_cr_setting));
	}
	else if (test_type == MTK_12V_TEST_CR)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._12v_cr_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._12v_cr_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._12v_cr_setting));
	}
	else if (test_type == MTK_20V_TEST_CR)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._20v_cr_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._20v_cr_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._20v_cr_setting));
	}
}

static void save_mtk_test_over_current_setting(int group, int step)
{
	MTK_TEST_TYPE test_type = s_mtk_test_setting.mtk_normal_test_setting[step - 2].test_type;
	
	if (test_type == MTK_5V_TEST_OVER_CURRENT)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._5v_over_current_test_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._5v_over_current_test_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._5v_over_current_test_setting));
	}
	else if (test_type == MTK_9V_TEST_OVER_CURRENT)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._9v_over_current_test_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._9v_over_current_test_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._9v_over_current_test_setting));
	}
	else if (test_type == MTK_12V_TEST_OVER_CURRENT)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._12v_over_current_test_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._12v_over_current_test_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._12v_over_current_test_setting));
	}
	else if (test_type == MTK_20V_TEST_OVER_CURRENT)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._20v_over_current_test_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._20v_over_current_test_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._20v_over_current_test_setting));
	}
}

static void save_mtk_test_short_setting(int group, int step)
{
	MTK_TEST_TYPE test_type = s_mtk_test_setting.mtk_normal_test_setting[step - 2].test_type;
	
	if (test_type == MTK_5V_TEST_SHORT)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._5v_short_test_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._5v_short_test_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._5v_short_test_setting));
	}
	else if (test_type == MTK_9V_TEST_SHORT)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._9v_short_test_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._9v_short_test_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._9v_short_test_setting));
	}
	else if (test_type == MTK_12V_TEST_SHORT)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._12v_short_test_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._12v_short_test_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._12v_short_test_setting));
	}
	else if (test_type == MTK_20V_TEST_SHORT)
	{
		save_parameter(STRUCT_OFFSET(PARAMETER, mtk_test_setting[group].mtk_normal_test_setting[step - 2]._20v_short_test_setting),
					&s_mtk_test_setting.mtk_normal_test_setting[step - 2]._20v_short_test_setting,
					sizeof(s_mtk_test_setting.mtk_normal_test_setting[step - 2]._20v_short_test_setting));
	}
}
/* unfocus function */
static void unfocus_group(void)
{
	draw_normal_test_setting_group(s_cur_group + 1);
}

static void unfocus_test(void)
{
	draw_normal_test();
}

static void unfocus_item_1_setting(void)
{
	draw_normal_test_item_1_setting();
}

static void unfocus_item_2_synth_type(void)
{
	draw_normal_synth_item_2_type(s_synth_test_setting.synth_normal_test_setting[0].test_type);
}

static void unfocus_item_2_qc_20_type(void)
{
	draw_normal_qc_20_item_2_type(s_qc_20_test_setting.qc_20_normal_test_setting[0].test_type);
}

static void unfocus_item_2_MTK_type(void)
{

}

static void (*const s_unfocus_item_2_type_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = unfocus_item_2_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = unfocus_item_2_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = unfocus_item_2_MTK_type
};

static void unfocus_item_2_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_unfocus_item_2_type_func[s_cur_test_category]();
	}
}

static void unfocus_item_2_synth_on_off(void)
{
	draw_normal_test_item_2_on_off(s_synth_test_setting.synth_normal_test_setting[0].on_off);
}

static void unfocus_item_2_qc_20_on_off(void)
{
	draw_normal_test_item_2_on_off(s_qc_20_test_setting.qc_20_normal_test_setting[0].on_off);
}

static void unfocus_item_2_MTK_on_off(void)
{

}

static void (*const s_unfocus_item_2_on_off_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = unfocus_item_2_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = unfocus_item_2_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = unfocus_item_2_MTK_on_off
};

static void unfocus_item_2_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_unfocus_item_2_on_off_func[s_cur_test_category]();
	}
}

static void unfocus_item_2_setting(void)
{
	draw_normal_test_item_2_setting();
}


static void unfocus_item_3_synth_type(void)
{
	draw_normal_synth_item_3_type(s_synth_test_setting.synth_normal_test_setting[1].test_type);
}

static void unfocus_item_3_qc_20_type(void)
{
	draw_normal_qc_20_item_3_type(s_qc_20_test_setting.qc_20_normal_test_setting[1].test_type);
}

static void unfocus_item_3_MTK_type(void)
{

}

static void (*const s_unfocus_item_3_type_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = unfocus_item_3_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = unfocus_item_3_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = unfocus_item_3_MTK_type
};

static void unfocus_item_3_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_unfocus_item_3_type_func[s_cur_test_category]();
	}
}

static void unfocus_item_3_synth_on_off(void)
{
	draw_normal_test_item_3_on_off(s_synth_test_setting.synth_normal_test_setting[1].on_off);
}

static void unfocus_item_3_qc_20_on_off(void)
{
	draw_normal_test_item_3_on_off(s_qc_20_test_setting.qc_20_normal_test_setting[1].on_off);
}

static void unfocus_item_3_MTK_on_off(void)
{

}

static void (*const s_unfocus_item_3_on_off_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = unfocus_item_3_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = unfocus_item_3_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = unfocus_item_3_MTK_on_off
};

static void unfocus_item_3_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_unfocus_item_3_on_off_func[s_cur_test_category]();
	}
}

static void unfocus_item_3_setting(void)
{
	draw_normal_test_item_3_setting();
}

static void unfocus_item_4_synth_type(void)
{
	draw_normal_synth_item_4_type(s_synth_test_setting.synth_normal_test_setting[2].test_type);
}

static void unfocus_item_4_qc_20_type(void)
{
	draw_normal_qc_20_item_4_type(s_qc_20_test_setting.qc_20_normal_test_setting[2].test_type);
}

static void unfocus_item_4_MTK_type(void)
{

}

static void (*const s_unfocus_item_4_type_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = unfocus_item_4_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = unfocus_item_4_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = unfocus_item_4_MTK_type
};

static void unfocus_item_4_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_unfocus_item_4_type_func[s_cur_test_category]();
	}
}

static void unfocus_item_4_synth_on_off(void)
{
	draw_normal_test_item_4_on_off(s_synth_test_setting.synth_normal_test_setting[2].on_off);
}

static void unfocus_item_4_qc_20_on_off(void)
{
	draw_normal_test_item_4_on_off(s_qc_20_test_setting.qc_20_normal_test_setting[2].on_off);
}

static void unfocus_item_4_MTK_on_off(void)
{

}

static void (*const s_unfocus_item_4_on_off_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = unfocus_item_4_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = unfocus_item_4_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = unfocus_item_4_MTK_on_off
};

static void unfocus_item_4_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_unfocus_item_4_on_off_func[s_cur_test_category]();
	}
}


static void unfocus_item_4_setting(void)
{
	draw_normal_test_item_4_setting();
}

static void unfocus_item_5_synth_type(void)
{
	draw_normal_synth_item_5_type(s_synth_test_setting.synth_normal_test_setting[3].test_type);
}

static void unfocus_item_5_qc_20_type(void)
{
	draw_normal_qc_20_item_5_type(s_qc_20_test_setting.qc_20_normal_test_setting[3].test_type);
}

static void unfocus_item_5_MTK_type(void)
{

}

static void (*const s_unfocus_item_5_type_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = unfocus_item_5_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = unfocus_item_5_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = unfocus_item_5_MTK_type
};

static void unfocus_item_5_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_unfocus_item_5_type_func[s_cur_test_category]();
	}
}


static void unfocus_item_5_synth_on_off(void)
{
	draw_normal_test_item_5_on_off(s_synth_test_setting.synth_normal_test_setting[3].on_off);
}

static void unfocus_item_5_qc_20_on_off(void)
{
	draw_normal_test_item_5_on_off(s_qc_20_test_setting.qc_20_normal_test_setting[3].on_off);
}

static void unfocus_item_5_MTK_on_off(void)
{

}

static void (*const s_unfocus_item_5_on_off_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = unfocus_item_5_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = unfocus_item_5_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = unfocus_item_5_MTK_on_off
};

static void unfocus_item_5_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_unfocus_item_5_on_off_func[s_cur_test_category]();
	}
}

static void unfocus_item_5_setting(void)
{
	draw_normal_test_item_5_setting();
}

static void unfocus_item_6_synth_type(void)
{
	draw_normal_synth_item_6_type(s_synth_test_setting.synth_normal_test_setting[4].test_type);
}

static void unfocus_item_6_qc_20_type(void)
{
	draw_normal_qc_20_item_6_type(s_qc_20_test_setting.qc_20_normal_test_setting[4].test_type);
}

static void unfocus_item_6_MTK_type(void)
{

}

static void (*const s_unfocus_item_6_type_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = unfocus_item_6_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = unfocus_item_6_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = unfocus_item_6_MTK_type
};

static void unfocus_item_6_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_unfocus_item_6_type_func[s_cur_test_category]();
	}
}

static void unfocus_item_6_synth_on_off(void)
{
	draw_normal_test_item_6_on_off(s_synth_test_setting.synth_normal_test_setting[4].on_off);
}

static void unfocus_item_6_qc_20_on_off(void)
{
	draw_normal_test_item_6_on_off(s_qc_20_test_setting.qc_20_normal_test_setting[4].on_off);
}

static void unfocus_item_6_MTK_on_off(void)
{

}

static void (*const s_unfocus_item_6_on_off_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = unfocus_item_6_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = unfocus_item_6_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = unfocus_item_6_MTK_on_off
};

static void unfocus_item_6_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_unfocus_item_6_on_off_func[s_cur_test_category]();
	}
}

static void unfocus_item_6_setting(void)
{
	draw_normal_test_item_6_setting();
}

static void unfocus_item_7_synth_type(void)
{
	draw_normal_synth_item_7_type(s_synth_test_setting.synth_normal_test_setting[5].test_type);
}

static void unfocus_item_7_qc_20_type(void)
{
	draw_normal_qc_20_item_7_type(s_qc_20_test_setting.qc_20_normal_test_setting[5].test_type);
}

static void unfocus_item_7_MTK_type(void)
{

}

static void (*const s_unfocus_item_7_type_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = unfocus_item_7_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = unfocus_item_7_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = unfocus_item_7_MTK_type
};

static void unfocus_item_7_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_unfocus_item_7_type_func[s_cur_test_category]();
	}
}

static void unfocus_item_7_synth_on_off(void)
{
	draw_normal_test_item_7_on_off(s_synth_test_setting.synth_normal_test_setting[5].on_off);
}

static void unfocus_item_7_qc_20_on_off(void)
{
	draw_normal_test_item_7_on_off(s_qc_20_test_setting.qc_20_normal_test_setting[5].on_off);
}

static void unfocus_item_7_MTK_on_off(void)
{

}

static void (*const s_unfocus_item_7_on_off_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = unfocus_item_7_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = unfocus_item_7_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = unfocus_item_7_MTK_on_off
};

static void unfocus_item_7_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_unfocus_item_7_on_off_func[s_cur_test_category]();
	}
}

static void unfocus_item_7_setting(void)
{
	draw_normal_test_item_7_setting();
}

static void unfocus_item_8_synth_on_off(void)
{
	draw_normal_test_item_8_on_off(s_synth_test_setting.discharge_test_setting.on_off);
}

static void unfocus_item_8_qc_20_on_off(void)
{
	draw_normal_test_item_8_on_off(s_qc_20_test_setting.discharge_test_setting.on_off);
}

static void unfocus_item_8_MTK_on_off(void)
{

}

static void (*const s_unfocus_item_8_on_off_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = unfocus_item_8_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = unfocus_item_8_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = unfocus_item_8_MTK_on_off
};

static void unfocus_item_8_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_unfocus_item_8_on_off_func[s_cur_test_category]();
	}
}

static void unfocus_item_8_setting(void)
{
	draw_normal_test_item_8_setting();
}

static void (*const s_unfocus_fun_arr[])(void) = 
{
	[FOCUS_GROUP]          = unfocus_group,
	[FOCUS_TEST]           = unfocus_test,
	
	[FOCUS_ITEM_1_SETTING] = unfocus_item_1_setting,
	
	[FOCUS_ITEM_2_TYPE]    = unfocus_item_2_type,
	[FOCUS_ITEM_2_ON_OFF]  = unfocus_item_2_on_off,
	[FOCUS_ITEM_2_SETTING] = unfocus_item_2_setting,
	
	[FOCUS_ITEM_3_TYPE]    = unfocus_item_3_type,
	[FOCUS_ITEM_3_ON_OFF]  = unfocus_item_3_on_off,
	[FOCUS_ITEM_3_SETTING] = unfocus_item_3_setting,	

	[FOCUS_ITEM_4_TYPE]    = unfocus_item_4_type,
	[FOCUS_ITEM_4_ON_OFF]  = unfocus_item_4_on_off,
	[FOCUS_ITEM_4_SETTING] = unfocus_item_4_setting,
	
	[FOCUS_ITEM_5_TYPE]    = unfocus_item_5_type,
	[FOCUS_ITEM_5_ON_OFF]  = unfocus_item_5_on_off,
	[FOCUS_ITEM_5_SETTING] = unfocus_item_5_setting,
	
	[FOCUS_ITEM_6_TYPE]    = unfocus_item_6_type,
	[FOCUS_ITEM_6_ON_OFF]  = unfocus_item_6_on_off,
	[FOCUS_ITEM_6_SETTING] = unfocus_item_6_setting,
	
	[FOCUS_ITEM_7_TYPE]    = unfocus_item_7_type,
	[FOCUS_ITEM_7_ON_OFF]  = unfocus_item_7_on_off,
	[FOCUS_ITEM_7_SETTING] = unfocus_item_7_setting,

	[FOCUS_ITEM_8_ON_OFF]  = unfocus_item_8_on_off,
	[FOCUS_ITEM_8_SETTING] = unfocus_item_8_setting,		
};

/* focus function */
static void focus_group(void)
{
	draw_focus_test_setting_group(s_cur_group + 1);
}

static void focus_test(void)
{
	draw_focus_test();
}
	
static void focus_item_1_setting(void)
{
	draw_focus_test_item_1_setting();
}

static void focus_item_2_synth_type(void)
{
	draw_focus_synth_item_2_type(s_synth_test_setting.synth_normal_test_setting[0].test_type);
}

static void focus_item_2_qc_20_type(void)
{
	draw_focus_qc_20_item_2_type(s_qc_20_test_setting.qc_20_normal_test_setting[0].test_type);
}

static void focus_item_2_MTK_type(void)
{

}

static void (*const s_focus_item_2_type_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = focus_item_2_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = focus_item_2_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = focus_item_2_MTK_type
};

static void focus_item_2_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_focus_item_2_type_func[s_cur_test_category]();
	}
}

static void focus_item_2_synth_on_off(void)
{
	draw_focus_test_item_2_on_off(s_synth_test_setting.synth_normal_test_setting[0].on_off);
}

static void focus_item_2_qc_20_on_off(void)
{
	draw_focus_test_item_2_on_off(s_qc_20_test_setting.qc_20_normal_test_setting[0].on_off);
}

static void focus_item_2_MTK_on_off(void)
{

}

static void (*const s_focus_item_2_on_off_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = focus_item_2_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = focus_item_2_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = focus_item_2_MTK_on_off
};

static void focus_item_2_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_focus_item_2_on_off_func[s_cur_test_category]();
	}
}

static void focus_item_2_setting(void)
{
	draw_focus_test_item_2_setting();
}

static void focus_item_3_synth_type(void)
{
	draw_focus_synth_item_3_type(s_synth_test_setting.synth_normal_test_setting[1].test_type);
}

static void focus_item_3_qc_20_type(void)
{
	draw_focus_qc_20_item_3_type(s_qc_20_test_setting.qc_20_normal_test_setting[1].test_type);
}

static void focus_item_3_MTK_type(void)
{

}

static void (*const s_focus_item_3_type_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = focus_item_3_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = focus_item_3_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = focus_item_3_MTK_type
};

static void focus_item_3_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_focus_item_3_type_func[s_cur_test_category]();
	}
}


static void focus_item_3_synth_on_off(void)
{
	draw_focus_test_item_3_on_off(s_synth_test_setting.synth_normal_test_setting[1].on_off);
}

static void focus_item_3_qc_20_on_off(void)
{
	draw_focus_test_item_3_on_off(s_qc_20_test_setting.qc_20_normal_test_setting[1].on_off);
}

static void focus_item_3_MTK_on_off(void)
{

}

static void (*const s_focus_item_3_on_off_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = focus_item_3_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = focus_item_3_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = focus_item_3_MTK_on_off
};

static void focus_item_3_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_focus_item_3_on_off_func[s_cur_test_category]();
	}
}

static void focus_item_3_setting(void)
{
	draw_focus_test_item_3_setting();
}

static void focus_item_4_synth_type(void)
{
	draw_focus_synth_item_4_type(s_synth_test_setting.synth_normal_test_setting[2].test_type);
}

static void focus_item_4_qc_20_type(void)
{
	draw_focus_qc_20_item_4_type(s_qc_20_test_setting.qc_20_normal_test_setting[2].test_type);
}

static void focus_item_4_MTK_type(void)
{

}

static void (*const s_focus_item_4_type_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = focus_item_4_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = focus_item_4_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = focus_item_4_MTK_type
};

static void focus_item_4_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_focus_item_4_type_func[s_cur_test_category]();
	}
}

static void focus_item_4_synth_on_off(void)
{
	draw_focus_test_item_4_on_off(s_synth_test_setting.synth_normal_test_setting[2].on_off);
}

static void focus_item_4_qc_20_on_off(void)
{
	draw_focus_test_item_4_on_off(s_qc_20_test_setting.qc_20_normal_test_setting[2].on_off);
}

static void focus_item_4_MTK_on_off(void)
{

}

static void (*const s_focus_item_4_on_off_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = focus_item_4_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = focus_item_4_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = focus_item_4_MTK_on_off
};

static void focus_item_4_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_focus_item_4_on_off_func[s_cur_test_category]();
	}
}

static void focus_item_4_setting(void)
{
	draw_focus_test_item_4_setting();
}

static void focus_item_5_synth_type(void)
{
	draw_focus_synth_item_5_type(s_synth_test_setting.synth_normal_test_setting[3].test_type);
}

static void focus_item_5_qc_20_type(void)
{
	draw_focus_qc_20_item_5_type(s_qc_20_test_setting.qc_20_normal_test_setting[3].test_type);
}

static void focus_item_5_MTK_type(void)
{

}

static void (*const s_focus_item_5_type_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = focus_item_5_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = focus_item_5_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = focus_item_5_MTK_type
};

static void focus_item_5_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_focus_item_5_type_func[s_cur_test_category]();
	}
}

static void focus_item_5_synth_on_off(void)
{
	draw_focus_test_item_5_on_off(s_synth_test_setting.synth_normal_test_setting[3].on_off);
}

static void focus_item_5_qc_20_on_off(void)
{
	draw_focus_test_item_5_on_off(s_qc_20_test_setting.qc_20_normal_test_setting[3].on_off);
}

static void focus_item_5_MTK_on_off(void)
{

}

static void (*const s_focus_item_5_on_off_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = focus_item_5_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = focus_item_5_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = focus_item_5_MTK_on_off
};

static void focus_item_5_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_focus_item_5_on_off_func[s_cur_test_category]();
	}
}

static void focus_item_5_setting(void)
{
	draw_focus_test_item_5_setting();
}

static void focus_item_6_synth_type(void)
{
	draw_focus_synth_item_6_type(s_synth_test_setting.synth_normal_test_setting[4].test_type);
}

static void focus_item_6_qc_20_type(void)
{
	draw_focus_qc_20_item_6_type(s_qc_20_test_setting.qc_20_normal_test_setting[4].test_type);
}

static void focus_item_6_MTK_type(void)
{

}

static void (*const s_focus_item_6_type_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = focus_item_6_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = focus_item_6_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = focus_item_6_MTK_type
};

static void focus_item_6_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_focus_item_6_type_func[s_cur_test_category]();
	}
}

static void focus_item_6_synth_on_off(void)
{
	draw_focus_test_item_6_on_off(s_synth_test_setting.synth_normal_test_setting[4].on_off);
}

static void focus_item_6_qc_20_on_off(void)
{
	draw_focus_test_item_6_on_off(s_qc_20_test_setting.qc_20_normal_test_setting[4].on_off);
}

static void focus_item_6_MTK_on_off(void)
{

}

static void (*const s_focus_item_6_on_off_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = focus_item_6_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = focus_item_6_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = focus_item_6_MTK_on_off
};

static void focus_item_6_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_focus_item_6_on_off_func[s_cur_test_category]();
	}
}

static void focus_item_6_setting(void)
{
	draw_focus_test_item_6_setting();
}

static void focus_item_7_synth_type(void)
{
	draw_focus_synth_item_7_type(s_synth_test_setting.synth_normal_test_setting[5].test_type);
}

static void focus_item_7_qc_20_type(void)
{
	draw_focus_qc_20_item_7_type(s_qc_20_test_setting.qc_20_normal_test_setting[5].test_type);
}

static void focus_item_7_MTK_type(void)
{

}

static void (*const s_focus_item_7_type_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = focus_item_7_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = focus_item_7_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = focus_item_7_MTK_type
};

static void focus_item_7_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_focus_item_7_type_func[s_cur_test_category]();
	}
}

static void focus_item_7_synth_on_off(void)
{
	draw_focus_test_item_7_on_off(s_synth_test_setting.synth_normal_test_setting[5].on_off);
}

static void focus_item_7_qc_20_on_off(void)
{
	draw_focus_test_item_7_on_off(s_qc_20_test_setting.qc_20_normal_test_setting[5].on_off);
}

static void focus_item_7_MTK_on_off(void)
{

}

static void (*const s_focus_item_7_on_off_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = focus_item_7_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = focus_item_7_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = focus_item_7_MTK_on_off
};

static void focus_item_7_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_focus_item_7_on_off_func[s_cur_test_category]();
	}
}

static void focus_item_7_setting(void)
{
	draw_focus_test_item_7_setting();
}

static void focus_item_8_synth_on_off(void)
{
	draw_focus_test_item_8_on_off(s_synth_test_setting.discharge_test_setting.on_off);
}

static void focus_item_8_qc_20_on_off(void)
{
	draw_focus_test_item_8_on_off(s_qc_20_test_setting.discharge_test_setting.on_off);
}

static void focus_item_8_MTK_on_off(void)
{

}

static void (*const s_focus_item_8_on_off_func[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = focus_item_8_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = focus_item_8_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = focus_item_8_MTK_on_off
};

static void focus_item_8_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_focus_item_8_on_off_func[s_cur_test_category]();
	}
}
static void focus_item_8_setting(void)
{
	draw_focus_test_item_8_setting();
}


static void (*const s_focus_fun_arr[])(void) = 
{
	[FOCUS_GROUP]          = focus_group,
	[FOCUS_TEST]           = focus_test,
	
	[FOCUS_ITEM_1_SETTING] = focus_item_1_setting,
	
	[FOCUS_ITEM_2_TYPE]    = focus_item_2_type,
	[FOCUS_ITEM_2_ON_OFF]  = focus_item_2_on_off,
	[FOCUS_ITEM_2_SETTING] = focus_item_2_setting,
	
	[FOCUS_ITEM_3_TYPE]    = focus_item_3_type,
	[FOCUS_ITEM_3_ON_OFF]  = focus_item_3_on_off,
	[FOCUS_ITEM_3_SETTING] = focus_item_3_setting,	

	[FOCUS_ITEM_4_TYPE]    = focus_item_4_type,
	[FOCUS_ITEM_4_ON_OFF]  = focus_item_4_on_off,
	[FOCUS_ITEM_4_SETTING] = focus_item_4_setting,
	
	[FOCUS_ITEM_5_TYPE]    = focus_item_5_type,
	[FOCUS_ITEM_5_ON_OFF]  = focus_item_5_on_off,
	[FOCUS_ITEM_5_SETTING] = focus_item_5_setting,
	
	[FOCUS_ITEM_6_TYPE]    = focus_item_6_type,
	[FOCUS_ITEM_6_ON_OFF]  = focus_item_6_on_off,
	[FOCUS_ITEM_6_SETTING] = focus_item_6_setting,
	
	[FOCUS_ITEM_7_TYPE]    = focus_item_7_type,
	[FOCUS_ITEM_7_ON_OFF]  = focus_item_7_on_off,
	[FOCUS_ITEM_7_SETTING] = focus_item_7_setting,

	[FOCUS_ITEM_8_ON_OFF]  = focus_item_8_on_off,
	[FOCUS_ITEM_8_SETTING] = focus_item_8_setting,	
};

/* enter edit functions */
static void enter_edit_group(void)
{
	draw_edit_test_setting_group(s_cur_group + 1);
	
	s_edit_item = EDIT_GROUP;
}

static void enter_edit_test(void)
{
	/* start test */
	switch_to_menu(MENU_ID_SYNTH_TEST);
}

static void enter_edit_item_1_setting(void)
{
	switch_to_menu(MENU_ID_EMPTY_LOAD_SETTING);
}

static void enter_edit_item_2_synth_type(void)
{
	s_cur_test_type_index = s_synth_test_type_to_index[s_synth_test_setting.synth_normal_test_setting[0].test_type];
	
	draw_edit_synth_item_2_type(s_synth_test_setting.synth_normal_test_setting[0].test_type);
}

static void enter_edit_item_2_qc_20_type(void)
{
	s_cur_test_type_index = s_qc_20_test_type_to_index[s_qc_20_test_setting.qc_20_normal_test_setting[0].test_type];

	draw_edit_qc_20_item_2_type(s_qc_20_test_setting.qc_20_normal_test_setting[0].test_type);
}

static void enter_edit_item_2_MTK_type(void)
{
	s_cur_test_type_index = s_mtk_test_type_to_index[s_mtk_test_setting.mtk_normal_test_setting[0].test_type];

	draw_edit_mtk_item_2_type(s_mtk_test_setting.mtk_normal_test_setting[0].test_type);
}

static void (*const s_enter_edit_item_2_type[])(void) = 

{
	[TEST_CATEGORY_SYNTH_TEST] = enter_edit_item_2_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = enter_edit_item_2_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = enter_edit_item_2_MTK_type
};

static void enter_edit_item_2_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_enter_edit_item_2_type[s_cur_test_category]();

		s_edit_item = EDIT_ITEM_2_TYPE;
	}
}

static void enter_edit_item_2_synth_on_off(void)
{
	s_cur_option_on_off = s_synth_test_setting.synth_normal_test_setting[0].on_off;

	draw_edit_test_item_2_on_off(s_cur_option_on_off);
}

static void enter_edit_item_2_qc_20_on_off(void)
{
	s_cur_option_on_off = s_qc_20_test_setting.qc_20_normal_test_setting[0].on_off;

	draw_edit_test_item_2_on_off(s_cur_option_on_off);
}

static void enter_edit_item_2_MTK_on_off(void)
{
	s_cur_option_on_off = s_mtk_test_setting.mtk_normal_test_setting[0].on_off;

	draw_edit_test_item_2_on_off(s_cur_option_on_off);
}

static void (*const s_enter_edit_item_2_on_off[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = enter_edit_item_2_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = enter_edit_item_2_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = enter_edit_item_2_MTK_on_off
};

static void enter_edit_item_2_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_enter_edit_item_2_on_off[s_cur_test_category]();

		s_edit_item = EDIT_ITEM_2_ON_OFF;
	}
}

static void enter_edit_item_2_synth_setting(void)
{
	switch_to_menu(get_cur_synth_test_type_menu(s_synth_test_setting.synth_normal_test_setting[0].test_type));
}

static void enter_edit_item_2_qc_20_setting(void)
{
	switch_to_menu(get_cur_qc_20_test_type_menu(s_qc_20_test_setting.qc_20_normal_test_setting[0].test_type));
}

static void enter_edit_item_2_MTK_setting(void)
{
	switch_to_menu(get_cur_mtk_test_type_menu(s_mtk_test_setting.mtk_normal_test_setting[0].test_type));
}

static void (*const s_enter_edit_item_2_setting[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = enter_edit_item_2_synth_setting,

	[TEST_CATEGORY_QC_20_TEST] = enter_edit_item_2_qc_20_setting,

	[TEST_CATEGORY_MTK_TEST]   = enter_edit_item_2_MTK_setting
};

static void enter_edit_item_2_setting(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_enter_edit_item_2_setting[s_cur_test_category]();
	}
}


static void enter_edit_item_3_synth_type(void)
{
	s_cur_test_type_index = s_synth_test_type_to_index[s_synth_test_setting.synth_normal_test_setting[1].test_type];
	
	draw_edit_synth_item_3_type(s_synth_test_setting.synth_normal_test_setting[1].test_type);
}

static void enter_edit_item_3_qc_20_type(void)
{
	s_cur_test_type_index = s_qc_20_test_type_to_index[s_qc_20_test_setting.qc_20_normal_test_setting[1].test_type];

	draw_edit_qc_20_item_3_type(s_qc_20_test_setting.qc_20_normal_test_setting[1].test_type);
}

static void enter_edit_item_3_MTK_type(void)
{
	s_cur_test_type_index = s_mtk_test_type_to_index[s_mtk_test_setting.mtk_normal_test_setting[1].test_type];

	draw_edit_mtk_item_3_type(s_mtk_test_setting.mtk_normal_test_setting[1].test_type);
}

static void (*const s_enter_edit_item_3_type[])(void) = 

{
	[TEST_CATEGORY_SYNTH_TEST] = enter_edit_item_3_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = enter_edit_item_3_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = enter_edit_item_3_MTK_type
};

static void enter_edit_item_3_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_enter_edit_item_3_type[s_cur_test_category]();

		s_edit_item = EDIT_ITEM_3_TYPE;
	}
}

static void enter_edit_item_3_synth_on_off(void)
{
	s_cur_option_on_off = s_synth_test_setting.synth_normal_test_setting[1].on_off;

	draw_edit_test_item_3_on_off(s_cur_option_on_off);
}

static void enter_edit_item_3_qc_20_on_off(void)
{
	s_cur_option_on_off = s_qc_20_test_setting.qc_20_normal_test_setting[1].on_off;

	draw_edit_test_item_3_on_off(s_cur_option_on_off);
}

static void enter_edit_item_3_MTK_on_off(void)
{
	s_cur_option_on_off = s_mtk_test_setting.mtk_normal_test_setting[1].on_off;

	draw_edit_test_item_3_on_off(s_cur_option_on_off);
}

static void (*const s_enter_edit_item_3_on_off[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = enter_edit_item_3_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = enter_edit_item_3_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = enter_edit_item_3_MTK_on_off
};

static void enter_edit_item_3_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_enter_edit_item_3_on_off[s_cur_test_category]();

		s_edit_item = EDIT_ITEM_3_ON_OFF;
	}
}

static void enter_edit_item_3_synth_setting(void)
{
	switch_to_menu(get_cur_synth_test_type_menu(s_synth_test_setting.synth_normal_test_setting[1].test_type));
}

static void enter_edit_item_3_qc_20_setting(void)
{
	switch_to_menu(get_cur_qc_20_test_type_menu(s_qc_20_test_setting.qc_20_normal_test_setting[1].test_type));
}

static void enter_edit_item_3_MTK_setting(void)
{
	switch_to_menu(get_cur_mtk_test_type_menu(s_mtk_test_setting.mtk_normal_test_setting[1].test_type));
}

static void (*const s_enter_edit_item_3_setting[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = enter_edit_item_3_synth_setting,

	[TEST_CATEGORY_QC_20_TEST] = enter_edit_item_3_qc_20_setting,

	[TEST_CATEGORY_MTK_TEST]   = enter_edit_item_3_MTK_setting
};

static void enter_edit_item_3_setting(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_enter_edit_item_3_setting[s_cur_test_category]();
	}
}

static void enter_edit_item_4_synth_type(void)
{
	s_cur_test_type_index = s_synth_test_type_to_index[s_synth_test_setting.synth_normal_test_setting[2].test_type];
	
	draw_edit_synth_item_4_type(s_synth_test_setting.synth_normal_test_setting[2].test_type);
}

static void enter_edit_item_4_qc_20_type(void)
{
	s_cur_test_type_index = s_qc_20_test_type_to_index[s_qc_20_test_setting.qc_20_normal_test_setting[2].test_type];

	draw_edit_qc_20_item_4_type(s_qc_20_test_setting.qc_20_normal_test_setting[2].test_type);
}

static void enter_edit_item_4_MTK_type(void)
{
	s_cur_test_type_index = s_mtk_test_type_to_index[s_mtk_test_setting.mtk_normal_test_setting[2].test_type];

	draw_edit_mtk_item_4_type(s_mtk_test_setting.mtk_normal_test_setting[2].test_type);
}

static void (*const s_enter_edit_item_4_type[])(void) = 

{
	[TEST_CATEGORY_SYNTH_TEST] = enter_edit_item_4_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = enter_edit_item_4_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = enter_edit_item_4_MTK_type
};

static void enter_edit_item_4_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_enter_edit_item_4_type[s_cur_test_category]();

		s_edit_item = EDIT_ITEM_4_TYPE;
	}
}

static void enter_edit_item_4_synth_on_off(void)
{
	s_cur_option_on_off = s_synth_test_setting.synth_normal_test_setting[2].on_off;

	draw_edit_test_item_4_on_off(s_cur_option_on_off);
}

static void enter_edit_item_4_qc_20_on_off(void)
{
	s_cur_option_on_off = s_qc_20_test_setting.qc_20_normal_test_setting[1].on_off;

	draw_edit_test_item_4_on_off(s_cur_option_on_off);
}

static void enter_edit_item_4_MTK_on_off(void)
{
	s_cur_option_on_off = s_mtk_test_setting.mtk_normal_test_setting[1].on_off;

	draw_edit_test_item_4_on_off(s_cur_option_on_off);
}

static void (*const s_enter_edit_item_4_on_off[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = enter_edit_item_4_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = enter_edit_item_4_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = enter_edit_item_4_MTK_on_off
};

static void enter_edit_item_4_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_enter_edit_item_4_on_off[s_cur_test_category]();

		s_edit_item = EDIT_ITEM_4_ON_OFF;
	}
}

static void enter_edit_item_4_synth_setting(void)
{
	switch_to_menu(get_cur_synth_test_type_menu(s_synth_test_setting.synth_normal_test_setting[2].test_type));
}

static void enter_edit_item_4_qc_20_setting(void)
{
	switch_to_menu(get_cur_qc_20_test_type_menu(s_qc_20_test_setting.qc_20_normal_test_setting[2].test_type));
}

static void enter_edit_item_4_MTK_setting(void)
{
	switch_to_menu(get_cur_mtk_test_type_menu(s_mtk_test_setting.mtk_normal_test_setting[2].test_type));
}

static void (*const s_enter_edit_item_4_setting[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = enter_edit_item_4_synth_setting,

	[TEST_CATEGORY_QC_20_TEST] = enter_edit_item_4_qc_20_setting,

	[TEST_CATEGORY_MTK_TEST]   = enter_edit_item_4_MTK_setting
};

static void enter_edit_item_4_setting(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_enter_edit_item_4_setting[s_cur_test_category]();
	}
}

static void enter_edit_item_5_synth_type(void)
{
	s_cur_test_type_index = s_synth_test_type_to_index[s_synth_test_setting.synth_normal_test_setting[3].test_type];
	
	draw_edit_synth_item_5_type(s_synth_test_setting.synth_normal_test_setting[3].test_type);
}

static void enter_edit_item_5_qc_20_type(void)
{
	s_cur_test_type_index = s_qc_20_test_type_to_index[s_qc_20_test_setting.qc_20_normal_test_setting[3].test_type];

	draw_edit_qc_20_item_5_type(s_qc_20_test_setting.qc_20_normal_test_setting[3].test_type);
}

static void enter_edit_item_5_MTK_type(void)
{
	s_cur_test_type_index = s_mtk_test_type_to_index[s_mtk_test_setting.mtk_normal_test_setting[3].test_type];

	draw_edit_mtk_item_5_type(s_mtk_test_setting.mtk_normal_test_setting[3].test_type);
}

static void (*const s_enter_edit_item_5_type[])(void) = 

{
	[TEST_CATEGORY_SYNTH_TEST] = enter_edit_item_5_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = enter_edit_item_5_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = enter_edit_item_5_MTK_type
};

static void enter_edit_item_5_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_enter_edit_item_5_type[s_cur_test_category]();

		s_edit_item = EDIT_ITEM_5_TYPE;
	}
}

static void enter_edit_item_5_synth_on_off(void)
{
	s_cur_option_on_off = s_synth_test_setting.synth_normal_test_setting[3].on_off;

	draw_edit_test_item_5_on_off(s_cur_option_on_off);
}

static void enter_edit_item_5_qc_20_on_off(void)
{
	s_cur_option_on_off = s_qc_20_test_setting.qc_20_normal_test_setting[3].on_off;

	draw_edit_test_item_5_on_off(s_cur_option_on_off);
}

static void enter_edit_item_5_MTK_on_off(void)
{
	s_cur_option_on_off = s_mtk_test_setting.mtk_normal_test_setting[3].on_off;

	draw_edit_test_item_5_on_off(s_cur_option_on_off);
}

static void (*const s_enter_edit_item_5_on_off[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = enter_edit_item_5_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = enter_edit_item_5_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = enter_edit_item_5_MTK_on_off
};

static void enter_edit_item_5_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_enter_edit_item_5_on_off[s_cur_test_category]();

		s_edit_item = EDIT_ITEM_5_ON_OFF;
	}
}

static void enter_edit_item_5_synth_setting(void)
{
	switch_to_menu(get_cur_synth_test_type_menu(s_synth_test_setting.synth_normal_test_setting[3].test_type));
}

static void enter_edit_item_5_qc_20_setting(void)
{
	switch_to_menu(get_cur_qc_20_test_type_menu(s_qc_20_test_setting.qc_20_normal_test_setting[3].test_type));
}

static void enter_edit_item_5_MTK_setting(void)
{
	switch_to_menu(get_cur_mtk_test_type_menu(s_mtk_test_setting.mtk_normal_test_setting[3].test_type));
}

static void (*const s_enter_edit_item_5_setting[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = enter_edit_item_5_synth_setting,

	[TEST_CATEGORY_QC_20_TEST] = enter_edit_item_5_qc_20_setting,

	[TEST_CATEGORY_MTK_TEST]   = enter_edit_item_5_MTK_setting
};

static void enter_edit_item_5_setting(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_enter_edit_item_5_setting[s_cur_test_category]();
	}
}

static void enter_edit_item_6_synth_type(void)
{
	s_cur_test_type_index = s_synth_test_type_to_index[s_synth_test_setting.synth_normal_test_setting[4].test_type];
	
	draw_edit_synth_item_6_type(s_synth_test_setting.synth_normal_test_setting[4].test_type);
}

static void enter_edit_item_6_qc_20_type(void)
{
	s_cur_test_type_index = s_qc_20_test_type_to_index[s_qc_20_test_setting.qc_20_normal_test_setting[4].test_type];

	draw_edit_qc_20_item_6_type(s_qc_20_test_setting.qc_20_normal_test_setting[4].test_type);
}

static void enter_edit_item_6_MTK_type(void)
{
	s_cur_test_type_index = s_mtk_test_type_to_index[s_mtk_test_setting.mtk_normal_test_setting[4].test_type];

	draw_edit_mtk_item_6_type(s_mtk_test_setting.mtk_normal_test_setting[4].test_type);
}

static void (*const s_enter_edit_item_6_type[])(void) = 

{
	[TEST_CATEGORY_SYNTH_TEST] = enter_edit_item_6_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = enter_edit_item_6_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = enter_edit_item_6_MTK_type
};

static void enter_edit_item_6_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_enter_edit_item_6_type[s_cur_test_category]();

		s_edit_item = EDIT_ITEM_6_TYPE;
	}
}

static void enter_edit_item_6_synth_on_off(void)
{
	s_cur_option_on_off = s_synth_test_setting.synth_normal_test_setting[4].on_off;

	draw_edit_test_item_6_on_off(s_cur_option_on_off);
}

static void enter_edit_item_6_qc_20_on_off(void)
{
	s_cur_option_on_off = s_qc_20_test_setting.qc_20_normal_test_setting[4].on_off;

	draw_edit_test_item_6_on_off(s_cur_option_on_off);
}

static void enter_edit_item_6_MTK_on_off(void)
{
	s_cur_option_on_off = s_mtk_test_setting.mtk_normal_test_setting[4].on_off;

	draw_edit_test_item_6_on_off(s_cur_option_on_off);
}

static void (*const s_enter_edit_item_6_on_off[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = enter_edit_item_6_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = enter_edit_item_6_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = enter_edit_item_6_MTK_on_off
};

static void enter_edit_item_6_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_enter_edit_item_6_on_off[s_cur_test_category]();

		s_edit_item = EDIT_ITEM_6_ON_OFF;
	}
}

static void enter_edit_item_6_synth_setting(void)
{
	switch_to_menu(get_cur_synth_test_type_menu(s_synth_test_setting.synth_normal_test_setting[4].test_type));
}

static void enter_edit_item_6_qc_20_setting(void)
{
	switch_to_menu(get_cur_qc_20_test_type_menu(s_qc_20_test_setting.qc_20_normal_test_setting[4].test_type));
}

static void enter_edit_item_6_MTK_setting(void)
{
	switch_to_menu(get_cur_mtk_test_type_menu(s_mtk_test_setting.mtk_normal_test_setting[4].test_type));
}

static void (*const s_enter_edit_item_6_setting[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = enter_edit_item_6_synth_setting,

	[TEST_CATEGORY_QC_20_TEST] = enter_edit_item_6_qc_20_setting,

	[TEST_CATEGORY_MTK_TEST]   = enter_edit_item_6_MTK_setting
};

static void enter_edit_item_6_setting(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_enter_edit_item_6_setting[s_cur_test_category]();
	}
}

static void enter_edit_item_7_synth_type(void)
{
	s_cur_test_type_index = s_synth_test_type_to_index[s_synth_test_setting.synth_normal_test_setting[5].test_type];
	
	draw_edit_synth_item_7_type(s_synth_test_setting.synth_normal_test_setting[5].test_type);
}

static void enter_edit_item_7_qc_20_type(void)
{
	s_cur_test_type_index = s_qc_20_test_type_to_index[s_qc_20_test_setting.qc_20_normal_test_setting[5].test_type];

	draw_edit_qc_20_item_7_type(s_qc_20_test_setting.qc_20_normal_test_setting[5].test_type);
}

static void enter_edit_item_7_MTK_type(void)
{
	s_cur_test_type_index = s_mtk_test_type_to_index[s_mtk_test_setting.mtk_normal_test_setting[5].test_type];

	draw_edit_mtk_item_7_type(s_mtk_test_setting.mtk_normal_test_setting[5].test_type);
}

static void (*const s_enter_edit_item_7_type[])(void) = 

{
	[TEST_CATEGORY_SYNTH_TEST] = enter_edit_item_7_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = enter_edit_item_7_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = enter_edit_item_7_MTK_type
};

static void enter_edit_item_7_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_enter_edit_item_7_type[s_cur_test_category]();

		s_edit_item = EDIT_ITEM_7_TYPE;
	}
}

static void enter_edit_item_7_synth_on_off(void)
{
	s_cur_option_on_off = s_synth_test_setting.synth_normal_test_setting[5].on_off;

	draw_edit_test_item_7_on_off(s_cur_option_on_off);
}

static void enter_edit_item_7_qc_20_on_off(void)
{
	s_cur_option_on_off = s_qc_20_test_setting.qc_20_normal_test_setting[5].on_off;

	draw_edit_test_item_7_on_off(s_cur_option_on_off);
}

static void enter_edit_item_7_MTK_on_off(void)
{
	s_cur_option_on_off = s_mtk_test_setting.mtk_normal_test_setting[5].on_off;

	draw_edit_test_item_7_on_off(s_cur_option_on_off);
}

static void (*const s_enter_edit_item_7_on_off[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = enter_edit_item_7_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = enter_edit_item_7_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = enter_edit_item_7_MTK_on_off
};

static void enter_edit_item_7_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_enter_edit_item_7_on_off[s_cur_test_category]();

		s_edit_item = EDIT_ITEM_7_ON_OFF;
	}
}

static void enter_edit_item_7_synth_setting(void)
{
	switch_to_menu(get_cur_synth_test_type_menu(s_synth_test_setting.synth_normal_test_setting[5].test_type));
}

static void enter_edit_item_7_qc_20_setting(void)
{
	switch_to_menu(get_cur_qc_20_test_type_menu(s_qc_20_test_setting.qc_20_normal_test_setting[5].test_type));
}

static void enter_edit_item_7_MTK_setting(void)
{
	switch_to_menu(get_cur_mtk_test_type_menu(s_mtk_test_setting.mtk_normal_test_setting[5].test_type));
}

static void (*const s_enter_edit_item_7_setting[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = enter_edit_item_7_synth_setting,

	[TEST_CATEGORY_QC_20_TEST] = enter_edit_item_7_qc_20_setting,

	[TEST_CATEGORY_MTK_TEST]   = enter_edit_item_7_MTK_setting
};

static void enter_edit_item_7_setting(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_enter_edit_item_7_setting[s_cur_test_category]();
	}
}

static void enter_edit_item_8_synth_on_off(void)
{
	s_cur_option_on_off = s_synth_test_setting.discharge_test_setting.on_off;

	draw_edit_test_item_8_on_off(s_cur_option_on_off);
}

static void enter_edit_item_8_qc_20_on_off(void)
{
	s_cur_option_on_off = s_qc_20_test_setting.discharge_test_setting.on_off;

	draw_edit_test_item_8_on_off(s_cur_option_on_off);
}

static void enter_edit_item_8_MTK_on_off(void)
{
	s_cur_option_on_off = s_mtk_test_setting.discharge_test_setting.on_off;

	draw_edit_test_item_8_on_off(s_cur_option_on_off);
}

static void (*const s_enter_edit_item_8_on_off[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = enter_edit_item_8_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = enter_edit_item_8_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = enter_edit_item_8_MTK_on_off
};

static void enter_edit_item_8_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_enter_edit_item_8_on_off[s_cur_test_category]();

		s_edit_item = EDIT_ITEM_8_ON_OFF;
	}
}
static void enter_edit_item_8_setting(void)
{
	switch_to_menu(MENU_ID_DISCHARGE_SETTING);
}

static void (*const s_enter_edit_fun_arr[])(void) = 
{
	[FOCUS_GROUP] = enter_edit_group,
	[FOCUS_TEST]  = enter_edit_test,
	
	[FOCUS_ITEM_1_SETTING] = enter_edit_item_1_setting,
	
	[FOCUS_ITEM_2_TYPE]    = enter_edit_item_2_type,
	[FOCUS_ITEM_2_ON_OFF]  = enter_edit_item_2_on_off, 
	[FOCUS_ITEM_2_SETTING] = enter_edit_item_2_setting, 
	
	[FOCUS_ITEM_3_TYPE]    = enter_edit_item_3_type,
	[FOCUS_ITEM_3_ON_OFF]  = enter_edit_item_3_on_off,
	[FOCUS_ITEM_3_SETTING] = enter_edit_item_3_setting,

	[FOCUS_ITEM_4_TYPE]    = enter_edit_item_4_type,
	[FOCUS_ITEM_4_ON_OFF]  = enter_edit_item_4_on_off,
	[FOCUS_ITEM_4_SETTING] = enter_edit_item_4_setting,
	
	[FOCUS_ITEM_5_TYPE]    = enter_edit_item_5_type,
	[FOCUS_ITEM_5_ON_OFF]  = enter_edit_item_5_on_off,
	[FOCUS_ITEM_5_SETTING] = enter_edit_item_5_setting,
	
	[FOCUS_ITEM_6_TYPE]    = enter_edit_item_6_type,
	[FOCUS_ITEM_6_ON_OFF]  = enter_edit_item_6_on_off,
	[FOCUS_ITEM_6_SETTING] = enter_edit_item_6_setting,
	
	[FOCUS_ITEM_7_TYPE]    = enter_edit_item_7_type,
	[FOCUS_ITEM_7_ON_OFF]  = enter_edit_item_7_on_off,
	[FOCUS_ITEM_7_SETTING] = enter_edit_item_7_setting,

	[FOCUS_ITEM_8_ON_OFF]  = enter_edit_item_8_on_off,
	[FOCUS_ITEM_8_SETTING] = enter_edit_item_8_setting
};

/* confirm edit functions */
static void confirm_edit_group(void)
{
	draw_focus_test_setting_group(s_cur_group + 1);
}

static void confirm_edit_test(void)
{
	/* test */
}

static void confirm_edit_item_1_setting(void)
{
	
}

static void confirm_edit_item_2_synth_type(void)
{
	s_synth_test_setting.synth_normal_test_setting[0].test_type = s_synth_test_index_to_type[s_cur_test_type_index];
	
	draw_focus_synth_item_2_type(s_synth_test_setting.synth_normal_test_setting[0].test_type);

	/* save */
	save_synth_test_type(s_cur_group, 2);
}


static void confirm_edit_item_2_qc_20_type(void)
{
	s_qc_20_test_setting.qc_20_normal_test_setting[0].test_type = s_qc_20_test_index_to_type[s_cur_test_type_index];

	draw_focus_qc_20_item_2_type(s_qc_20_test_setting.qc_20_normal_test_setting[0].test_type);

	save_qc_20_test_type(s_cur_group, 2);
}

static void confirm_edit_item_2_MTK_type(void)
{
	s_mtk_test_setting.mtk_normal_test_setting[0].test_type = s_mtk_test_index_to_type[s_cur_test_type_index];

	draw_focus_mtk_item_2_type(s_mtk_test_setting.mtk_normal_test_setting[0].test_type);

	save_mtk_test_type(s_cur_group, 2);
}

static void (*const s_confirm_edit_item_2_type[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = confirm_edit_item_2_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = confirm_edit_item_2_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = confirm_edit_item_2_MTK_type
};

static void confirm_edit_item_2_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_confirm_edit_item_2_type[s_cur_test_category]();
	}
}

static void confirm_edit_item_2_synth_on_off(void)
{
	s_synth_test_setting.synth_normal_test_setting[0].on_off = s_cur_option_on_off;
	
	draw_focus_test_item_2_on_off(s_synth_test_setting.synth_normal_test_setting[0].on_off);

	save_synth_test_on_off(s_cur_group, 2);
}

static void confirm_edit_item_2_qc_20_on_off(void)
{
	s_qc_20_test_setting.qc_20_normal_test_setting[0].on_off = s_cur_option_on_off;
	
	draw_focus_test_item_2_on_off(s_qc_20_test_setting.qc_20_normal_test_setting[0].on_off);

	save_qc_20_test_on_off(s_cur_group, 2);
}


static void confirm_edit_item_2_MTK_on_off(void)
{
	s_mtk_test_setting.mtk_normal_test_setting[0].on_off = s_cur_option_on_off;
	
	draw_focus_test_item_2_on_off(s_mtk_test_setting.mtk_normal_test_setting[0].on_off);

	save_mtk_test_on_off(s_cur_group, 2);
}


static void (*s_confirm_edit_item_2_on_off[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = confirm_edit_item_2_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = confirm_edit_item_2_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = confirm_edit_item_2_MTK_on_off

};

static void confirm_edit_item_2_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_confirm_edit_item_2_on_off[s_cur_test_category]();
	}
}

static void confirm_edit_item_2_setting(void)
{
	
}

static void confirm_edit_item_3_synth_type(void)
{
	s_synth_test_setting.synth_normal_test_setting[1].test_type = s_synth_test_index_to_type[s_cur_test_type_index];
	
	draw_focus_synth_item_3_type(s_synth_test_setting.synth_normal_test_setting[1].test_type);

	/* save */
	save_synth_test_type(s_cur_group, 3);
}


static void confirm_edit_item_3_qc_20_type(void)
{
	s_qc_20_test_setting.qc_20_normal_test_setting[1].test_type = s_qc_20_test_index_to_type[s_cur_test_type_index];

	draw_focus_qc_20_item_3_type(s_qc_20_test_setting.qc_20_normal_test_setting[1].test_type);

	save_qc_20_test_type(s_cur_group, 3);
}

static void confirm_edit_item_3_MTK_type(void)
{
	s_mtk_test_setting.mtk_normal_test_setting[1].test_type = s_mtk_test_index_to_type[s_cur_test_type_index];

	draw_focus_mtk_item_3_type(s_mtk_test_setting.mtk_normal_test_setting[1].test_type);

	save_mtk_test_type(s_cur_group, 3);
}

static void (*const s_confirm_edit_item_3_type[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = confirm_edit_item_3_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = confirm_edit_item_3_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = confirm_edit_item_3_MTK_type
};

static void confirm_edit_item_3_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_confirm_edit_item_3_type[s_cur_test_category]();
	}
}

static void confirm_edit_item_3_synth_on_off(void)
{
	s_synth_test_setting.synth_normal_test_setting[1].on_off = s_cur_option_on_off;
	
	draw_focus_test_item_3_on_off(s_synth_test_setting.synth_normal_test_setting[1].on_off);

	save_synth_test_on_off(s_cur_group, 3);
}

static void confirm_edit_item_3_qc_20_on_off(void)
{
	s_qc_20_test_setting.qc_20_normal_test_setting[1].on_off = s_cur_option_on_off;
	
	draw_focus_test_item_3_on_off(s_qc_20_test_setting.qc_20_normal_test_setting[1].on_off);

	save_qc_20_test_on_off(s_cur_group, 3);
}


static void confirm_edit_item_3_MTK_on_off(void)
{
	s_mtk_test_setting.mtk_normal_test_setting[1].on_off = s_cur_option_on_off;
	
	draw_focus_test_item_3_on_off(s_mtk_test_setting.mtk_normal_test_setting[1].on_off);

	save_mtk_test_on_off(s_cur_group, 3);
}


static void (*s_confirm_edit_item_3_on_off[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = confirm_edit_item_3_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = confirm_edit_item_3_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = confirm_edit_item_3_MTK_on_off

};

static void confirm_edit_item_3_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_confirm_edit_item_3_on_off[s_cur_test_category]();
	}
}

static void confirm_edit_item_3_setting(void)
{
	
}

static void confirm_edit_item_4_synth_type(void)
{
	s_synth_test_setting.synth_normal_test_setting[2].test_type = s_synth_test_index_to_type[s_cur_test_type_index];
	
	draw_focus_synth_item_4_type(s_synth_test_setting.synth_normal_test_setting[2].test_type);

	/* save */
	save_synth_test_type(s_cur_group, 4);
}


static void confirm_edit_item_4_qc_20_type(void)
{
	s_qc_20_test_setting.qc_20_normal_test_setting[2].test_type = s_qc_20_test_index_to_type[s_cur_test_type_index];

	draw_focus_qc_20_item_4_type(s_qc_20_test_setting.qc_20_normal_test_setting[2].test_type);

	save_qc_20_test_type(s_cur_group, 4);
}

static void confirm_edit_item_4_MTK_type(void)
{
	s_mtk_test_setting.mtk_normal_test_setting[2].test_type = s_mtk_test_index_to_type[s_cur_test_type_index];

	draw_focus_mtk_item_4_type(s_mtk_test_setting.mtk_normal_test_setting[2].test_type);

	save_mtk_test_type(s_cur_group, 4);
}

static void (*const s_confirm_edit_item_4_type[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = confirm_edit_item_4_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = confirm_edit_item_4_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = confirm_edit_item_4_MTK_type
};

static void confirm_edit_item_4_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_confirm_edit_item_4_type[s_cur_test_category]();
	}
}

static void confirm_edit_item_4_synth_on_off(void)
{
	s_synth_test_setting.synth_normal_test_setting[2].on_off = s_cur_option_on_off;
	
	draw_focus_test_item_4_on_off(s_synth_test_setting.synth_normal_test_setting[2].on_off);

	save_synth_test_on_off(s_cur_group, 4);
}

static void confirm_edit_item_4_qc_20_on_off(void)
{
	s_qc_20_test_setting.qc_20_normal_test_setting[2].on_off = s_cur_option_on_off;
	
	draw_focus_test_item_4_on_off(s_qc_20_test_setting.qc_20_normal_test_setting[2].on_off);

	save_qc_20_test_on_off(s_cur_group, 4);
}

static void confirm_edit_item_4_MTK_on_off(void)
{
	s_mtk_test_setting.mtk_normal_test_setting[2].on_off = s_cur_option_on_off;
	
	draw_focus_test_item_4_on_off(s_mtk_test_setting.mtk_normal_test_setting[2].on_off);

	save_mtk_test_on_off(s_cur_group, 4);
}


static void (*s_confirm_edit_item_4_on_off[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = confirm_edit_item_4_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = confirm_edit_item_4_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = confirm_edit_item_4_MTK_on_off

};

static void confirm_edit_item_4_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_confirm_edit_item_4_on_off[s_cur_test_category]();
	}
}

static void confirm_edit_item_4_setting(void)
{
	
}

static void confirm_edit_item_5_synth_type(void)
{
	s_synth_test_setting.synth_normal_test_setting[3].test_type = s_synth_test_index_to_type[s_cur_test_type_index];
	
	draw_focus_synth_item_5_type(s_synth_test_setting.synth_normal_test_setting[3].test_type);

	/* save */
	save_synth_test_type(s_cur_group, 5);
}


static void confirm_edit_item_5_qc_20_type(void)
{
	s_qc_20_test_setting.qc_20_normal_test_setting[3].test_type = s_qc_20_test_index_to_type[s_cur_test_type_index];

	draw_focus_qc_20_item_5_type(s_qc_20_test_setting.qc_20_normal_test_setting[3].test_type);

	save_qc_20_test_type(s_cur_group, 5);
}

static void confirm_edit_item_5_MTK_type(void)
{
	s_mtk_test_setting.mtk_normal_test_setting[3].test_type = s_mtk_test_index_to_type[s_cur_test_type_index];

	draw_focus_mtk_item_5_type(s_mtk_test_setting.mtk_normal_test_setting[3].test_type);

	save_mtk_test_type(s_cur_group, 5);
}

static void (*const s_confirm_edit_item_5_type[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = confirm_edit_item_5_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = confirm_edit_item_5_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = confirm_edit_item_5_MTK_type
};

static void confirm_edit_item_5_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_confirm_edit_item_5_type[s_cur_test_category]();
	}
}

static void confirm_edit_item_5_synth_on_off(void)
{
	s_synth_test_setting.synth_normal_test_setting[3].on_off = s_cur_option_on_off;
	
	draw_focus_test_item_5_on_off(s_synth_test_setting.synth_normal_test_setting[3].on_off);

	save_synth_test_on_off(s_cur_group, 5);
}

static void confirm_edit_item_5_qc_20_on_off(void)
{
	s_qc_20_test_setting.qc_20_normal_test_setting[3].on_off = s_cur_option_on_off;
	
	draw_focus_test_item_5_on_off(s_qc_20_test_setting.qc_20_normal_test_setting[3].on_off);

	save_qc_20_test_on_off(s_cur_group, 5);
}

static void confirm_edit_item_5_MTK_on_off(void)
{
	s_mtk_test_setting.mtk_normal_test_setting[3].on_off = s_cur_option_on_off;
	
	draw_focus_test_item_5_on_off(s_mtk_test_setting.mtk_normal_test_setting[3].on_off);

	save_mtk_test_on_off(s_cur_group, 5);
}


static void (*s_confirm_edit_item_5_on_off[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = confirm_edit_item_5_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = confirm_edit_item_5_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = confirm_edit_item_5_MTK_on_off

};

static void confirm_edit_item_5_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_confirm_edit_item_5_on_off[s_cur_test_category]();
	}
}

static void confirm_edit_item_5_setting(void)
{
	
}

static void confirm_edit_item_6_synth_type(void)
{
	s_synth_test_setting.synth_normal_test_setting[4].test_type = s_synth_test_index_to_type[s_cur_test_type_index];
	
	draw_focus_synth_item_6_type(s_synth_test_setting.synth_normal_test_setting[4].test_type);

	/* save */
	save_synth_test_type(s_cur_group, 6);
}


static void confirm_edit_item_6_qc_20_type(void)
{
	s_qc_20_test_setting.qc_20_normal_test_setting[4].test_type = s_qc_20_test_index_to_type[s_cur_test_type_index];

	draw_focus_qc_20_item_6_type(s_qc_20_test_setting.qc_20_normal_test_setting[4].test_type);

	save_qc_20_test_type(s_cur_group, 6);
}

static void confirm_edit_item_6_MTK_type(void)
{
	s_mtk_test_setting.mtk_normal_test_setting[4].test_type = s_mtk_test_index_to_type[s_cur_test_type_index];

	draw_focus_mtk_item_6_type(s_mtk_test_setting.mtk_normal_test_setting[4].test_type);

	save_mtk_test_type(s_cur_group, 6);
}

static void (*const s_confirm_edit_item_6_type[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = confirm_edit_item_6_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = confirm_edit_item_6_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = confirm_edit_item_6_MTK_type
};

static void confirm_edit_item_6_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_confirm_edit_item_6_type[s_cur_test_category]();
	}
}

static void confirm_edit_item_6_synth_on_off(void)
{
	s_synth_test_setting.synth_normal_test_setting[4].on_off = s_cur_option_on_off;
	
	draw_focus_test_item_6_on_off(s_synth_test_setting.synth_normal_test_setting[4].on_off);

	save_synth_test_on_off(s_cur_group, 6);
}

static void confirm_edit_item_6_qc_20_on_off(void)
{
	s_qc_20_test_setting.qc_20_normal_test_setting[4].on_off = s_cur_option_on_off;
	
	draw_focus_test_item_6_on_off(s_qc_20_test_setting.qc_20_normal_test_setting[4].on_off);

	save_qc_20_test_on_off(s_cur_group, 6);
}

static void confirm_edit_item_6_MTK_on_off(void)
{
	s_mtk_test_setting.mtk_normal_test_setting[4].on_off = s_cur_option_on_off;
	
	draw_focus_test_item_6_on_off(s_mtk_test_setting.mtk_normal_test_setting[4].on_off);

	save_mtk_test_on_off(s_cur_group, 6);
}

static void (*s_confirm_edit_item_6_on_off[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = confirm_edit_item_6_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = confirm_edit_item_6_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = confirm_edit_item_6_MTK_on_off

};

static void confirm_edit_item_6_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_confirm_edit_item_6_on_off[s_cur_test_category]();
	}
}

static void confirm_edit_item_6_setting(void)
{
	
}

static void confirm_edit_item_7_synth_type(void)
{
	s_synth_test_setting.synth_normal_test_setting[5].test_type = s_synth_test_index_to_type[s_cur_test_type_index];
	
	draw_focus_synth_item_7_type(s_synth_test_setting.synth_normal_test_setting[5].test_type);

	/* save */
	save_synth_test_type(s_cur_group, 7);
}


static void confirm_edit_item_7_qc_20_type(void)
{
	s_qc_20_test_setting.qc_20_normal_test_setting[5].test_type = s_qc_20_test_index_to_type[s_cur_test_type_index];

	draw_focus_qc_20_item_7_type(s_qc_20_test_setting.qc_20_normal_test_setting[5].test_type);

	save_qc_20_test_type(s_cur_group, 7);
}

static void confirm_edit_item_7_MTK_type(void)
{
	s_mtk_test_setting.mtk_normal_test_setting[5].test_type = s_mtk_test_index_to_type[s_cur_test_type_index];

	draw_focus_mtk_item_7_type(s_mtk_test_setting.mtk_normal_test_setting[5].test_type);

	save_mtk_test_type(s_cur_group, 7);
}

static void (*const s_confirm_edit_item_7_type[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = confirm_edit_item_7_synth_type,

	[TEST_CATEGORY_QC_20_TEST] = confirm_edit_item_7_qc_20_type,

	[TEST_CATEGORY_MTK_TEST]   = confirm_edit_item_7_MTK_type
};

static void confirm_edit_item_7_type(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_confirm_edit_item_7_type[s_cur_test_category]();
	}
}

static void confirm_edit_item_7_synth_on_off(void)
{
	s_synth_test_setting.synth_normal_test_setting[5].on_off = s_cur_option_on_off;
	
	draw_focus_test_item_7_on_off(s_synth_test_setting.synth_normal_test_setting[5].on_off);

	save_synth_test_on_off(s_cur_group, 7);
}

static void confirm_edit_item_7_qc_20_on_off(void)
{
	s_qc_20_test_setting.qc_20_normal_test_setting[5].on_off = s_cur_option_on_off;
	
	draw_focus_test_item_7_on_off(s_qc_20_test_setting.qc_20_normal_test_setting[5].on_off);

	save_qc_20_test_on_off(s_cur_group, 7);
}

static void confirm_edit_item_7_MTK_on_off(void)
{
	s_mtk_test_setting.mtk_normal_test_setting[5].on_off = s_cur_option_on_off;
	
	draw_focus_test_item_7_on_off(s_mtk_test_setting.mtk_normal_test_setting[5].on_off);

	save_mtk_test_on_off(s_cur_group, 7);
}


static void (*s_confirm_edit_item_7_on_off[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = confirm_edit_item_7_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = confirm_edit_item_7_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = confirm_edit_item_7_MTK_on_off

};

static void confirm_edit_item_7_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_confirm_edit_item_7_on_off[s_cur_test_category]();
	}
}

static void confirm_edit_item_7_setting(void)
{

}


static void confirm_edit_item_8_synth_on_off(void)
{
	s_synth_test_setting.discharge_test_setting.on_off = s_cur_option_on_off;
	
	draw_focus_test_item_8_on_off(s_synth_test_setting.discharge_test_setting.on_off);

	save_synth_test_discharge_setting(s_cur_group);
}

static void confirm_edit_item_8_qc_20_on_off(void)
{
	s_qc_20_test_setting.discharge_test_setting.on_off = s_cur_option_on_off;
	
	draw_focus_test_item_8_on_off(s_qc_20_test_setting.discharge_test_setting.on_off);

	save_qc_20_test_discharge_setting(s_cur_group);
}

static void confirm_edit_item_8_MTK_on_off(void)
{
	s_mtk_test_setting.discharge_test_setting.on_off = s_cur_option_on_off;
	
	draw_focus_test_item_8_on_off(s_mtk_test_setting.discharge_test_setting.on_off);

	save_mtk_test_discharge_setting(s_cur_group);
}


static void (*s_confirm_edit_item_8_on_off[])(void) = 
{
	[TEST_CATEGORY_SYNTH_TEST] = confirm_edit_item_8_synth_on_off,

	[TEST_CATEGORY_QC_20_TEST] = confirm_edit_item_8_qc_20_on_off,

	[TEST_CATEGORY_MTK_TEST]   = confirm_edit_item_8_MTK_on_off

};

static void confirm_edit_item_8_on_off(void)
{
	if (s_cur_test_category < TEST_CATEGORY_COUNT)
	{
		s_confirm_edit_item_8_on_off[s_cur_test_category]();
	}
}
static void confirm_edit_item_8_setting(void)
{
	
}

static void (*const confirm_edit_fun_arr[])(void) = 
{
	[FOCUS_GROUP] = confirm_edit_group,
	[FOCUS_TEST]  = confirm_edit_test,
	
	[FOCUS_ITEM_1_SETTING] = confirm_edit_item_1_setting,
	
	[FOCUS_ITEM_2_TYPE]    = confirm_edit_item_2_type,
	[FOCUS_ITEM_2_ON_OFF]  = confirm_edit_item_2_on_off, 
	[FOCUS_ITEM_2_SETTING] = confirm_edit_item_2_setting, 
	
	[FOCUS_ITEM_3_TYPE]    = confirm_edit_item_3_type,
	[FOCUS_ITEM_3_ON_OFF]  = confirm_edit_item_3_on_off,
	[FOCUS_ITEM_3_SETTING] = confirm_edit_item_3_setting,

	[FOCUS_ITEM_4_TYPE]    = confirm_edit_item_4_type,
	[FOCUS_ITEM_4_ON_OFF]  = confirm_edit_item_4_on_off,
	[FOCUS_ITEM_4_SETTING] = confirm_edit_item_4_setting,
	
	[FOCUS_ITEM_5_TYPE]    = confirm_edit_item_5_type,
	[FOCUS_ITEM_5_ON_OFF]  = confirm_edit_item_5_on_off,
	[FOCUS_ITEM_5_SETTING] = confirm_edit_item_5_setting,
	
	[FOCUS_ITEM_6_TYPE]    = confirm_edit_item_6_type,
	[FOCUS_ITEM_6_ON_OFF]  = confirm_edit_item_6_on_off,
	[FOCUS_ITEM_6_SETTING] = confirm_edit_item_6_setting,
	
	[FOCUS_ITEM_7_TYPE]    = confirm_edit_item_7_type,
	[FOCUS_ITEM_7_ON_OFF]  = confirm_edit_item_7_on_off,
	[FOCUS_ITEM_7_SETTING] = confirm_edit_item_7_setting,

	[FOCUS_ITEM_8_ON_OFF]  = confirm_edit_item_8_on_off,
	[FOCUS_ITEM_8_SETTING] = confirm_edit_item_8_setting
};

/* edit functions */
static void edit_group(uint8_t key)
{
	bool need_refresh_caption = false;
	
	if (key == KEY_UP || key == KEY_RIGHT)
	{
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			s_cur_group++;
			if (s_cur_group == SYNTH_TEST_GROUP_COUNT)
			{
				if (s_device_privilege.QC_20_test_on_off == OPTION_ON)
				{
					s_cur_test_category = TEST_CATEGORY_QC_20_TEST;
				}
				else if (s_device_privilege.MTK_test_on_off == OPTION_ON)
				{
					s_cur_test_category = TEST_CATEGORY_MTK_TEST;
				}
				
				s_cur_group = 0;

				need_refresh_caption = true;
			}
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			s_cur_group++;
			if (s_cur_group == QC_20_TEST_GROUP_COUNT)
			{
				if (s_device_privilege.MTK_test_on_off == OPTION_ON)
				{
					s_cur_test_category = TEST_CATEGORY_MTK_TEST;
				}

				else
				{
					s_cur_test_category = TEST_CATEGORY_SYNTH_TEST;
				}

				s_cur_group = 0;

				need_refresh_caption = true;
			}
		}
		else if (s_cur_test_category == TEST_CATEGORY_MTK_TEST)
		{
			s_cur_group++;
			if (s_cur_group == MTK_TEST_GROUP_COUNT)
			{
				s_cur_test_category = TEST_CATEGORY_SYNTH_TEST;

				s_cur_group = 0;

				need_refresh_caption = true;
			}
		}
		
		load_group_test_setting(s_cur_test_category, s_cur_group);

		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			if (need_refresh_caption)
			{
				draw_synth_test_setting_caption();
			}
			
			draw_synth_test_setting_menu(&s_synth_test_setting);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			if (need_refresh_caption)
			{
				draw_qc_20_test_setting_caption();
			}
			
			draw_QC_20_test_setting_menu(&s_qc_20_test_setting);
		}
		else if (s_cur_test_category == TEST_CATEGORY_MTK_TEST)
		{

		}

		draw_edit_test_setting_group(s_cur_group + 1);
		
		lcd_validate_cmd();
	}
	else if (key == KEY_DOWN || key == KEY_LEFT)
	{
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			s_cur_group--;
			if (s_cur_group < 0)
			{
				if (s_device_privilege.MTK_test_on_off == OPTION_ON)
				{
					s_cur_test_category = TEST_CATEGORY_MTK_TEST;

					s_cur_group = MTK_TEST_GROUP_COUNT - 1;
				}
				else if (s_device_privilege.QC_20_test_on_off == OPTION_ON)
				{
					s_cur_test_category = TEST_CATEGORY_QC_20_TEST;

					s_cur_group = QC_20_TEST_GROUP_COUNT - 1;
				}
				else
				{
					s_cur_group = SYNTH_TEST_GROUP_COUNT - 1;
				}

				need_refresh_caption = true;
			}
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			s_cur_group--;
			if (s_cur_group < 0)
			{
				s_cur_test_category = TEST_CATEGORY_SYNTH_TEST;

				s_cur_group = SYNTH_TEST_GROUP_COUNT - 1;

				need_refresh_caption = true;
			}
		}
		else if (s_cur_test_category == TEST_CATEGORY_MTK_TEST)
		{
			s_cur_group--;
			if (s_cur_group < 0)
			{
				if (s_device_privilege.QC_20_test_on_off == OPTION_ON)
				{
					s_cur_test_category = TEST_CATEGORY_QC_20_TEST;

					s_cur_group = TEST_CATEGORY_QC_20_TEST - 1;
				}
				else
				{
					s_cur_test_category = TEST_CATEGORY_SYNTH_TEST;

					s_cur_group = TEST_CATEGORY_SYNTH_TEST - 1;
				}

				need_refresh_caption = true;
			}
		}
		
		load_group_test_setting(s_cur_test_category, s_cur_group);

		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			if (need_refresh_caption)
			{
				draw_synth_test_setting_caption();
			}
			
			draw_synth_test_setting_menu(&s_synth_test_setting);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			if (need_refresh_caption)
			{
				draw_qc_20_test_setting_caption();
			}
			
			draw_QC_20_test_setting_menu(&s_qc_20_test_setting);
		}
		else if (s_cur_test_category == TEST_CATEGORY_MTK_TEST)
		{

		}

		draw_edit_test_setting_group(s_cur_group + 1);
		
		lcd_validate_cmd();
	}
}

static void edit_item_2_type(uint8_t key)
{
	if (key == KEY_LEFT || key == KEY_DOWN)
	{	
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			s_cur_test_type_index += sizeof(s_synth_test_index_to_type) / sizeof(s_synth_test_index_to_type[0]) - 1;
			s_cur_test_type_index %= sizeof(s_synth_test_index_to_type) / sizeof(s_synth_test_index_to_type[0]);
		
			draw_edit_synth_item_2_type(s_synth_test_index_to_type[s_cur_test_type_index]);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			s_cur_test_type_index += sizeof(s_qc_20_test_index_to_type) / sizeof(s_qc_20_test_index_to_type[0]) - 1;
			s_cur_test_type_index %= sizeof(s_qc_20_test_index_to_type) / sizeof(s_qc_20_test_index_to_type[0]);
		
			draw_edit_qc_20_item_2_type(s_qc_20_test_index_to_type[s_cur_test_type_index]);
		}
		else
		{

		}
	}
	else if (key == KEY_RIGHT || key == KEY_UP)
	{	
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			s_cur_test_type_index++;
			s_cur_test_type_index %= sizeof(s_synth_test_index_to_type) / sizeof(s_synth_test_index_to_type[0]);
			
			draw_edit_synth_item_2_type(s_synth_test_index_to_type[s_cur_test_type_index]);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			s_cur_test_type_index++;
			s_cur_test_type_index %= sizeof(s_qc_20_test_index_to_type) / sizeof(s_qc_20_test_index_to_type[0]);
		
			draw_edit_qc_20_item_2_type(s_qc_20_test_index_to_type[s_cur_test_type_index]);
		}
		else
		{

		}
	}
}

static void edit_item_2_on_off(uint8_t key)
{
	if (key == KEY_LEFT || key == KEY_DOWN)
	{
		s_cur_option_on_off += OPTION_ON_OFF_COUNT - 1;
		s_cur_option_on_off %= OPTION_ON_OFF_COUNT;
		
		draw_edit_test_item_2_on_off(s_cur_option_on_off);
	}
	else if (key == KEY_RIGHT || key == KEY_UP)
	{
		s_cur_option_on_off++;
		s_cur_option_on_off %= OPTION_ON_OFF_COUNT;
		
		draw_edit_test_item_2_on_off(s_cur_option_on_off);
	}
}

static void edit_item_3_type(uint8_t key)
{
	if (key == KEY_LEFT || key == KEY_DOWN)
	{
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			s_cur_test_type_index += sizeof(s_synth_test_index_to_type) / sizeof(s_synth_test_index_to_type[0]) - 1;
			s_cur_test_type_index %= sizeof(s_synth_test_index_to_type) / sizeof(s_synth_test_index_to_type[0]);
			
			draw_edit_synth_item_3_type(s_synth_test_index_to_type[s_cur_test_type_index]);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			s_cur_test_type_index += sizeof(s_qc_20_test_index_to_type) / sizeof(s_qc_20_test_index_to_type[0]) - 1;
			s_cur_test_type_index %= sizeof(s_qc_20_test_index_to_type) / sizeof(s_qc_20_test_index_to_type[0]);
		
			draw_edit_qc_20_item_3_type(s_qc_20_test_index_to_type[s_cur_test_type_index]);
		}
		else
		{

		}
	}
	else if (key == KEY_RIGHT || key == KEY_UP)
	{
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			s_cur_test_type_index++;
			s_cur_test_type_index %= sizeof(s_synth_test_index_to_type) / sizeof(s_synth_test_index_to_type[0]);
			
			draw_edit_synth_item_3_type(s_synth_test_index_to_type[s_cur_test_type_index]);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			s_cur_test_type_index++;
			s_cur_test_type_index %= sizeof(s_qc_20_test_index_to_type) / sizeof(s_qc_20_test_index_to_type[0]);
		
			draw_edit_qc_20_item_3_type(s_qc_20_test_index_to_type[s_cur_test_type_index]);
		}
		else
		{

		}
	}	
}

static void edit_item_3_on_off(uint8_t key)
{
	if (key == KEY_LEFT || key == KEY_DOWN)
	{
		s_cur_option_on_off += OPTION_ON_OFF_COUNT - 1;
		s_cur_option_on_off %= OPTION_ON_OFF_COUNT;
		
		draw_edit_test_item_3_on_off(s_cur_option_on_off);
	}
	else if (key == KEY_RIGHT || key == KEY_UP)
	{
		s_cur_option_on_off++;
		s_cur_option_on_off %= OPTION_ON_OFF_COUNT;
		
		draw_edit_test_item_3_on_off(s_cur_option_on_off);
	}
}

static void edit_item_4_type(uint8_t key)
{
	if (key == KEY_LEFT || key == KEY_DOWN)
	{
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			s_cur_test_type_index += sizeof(s_synth_test_index_to_type) / sizeof(s_synth_test_index_to_type[0]) - 1;
			s_cur_test_type_index %= sizeof(s_synth_test_index_to_type) / sizeof(s_synth_test_index_to_type[0]);
			
			draw_edit_synth_item_4_type(s_synth_test_index_to_type[s_cur_test_type_index]);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			s_cur_test_type_index += sizeof(s_qc_20_test_index_to_type) / sizeof(s_qc_20_test_index_to_type[0]) - 1;
			s_cur_test_type_index %= sizeof(s_qc_20_test_index_to_type) / sizeof(s_qc_20_test_index_to_type[0]);
		
			draw_edit_qc_20_item_4_type(s_qc_20_test_index_to_type[s_cur_test_type_index]);
		}
		else
		{

		}
	}
	else if (key == KEY_RIGHT || key == KEY_UP)
	{
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			s_cur_test_type_index++;
			s_cur_test_type_index %= sizeof(s_synth_test_index_to_type) / sizeof(s_synth_test_index_to_type[0]);
			
			draw_edit_synth_item_4_type(s_synth_test_index_to_type[s_cur_test_type_index]);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			s_cur_test_type_index++;
			s_cur_test_type_index %= sizeof(s_qc_20_test_index_to_type) / sizeof(s_qc_20_test_index_to_type[0]);
		
			draw_edit_qc_20_item_4_type(s_qc_20_test_index_to_type[s_cur_test_type_index]);
		}
		else
		{

		}
	}	
}

static void edit_item_4_on_off(uint8_t key)
{
	if (key == KEY_LEFT || key == KEY_DOWN)
	{
		s_cur_option_on_off += OPTION_ON_OFF_COUNT - 1;
		s_cur_option_on_off %= OPTION_ON_OFF_COUNT;
		
		draw_edit_test_item_4_on_off(s_cur_option_on_off);
	}
	else if (key == KEY_RIGHT || key == KEY_UP)
	{
		s_cur_option_on_off++;
		s_cur_option_on_off %= OPTION_ON_OFF_COUNT;
		
		draw_edit_test_item_4_on_off(s_cur_option_on_off);
	}
}

static void edit_item_5_type(uint8_t key)
{
	if (key == KEY_LEFT || key == KEY_DOWN)
	{
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			s_cur_test_type_index += sizeof(s_synth_test_index_to_type) / sizeof(s_synth_test_index_to_type[0]) - 1;
			s_cur_test_type_index %= sizeof(s_synth_test_index_to_type) / sizeof(s_synth_test_index_to_type[0]);
			
			draw_edit_synth_item_5_type(s_synth_test_index_to_type[s_cur_test_type_index]);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			s_cur_test_type_index += sizeof(s_qc_20_test_index_to_type) / sizeof(s_qc_20_test_index_to_type[0]) - 1;
			s_cur_test_type_index %= sizeof(s_qc_20_test_index_to_type) / sizeof(s_qc_20_test_index_to_type[0]);
		
			draw_edit_qc_20_item_5_type(s_qc_20_test_index_to_type[s_cur_test_type_index]);
		}
	}
	else if (key == KEY_RIGHT || key == KEY_UP)
	{
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			s_cur_test_type_index++;
			s_cur_test_type_index %= sizeof(s_synth_test_index_to_type) / sizeof(s_synth_test_index_to_type[0]);
			
			draw_edit_synth_item_5_type(s_synth_test_index_to_type[s_cur_test_type_index]);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			s_cur_test_type_index++;
			s_cur_test_type_index %= sizeof(s_qc_20_test_index_to_type) / sizeof(s_qc_20_test_index_to_type[0]);
		
			draw_edit_qc_20_item_5_type(s_qc_20_test_index_to_type[s_cur_test_type_index]);
		}
	}	
}

static void edit_item_5_on_off(uint8_t key)
{
	if (key == KEY_LEFT || key == KEY_DOWN)
	{
		s_cur_option_on_off += OPTION_ON_OFF_COUNT - 1;
		s_cur_option_on_off %= OPTION_ON_OFF_COUNT;
		
		draw_edit_test_item_5_on_off(s_cur_option_on_off);
	}
	else if (key == KEY_RIGHT || key == KEY_UP)
	{
		s_cur_option_on_off++;
		s_cur_option_on_off %= OPTION_ON_OFF_COUNT;
		
		draw_edit_test_item_5_on_off(s_cur_option_on_off);
	}
}

static void edit_item_6_type(uint8_t key)
{
	if (key == KEY_LEFT || key == KEY_DOWN)
	{
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			s_cur_test_type_index += sizeof(s_synth_test_index_to_type) / sizeof(s_synth_test_index_to_type[0]) - 1;
			s_cur_test_type_index %= sizeof(s_synth_test_index_to_type) / sizeof(s_synth_test_index_to_type[0]);
			
			draw_edit_synth_item_6_type(s_synth_test_index_to_type[s_cur_test_type_index]);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			s_cur_test_type_index += sizeof(s_qc_20_test_index_to_type) / sizeof(s_qc_20_test_index_to_type[0]) - 1;
			s_cur_test_type_index %= sizeof(s_qc_20_test_index_to_type) / sizeof(s_qc_20_test_index_to_type[0]);
		
			draw_edit_qc_20_item_6_type(s_qc_20_test_index_to_type[s_cur_test_type_index]);
		}
		else
		{

		}
	}
	else if (key == KEY_RIGHT || key == KEY_UP)
	{
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			s_cur_test_type_index++;
			s_cur_test_type_index %= sizeof(s_synth_test_index_to_type) / sizeof(s_synth_test_index_to_type[0]);
			
			draw_edit_synth_item_6_type(s_synth_test_index_to_type[s_cur_test_type_index]);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			s_cur_test_type_index++;
			s_cur_test_type_index %= sizeof(s_qc_20_test_index_to_type) / sizeof(s_qc_20_test_index_to_type[0]);
		
			draw_edit_qc_20_item_6_type(s_qc_20_test_index_to_type[s_cur_test_type_index]);
		}
		else
		{

		}
	}		
}

static void edit_item_6_on_off(uint8_t key)
{
	if (key == KEY_LEFT || key == KEY_DOWN)
	{
		s_cur_option_on_off += OPTION_ON_OFF_COUNT - 1;
		s_cur_option_on_off %= OPTION_ON_OFF_COUNT;
		
		draw_edit_test_item_6_on_off(s_cur_option_on_off);
	}
	else if (key == KEY_RIGHT || key == KEY_UP)
	{
		s_cur_option_on_off++;
		s_cur_option_on_off %= OPTION_ON_OFF_COUNT;
		
		draw_edit_test_item_6_on_off(s_cur_option_on_off);
	}
}

static void edit_item_7_type(uint8_t key)
{
	if (key == KEY_LEFT || key == KEY_DOWN)
	{
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			s_cur_test_type_index += sizeof(s_synth_test_index_to_type) / sizeof(s_synth_test_index_to_type[0]) - 1;
			s_cur_test_type_index %= sizeof(s_synth_test_index_to_type) / sizeof(s_synth_test_index_to_type[0]);
			
			draw_edit_synth_item_7_type(s_synth_test_index_to_type[s_cur_test_type_index]);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			s_cur_test_type_index += sizeof(s_qc_20_test_index_to_type) / sizeof(s_qc_20_test_index_to_type[0]) - 1;
			s_cur_test_type_index %= sizeof(s_qc_20_test_index_to_type) / sizeof(s_qc_20_test_index_to_type[0]);
		
			draw_edit_qc_20_item_7_type(s_qc_20_test_index_to_type[s_cur_test_type_index]);
		}
		else
		{

		}
	}
	else if (key == KEY_RIGHT || key == KEY_UP)
	{
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			s_cur_test_type_index++;
			s_cur_test_type_index %= sizeof(s_synth_test_index_to_type) / sizeof(s_synth_test_index_to_type[0]);
			
			draw_edit_synth_item_7_type(s_synth_test_index_to_type[s_cur_test_type_index]);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			s_cur_test_type_index++;
			s_cur_test_type_index %= sizeof(s_qc_20_test_index_to_type) / sizeof(s_qc_20_test_index_to_type[0]);
		
			draw_edit_qc_20_item_7_type(s_qc_20_test_index_to_type[s_cur_test_type_index]);
		}
		else
		{

		}
	}		
}

static void edit_item_7_on_off(uint8_t key)
{
	if (key == KEY_LEFT || key == KEY_DOWN)
	{
		s_cur_option_on_off += OPTION_ON_OFF_COUNT - 1;
		s_cur_option_on_off %= OPTION_ON_OFF_COUNT;
		
		draw_edit_test_item_7_on_off(s_cur_option_on_off);
	}
	else if (key == KEY_RIGHT || key == KEY_UP)
	{
		s_cur_option_on_off++;
		s_cur_option_on_off %= OPTION_ON_OFF_COUNT;
		
		draw_edit_test_item_7_on_off(s_cur_option_on_off);
	}
}

static void edit_item_8_on_off(uint8_t key)
{
	if (key == KEY_LEFT || key == KEY_DOWN)
	{
		s_cur_option_on_off += OPTION_ON_OFF_COUNT - 1;
		s_cur_option_on_off %= OPTION_ON_OFF_COUNT;
		
		draw_edit_test_item_8_on_off(s_cur_option_on_off);
	}
	else if (key == KEY_RIGHT || key == KEY_UP)
	{
		s_cur_option_on_off++;
		s_cur_option_on_off %= OPTION_ON_OFF_COUNT;
		
		draw_edit_test_item_8_on_off(s_cur_option_on_off);
	}
}

static void (*const s_edit_fun_arr[])(uint8_t key) = 
{
	[EDIT_GROUP]         = edit_group,
	
	[EDIT_ITEM_2_TYPE]   = edit_item_2_type,
	[EDIT_ITEM_2_ON_OFF] = edit_item_2_on_off,

	[EDIT_ITEM_3_TYPE]   = edit_item_3_type,
	[EDIT_ITEM_3_ON_OFF] = edit_item_3_on_off,

	[EDIT_ITEM_4_TYPE]   = edit_item_4_type,
	[EDIT_ITEM_4_ON_OFF] = edit_item_4_on_off,	
	
	[EDIT_ITEM_5_TYPE]   = edit_item_5_type,
	[EDIT_ITEM_5_ON_OFF] = edit_item_5_on_off,

	[EDIT_ITEM_6_TYPE]   = edit_item_6_type,
	[EDIT_ITEM_6_ON_OFF] = edit_item_6_on_off,	
	
	[EDIT_ITEM_7_TYPE]   = edit_item_7_type,
	[EDIT_ITEM_7_ON_OFF] = edit_item_7_on_off,	

	[EDIT_ITEM_8_ON_OFF] = edit_item_8_on_off
};

static focus_item get_next_horz_focus_item(void)
{
	focus_item item;
	
	do
	{
		s_focus_col_index++;
		if (s_focus_col_index == 4)
		{
			s_focus_col_index = 0;

			s_focus_row_index++;
			s_focus_row_index %= sizeof(s_focus_arr) / sizeof(s_focus_arr[0]);
		}

		item = s_focus_arr[s_focus_row_index][s_focus_col_index];
	} while (item == FOCUS_NONE);

	return item;
}

static focus_item get_prev_horz_focus_item(void)
{
	focus_item item;
	
	do
	{
		s_focus_col_index--;
		if (s_focus_col_index == -1)
		{
			s_focus_col_index = 3;

			s_focus_row_index += sizeof(s_focus_arr) / sizeof(s_focus_arr[0]) - 1;
			s_focus_row_index %= sizeof(s_focus_arr) / sizeof(s_focus_arr[0]);
		}

		item = s_focus_arr[s_focus_row_index][s_focus_col_index];
	} while (item == FOCUS_NONE);

	return item;
}

static focus_item get_next_vert_focus_item(void)
{
	focus_item item;
	
	do
	{
		s_focus_row_index++;
		if (s_focus_row_index == sizeof(s_focus_arr) / sizeof(s_focus_arr[0]))
		{
			s_focus_row_index = 0;

			s_focus_col_index++;
			s_focus_col_index %= 4;
		}

		item = s_focus_arr[s_focus_row_index][s_focus_col_index];
	} while (item == FOCUS_NONE);

	return item;
}

static focus_item get_prev_vert_focus_item(void)
{
	focus_item item;
	
	do
	{
		s_focus_row_index--;
		if (s_focus_row_index == -1)
		{
			s_focus_row_index = sizeof(s_focus_arr) / sizeof(s_focus_arr[0]) - 1;

			s_focus_col_index += 3;
			s_focus_col_index %= 4;
		}

		item = s_focus_arr[s_focus_row_index][s_focus_col_index];
	} while (item == FOCUS_NONE);

	return item;
}

static focus_item current_focus_item(void)
{
	return s_focus_arr[s_focus_row_index][s_focus_col_index];
}

static void key_handler(void *msg)
{
	key_t key_msg = (key_t)(uint32_t)msg;
	uint8_t key = KEY_VALUE(key_msg);
	
	if (KEY_TYPE(key_msg) == MASK_KEY_RELEASE 
		|| (s_edit_item == EDIT_GROUP && KEY_TYPE(key_msg) != MASK_KEY_PRESS))
	{
		return;
	}
	
	beeper_beep(BEEPER_VOL_LOW, 50, 50, 1);
	
	if (key == KEY_LEFT)
	{
		if (s_edit_item == EDIT_NONE)
		{
			s_unfocus_fun_arr[current_focus_item()]();
			
			s_focus_fun_arr[get_prev_horz_focus_item()]();
			
			lcd_validate_cmd();
		}
		else
		{
			s_edit_fun_arr[s_edit_item](key);
			
			lcd_validate_cmd();
		}
	}
	else if (key == KEY_UP)
	{
		if (s_edit_item == EDIT_NONE)
		{
			s_unfocus_fun_arr[current_focus_item()]();
			
			s_focus_fun_arr[get_prev_vert_focus_item()]();	
	
			lcd_validate_cmd();
		}
		else
		{
			s_edit_fun_arr[s_edit_item](key);
			
			lcd_validate_cmd();
		}		
	}
	else if (key == KEY_RIGHT)
	{
		if (s_edit_item == EDIT_NONE)
		{
			s_unfocus_fun_arr[current_focus_item()]();
			
			s_focus_fun_arr[get_next_horz_focus_item()]();	

			lcd_validate_cmd();
		}
		else
		{
			s_edit_fun_arr[s_edit_item](key);
			
			lcd_validate_cmd();
		}
	}
	else if (key == KEY_DOWN)
	{
		if (s_edit_item == EDIT_NONE)
		{
			s_unfocus_fun_arr[current_focus_item()]();
				
			s_focus_fun_arr[get_next_vert_focus_item()]();
			
			lcd_validate_cmd();
		}
		else
		{
			s_edit_fun_arr[s_edit_item](key);
			
			lcd_validate_cmd();
		}	
	}
	else if (key == KEY_OK)
	{
		if (s_edit_item == EDIT_NONE)
		{
			s_enter_edit_fun_arr[current_focus_item()]();
			
			lcd_validate_cmd();
		}
		else
		{
			confirm_edit_fun_arr[current_focus_item()]();
			
			lcd_validate_cmd();

			s_edit_item = EDIT_NONE;
		}
	}
	else if (key == KEY_CANCEL)
	{
		if (s_edit_item == EDIT_NONE)
		{
			switch_to_menu(MENU_ID_MAIN);
		}
		else
		{
			s_focus_fun_arr[current_focus_item()]();
			
			lcd_validate_cmd();
			
			s_edit_item = EDIT_NONE;
		}
	}
}

int get_cur_test_setting_step(void)
{
	int step = -1;
	
	focus_item item = current_focus_item();
	
	switch (item)
	{
	case FOCUS_ITEM_1_SETTING:
		step = 1;
	
		break;

	case FOCUS_ITEM_2_SETTING:
		step = 2;
	
		break;

	case FOCUS_ITEM_3_SETTING:
		step = 3;
	
		break;

	case FOCUS_ITEM_4_SETTING:
		step = 4;
	
		break;

	case FOCUS_ITEM_5_SETTING:
		step = 5;
	
		break;

	case FOCUS_ITEM_6_SETTING:
		step = 6;
	
		break;
	
	case FOCUS_ITEM_7_SETTING:
		step = 7;
	
		break;

	case FOCUS_ITEM_8_SETTING:
		step = 8;
	
		break;
		
	default:
		
		break;
	}

	return step;	
}

static void init_callback(void *msg)
{
	MENU_ID id = (MENU_ID)(int)msg;

	int step = get_cur_test_setting_step();

	if (id == MENU_ID_MAIN)
	{
		load_device_privilege(&s_device_privilege);
		
		load_group_test_setting(s_cur_test_category, s_cur_group);

		s_focus_col_index = 0;
		s_focus_row_index = 0;
	}
	else if (id == MENU_ID_EMPTY_LOAD_SETTING)
	{
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			save_synth_test_empty_load_setting(s_cur_group);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			save_qc_20_test_empty_load_setting(s_cur_group);
		}
		else
		{
			save_mtk_test_empty_load_setting(s_cur_group);
		}
	}
	else if (id == MENU_ID_CC_SETTING)
	{
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			save_synth_test_cc_setting(s_cur_group, step);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			save_qc_20_test_cc_setting(s_cur_group, step);
		}
		else
		{
			save_mtk_test_cc_setting(s_cur_group, step);
		}
	}
	else if (id == MENU_ID_CV_SETTING)
	{
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			save_synth_test_cv_setting(s_cur_group, step);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			save_qc_20_test_cv_setting(s_cur_group, step);
		}
		else
		{
			save_mtk_test_cv_setting(s_cur_group, step);
		}
	}
	else if (id == MENU_ID_CR_SETTING)
	{
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{	
			save_synth_test_cr_setting(s_cur_group, step);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			save_qc_20_test_cr_setting(s_cur_group, step);
		}
		else
		{
			save_mtk_test_cr_setting(s_cur_group, step);
		}
	}
	else if (id == MENU_ID_OVER_CURRENT_SETTING)
	{
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			save_synth_test_over_current_setting(s_cur_group, step);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			save_qc_20_test_over_current_setting(s_cur_group, step);
		}
		else
		{
			save_mtk_test_over_current_setting(s_cur_group, step);
		}
	}
	else if (id == MENU_ID_SHORT_SETTING)
	{
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			save_synth_test_short_setting(s_cur_group, step);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			save_qc_20_test_short_setting(s_cur_group, step);
		}
		else
		{
			save_mtk_test_short_setting(s_cur_group, step);
		}
	}
	else if (id == MENU_ID_DISCHARGE_SETTING)
	{
		if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
		{
			save_synth_test_discharge_setting(s_cur_group);
		}
		else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
		{
			save_qc_20_test_discharge_setting(s_cur_group);
		}
		else
		{
			save_mtk_test_discharge_setting(s_cur_group);
		}
	}

	draw_test_setting_menu_const();

	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		draw_synth_test_setting_caption();
		
		draw_synth_test_setting_menu(&s_synth_test_setting);
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		draw_qc_20_test_setting_caption();
		
		draw_QC_20_test_setting_menu(&s_qc_20_test_setting);
	}
	else
	{

	}
	
	/* validate cmd for the first time */
	lcd_validate_cmd();
	
	if (current_focus_item() == FOCUS_NONE)
	{
		get_next_horz_focus_item();
	}
	s_focus_fun_arr[current_focus_item()]();
	
	if (current_focus_item() != FOCUS_GROUP)
	{
		draw_normal_test_setting_group(s_cur_group + 1);
	}
	
	/* validate cmd for the second time */
	lcd_validate_cmd();
}

static void destroy_callback(void *msg)
{
	lcd_clear(SCREEN_BACK_COLOR);
}

const SYNTH_TEST_SETTING * get_synth_test_setting(void)
{
	return &s_synth_test_setting;
}

const QC_20_TEST_SETTING *get_qc_20_test_setting(void)
{
	return &s_qc_20_test_setting;
}

TEST_CATEGORY get_cur_test_category(void)
{
	return s_cur_test_category;
}

SYNTH_TEST_TYPE get_cur_synth_test_type(int step)
{
	if (step <= 1 || step >= SYNTH_TEST_ITEM_COUNT)
	{
		return SYNTH_TEST_NONE;
	}

	return s_synth_test_setting.synth_normal_test_setting[step - 2].test_type;
}

QC_20_TEST_TYPE get_cur_qc_20_test_type(int step)
{
	if (step <= 1 || step >= SYNTH_TEST_ITEM_COUNT)
	{
		return QC_20_TEST_NONE;
	}

	return s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].test_type;
}

int get_test_group(void)
{
	return s_cur_group;
}

/* get empty load test setting */
void get_test_empty_load_setting(EMPTY_LOAD_TEST_SETTING *empty_load_test_setting)
{
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		*empty_load_test_setting = s_synth_test_setting.empty_load_test_setting;
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		*empty_load_test_setting = s_qc_20_test_setting.empty_load_test_setting;
	}
	else
	{

	}
}

/* set empty load test setting */
void set_test_empty_load_setting(const EMPTY_LOAD_TEST_SETTING *empty_load_test_setting)
{
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		s_synth_test_setting.empty_load_test_setting = *empty_load_test_setting;
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		s_qc_20_test_setting.empty_load_test_setting = *empty_load_test_setting;
	}
	else
	{

	}
}

/* get cc test setting */
bool get_test_cc_setting(int step, CC_TEST_SETTING *cc_test_setting)
{	
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		if (step <= 1 || step >= SYNTH_TEST_ITEM_COUNT)
		{
			return false;
		}
		
		*cc_test_setting = s_synth_test_setting.synth_normal_test_setting[step - 2].cc_setting;
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		QC_20_TEST_TYPE test_type;
		
		if (step <= 1 || step >= QC_20_TEST_ITEM_COUNT)
		{
			return false;
		}

		test_type = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].test_type;
		if (test_type == QC_20_5V_TEST_CC)
		{
			*cc_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_cc_setting;
		}
		else if (test_type == QC_20_9V_TEST_CC)
		{
			*cc_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_cc_setting;
		}
		else if (test_type == QC_20_12V_TEST_CC)
		{
			*cc_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_cc_setting;
		}
		else if (test_type == QC_20_20V_TEST_CC)
		{
			*cc_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_cc_setting;
		}
		else
		{
			return false;
		}
	}
	else
	{

	}
	
	return true;
}

/* set cc test setting */
bool set_test_cc_setting(int step, const CC_TEST_SETTING *cc_test_setting)
{
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		if (step <= 1 || step >= SYNTH_TEST_ITEM_COUNT)
		{
			return false;
		}

		s_synth_test_setting.synth_normal_test_setting[step - 2].cc_setting = *cc_test_setting;
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		QC_20_TEST_TYPE test_type;
		
		if (step <= 1 || step >= QC_20_TEST_ITEM_COUNT)
		{
			return false;
		}

		test_type = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].test_type;
		if (test_type == QC_20_5V_TEST_CC)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_cc_setting = *cc_test_setting;
		}
		else if (test_type == QC_20_9V_TEST_CC)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_cc_setting = *cc_test_setting;
		}
		else if (test_type == QC_20_12V_TEST_CC)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_cc_setting = *cc_test_setting;
		}
		else if (test_type == QC_20_20V_TEST_CC)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_cc_setting = *cc_test_setting;
		}
		else
		{
			return false;
		}
	}
	else
	{

	}
	
	return true;
}

/* get cv test setting */
bool get_test_cv_setting(int step, CV_TEST_SETTING *cv_test_setting)
{	
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		if (step <= 1 || step >= SYNTH_TEST_ITEM_COUNT)
		{
			return false;
		}
	
		*cv_test_setting = s_synth_test_setting.synth_normal_test_setting[step - 2].cv_setting;
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		QC_20_TEST_TYPE test_type;
		
		if (step <= 1 || step >= QC_20_TEST_ITEM_COUNT)
		{
			return false;
		}

		test_type = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].test_type;
		if (test_type == QC_20_5V_TEST_CV)
		{
			*cv_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_cv_setting;
		}
		else if (test_type == QC_20_9V_TEST_CV)
		{
			*cv_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_cv_setting;
		}
		else if (test_type == QC_20_12V_TEST_CV)
		{
			*cv_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_cv_setting;
		}
		else if (test_type == QC_20_20V_TEST_CV)
		{
			*cv_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_cv_setting;
		}
		else
		{
			return false;
		}
	}
	
	return true;
}

/* set cv test setting */
bool set_test_cv_setting(int step, const CV_TEST_SETTING *cv_test_setting)
{
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		if (step <= 1 || step >= SYNTH_TEST_ITEM_COUNT)
		{
			return false;
		}

		s_synth_test_setting.synth_normal_test_setting[step - 2].cv_setting = *cv_test_setting;
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		QC_20_TEST_TYPE test_type;
		
		if (step <= 1 || step >= QC_20_TEST_ITEM_COUNT)
		{
			return false;
		}

		test_type = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].test_type;
		if (test_type == QC_20_5V_TEST_CV)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_cv_setting = *cv_test_setting;
		}
		else if (test_type == QC_20_9V_TEST_CV)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_cv_setting = *cv_test_setting;
		}
		else if (test_type == QC_20_12V_TEST_CV)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_cv_setting = *cv_test_setting;
		}
		else if (test_type == QC_20_20V_TEST_CV)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_cv_setting = *cv_test_setting;
		}
		else
		{
			return false;
		}
	}
	else
	{

	}
	
	return true;
}

/* get cr test setting */
bool get_test_cr_setting(int step, CR_TEST_SETTING *cr_test_setting)
{	
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		if (step <= 1 || step >= SYNTH_TEST_ITEM_COUNT)
		{
			return false;
		}
	
		*cr_test_setting = s_synth_test_setting.synth_normal_test_setting[step - 2].cr_setting;
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		QC_20_TEST_TYPE test_type;
		
		if (step <= 1 || step >= QC_20_TEST_ITEM_COUNT)
		{
			return false;
		}

		test_type = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].test_type;
		if (test_type == QC_20_5V_TEST_CR)
		{
			*cr_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_cr_setting;
		}
		else if (test_type == QC_20_9V_TEST_CR)
		{
			*cr_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_cr_setting;
		}
		else if (test_type == QC_20_12V_TEST_CR)
		{
			*cr_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_cr_setting;
		}
		else if (test_type == QC_20_20V_TEST_CR)
		{
			*cr_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_cr_setting;
		}
		else
		{
			return false;
		}
	}
	else
	{

	}
	
	return true;
}

/* set cr test setting */
bool set_test_cr_setting(int step, const CR_TEST_SETTING *cr_test_setting)
{
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		if (step <= 1 || step >= SYNTH_TEST_ITEM_COUNT)
		{
			return false;
		}

		s_synth_test_setting.synth_normal_test_setting[step - 2].cr_setting = *cr_test_setting;
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		QC_20_TEST_TYPE test_type;
		
		if (step <= 1 || step >= QC_20_TEST_ITEM_COUNT)
		{
			return false;
		}

		test_type = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].test_type;
		if (test_type == QC_20_5V_TEST_CR)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_cr_setting = *cr_test_setting;
		}
		else if (test_type == QC_20_9V_TEST_CR)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_cr_setting = *cr_test_setting;
		}
		else if (test_type == QC_20_12V_TEST_CR)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_cr_setting = *cr_test_setting;
		}
		else if (test_type == QC_20_20V_TEST_CR)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_cr_setting = *cr_test_setting;
		}
		else
		{
			return false;
		}
	}
	else
	{

	}
	
	return true;
}

/* get oc test setting */
bool get_test_oc_setting(int step, OVER_CURRENT_TEST_SETTING *oc_test_setting)
{	
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		if (step <= 1 || step >= SYNTH_TEST_ITEM_COUNT)
		{
			return false;
		}
	
		*oc_test_setting = s_synth_test_setting.synth_normal_test_setting[step - 2].over_current_test_setting;
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		QC_20_TEST_TYPE test_type;
		
		if (step <= 1 || step >= QC_20_TEST_ITEM_COUNT)
		{
			return false;
		}

		test_type = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].test_type;
		if (test_type == QC_20_5V_TEST_OVER_CURRENT)
		{
			*oc_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_over_current_test_setting;
		}
		else if (test_type == QC_20_9V_TEST_OVER_CURRENT)
		{
			*oc_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_over_current_test_setting;
		}
		else if (test_type == QC_20_12V_TEST_OVER_CURRENT)
		{
			*oc_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_over_current_test_setting;
		}
		else if (test_type == QC_20_20V_TEST_OVER_CURRENT)
		{
			*oc_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_over_current_test_setting;
		}
		else
		{
			return false;
		}
	}
	else
	{

	}
	
	return true;
}

/* set oc test setting */
bool set_test_oc_setting(int step, const OVER_CURRENT_TEST_SETTING *oc_test_setting)
{
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		if (step <= 1 || step >= SYNTH_TEST_ITEM_COUNT)
		{
			return false;
		}

		s_synth_test_setting.synth_normal_test_setting[step - 2].over_current_test_setting = *oc_test_setting;
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		QC_20_TEST_TYPE test_type;
		
		if (step <= 1 || step >= QC_20_TEST_ITEM_COUNT)
		{
			return false;
		}

		test_type = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].test_type;
		if (test_type == QC_20_5V_TEST_OVER_CURRENT)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_over_current_test_setting = *oc_test_setting;
		}
		else if (test_type == QC_20_9V_TEST_OVER_CURRENT)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_over_current_test_setting = *oc_test_setting;
		}
		else if (test_type == QC_20_12V_TEST_OVER_CURRENT)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_over_current_test_setting = *oc_test_setting;
		}
		else if (test_type == QC_20_20V_TEST_OVER_CURRENT)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_over_current_test_setting = *oc_test_setting;
		}
		else
		{
			return false;
		}
	}
	else
	{

	}
	
	return true;
}

/* get short test setting */
bool get_test_short_setting(int step, SHORT_TEST_SETTING *short_test_setting)
{	
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		if (step <= 1 || step >= SYNTH_TEST_ITEM_COUNT)
		{
			return false;
		}
	
		*short_test_setting = s_synth_test_setting.synth_normal_test_setting[step - 2].short_test_setting;
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		QC_20_TEST_TYPE test_type;
		
		if (step <= 1 || step >= QC_20_TEST_ITEM_COUNT)
		{
			return false;
		}

		test_type = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].test_type;
		if (test_type == QC_20_5V_TEST_SHORT)
		{
			*short_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_short_test_setting;
		}
		else if (test_type == QC_20_9V_TEST_SHORT)
		{
			*short_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_short_test_setting;
		}
		else if (test_type == QC_20_12V_TEST_SHORT)
		{
			*short_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_short_test_setting;
		}
		else if (test_type == QC_20_20V_TEST_SHORT)
		{
			*short_test_setting = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_short_test_setting;
		}
		else
		{
			return false;
		}
	}
	else
	{

	}
	
	return true;
}

/* set short test setting */
bool set_test_short_setting(int step, const SHORT_TEST_SETTING *short_test_setting)
{
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		if (step <= 1 || step >= SYNTH_TEST_ITEM_COUNT)
		{
			return false;
		}

		s_synth_test_setting.synth_normal_test_setting[step - 2].short_test_setting = *short_test_setting;
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		QC_20_TEST_TYPE test_type;
		
		if (step <= 1 || step >= QC_20_TEST_ITEM_COUNT)
		{
			return false;
		}

		test_type = s_qc_20_test_setting.qc_20_normal_test_setting[step - 2].test_type;
		if (test_type == QC_20_5V_TEST_SHORT)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._5v_short_test_setting = *short_test_setting;
		}
		else if (test_type == QC_20_9V_TEST_SHORT)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._9v_short_test_setting = *short_test_setting;
		}
		else if (test_type == QC_20_12V_TEST_SHORT)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._12v_short_test_setting = *short_test_setting;
		}
		else if (test_type == QC_20_20V_TEST_SHORT)
		{
			s_qc_20_test_setting.qc_20_normal_test_setting[step - 2]._20v_short_test_setting = *short_test_setting;
		}
		else
		{
			return false;
		}
	}
	else
	{

	}
	
	return true;
}

/* get discharge test setting */
void get_test_discharge_setting(DISCHARGE_TEST_SETTING *discharge_test_setting)
{
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{	
		*discharge_test_setting = s_synth_test_setting.discharge_test_setting;
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		*discharge_test_setting = s_qc_20_test_setting.discharge_test_setting;
	}
	else
	{

	}
}

/* set discharge test setting */
void set_test_discharge_setting(const DISCHARGE_TEST_SETTING *discharge_test_setting)
{
	if (s_cur_test_category == TEST_CATEGORY_SYNTH_TEST)
	{
		s_synth_test_setting.discharge_test_setting = *discharge_test_setting;
	}
	else if (s_cur_test_category == TEST_CATEGORY_QC_20_TEST)
	{
		s_qc_20_test_setting.discharge_test_setting = *discharge_test_setting;
	}
	else
	{

	}
}

BEGIN_MENU_HANDLER(MENU_ID_SYNTH_TEST_SETTING)

IMPLEMENT_MSG_HANDLER(MSG_ID_KEY, key_handler)
IMPLEMENT_MSG_HANDLER(MSG_ID_INIT, init_callback)
IMPLEMENT_MSG_HANDLER(MSG_ID_DESTROY, destroy_callback)

END_MENU_HANDLER()

