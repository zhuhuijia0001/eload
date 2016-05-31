#include <rtthread.h>

#include <stdint.h>
#include "type.h"

#include "utility.h"

#include "dev_lcd.h"

#include "lcd.h"

#define LCD_CMD_BUFFER_LEN      100
static char s_lcd_cmd_buffer[LCD_CMD_BUFFER_LEN];

/* device */
static rt_device_t s_dev_lcd = RT_NULL;

/* need validate cmd */
static rt_bool_t s_need_validate_cmd = RT_FALSE;

void lcd_init(void)
{
	dev_lcd_init();
	
	s_dev_lcd = rt_device_find("uart0");
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_open(s_dev_lcd, RT_DEVICE_OFLAG_WRONLY);
}

void lcd_clear(lcd_color color)
{
	rt_uint32_t n;
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "CLS(%d);", color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);
	
	s_need_validate_cmd = RT_TRUE;
}

void lcd_set_backlight(uint8_t brightness)
{
	rt_uint32_t n;
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "SEBL(%d);", brightness);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);

	s_need_validate_cmd = RT_TRUE;
}

void lcd_set_back_color(lcd_color color)
{
	rt_uint32_t n;
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "SBC(%d);", color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);
	
	s_need_validate_cmd = RT_TRUE;
}

void lcd_draw_rectangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, lcd_color color)
{
	rt_uint32_t n;
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "BOX(%d,%d,%d,%d,%d);", x1, y1, x2, y2, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);
	
	s_need_validate_cmd = RT_TRUE;
}

void lcd_fill_rectangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, lcd_color color)
{
	rt_uint32_t n;
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "BOXF(%d,%d,%d,%d,%d);", x1, y1, x2, y2, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);	
	
	s_need_validate_cmd = RT_TRUE;
}

static void lcd_display_ascii_char_12(uint32_t x, uint32_t y, char c, lcd_color color)
{
	rt_uint32_t n;
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "DS12(%d,%d,'%c',%d);", x, y, c, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);

	s_need_validate_cmd = RT_TRUE;
}

static void lcd_display_ascii_char_16(uint32_t x, uint32_t y, char c, lcd_color color)
{
	rt_uint32_t n;
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "DS16(%d,%d,'%c',%d);", x, y, c, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);
	
	s_need_validate_cmd = RT_TRUE;
}

static void lcd_display_ascii_char_24(uint32_t x, uint32_t y, char c, lcd_color color)
{
	rt_uint32_t n;
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "DS24(%d,%d,'%c',%d);", x, y, c, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);
	
	s_need_validate_cmd = RT_TRUE;
}

static void lcd_display_ascii_char_32(uint32_t x, uint32_t y, char c, lcd_color color)
{
	rt_uint32_t n;
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "DS32(%d,%d,'%c',%d);", x, y, c, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);
	
	s_need_validate_cmd = RT_TRUE;
}

static void lcd_display_ascii_char_48(uint32_t x, uint32_t y, char c, lcd_color color)
{
	rt_uint32_t n;
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "DS48(%d,%d,'%c',%d);", x, y, c, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);

	s_need_validate_cmd = RT_TRUE;
}

static void lcd_display_ascii_char_64(uint32_t x, uint32_t y, char c, lcd_color color)
{
	rt_uint32_t n;
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "DS64(%d,%d,'%c',%d);", x, y, c, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);

	s_need_validate_cmd = RT_TRUE;
}

static void (*const s_lcd_display_ascii_char[])(uint32_t x, uint32_t y, char c, lcd_color color) = 
{
	[FONT_12] = lcd_display_ascii_char_12,
	
	[FONT_16] = lcd_display_ascii_char_16,
	
	[FONT_24] = lcd_display_ascii_char_24,
	
	[FONT_32] = lcd_display_ascii_char_32,
	
	[FONT_48] = lcd_display_ascii_char_48,
	
	[FONT_64] = lcd_display_ascii_char_64
};

void lcd_display_ascii_char(uint32_t x, uint32_t y, char c, lcd_color color, lcd_font font)
{
	if (font < FONT_NUM)
	{
		s_lcd_display_ascii_char[font](x, y, c, color);
	}
}

static void lcd_display_string_12(uint32_t x, uint32_t y, const char *str, lcd_color color)
{
	rt_uint32_t n;
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "DS12(%d,%d,'%s',%d);", x, y, str, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);

	s_need_validate_cmd = RT_TRUE;
}

