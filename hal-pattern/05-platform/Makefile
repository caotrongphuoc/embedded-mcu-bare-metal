PROJECT     := led_blink_ak_base_kit
PROJECT_DIR := examples/ak_base_kit/gpio/led_blink

BUILD_DIR := build
TARGET     := $(BUILD_DIR)/$(PROJECT)

CROSS_COMPILE ?= arm-none-eabi-

CC      := $(CROSS_COMPILE)gcc
AS      := $(CROSS_COMPILE)gcc
OBJCOPY := $(CROSS_COMPILE)objcopy
SIZE    := $(CROSS_COMPILE)size

MCU_FLAGS := -mcpu=cortex-m3 -mthumb

CPPFLAGS := \
	-DSTM32L151xB \
	-Icmsis \
	-Iboard/ak_base_kit \
	-Ihal/inc/api \
	-Ihal/inc/instances \
	-Ihal/src/bsp/mcu/stm32l1 \
	-I$(PROJECT_DIR)/hal_cfg/bsp \
	-I$(PROJECT_DIR)/hal_cfg/driver \
	-I$(PROJECT_DIR)/hal_gen

CFLAGS := \
	$(MCU_FLAGS) \
	-std=c99 \
	-Os \
	-g \
	-Wall \
	-Wextra \
	-ffunction-sections \
	-fdata-sections \
	-fsigned-char \
	-fmessage-length=0 \
	-MMD \
	-MP

ASFLAGS := \
	$(MCU_FLAGS) \
	-x assembler-with-cpp \
	-MMD \
	-MP

LINKER_SCRIPT := script/stm32l151cbtx_flash.ld

LDFLAGS := \
	$(MCU_FLAGS) \
	-T$(LINKER_SCRIPT) \
	-Wl,--gc-sections \
	-Wl,-Map=$(TARGET).map \
	--specs=nano.specs \
	--specs=nosys.specs

LDLIBS := -lc -lm -lnosys

CMSIS_SOURCES := \
	cmsis/system_stm32l1xx.c

BSP_SOURCES := \
	hal/src/bsp/mcu/stm32l1/bsp_clocks.c

HAL_SOURCES := \
	hal/src/mcu/stm32l1/gpio/stm32l1_gpio.c

GENERATED_SOURCES := \
	$(PROJECT_DIR)/hal_gen/hal_data.c \
	$(PROJECT_DIR)/hal_gen/pin_data.c

BOARD_SOURCES := \
	board/ak_base_kit/board_init.c \
	board/ak_base_kit/board_leds.c

STARTUP_SOURCE := cmsis/startup_stm32l151xb.s

PLATFORM_SOURCES := \
	$(CMSIS_SOURCES) \
	$(BSP_SOURCES) \
	$(HAL_SOURCES) \
	$(GENERATED_SOURCES) \
	$(BOARD_SOURCES)

APPLICATION_SOURCES :=

C_SOURCES   := $(PLATFORM_SOURCES) $(APPLICATION_SOURCES)
ASM_SOURCES := $(STARTUP_SOURCE)

C_OBJECTS   := $(addprefix $(BUILD_DIR)/,$(C_SOURCES:.c=.o))
ASM_OBJECTS := $(addprefix $(BUILD_DIR)/,$(ASM_SOURCES:.s=.o))
OBJECTS     := $(C_OBJECTS) $(ASM_OBJECTS)
DEPS        := $(OBJECTS:.o=.d)

ifeq ($(strip $(APPLICATION_SOURCES)),)
all: platform
	@echo "Platform objects built. Add an application source to link the target."
else
all: $(TARGET).bin
endif

platform: $(addprefix $(BUILD_DIR)/,$(PLATFORM_SOURCES:.c=.o)) $(ASM_OBJECTS)

$(TARGET).elf: $(OBJECTS) $(LINKER_SCRIPT)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@
	$(SIZE) $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(CPPFLAGS) $(ASFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)

.PHONY: all clean platform
