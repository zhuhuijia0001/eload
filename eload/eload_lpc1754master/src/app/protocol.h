#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

/* header */
#define PACKET_HEADER     0xAA55

/* test cmd */
#define CMD_NONE               0x00

#define CMD_CV_TEST            0x01
#define CMD_CC_TEST            0x02
#define CMD_CR_TEST            0x03
#define CMD_EMPTY_LOAD_TEST    0x04
#define CMD_OVER_CURRENT_TEST  0x05
#define CMD_SHORT_TEST         0x06
#define CMD_DISCHARGE_TEST     0x07

#define CMD_CV_MODE            0x08
#define CMD_CC_MODE            0x09
#define CMD_CR_MODE            0x0A

#define CMD_POLL               0x0B
#define CMD_STOP               0x0C

#define CMD_SET_ADJUST_VALUE   0x0D
#define CMD_GET_ADJUST_VALUE   0x0E

/* test type */
#define TEST_TYPE_NONE              CMD_NONE
#define TEST_TYPE_CV_TEST           CMD_CV_TEST
#define TEST_TYPE_CC_TEST           CMD_CC_TEST
#define TEST_TYPE_CR_TEST           CMD_CR_TEST
#define TEST_TYPE_EMPTY_LOAD_TEST   CMD_EMPTY_LOAD_TEST
#define TEST_TYPE_OVER_CURRENT_TEST CMD_OVER_CURRENT_TEST
#define TEST_TYPE_SHORT_TEST        CMD_SHORT_TEST
#define TEST_TYPE_DISCHARGE_TEST    CMD_DISCHARGE_TEST
#define TEST_TYPE_CV_MODE           CMD_CV_MODE
#define TEST_TYPE_CC_MODE           CMD_CC_MODE
#define TEST_TYPE_CR_MODE           CMD_CR_MODE

#define TEST_TYPE_SET_ADJUST_VALUE  CMD_SET_ADJUST_VALUE
#define TEST_TYPE_GET_ADJUST_VALUE  CMD_GET_ADJUST_VALUE

/* test status */
#define TEST_STATUS_IDLE       0x00
#define TEST_STATUS_ON         0x01
#define TEST_STATUS_NORMAL     0x02
#define TEST_STATUS_ABNORMAL   0x03

/* test category */
#define TEST_CATEGORY_SYNTH    0x00
#define TEST_CATEGORY_QC_20    0x01
#define TEST_CATEGORY_MTK      0x02

/* test voltage level */
#define TEST_VOLTAGE_LEVEL_DEFAULT  0x00
#define TEST_VOLTAGE_LEVEL_5V       0x01
#define TEST_VOLTAGE_LEVEL_9V       0x02
#define TEST_VOLTAGE_LEVEL_12V      0x03
#define TEST_VOLTAGE_LEVEL_20V      0x04

/* padding */
#define PADDING           0x00

/* result */
#define RESULT_OK         0

#define RESULT_FAIL       1

/* max packet size */
#define MAX_SEND_PACKET_SIZE   36

#define MAX_RECV_PACKET_SIZE   22

/* automatic time */
#define AUTOMATIC_TIME      0xffffffff

#endif

