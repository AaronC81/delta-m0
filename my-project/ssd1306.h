#pragma once
/*
Control an SSD1306 OLED display over I2C.
*/

#include <stdint.h>

#define SSD1306_ADDR 0x3C
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

void ssd1306_command(uint8_t cmd);

void ssd1306_init(void);

void ssd1306_data_start(uint8_t count);
void ssd1306_data(uint8_t datum);

void ssd1306_set_window(uint8_t col_start, uint8_t col_end, uint8_t page_start, uint8_t page_end);
void ssd1306_set_position(uint8_t col, uint8_t page);

void ssd1306_fill(uint8_t colour);
void ssd1306_draw_bitmap(uint8_t *bitmap, uint8_t x, uint8_t page);
