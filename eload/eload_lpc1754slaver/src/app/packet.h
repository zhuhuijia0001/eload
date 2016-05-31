#ifndef _PACKET_H_
#define _PACKET_H_

#include "protocol.h"

/* packet result */
#define PACKET_TOO_LONG   ((uint16_t)-1)

/* packet struct */
typedef struct __attribute__((packed))
{
	uint16_t    header;
	
	uint8_t     sum;
	
	uint16_t    payload_size;
	
	uint8_t     payload[1];
} PACKET;

/* payload */
/* cv test */
typedef struct __attribute__((packed))
{
	uint8_t    cmd;

	uint8_t    test_category;
	
	uint8_t    voltage_level;
	
	uint32_t   voltage_val;
	
	uint32_t   duration;
	
	uint32_t   ac_upper;

	uint32_t   current_lower;

	uint32_t   current_upper;
} PAYLOAD_CMD_CV_TEST;

/* cc test */
typedef struct __attribute__((packed))
{
	uint8_t    cmd;

	uint8_t    test_category;
	
	uint8_t    voltage_level;
	
	uint32_t   current_val;
	
	uint32_t   duration;
	
	uint32_t   ac_upper;

	uint32_t   voltage_lower;

	uint32_t   voltage_upper;
} PAYLOAD_CMD_CC_TEST;

/* cr test */
typedef struct __attribute__((packed))
{
	uint8_t    cmd;

	uint8_t    test_category;
	
	uint8_t    voltage_level;
	
	uint32_t   resist_val;
	
	uint32_t   duration;
	
	uint32_t   ac_upper;

	uint32_t   current_lower;

	uint32_t   current_upper;
	
	uint32_t   voltage_lower;

	uint32_t   voltage_upper;
} PAYLOAD_CMD_CR_TEST;

/* empty load test */
typedef struct __attribute__((packed))
{
	uint8_t    cmd;
	
	uint32_t   duration;
	
	uint32_t   ac_upper;

	uint32_t   voltage_lower;

	uint32_t   voltage_upper;
} PAYLOAD_CMD_EMPTY_LOAD_TEST;

/* over current test */
typedef struct __attribute__((packed))
{
	uint8_t    cmd;

	uint8_t    test_category;
	
	uint8_t    voltage_level;
	
	uint32_t   interval;
	
	uint32_t   ac_upper;

	uint32_t   current_upper;
} PAYLOAD_CMD_OVER_CURRENT_TEST;

/* short test */
typedef struct __attribute__((packed))
{
	uint8_t    cmd;

	uint8_t    test_category;
	
	uint8_t    voltage_level;
	
	uint32_t   duration;
	
	uint32_t   ac_upper;

	uint32_t   current_upper;
} PAYLOAD_CMD_SHORT_TEST;

/* discharge test */
typedef struct __attribute__((packed))
{
	uint8_t    cmd;

	uint32_t   duration;

	uint32_t   current_val;

} PAYLOAD_CMD_DISCHARGE_TEST;

/* cv mode */
typedef struct __attribute__((packed))
{
	uint8_t   cmd;

	uint32_t  voltage_val;
} PAYLOAD_CMD_CV_MODE;

/* cc mode */
typedef struct __attribute__((packed))
{
	uint8_t   cmd;

	uint32_t  current_val;
} PAYLOAD_CMD_CC_MODE;

/* cr mode */
typedef struct __attribute__((packed))
{
	uint8_t   cmd;

	uint32_t  resist_val;
} PAYLOAD_CMD_CR_MODE;

/* cmd return */
typedef struct __attribute__((packed))
{
	uint8_t    cmd;
	
	uint8_t    result;
} PAYLOAD_CMD_RET;

/* poll cmd packet */
typedef struct __attribute__((packed))
{
	uint8_t   cmd;
	
	uint8_t   padding;
} PAYLOAD_CMD_POLL;

/* poll cmd return packet */
typedef struct __attribute__((packed))
{
	uint8_t   cmd;
	
	uint8_t   test_type;

	uint8_t   test_status;
	
	uint32_t  ac;
	
	uint32_t  voltage;
	
	uint32_t  current;
} PAYLOAD_CMD_POLL_RET;

/* stop cmd packet */
typedef PAYLOAD_CMD_POLL  PAYLOAD_CMD_STOP;

/* stop cmd return packet */
typedef struct __attribute__((packed))
{
	uint8_t   cmd;
	
	uint8_t   test_type;
} PAYLOAD_CMD_STOP_RET;

/* set adjust value cmd packet */
typedef struct __attribute__((packed))
{
	uint8_t   cmd;

	uint32_t  measure_voltage;

	uint32_t  actual_voltage;

	uint32_t  measure_current;

	uint32_t  actual_current;
} PAYLOAD_CMD_SET_ADJUST_VALUE;

typedef struct __attribute__((packed))
{
	uint8_t   cmd;

	uint8_t   padding;
} PAYLOAD_CMD_SET_ADJUST_VALUE_RET;

/* get adjust value cmd packet */
typedef PAYLOAD_CMD_SET_ADJUST_VALUE_RET PAYLOAD_CMD_GET_ADJUST_VALUE;

typedef PAYLOAD_CMD_SET_ADJUST_VALUE PAYLOAD_CMD_GET_ADJUST_VALUE_RET;

extern uint16_t build_cv_test_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result);

extern uint16_t build_cc_test_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result);

extern uint16_t build_cr_test_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result);

extern uint16_t build_empty_load_test_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result);

extern uint16_t build_over_current_test_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result);

extern uint16_t build_short_test_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result);

extern uint16_t build_discharge_test_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result);

extern uint16_t build_cv_mode_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result);

extern uint16_t build_cc_mode_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result);

extern uint16_t build_cr_mode_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result);

extern uint16_t build_poll_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t test_type, uint8_t test_status,
											uint32_t ac, uint32_t voltage, uint32_t current);

extern uint16_t build_stop_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t test_type);

extern uint16_t build_set_adjust_value_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result);

extern uint16_t build_get_adjust_value_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint32_t measure_voltage, uint32_t actual_voltage,
													uint32_t measure_current, uint32_t actual_current);
#endif

