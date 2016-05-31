
#include <stdint.h>

#include "packet.h"

static uint16_t build_packet(uint8_t *buffer, uint16_t buffer_len, const uint8_t *payload, uint16_t payload_size)
{
	PACKET *packet;
	
	uint8_t sum;
	
	uint16_t i;
	
	if (sizeof(PACKET) - 1 + payload_size > buffer_len)
	{
		/* payload too large */
		return PACKET_TOO_LONG;
	}
	
	packet = (PACKET *)buffer;
	packet->header       = PACKET_HEADER;
	packet->payload_size = payload_size;
	
	sum = 0;
	for (i = 0; i < payload_size; i++)
	{
		packet->payload[i] = payload[i];
		
		sum ^= payload[i];
	}
	
	packet->sum = sum;
	
	return sizeof(PACKET) - 1 + payload_size;
}

uint16_t build_cv_mode_cmd_packet(uint8_t *buffer, uint16_t buffer_len, uint32_t voltage_val)
{
	PAYLOAD_CMD_CV_MODE payload;
	payload.cmd         = CMD_CV_MODE;
	payload.voltage_val = voltage_val;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

uint16_t build_cc_mode_cmd_packet(uint8_t *buffer, uint16_t buffer_len, uint32_t current_val)
{
	PAYLOAD_CMD_CC_MODE payload;
	payload.cmd         = CMD_CC_MODE;
	payload.current_val = current_val;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

uint16_t build_cr_mode_cmd_packet(uint8_t *buffer, uint16_t buffer_len, uint32_t resist_val)
{
	PAYLOAD_CMD_CR_MODE payload;
	payload.cmd         = CMD_CR_MODE;
	payload.resist_val = resist_val;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

uint16_t build_cv_test_cmd_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t test_category, uint8_t voltage_level, uint32_t voltage_val, uint32_t test_duration,
														uint32_t ac_upper, uint32_t current_lower, uint32_t current_upper)
{
	PAYLOAD_CMD_CV_TEST payload;
	payload.cmd         = CMD_CV_TEST;
	payload.test_category = test_category;
	payload.voltage_level = voltage_level;
	payload.voltage_val = voltage_val;
	payload.duration    = test_duration;
	payload.ac_upper    = ac_upper;
	payload.current_lower = current_lower;
	payload.current_upper = current_upper;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

uint16_t build_cc_test_cmd_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t test_category, uint8_t voltage_level, uint32_t current_val, uint32_t test_duration,
														uint32_t ac_upper, uint32_t voltage_lower, uint32_t voltage_upper)
{
	PAYLOAD_CMD_CC_TEST payload;
	payload.cmd         = CMD_CC_TEST;
	payload.test_category = test_category;
	payload.voltage_level = voltage_level;
	payload.current_val = current_val;
	payload.duration    = test_duration;
	payload.ac_upper    = ac_upper;
	payload.voltage_lower = voltage_lower;
	payload.voltage_upper = voltage_upper;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

uint16_t build_cr_test_cmd_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t test_category, uint8_t voltage_level, uint32_t resist_val, uint32_t test_duration,
														uint32_t ac_upper, uint32_t voltage_lower, uint32_t voltage_upper,
														uint32_t current_lower, uint32_t current_upper)
{
	PAYLOAD_CMD_CR_TEST payload;
	payload.cmd         = CMD_CR_TEST;
	payload.test_category = test_category;
	payload.voltage_level = voltage_level;
	payload.resist_val  = resist_val;
	payload.duration    = test_duration;
	payload.ac_upper    = ac_upper;
	payload.voltage_lower = voltage_lower;
	payload.voltage_upper = voltage_upper;
	payload.current_lower = current_lower;
	payload.current_upper = current_upper;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

uint16_t build_empty_load_test_cmd_packet(uint8_t *buffer, uint16_t buffer_len, uint32_t test_duration,
														uint32_t ac_upper, uint32_t voltage_lower, uint32_t voltage_upper)
{
	PAYLOAD_CMD_EMPTY_LOAD_TEST payload;
	payload.cmd         = CMD_EMPTY_LOAD_TEST;
	payload.duration    = test_duration;
	payload.ac_upper    = ac_upper;
	payload.voltage_lower = voltage_lower;
	payload.voltage_upper = voltage_upper;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

uint16_t build_over_current_test_cmd_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t test_category, uint8_t voltage_level, uint32_t test_interval,
													uint32_t ac_upper, uint32_t current_upper)
{
	PAYLOAD_CMD_OVER_CURRENT_TEST payload;
	payload.cmd         = CMD_OVER_CURRENT_TEST;
	payload.test_category = test_category;
	payload.voltage_level = voltage_level;
	payload.interval    = test_interval;
	payload.ac_upper    = ac_upper;
	payload.current_upper = current_upper;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

uint16_t build_short_test_cmd_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t test_category, uint8_t voltage_level, uint32_t test_duration,
												uint32_t ac_upper, uint32_t current_upper)
{
	PAYLOAD_CMD_SHORT_TEST payload;
	payload.cmd         = CMD_SHORT_TEST;
	payload.test_category = test_category;
	payload.voltage_level = voltage_level;
	payload.duration    = test_duration;
	payload.ac_upper    = ac_upper;
	payload.current_upper = current_upper;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

uint16_t build_discharge_test_cmd_packet(uint8_t *buffer, uint16_t buffer_len, uint32_t current_val, uint32_t test_duration)
{
	PAYLOAD_CMD_DISCHARGE_TEST payload;
	payload.cmd         = CMD_DISCHARGE_TEST;
	payload.duration    = test_duration;
	payload.current_val = current_val;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

uint16_t build_poll_cmd_packet(uint8_t *buffer, uint16_t buffer_len)
{
	PAYLOAD_CMD_POLL payload;
	payload.cmd     = CMD_POLL;
	payload.padding = PADDING;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

uint16_t build_stop_cmd_packet(uint8_t *buffer, uint16_t buffer_len)
{
	PAYLOAD_CMD_STOP payload;
	payload.cmd     = CMD_STOP;
	payload.padding = PADDING;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

uint16_t build_set_adjust_value_cmd_packet(uint8_t *buffer, uint16_t buffer_len, uint32_t measure_voltage, uint32_t actual_voltage,
													uint32_t measure_current, uint32_t actual_current)
{
	PAYLOAD_CMD_SET_ADJUST_VALUE payload;
	payload.cmd  = CMD_SET_ADJUST_VALUE;
	payload.measure_voltage = measure_voltage;
	payload.actual_voltage  = actual_voltage;
	payload.measure_current = measure_current;
	payload.actual_current  = actual_current;

	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

uint16_t build_get_adjust_value_cmd_packet(uint8_t *buffer, uint16_t buffer_len)
{
	PAYLOAD_CMD_GET_ADJUST_VALUE payload;
	payload.cmd     = CMD_GET_ADJUST_VALUE;
	payload.padding = PADDING;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

