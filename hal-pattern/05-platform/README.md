# HAL for MCU Platforms

## Introduction

This project builds a reusable Hardware Abstraction Layer for MCU platforms. STM32L151 on the AK Embedded Base Kit is the first target used to write and test it.

The layout, naming, and configuration follow Renesas FSP (Flexible Software Package) so the source reads side by side with FSP. The interfaces do not depend on the MCU or the board. Porting to another target needs a peripheral implementation, board support, and target configuration.

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

Requires the Arm GNU Toolchain (`arm-none-eabi-gcc`, tested with GCC 10.3 or newer). Put it on `PATH`.

Build the default LED blink firmware:

```sh
make
```

Build a different example. Point `PROJECT_DIR` at the example folder:

```sh
make PROJECT_DIR=examples/ak_base_kit/gpio/led_blink
make PROJECT_DIR=examples/ak_base_kit/uart/rs485
```

Build only the platform sources without linking an application:

```sh
make platform
```

Output goes to `build/<example>.{elf,map,bin}`. `<example>` is the last path segment of `PROJECT_DIR`.

Clean:

```sh
make clean
```

### V. Flash

The firmware in `build/<example>.bin` is a standalone image linked at `0x08000000`.

> **Warning:** the AK Embedded Base Kit ships with an AK bootloader at the same flash origin. Flashing this image with ST-Link overwrites the bootloader. Save the bootloader image first if you want to keep it.

With OpenOCD:

```sh
openocd -f interface/stlink.cfg -f target/stm32l1.cfg \
    -c "program build/led_blink.bin 0x08000000 verify reset exit"
```

With `st-flash`:

```sh
st-flash write build/led_blink.bin 0x08000000
```

To keep the AK bootloader, edit the linker `ORIGIN` to skip past the bootloader region and rebuild. Flash the new image at the offset. Do not erase the bootloader region.

### VI. Porting checklist

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

### VII. References

1. [Renesas RA0E3](https://www.renesas.com/en/products/ra0e3): MCU overview and technical documents.
2. [FSP Architecture](https://renesas.github.io/fsp/_f_s_p__a_r_c_h_i_t_e_c_t_u_r_e.html): interfaces, instances, API conventions, build time configuration, and file structure.
3. [FSP Support for RA0E3](https://renesas.github.io/fsp/group___b_s_p___m_c_u___r_a0_e3.html): BSP configuration and peripheral modules supported by RA0E3.
