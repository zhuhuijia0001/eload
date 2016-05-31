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

uint16_t build_cv_test_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result)
{
	PAYLOAD_CMD_RET payload;
	payload.cmd           = CMD_CV_TEST;
	payload.result        = result;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));	
}

uint16_t build_cc_test_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result)
{
	PAYLOAD_CMD_RET payload;
	payload.cmd           = CMD_CC_TEST;
	payload.result        = result;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));	
}

uint16_t build_cr_test_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result)
{
	PAYLOAD_CMD_RET payload;
	payload.cmd           = CMD_CR_TEST;
	payload.result        = result;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));	
}

uint16_t build_empty_load_test_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result)
{
	PAYLOAD_CMD_RET payload;
	payload.cmd           = CMD_EMPTY_LOAD_TEST;
	payload.result        = result;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));	
}

uint16_t build_over_current_test_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result)
{
	PAYLOAD_CMD_RET payload;
	payload.cmd           = CMD_OVER_CURRENT_TEST;
	payload.result        = result;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));	
}

uint16_t build_short_test_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result)
{
	PAYLOAD_CMD_RET payload;
	payload.cmd           = CMD_SHORT_TEST;
	payload.result        = result;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));	
}

uint16_t build_discharge_test_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result)
{
	PAYLOAD_CMD_RET payload;
	payload.cmd           = CMD_DISCHARGE_TEST;
	payload.result        = result;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

uint16_t build_cv_mode_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result)
{
	PAYLOAD_CMD_RET payload;
	payload.cmd           = CMD_CV_MODE;
	payload.result        = result;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));	
}

uint16_t build_cc_mode_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result)
{
	PAYLOAD_CMD_RET payload;
	payload.cmd           = CMD_CC_MODE;
	payload.result        = result;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

uint16_t build_cr_mode_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result)
{
	PAYLOAD_CMD_RET payload;
	payload.cmd           = CMD_CR_MODE;
	payload.result        = result;
	
	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

uint16_t build_poll_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t test_type, uint8_t test_status,
											uint32_t ac, uint32_t voltage, uint32_t current)
{
	PAYLOAD_CMD_POLL_RET payload;
	payload.cmd         = CMD_POLL;
	payload.test_type   = test_type;
	payload.test_status = test_status;
	payload.ac          = ac;
	payload.voltage     = voltage;
	payload.current     = current;

	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

uint16_t build_stop_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t test_type)
{
	PAYLOAD_CMD_STOP_RET payload;
	payload.cmd       = CMD_STOP;
	payload.test_type = test_type;

	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

uint16_t build_set_adjust_value_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint8_t result)
{
	PAYLOAD_CMD_SET_ADJUST_VALUE_RET payload;
	payload.cmd  = CMD_SET_ADJUST_VALUE;
	payload.padding = 0;

	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));
}

uint16_t build_get_adjust_value_cmd_ret_packet(uint8_t *buffer, uint16_t buffer_len, uint32_t measure_voltage, uint32_t actual_voltage,
													uint32_t measure_current, uint32_t actual_current)
{
	PAYLOAD_CMD_GET_ADJUST_VALUE_RET payload;
	payload.cmd  = CMD_GET_ADJUST_VALUE;
	payload.measure_voltage = measure_voltage;
	payload.actual_voltage  = actual_voltage;
	payload.measure_current = measure_current;
	payload.actual_current  = actual_current;


	return build_packet(buffer, buffer_len, (uint8_t *)&payload, sizeof(payload));

}
													
