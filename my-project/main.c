#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include "ssd1306.h"
#include "keypad.h"
#include "tokens.h"
#include "input.h"
#include "assets/graphics.h"

uint8_t x;

int main(void) {
	init();
	ssd1306_fill(0); // Blank

	while (1) {
		uint8_t row, col;
		if (keypad_get_pressed(&row, &col)) {
			input_insert(TOKEN_0);
			input_redraw_tokens(2, 3);

			for (volatile int i = 0; i < 500000; i++);
		}
	}
}
