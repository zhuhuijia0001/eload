#ifndef _UTILITY_H_
#define _UTILITY_H_

extern bool number_to_string(char *buffer, uint32_t buffer_len, uint32_t integer, uint32_t integer_len, uint32_t decimal, uint32_t decimal_len,
						bool leading_zero, bool align_left);

extern bool string_to_number(const char *str, uint32_t *integer, uint32_t *decimal);

extern bool literal_number_to_string(char *buffer, uint32_t buffer_len, const char *number, uint32_t number_len);

extern bool literal_string_to_number(char *number, uint32_t number_len, const char *buffer, uint32_t buffer_len);

#endif
