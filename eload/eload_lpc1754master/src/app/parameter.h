#ifndef _PARAMETER_H_
#define _PARAMETER_H_

/*channel count */
#define CHANNEL_COUNT        8

/* synth test group count */
#define SYNTH_TEST_GROUP_COUNT  20

/* synth test item count */
#define SYNTH_TEST_ITEM_COUNT   8

/* QC2.0 test group count */
#define QC_20_TEST_GROUP_COUNT  20

/* QC2.0 test item count */
#define QC_20_TEST_ITEM_COUNT   8

/* MTK test group count */
#define MTK_TEST_GROUP_COUNT  20

/* MTK test item count */
#define MTK_TEST_ITEM_COUNT   8

/* test category */
typedef enum
{
	TEST_CATEGORY_SYNTH_TEST = 0,

	TEST_CATEGORY_QC_20_TEST,

	TEST_CATEGORY_MTK_TEST,

	TEST_CATEGORY_COUNT
} TEST_CATEGORY;

typedef enum
{
	SYNTH_TEST_EMPTY_LOAD = 0,
	
	SYNTH_TEST_CV,
	
	SYNTH_TEST_CC,
	
	SYNTH_TEST_CR,
	
	SYNTH_TEST_OVER_CURRENT,
	
	SYNTH_TEST_SHORT,
	
	SYNTH_TEST_DISCHARGE,

	SYNTH_TEST_NONE,
	
	SYNTH_TEST_TYPE_COUNT = SYNTH_TEST_NONE
} SYNTH_TEST_TYPE;

typedef enum
{
	QC_20_TEST_EMPTY_LOAD = 0,
	
	QC_20_5V_TEST_CV,
	
	QC_20_5V_TEST_CC,
	
	QC_20_5V_TEST_CR,

	QC_20_5V_TEST_OVER_CURRENT,

	QC_20_5V_TEST_SHORT,

	QC_20_9V_TEST_CV,
	
	QC_20_9V_TEST_CC,
	
	QC_20_9V_TEST_CR,

	QC_20_9V_TEST_OVER_CURRENT,

	QC_20_9V_TEST_SHORT,
	
	QC_20_12V_TEST_CV,
	
	QC_20_12V_TEST_CC,
	
	QC_20_12V_TEST_CR,

	QC_20_12V_TEST_OVER_CURRENT,

	QC_20_12V_TEST_SHORT,
	
	QC_20_20V_TEST_CV,
	
	QC_20_20V_TEST_CC,
	
	QC_20_20V_TEST_CR,

	QC_20_20V_TEST_OVER_CURRENT,

	QC_20_20V_TEST_SHORT,

	QC_20_TEST_DISCHARGE,

	QC_20_TEST_NONE,

	QC_20_TEST_TYPE_COUNT = QC_20_TEST_NONE
} QC_20_TEST_TYPE;

typedef enum
{
	MTK_TEST_EMPTY_LOAD = 0,
	
	MTK_5V_TEST_CV,
	
	MTK_5V_TEST_CC,
	
	MTK_5V_TEST_CR,

	MTK_5V_TEST_OVER_CURRENT,

	MTK_5V_TEST_SHORT,

	MTK_9V_TEST_CV,
	
	MTK_9V_TEST_CC,
	
	MTK_9V_TEST_CR,

	MTK_9V_TEST_OVER_CURRENT,

	MTK_9V_TEST_SHORT,
	
	MTK_12V_TEST_CV,
	
	MTK_12V_TEST_CC,
	
	MTK_12V_TEST_CR,

	MTK_12V_TEST_OVER_CURRENT,

	MTK_12V_TEST_SHORT,
	
	MTK_20V_TEST_CV,
	
	MTK_20V_TEST_CC,
	
	MTK_20V_TEST_CR,

	MTK_20V_TEST_OVER_CURRENT,

	MTK_20V_TEST_SHORT,

	MTK_TEST_DISCHARGE,

	MTK_TEST_NONE,

	MTK_TEST_TYPE_COUNT = MTK_TEST_NONE
} MTK_TEST_TYPE;

typedef enum
{
	OPTION_ON,
	
	OPTION_OFF,
	
	OPTION_ON_OFF_COUNT
} OPTION_ON_OFF;

typedef enum
{
	VOLTAGE_DIVIDE_MODE = 0,
	
	SHORT_MODE,
	
	SHORT_RESIST_MODE,

	DP_DN_MODE_COUNT
} USB_DP_DN_MODE;

typedef struct
{
	uint32_t dp_voltage_from;
	
	uint32_t dp_voltage_to;
	
	uint32_t dn_voltage_from;
	
	uint32_t dn_voltage_to;
} __attribute__ ((packed)) DIVIDE_MODE_SETTING;

typedef struct
{
	uint32_t short_resist;
} __attribute__ ((packed)) SHORT_MODE_SETTING;

typedef struct
{
	uint32_t short_resist;
	
	uint32_t dp_resist;
	
	uint32_t dn_resist;
} __attribute__ ((packed)) SHORT_RESIST_MODE_SETTING;

