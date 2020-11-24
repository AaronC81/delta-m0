PROJECT = delta-m0
BUILD_DIR = bin

CFILES = init.c ssd1306.c main.c

# TODO - you will need to edit these two lines!
DEVICE=stm32f031k6t6

.phony: usartflash

usartflash: all
	stm32flash /dev/ttyUSB0 -w $(PROJECT).bin

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
