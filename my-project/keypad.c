#include "keypad.h"

#include <libopencm3/stm32/gpio.h>

void keypad_init(void) {
    // Set columns (PA11..PA14) to input and pull-up
    gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP,
        GPIO11 | GPIO12 | GPIO13 | GPIO14);

    // Set rows (PA3..PA7) to output
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
        GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7);
}

void keypad_set_row(uint8_t row) {
    // One-out(?) the other rows
    gpio_set(GPIOA, GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7);

    // Set row by clearing it
    gpio_clear(GPIOA, (1 << (3 + row)));
}

uint8_t keypad_read_cols(void) {   
    return ((~(gpio_port_read(GPIOA) >> 11)) & 0x0000000F);
} 

bool keypad_get_pressed(uint8_t *row, uint8_t *col) {
    for (uint8_t r = 0; r < KEYPAD_ROWS; r++) {
        keypad_set_row(r);
        
        // Hardcoded to only support 4 columns!
        switch (keypad_read_cols()) {
            case 1:
                *col = 0;
                *row = r;
                return true;
            case 2:
                *col = 1;
                *row = r;
                return true;
            case 4:
                *col = 2;
                *row = r;
                return true;
            case 8:
                *col = 3;
                *row = r;
                return true;
            case 0:
                break;
            default:
                // Something went wrong
                *col = 255;
                *row = 255;
                break;
        }
    }

    return false;
}
