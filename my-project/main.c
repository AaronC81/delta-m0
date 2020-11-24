#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include "ssd1306.h"
#include "assets/graphics.h"

int main(void) {
	init();
	ssd1306_fill(0); // Blank

	while (1) {
		for (volatile int i = 0; i < 500000; i++);
		ssd1306_draw_bitmap(graphics_splash, 16, 6);
		for (volatile int i = 0; i < 500000; i++);
		ssd1306_fill(0);
	}
}
