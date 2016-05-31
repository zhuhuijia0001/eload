#ifndef _LCD_H_
#define _LCD_H_

/* font */
typedef enum
{
	FONT_12  = 0,
	
	FONT_16,
	
	FONT_24,
	
	FONT_32,
	
	FONT_48,
	
	FONT_64,
	
	FONT_NUM
} lcd_font;

/* color */
typedef enum
{
	COLOR_BLACK = 0,
	
	COLOR_RED   = 1,
	
	COLOR_GREEN = 2,
	
	COLOR_BLUE  = 3,
	
	COLOR_YELLOW = 4,
	
	COLOR_CYAN  = 5,
	
	COLOR_MAGENTA = 6,
	
	COLOR_GREY  = 7,
	
	COLOR_WHITE = 15
} lcd_color;
	
extern void lcd_init(void);

extern void lcd_clear(lcd_color color);

extern void lcd_set_backlight(uint8_t brightness);

extern void lcd_set_back_color(lcd_color color);

extern void lcd_draw_rectangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, lcd_color color);

extern void lcd_fill_rectangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, lcd_color color);

extern void lcd_draw_line(uint32_t x_src, uint32_t y_src, uint32_t x_dst, uint32_t y_dst, lcd_color color);

extern void lcd_display_ascii_char(uint32_t x, uint32_t y, char c, lcd_color color, lcd_font font);

extern void lcd_display_string(uint32_t x, uint32_t y, const char *str, lcd_color color, lcd_font font);

extern void lcd_display_number(uint32_t x, uint32_t y, uint32_t integer, uint32_t integer_len, uint32_t decimal, uint32_t decimal_len, 
								bool leading_zero, bool align_left, lcd_color color, lcd_font font);

extern void lcd_display_pic(uint32_t x, uint32_t y, uint16_t pic_id);

extern void lcd_validate_cmd(void);

#endif
