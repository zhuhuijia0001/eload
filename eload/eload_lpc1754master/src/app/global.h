#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "slave_port_define.h"

typedef struct
{
	uint32_t  voltage_val;
} CV_MODE_CONFIG;

typedef struct
{
	uint32_t  current_val;
} CC_MODE_CONFIG;

typedef struct
{
	uint32_t  resist_val;
} CR_MODE_CONFIG;

typedef struct
{
	uint8_t    test_category;
	
	uint8_t    voltage_level;
	
	uint32_t   voltage_val;
	
	uint32_t   duration;
	
	uint32_t   ac_upper;

	uint32_t   current_lower;

	uint32_t   current_upper;
} CV_TEST_CONFIG;

typedef struct
{
	uint8_t    test_category;
	
	uint8_t    voltage_level;
	
	uint32_t   current_val;
	
	uint32_t   duration;
	
	uint32_t   ac_upper;

	uint32_t   voltage_lower;

	uint32_t   voltage_upper;
} CC_TEST_CONFIG;

typedef struct
{
	uint8_t    test_category;
	
	uint8_t    voltage_level;
	
	uint32_t   resist_val;
	
	uint32_t   duration;
	
	uint32_t   ac_upper;

	uint32_t   current_lower;

	uint32_t   current_upper;
	
	uint32_t   voltage_lower;

	uint32_t   voltage_upper;
} CR_TEST_CONFIG;

typedef struct
{
	uint32_t   duration;
	
	uint32_t   ac_upper;

	uint32_t   voltage_lower;

	uint32_t   voltage_upper;
} EMPTY_LOAD_TEST_CONFIG;

typedef struct
{
	uint8_t    test_category;
	
	uint8_t    voltage_level;
	
	uint32_t   interval;
	
	uint32_t   ac_upper;

	uint32_t   current_upper;
} OVER_CURRENT_TEST_CONFIG;

typedef struct
{
	uint8_t    test_category;
	
	uint8_t    voltage_level;
	
	uint32_t   duration;
	
	uint32_t   ac_upper;

	uint32_t   current_upper;
} SHORT_TEST_CONFIG;

typedef struct
{
	uint32_t  duration;

	uint32_t  current_val;
} DISCHARGE_TEST_CONFIG;

typedef struct 
{
	uint32_t  measure_voltage;

	uint32_t  actual_voltage;

	uint32_t  measure_current;

	uint32_t  actual_current;
} ADJUST_VALUE_CONFIG;

typedef union
{
	CV_MODE_CONFIG  cv_mode_config;

	CC_MODE_CONFIG  cc_mode_config;

	CR_MODE_CONFIG  cr_mode_config;

	CV_TEST_CONFIG  cv_test_config;

	CC_TEST_CONFIG  cc_test_config;

	CR_TEST_CONFIG  cr_test_config;

	EMPTY_LOAD_TEST_CONFIG empty_load_test_config;

	OVER_CURRENT_TEST_CONFIG over_current_test_config;

	SHORT_TEST_CONFIG short_test_config;

	DISCHARGE_TEST_CONFIG discharge_test_config;

	ADJUST_VALUE_CONFIG adjust_value_config;
} TEST_CONFIG;

typedef struct 
{
	slave_com_port  channel;
	
	uint8_t test_type;

	TEST_CONFIG test_config;
} TEST_CMD;

/* channel status */
typedef enum
{
	CHANNEL_ONLINE = 0,

	CHANNEL_OFFLINE
} CHANNEL_STATUS;


/* test content */
typedef struct
{
	slave_com_port  channel;
	
	uint8_t  test_type;

	uint8_t  test_status;
	
	uint32_t ac_current;
	
	uint32_t voltage;
	
	uint32_t current;
} TEST_CONTENT;

typedef enum
{
	TEST_STEP_EMPTY_LOAD = 0,

	TEST_STEP_2,

	TEST_STEP_3,

	TEST_STEP_4,

	TEST_STEP_5,

	TEST_STEP_6,

	TEST_STEP_7,

	TEST_STEP_DISCHARGE,

	TEST_STEP_NONE
} TEST_STEP;

typedef struct
{
	TEST_STEP  test_step;

	TEST_CONTENT  test_content;
} TEST_RESULT;

typedef struct
{
	uint32_t  measure_voltage;

	uint32_t  actual_voltage;

	uint32_t  measure_current;

	uint32_t  actual_current;
} ADJUST_VALUE;

extern CHANNEL_STATUS  g_channel_status[CHANNEL_COUNT];

extern uint32_t g_channel_voltage[CHANNEL_COUNT];

extern ADJUST_VALUE g_channel_adjust_value[CHANNEL_COUNT];

extern void global_variable_init(void);

extern void test_cmd_notify(TEST_CMD *test_cmd);

extern int test_cmd_query(TEST_CMD *test_cmd, int timeout);

extern void test_content_notify(TEST_CONTENT *test_content);

extern int test_content_query(TEST_CONTENT *test_content, int timeout);

extern uint32_t measure_to_actual_voltage(int port, uint32_t measure_voltage);

extern uint32_t actual_to_measure_voltage(int port, uint32_t actual_voltage);

extern uint32_t measure_to_actual_current(int port, uint32_t measure_current);

extern uint32_t actual_to_measure_current(int port, uint32_t actual_current);

#endif

