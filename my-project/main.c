#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include "ssd1306.h"
#include "keypad.h"
#include "tokens.h"
#include "input.h"
#include "key_mapping.h"
#include "assets/graphics.h"

uint8_t x;

int main(void) {
	// Hang on for a little bit after starting up, or the display is unhappy
	// (This is about 0.2 seconds)
	for (volatile uint32_t i = 0; i < 100000; i++);

	init();
	ssd1306_fill(0); // Blank

	while (1) {
		uint8_t row, col;
		if (keypad_get_pressed(&row, &col)) {
			key_mapping_action(row, col);
			ssd1306_fill(0);

			// Shift indicator
			ssd1306_set_position(0, 0);
			ssd1306_data_start(1);
			ssd1306_data(key_shift ? 0xFF : 0x00);

			input_redraw_tokens(2, 6);
			input_evaluate();

			for (volatile int i = 0; i < 200000; i++);
		}
	}
}
