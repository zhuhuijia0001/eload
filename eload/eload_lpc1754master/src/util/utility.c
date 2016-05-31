#include <rtthread.h>
#include <stdint.h>
#include "type.h"
#include "utility.h"

static const char *trim_left(const char *str)
{
	const char *p;
	p = str;
	
	while (*p == ' ' || *p == '\t')
	{
		p++;
	}
	
	return p;
}

bool number_to_string(char *buffer, uint32_t buffer_len, uint32_t integer, uint32_t integer_len, uint32_t decimal, uint32_t decimal_len,
						bool leading_zero, bool align_left)
{
	uint32_t len;
	uint32_t r;
	
	uint8_t total_len = integer_len + decimal_len + 1;
	if (decimal_len == 0)
	{
		/* no decimal */
		total_len--;
	}
	
	if (total_len + 1 > buffer_len)
	{
		/* len too long */
		return false;
	}
	
	/* integer */
	len = integer_len;
	r = 1;
	
	do 
	{
		r *= 10;
		
		buffer[--len] = integer % 10 + '0';
		
		integer /= 10;
	} while (integer > 0 && len > 0);
	
	while (len--)
	{
		if (leading_zero)
		{
			buffer[len] = '0';
		}
		else
		{
			buffer[len] = ' ';
		}
	}
	
	/* decimal */
	if (decimal_len > 0)
	{
		len = total_len;
		r = 1;
	
		while (decimal > 0)
		{
			r *= 10;
		
			buffer[--len] = decimal % 10 + '0';
		
			decimal /= 10;
		}
		
		while (len-- > total_len - decimal_len)
		{
			buffer[len] = '0';
		}
		
		buffer[len] = '.';
	}
	
	buffer[total_len] = '\0';
	
	if (align_left)
	{
		const char *p = trim_left(buffer);
		
		uint32_t i;
		uint32_t str_len = rt_strlen(p);
		rt_memcpy(buffer, p, str_len);
		for (i = str_len; i < total_len; i++)
		{
			buffer[i] = ' ';
		}
	}

	return true;
}

bool string_to_number(const char *str, uint32_t *integer, uint32_t *decimal)
{
	uint32_t val;
	
	while (*str == ' ')
	{
		str++;
	}
	
	val = 0;
	
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
		{
			val *= 10;
			val += *str - '0';
			
			str++;
		}
		else
		{
			break;
		}
	}
	
	if (*str == '\0')
	{
		if (integer != NULL)
		{
			*integer = val;
		}
		
		if (decimal != NULL)
		{
			*decimal = 0;
		}
		
		return true;
	}
	
	if (*str == '.')
	{
		if (integer != NULL)
		{
			*integer = val;
		}
		
		str++;
		
		val = 0;
		
		while (*str != '\0')
		{
			if (*str >= '0' && *str <= '9')
			{
				val *= 10;
				val += *str - '0';
				
				str++;
			}
			else
			{
				break;
			}
		}

		if (*str == '\0')
		{	
			if (decimal != NULL)
			{
				*decimal = val;
			}
			
			return true;
		}
	}
	
	return false;
}

bool literal_number_to_string(char *buffer, uint32_t buffer_len, const char *number, uint32_t number_len)
{
	if (number_len + 1 > buffer_len)
	{
		/* number too long */
		return false;
	}
	
	while (number_len > 0)
	{
		if (*number > '9' || *number < '0')
		{
			/* invalid digit */
			break;
		}
		
		*buffer++ = *number++;
		
		number_len--;
	}
	
	if (number_len > 0)
	{
		return false;
	}
	
	*buffer = '\0';
	
	return true;
}

bool literal_string_to_number(char *number, uint32_t number_len, const char *buffer, uint32_t buffer_len)
{
	if (number_len + 1 > buffer_len)
	{
		/* number too long */
		return false;
	}
	
	while (number_len > 0)
	{
		if (*buffer > '9' || *buffer < '0')
		{
			/* invalid digit */
			break;
		}
		
		*number++ = *buffer++;
		
		number_len--;
	}
	
	if (number_len > 0)
	{
		return false;
	}
	
	return true;
}
