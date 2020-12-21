PROJECT = delta-m0
BUILD_DIR = bin

CFILES = assets/graphics.c tokens.c evaluator.c input.c key_mapping.c init.c ssd1306.c keypad.c main.c 

DEVICE=STM32F051K6T7

.phony: usartflash .FORCE

usartflash: all
	stm32flash /dev/ttyUSB0 -w $(PROJECT).bin

assets/graphics.c: .FORCE
	ruby assets/build_graphics.rb

.FORCE:

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
