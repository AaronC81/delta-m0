#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include "ssd1306.h"

int main(void) {
	init();

	while (1) {
		for (volatile int i = 0; i < 500000; i++);
		ssd1306_fill(1);
		for (volatile int i = 0; i < 500000; i++);
		ssd1306_fill(0);
	}
}