/* USB D+/D- setting */
typedef struct
{
	USB_DP_DN_MODE  mode;
	
	OPTION_ON_OFF   on_off;
	
	DIVIDE_MODE_SETTING divide_mode_setting;
	
	SHORT_MODE_SETTING short_mode_setting;
	
	SHORT_RESIST_MODE_SETTING short_resist_mode_setting;
} __attribute__ ((packed)) DP_DN_SETTING;

/* empty load test setting */
typedef struct
{
	uint32_t   duration;
	
	uint32_t   ac_limit;

	uint32_t   voltage_from;
	
	uint32_t   voltage_to;	
	
	DP_DN_SETTING  dp_dn_setting;
} __attribute__ ((packed)) EMPTY_LOAD_TEST_SETTING;

/* cc test setting */
typedef struct
{
	uint32_t   duration;
	
	uint32_t   ac_limit;
	
	uint32_t   cc_val;
	
	uint32_t   voltage_from;
	
	uint32_t   voltage_to;
} __attribute__ ((packed)) CC_TEST_SETTING;

/* cv test setting */
typedef struct
{
	uint32_t   duration;
	
	uint32_t   ac_limit;
	
	uint32_t   cv_val;
	
	uint32_t   current_from;
	
	uint32_t   current_to;	
} __attribute__ ((packed)) CV_TEST_SETTING;

/* cr test setting */
typedef struct
{
	uint32_t   duration;
	
	uint32_t   ac_limit;
	
	uint32_t   cr_val;
	
	uint32_t   current_from;
	
	uint32_t   current_to;	
	
	uint32_t   voltage_from;
	
	uint32_t   voltage_to;
} __attribute__ ((packed)) CR_TEST_SETTING;

/* over current test setting */
typedef struct
{
	uint32_t   interval;
	
	uint32_t   ac_limit;

	uint32_t   current_limit;
} __attribute__ ((packed)) OVER_CURRENT_TEST_SETTING;

/* short test setting */
typedef struct
{
	uint32_t   duration;
	
	uint32_t   ac_limit;

	uint32_t   short_limit;
} __attribute__ ((packed)) SHORT_TEST_SETTING;

/* discharge setting */
typedef struct
{
	OPTION_ON_OFF   on_off;
	
	uint32_t   discharge_current;
	
	uint32_t   discharge_duration;
	
	uint32_t   indicate_delay;
} __attribute__ ((packed)) DISCHARGE_TEST_SETTING;

/* synth test setting */
typedef struct
{
	SYNTH_TEST_TYPE  test_type;
	
	OPTION_ON_OFF    on_off;
	
	CV_TEST_SETTING  cv_setting;

	CC_TEST_SETTING  cc_setting;
			
	CR_TEST_SETTING  cr_setting;
			
	OVER_CURRENT_TEST_SETTING over_current_test_setting;
			
	SHORT_TEST_SETTING    short_test_setting;
} __attribute__ ((packed)) SYNTH_NORMAL_TEST_SETTING;

/* synth test setting */
typedef struct
{
	EMPTY_LOAD_TEST_SETTING  empty_load_test_setting;
	
	SYNTH_NORMAL_TEST_SETTING  synth_normal_test_setting[SYNTH_TEST_ITEM_COUNT - 2];
	
	DISCHARGE_TEST_SETTING   discharge_test_setting;
} __attribute__ ((packed)) SYNTH_TEST_SETTING;


/* QC2.0 normal test setting */
typedef struct
{
	QC_20_TEST_TYPE  test_type;
	
	OPTION_ON_OFF    on_off;

	/* 5V */
	CV_TEST_SETTING  _5v_cv_setting;

	CC_TEST_SETTING  _5v_cc_setting;
			
	CR_TEST_SETTING  _5v_cr_setting;

	OVER_CURRENT_TEST_SETTING _5v_over_current_test_setting;
			
	SHORT_TEST_SETTING    _5v_short_test_setting;

	/* 9V */
	CV_TEST_SETTING  _9v_cv_setting;

	CC_TEST_SETTING  _9v_cc_setting;
			
	CR_TEST_SETTING  _9v_cr_setting;

	OVER_CURRENT_TEST_SETTING _9v_over_current_test_setting;
			
	SHORT_TEST_SETTING    _9v_short_test_setting;

	/* 12V */
	CV_TEST_SETTING  _12v_cv_setting;

	CC_TEST_SETTING  _12v_cc_setting;
			
	CR_TEST_SETTING  _12v_cr_setting;

	OVER_CURRENT_TEST_SETTING _12v_over_current_test_setting;
			
	SHORT_TEST_SETTING    _12v_short_test_setting;

	/* 20V */
	CV_TEST_SETTING  _20v_cv_setting;

	CC_TEST_SETTING  _20v_cc_setting;
			
	CR_TEST_SETTING  _20v_cr_setting;

	OVER_CURRENT_TEST_SETTING _20v_over_current_test_setting;
			
	SHORT_TEST_SETTING    _20v_short_test_setting;
} __attribute__ ((packed)) QC_20_NORMAL_TEST_SETTING;

