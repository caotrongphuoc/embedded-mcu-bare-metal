# HAL for MCU Platforms

## Introduction

This project builds a reusable Hardware Abstraction Layer for MCU platforms. STM32L151 on the AK Embedded Base Kit is the first target used to write and test it.

The HAL uses a layered platform layout: one API per peripheral, one instance driver folder per MCU peripheral, a BSP layer for chip and board init, and per-project config headers. The interfaces do not depend on the MCU or the board. Porting to another target needs a peripheral implementation, board support, and target configuration.

### I. Design

Each peripheral has an API, configuration data, runtime control data, and an instance that connects them. Application and device driver code calls the API vtable. It does not touch MCU registers.

CMSIS provides the STM32L151 register definitions. The HAL source owns the peripheral logic above those definitions.

### II. Repo Layout

```text
05-platform/
├── Makefile                             # build one example and target
├── README.md                            # project overview and porting notes
├── board/
│   └── ak_base_kit/                     # board init, LED table, board.h
├── cmsis/                               # Cortex M and MCU register definitions
├── examples/
│   └── ak_base_kit/
│       └── gpio/
│           └── led_blink/
│               ├── hal_cfg/
│               │   ├── bsp/
│               │   │   ├── bsp_cfg.h        # project BSP config (assert, param check)
│               │   │   └── bsp_clock_cfg.h  # project clock tree config
│               │   └── driver/
│               │       └── stm32l1_gpio_cfg.h  # per-driver overrides
│               ├── hal_gen/             # generated: hal_data.[ch], pin_data.[ch]
│               └── src/
│                   └── hal_entry.c      # application entry
├── hal/
│   ├── inc/
│   │   ├── api/                         # interfaces shared by all MCUs
│   │   └── instances/                   # peripheral instances used by applications
│   └── src/
│       ├── bsp/
│       │   └── mcu/
│       │       ├── all/                 # bsp_common, bsp_delay, bsp_io, bsp_compiler_support
│       │       └── stm32l1/             # STM32L1 clock initialization
│       └── stm32l1_gpio/                # STM32L1 GPIO driver instance
└── script/
    └── stm32l151cbtx_flash.ld           # STM32L151CB Flash and RAM layout
```

A folder is added with its first working module. The repository does not keep empty source placeholders.

### III. First Target

```text
MCU     : STM32L151CBT6
Board   : AK Embedded Base Kit
LED     : PB8
Clocks  : HSE 8 MHz, PLL x12 / 3, SYSCLK 32 MHz
```

The first example uses GPIO and the BSP software delay to blink the LED. A new peripheral is added only with an example that can be built and tested.

### IV. Build

Requires the Arm GNU Toolchain (`arm-none-eabi-gcc`, tested with GCC 10.3). The Makefile expects it at `$(GCC_PATH)`. Set `GCC_PATH=` if installed elsewhere.

Build the default LED blink firmware:

```sh
make
```

Build a different example. Point `NAME_MODULE` at the example name and `PROJECT_DIR` at the example folder:

```sh
make NAME_MODULE=led_blink   PROJECT_DIR=examples/ak_base_kit/gpio/led_blink
make NAME_MODULE=echo        PROJECT_DIR=examples/ak_base_kit/uart/echo
```

Output goes to `build_<NAME_MODULE>/<NAME_MODULE>.{elf,map,bin}`.

Clean:

```sh
make clean
```

### V. Flash

The firmware in `build_<NAME_MODULE>/<NAME_MODULE>.bin` is a standalone image linked at `0x08000000`.

> **Warning:** the AK Embedded Base Kit ships with an AK bootloader at the same flash origin. Flashing this image with SWD overwrites the bootloader. Save the bootloader image first if you want to restore it later.

Uses STM32CubeProgrammer over SWD. Default path is `$(HOME)/Workspace/Tools/STM32CubeProgrammer/bin`. Set `PROGRAMER_PATH=` if installed elsewhere.

```sh
make flash
make flash PROGRAMER_PATH=/opt/st/stm32cubeprog/bin
make flash APP_START_ADDR=0x08003000     # skip the AK bootloader region
```

### VI. Debug

Runs `openocd` in a new `xterm` and launches GDB (or DDD) attached to the ELF.

```sh
make debug
make debug gdb=ddd
```

Needs `stm32l_init.gdb` in the folder (same style as folders 00 to 04).

### VII. Porting checklist

**Add a new board on STM32L1:**

1. Create `board/<board_name>/` with `board.h`, `board_init.[ch]`, `board_leds.[ch]`.
2. Define `BOARD_<NAME>` in `board.h`.
3. Add a new example under `examples/<board_name>/<peripheral>/<example>/` with its own `hal_cfg/` and `hal_gen/`.
4. Build with `make PROJECT_DIR=examples/<board_name>/...`.

**Add a new MCU:**

1. Put the vendor CMSIS headers under `cmsis/` (or a per-MCU subfolder).
2. Add `hal/src/bsp/mcu/<mcu>/bsp_clocks.[ch]` for clock init.
3. For each peripheral you use, add `hal/src/<mcu>_<peripheral>/<mcu>_<peripheral>.c` that implements the API vtable `g_<mod>_on_<mcu>_<peripheral>`.
4. Add a linker script under `script/` for the new MCU memory map.
5. Add a startup file that calls `SystemInit` and then `main`. `main` is defined weakly in `bsp_common.c`.
6. Application code (`hal_entry.c`) does not change. Only `hal_data.c` binds the new instance vtable.

### VIII. References

1. [STM32L151 reference manual (RM0038)](https://www.st.com/resource/en/reference_manual/rm0038-stm32l100xx-stm32l151xx-stm32l152xx-and-stm32l162xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf): register map and peripheral behaviour.
2. [Cortex-M3 Devices Generic User Guide](https://developer.arm.com/documentation/dui0552/a/): SysTick, NVIC, memory model.