static void lcd_display_string_16(uint32_t x, uint32_t y, const char *str, lcd_color color)
{
	rt_uint32_t n;
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "DS16(%d,%d,'%s',%d);", x, y, str, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);

	s_need_validate_cmd = RT_TRUE;
}

static void lcd_display_string_24(uint32_t x, uint32_t y, const char *str, lcd_color color)
{
	rt_uint32_t n;
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "DS24(%d,%d,'%s',%d);", x, y, str, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);

	s_need_validate_cmd = RT_TRUE;
}

static void lcd_display_string_32(uint32_t x, uint32_t y, const char *str, lcd_color color)
{
	rt_uint32_t n;
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "DS32(%d,%d,'%s',%d);", x, y, str, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);	
	
	s_need_validate_cmd = RT_TRUE;
}

static void lcd_display_string_48(uint32_t x, uint32_t y, const char *str, lcd_color color)
{
	rt_uint32_t n;
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "DS48(%d,%d,'%s',%d);", x, y, str, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);
	
	s_need_validate_cmd = RT_TRUE;
}

static void lcd_display_string_64(uint32_t x, uint32_t y, const char *str, lcd_color color)
{
	rt_uint32_t n;
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "DS64(%d,%d,'%s',%d);", x, y, str, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);

	s_need_validate_cmd = RT_TRUE;
}

static void (*const s_lcd_display_string[])(uint32_t x, uint32_t y, const char *str, lcd_color color) = 
{
	[FONT_12] = lcd_display_string_12,
	
	[FONT_16] = lcd_display_string_16,
	
	[FONT_24] = lcd_display_string_24,
	
	[FONT_32] = lcd_display_string_32,
	
	[FONT_48] = lcd_display_string_48,
	
	[FONT_64] = lcd_display_string_64
};

void lcd_display_string(uint32_t x, uint32_t y, const char *str, lcd_color color, lcd_font font)
{
	if (font < FONT_NUM)
	{
		s_lcd_display_string[font](x, y, str, color);
	}
}

static void lcd_display_number_12(uint32_t x, uint32_t y, uint32_t integer, uint32_t integer_len, uint32_t decimal, uint32_t decimal_len, 
									bool leading_zero, bool align_left, lcd_color color)
{
	char buffer[20];
	rt_uint32_t n;
	
	bool res = number_to_string(buffer, sizeof(buffer), integer, integer_len, decimal, decimal_len, leading_zero, align_left);
	if (!res)
	{
		return;
	}
	
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "DS12(%d,%d,'%s',%d);", x, y, buffer, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);

	s_need_validate_cmd = RT_TRUE;
}

static void lcd_display_number_16(uint32_t x, uint32_t y, uint32_t integer, uint32_t integer_len, uint32_t decimal, uint32_t decimal_len, 
									bool leading_zero, bool align_left, lcd_color color)
{
	char buffer[20];
	rt_uint32_t n;
	
	bool res = number_to_string(buffer, sizeof(buffer), integer, integer_len, decimal, decimal_len, leading_zero, align_left);
	if (!res)
	{
		return;
	}

	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "DS16(%d,%d,'%s',%d);", x, y, buffer, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);

	s_need_validate_cmd = RT_TRUE;
}

static void lcd_display_number_24(uint32_t x, uint32_t y, uint32_t integer, uint32_t integer_len, uint32_t decimal, uint32_t decimal_len, 
									bool leading_zero, bool align_left, lcd_color color)
{
	char buffer[20];
	rt_uint32_t n;;
	
	bool res = number_to_string(buffer, sizeof(buffer), integer, integer_len, decimal, decimal_len, leading_zero, align_left);
	if (!res)
	{
		return;
	}
	
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "DS24(%d,%d,'%s',%d);", x, y, buffer, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);

	s_need_validate_cmd = RT_TRUE;
}

static void lcd_display_number_32(uint32_t x, uint32_t y, uint32_t integer, uint32_t integer_len, uint32_t decimal, uint32_t decimal_len, 
									bool leading_zero, bool align_left, lcd_color color)
{
	char buffer[20];
	rt_uint32_t n;
	
	bool res = number_to_string(buffer, sizeof(buffer), integer, integer_len, decimal, decimal_len, leading_zero, align_left);
	if (!res)
	{
		return;
	}

	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "DS32(%d,%d,'%s',%d);", x, y, buffer, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);

	s_need_validate_cmd = RT_TRUE;
}

