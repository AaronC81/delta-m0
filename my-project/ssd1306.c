#include "ssd1306.h"

#include <libopencm3/stm32/i2c.h>

void ssd1306_command(uint8_t cmd) {
	uint8_t data[] = { 0, cmd };
	i2c_transfer7(I2C1, SSD1306_ADDR, data, 2, NULL, 0);
}

void ssd1306_init(void) {
    // Display off
    ssd1306_command(0xAE);
    
    // Set charge pump
    ssd1306_command(0x8D);
    ssd1306_command(0x14);

    // Flip display horizontally
    ssd1306_command(0xA1);

    // Display on
    ssd1306_command(0xAF);
}

void ssd1306_set_position(uint8_t col, uint8_t page) {
    // Column (split across nibbles)
    ssd1306_command(0x00 + (col & 0x0F));
    ssd1306_command(0x10 + ((col & 0xF0) >> 4));

    // Page
    ssd1306_command(0xB0 + page);
}

void ssd1306_data_start(uint8_t count) {
    i2c_set_7bit_address(I2C1, SSD1306_ADDR);
    i2c_set_bytes_to_transfer(I2C1, count + 1);
    i2c_send_start(I2C1);

    ssd1306_data(0x40);
}

void ssd1306_data(uint8_t datum) {
    while (!i2c_transmit_int_status(I2C1));
    i2c_send_data(I2C1, datum);
}

void ssd1306_fill(uint8_t colour) {
    for (uint8_t i = 0; i < (SSD1306_HEIGHT / 8); i++) {
        ssd1306_set_position(0, i);
        ssd1306_data_start(SSD1306_WIDTH);
        for (uint8_t i = 0; i < SSD1306_WIDTH; i++) {
            ssd1306_data(colour ? 0xFF : 0x00);
        }
    }
}

void ssd1306_draw_bitmap(uint8_t *bitmap, uint8_t x, uint8_t page) {
    uint8_t width = bitmap[0];
    uint8_t pages = bitmap[1];
    bitmap += 2;
    for (int p = 0; p < pages; p++) {
        ssd1306_set_position(x, page - p);
        ssd1306_data_start(width);
        for (int i = 0; i < width; i++) {
            ssd1306_data(bitmap[p * width + i]);
        }
    }
}
