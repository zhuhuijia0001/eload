#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "packet.h"

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
} TEST_CONFIG;
	
typedef struct 
{
	uint8_t test_type;

	TEST_CONFIG test_config;
} TEST_CMD;

typedef struct
{
	uint8_t  test_type;

	uint8_t  test_status;
	
	uint32_t ac_current;
	
	uint32_t voltage;
	
	uint32_t current;
} TEST_CONTENT;

typedef struct
{
	uint32_t over_current_test_current;

	uint32_t over_current_test_voltage;

	uint32_t over_current_test_ac;
} OVER_CURRENT_TEST_RESULT;

extern TEST_CONTENT  g_test_content;

extern OVER_CURRENT_TEST_RESULT g_over_current_test_result;

extern rt_sem_t  g_sem_test_content;

extern rt_mq_t   g_test_cmd_queue;

extern void global_variable_init(void);

#endif

