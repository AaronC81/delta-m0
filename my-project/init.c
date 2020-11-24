#include "init.h"

#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include "ssd1306.h"

// PB6: SCL
// PB7: SDA

// PA9/PA10: USART

void init(void) {
    // Set up GPIO
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);

	// Set up GPIO for USART1
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9 | GPIO10);
	gpio_set_af(GPIOA, GPIO_AF1, GPIO9 | GPIO10);

	// Set up USART1
	rcc_periph_clock_enable(RCC_USART1);
	usart_disable(USART1);
	usart_set_databits(USART1, 8);
	usart_set_baudrate(USART1, 9600);
	usart_set_mode(USART1, USART_MODE_TX);
	usart_enable(USART1);
	
	// Set up I2C1
	rcc_periph_clock_enable(RCC_I2C1);
	i2c_enable_autoend(I2C1);
	I2C_TIMINGR(I2C1) = 0x00100306 | (I2C_TIMINGR(I2C1) & 0x0F000000);
	i2c_peripheral_enable(I2C1);

	// Set up GPIO for I2C1
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO6 | GPIO7);
	gpio_set_output_options(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_LOW, GPIO6 | GPIO7);
	gpio_set_af(GPIOB, GPIO_AF1, GPIO6 | GPIO7);
    
    // Init display
    ssd1306_init();
}