static void lcd_display_number_48(uint32_t x, uint32_t y, uint32_t integer, uint32_t integer_len, uint32_t decimal, uint32_t decimal_len, 
									bool leading_zero, bool align_left, lcd_color color)
{
	char buffer[20];
	rt_uint32_t n;
	
	bool res = number_to_string(buffer, sizeof(buffer), integer, integer_len, decimal, decimal_len, leading_zero, align_left);
	if (!res)
	{
		return;
	}
	
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "DS48(%d,%d,'%s',%d);", x, y, buffer, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);

	s_need_validate_cmd = RT_TRUE;
}

static void lcd_display_number_64(uint32_t x, uint32_t y, uint32_t integer, uint32_t integer_len, uint32_t decimal, uint32_t decimal_len, 
									bool leading_zero, bool align_left, lcd_color color)
{
	char buffer[20];
	rt_uint32_t n;
	
	bool res = number_to_string(buffer, sizeof(buffer), integer, integer_len, decimal, decimal_len, leading_zero, align_left);
	if (!res)
	{
		return;
	}
	
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "DS64(%d,%d,'%s',%d);", x, y, buffer, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);

	s_need_validate_cmd = RT_TRUE;
}

static void (*const s_lcd_display_number[])(uint32_t x, uint32_t y, uint32_t integer, uint32_t integer_len, uint32_t decimal, uint32_t decimal_len, 
									bool leading_zero, bool align_left, lcd_color color) = 
{
	[FONT_12] = lcd_display_number_12,
	
	[FONT_16] = lcd_display_number_16,
	
	[FONT_24] = lcd_display_number_24,
	
	[FONT_32] = lcd_display_number_32,
	
	[FONT_48] = lcd_display_number_48,
	
	[FONT_64] = lcd_display_number_64
};

	
void lcd_display_number(uint32_t x, uint32_t y, uint32_t integer, uint32_t integer_len, uint32_t decimal, uint32_t decimal_len, 
									bool leading_zero, bool align_left, lcd_color color, lcd_font font)
{
	if (font < FONT_NUM)
	{
		s_lcd_display_number[font](x, y, integer, integer_len, decimal, decimal_len, leading_zero, align_left, color);
	}
}

void lcd_draw_line(uint32_t x_src, uint32_t y_src, uint32_t x_dst, uint32_t y_dst, lcd_color color)
{
	rt_uint32_t n;
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "PL(%d,%d,%d,%d,%d);", x_src, y_src, x_dst, y_dst, color);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);

	s_need_validate_cmd = RT_TRUE;
}

void lcd_display_pic(uint32_t x, uint32_t y, uint16_t pic_id)
{
	rt_uint32_t n;
	n = rt_snprintf(s_lcd_cmd_buffer, sizeof(s_lcd_cmd_buffer), "PIC(%d,%d,%d);", x, y, pic_id);
	
	RT_ASSERT(s_dev_lcd != RT_NULL);
	
	rt_device_write(s_dev_lcd, 0, (rt_uint8_t *)s_lcd_cmd_buffer, n);

	s_need_validate_cmd = RT_TRUE;
}

static const rt_uint8_t s_cmd_validate[] = { '\r', '\n' };

void lcd_validate_cmd(void)
{
	if (s_need_validate_cmd)
	{
		int busy;
		
		const uint32_t INIT_TIMEOUT = 0xffffff;
		
		uint32_t timeout;
		
		RT_ASSERT(s_dev_lcd != RT_NULL);
	
		rt_device_write(s_dev_lcd, 0, s_cmd_validate, sizeof(s_cmd_validate));	
		
		s_need_validate_cmd = RT_FALSE;
		
		//wait for work 
		timeout = INIT_TIMEOUT;
		
		do
		{
			rt_device_control(s_dev_lcd, CMD_LCD_QUERY_BUSY, &busy);
			timeout--;
		} while (busy == 0 && timeout > 0);
		
		//wait for complete
		timeout = INIT_TIMEOUT;
		
		do
		{
			rt_device_control(s_dev_lcd, CMD_LCD_QUERY_BUSY, &busy);
			timeout--;
		} while (busy == 1 && timeout > 0);
	}
}

