ARM_PREFIX = arm-none-eabi-
CC = $(ARM_PREFIX)gcc
OBJCOPY = $(ARM_PREFIX)objcopy

CFLAGS = -Wall -g -mcpu=cortex-m3 -mthumb 
INCLUDE_FOLDERS = -I board_cfg
LDFLAGS = -specs=nano.specs -specs=nosys.specs -T board_cfg/linker_script.ld

SRC_FILES = $(wildcard src/*.c)

OBJ_FILES = $(SRC_FILES:.c=.o)

all: app.bin

app.elf: $(OBJ_FILES) 
	$(CC)  $(LDFLAGS) -o app.elf $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS)  -c -o $@ $<

app.bin: app.elf
	$(OBJCOPY) -O binary app.elf app.bin

.PHONY: clean
clean:
	rm -rf $(OBJ_FILES) app.elf app.bin
