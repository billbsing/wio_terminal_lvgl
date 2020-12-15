
ARDMK_DIR     = $(realpath ../buildEnvironment/Arduino-Makefile)

ARDMK_VENDOR = Seeeduino
CMSIS_DIR = $(ARDUINO_PACKAGE_DIR)/Seeeduino/tools/CMSIS/5.4.0/CMSIS
CPPFLAGS += -I$(CMSIS_DIR)/Core/Include/
CPPFLAGS += -I$(CMSIS_DIR)/DSP/Include/
CMSIS_ATMEL_DIR = $(ARDUINO_PACKAGE_DIR)/Seeeduino/tools/CMSIS-Atmel/1.2.1/CMSIS-Atmel/CMSIS
RESET_CMD = $(PYTHON_CMD) $(ARDMK_DIR)/bin/ard-reset-arduino --zero $(MONITOR_PORT)
# ARD_RESET_ARDUINO_PATH = $(ARDMK_DIR)/bin
# BOSSA = /usr/local/bin/bossac --offset=0x4000
BOSSA_OPTS = -d --info --erase --write --verify --reset --offset=0x4000
ARDUINO_SKETCHBOOK = $(realpath ./src)
USER_LIB_PATH = $(realpath ../libraries)

# LOCAL_C_SRCS    ?= $(shell find . -type f -name '*.c' | tr '\n' ' ')
# LOCAL_CPP_SRCS  ?= $(shell find . -type f -name '*.cpp' | tr '\n' ' ')

F_CPU = 120000000L

ARDUINO_LIBS =              \
	SPI						\
	Adafruit_ZeroDMA		\
    Seeed_Arduino_LCD		\
	lvgl

MONITOR_PORT = /dev/cu.usbmodem*
# ISP_PORT = /dev/tty.usbmodem14201
BOARD_TAG = seeed_wio_terminal

include $(ARDMK_DIR)/Sam.mk