/* QC2.0 test setting */
typedef struct
{
	EMPTY_LOAD_TEST_SETTING  empty_load_test_setting;

	QC_20_NORMAL_TEST_SETTING qc_20_normal_test_setting[QC_20_TEST_ITEM_COUNT - 2];
	
	DISCHARGE_TEST_SETTING   discharge_test_setting;
} __attribute__ ((packed)) QC_20_TEST_SETTING;

/* MTK normal test setting */
typedef struct
{
	MTK_TEST_TYPE  test_type;
	
	OPTION_ON_OFF    on_off;

	/* 5V */
	CV_TEST_SETTING  _5v_cv_setting;

	CC_TEST_SETTING  _5v_cc_setting;
			
	CR_TEST_SETTING  _5v_cr_setting;

	OVER_CURRENT_TEST_SETTING _5v_over_current_test_setting;
			
	SHORT_TEST_SETTING    _5v_short_test_setting;

	/* 9V */
	CV_TEST_SETTING  _9v_cv_setting;

	CC_TEST_SETTING  _9v_cc_setting;
			
	CR_TEST_SETTING  _9v_cr_setting;

	OVER_CURRENT_TEST_SETTING _9v_over_current_test_setting;
			
	SHORT_TEST_SETTING    _9v_short_test_setting;

	/* 12V */
	CV_TEST_SETTING  _12v_cv_setting;

	CC_TEST_SETTING  _12v_cc_setting;
			
	CR_TEST_SETTING  _12v_cr_setting;

	OVER_CURRENT_TEST_SETTING _12v_over_current_test_setting;
			
	SHORT_TEST_SETTING    _12v_short_test_setting;

	/* 20V */
	CV_TEST_SETTING  _20v_cv_setting;

	CC_TEST_SETTING  _20v_cc_setting;
			
	CR_TEST_SETTING  _20v_cr_setting;

	OVER_CURRENT_TEST_SETTING _20v_over_current_test_setting;
			
	SHORT_TEST_SETTING    _20v_short_test_setting;
} __attribute__ ((packed)) MTK_NORMAL_TEST_SETTING;

/* QC2.0 test setting */
typedef struct
{
	EMPTY_LOAD_TEST_SETTING  empty_load_test_setting;

	MTK_NORMAL_TEST_SETTING mtk_normal_test_setting[MTK_TEST_ITEM_COUNT - 2];
	
	DISCHARGE_TEST_SETTING   discharge_test_setting;
} __attribute__ ((packed)) MTK_TEST_SETTING;

typedef struct
{
	uint32_t   actual_voltage;
	
	uint32_t   actual_current;
} __attribute__ ((packed)) ADJUST_SETTING;

typedef struct
{
	OPTION_ON_OFF   QC_20_test_on_off;
	
	OPTION_ON_OFF   MTK_test_on_off;
} __attribute__ ((packed)) DEVICE_PRIVILEGE;


typedef struct
{
	uint16_t      power_on_limit;
	uint16_t      power_on_count;		
} __attribute__ ((packed)) LIFE_LIMIT;

/* phone number */ 
#define  PHONE_NUMBER_LEN    11

typedef struct 
{
	char phone_number[PHONE_NUMBER_LEN];
} __attribute__ ((packed)) PHONE_NUMBER;

typedef struct
{
	PHONE_NUMBER  default_phone_number;
	PHONE_NUMBER  customer_phone_number;
	uint16_t      customer_phone_number_power_on_limit;
	uint16_t      customer_phone_number_power_on_count;	
} __attribute__ ((packed)) PHONE_NUMBER_SETTING;

#define  PARAM_FILE_HEADER     0xDEADBEEF

typedef struct
{
	uint32_t   cv_mode_voltage_set;  /* mV */
	uint32_t   cc_mode_current_set;  /* mA */
	uint32_t   cr_mode_resist_set;   /* mO */

	uint32_t   synth_test_group;
	SYNTH_TEST_SETTING  synth_test_setting[SYNTH_TEST_GROUP_COUNT];

	uint32_t   qc_20_test_group;
	QC_20_TEST_SETTING qc_20_test_setting[QC_20_TEST_GROUP_COUNT];

	uint32_t   mtk_test_group;
	MTK_TEST_SETTING mtk_test_setting[MTK_TEST_GROUP_COUNT];
	
	OPTION_ON_OFF  channel_set[CHANNEL_COUNT];
	
	ADJUST_SETTING  adjust_setting[CHANNEL_COUNT];

	DEVICE_PRIVILEGE device_privilege;
	
	LIFE_LIMIT    life_limit;
	
	PHONE_NUMBER_SETTING phone_number_setting;
} __attribute__ ((packed)) PARAMETER;

typedef struct 
{
	uint32_t    header;
	uint32_t    size;

	PARAMETER   param;
} __attribute__ ((packed)) PARAMETER_FILE_STRUCT;

#define  STRUCT_OFFSET(type, member)    ((int)(int *)&(((type *)0)->member))


extern bool parameter_file_exist(void);

extern bool save_default_parameters(void);

extern bool load_parameter(int offset, void *buffer, int len);
extern bool save_parameter(int offset, const void *buffer, int len);

#endif

