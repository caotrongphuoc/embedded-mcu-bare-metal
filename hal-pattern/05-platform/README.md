# HAL for MCU Platforms

## Introduction

This project develops a reusable Hardware Abstraction Layer for MCU platforms. STM32L151 and the AK Embedded Base Kit are the first target used to build and test it.

The interfaces are kept independent from the MCU and board. Porting to another target requires a peripheral implementation, board support, and target configuration.

### I. Design

Each peripheral is defined by an API, configuration data, runtime control data, and an instance that connects them. Application and device driver code use the API without accessing MCU registers.

CMSIS provides the STM32L151 register definitions. The HAL source owns the peripheral logic above those definitions.

### II. Repo Layout

```text
05-platform/
├── Makefile                         # build selected example and target
├── README.md                        # project overview and porting notes
├── board/
│   └── ak_base_kit/                 # board initialization and devices
├── cmsis/                           # Cortex M and MCU register definitions
├── examples/
│   └── ak_base_kit/
│       └── gpio/
│           └── led_blink/
│               ├── hal_cfg/        # project build configuration
│               ├── hal_gen/        # generated entry, instances and pin data
│               └── src/
│                   └── hal_entry.c # application entry
├── hal/
│   ├── inc/
│   │   ├── api/                     # interfaces shared by all MCUs
│   │   └── instances/               # peripheral instances used by applications
│   └── src/
│       ├── bsp/
│       │   └── mcu/
│       │       ├── all/             # BSP code shared by supported MCUs
│       │       └── stm32l1/         # STM32L1 clock initialization
│       └── stm32l1_gpio/            # STM32L1 GPIO driver instance
└── script/
    └── stm32l151cbtx_flash.ld        # STM32L151CB Flash and RAM layout
```

Folders are added with their first working module. The repository does not keep empty source placeholders.

### III. Board Bring Up

A board using STM32L151 needs a board directory under `board`. Each example keeps its pin, instance, and build configuration in its own `hal_gen` and `hal_cfg` directories. It reuses the peripheral implementations under `hal/src/stm32l1_*`.

A board using another MCU needs register definitions, an MCU BSP under `hal/src/bsp/mcu`, and one driver folder per peripheral instance under `hal/src/<instance>` (for example `hal/src/nrf52_gpio`). Existing applications and device drivers remain unchanged when the new target provides the same APIs.

### IV. First Target

```text
MCU    : STM32L151CBT6
Board  : AK Embedded Base Kit
LED    : PB8
```

The first example uses GPIO and the BSP software delay to blink the LED. Another peripheral is added only with an example that can be built and tested.

### V. Build

The build requires the Arm GNU Toolchain in `PATH`. Build the default LED blink firmware with:

```sh
make
```

Build a different example by pointing `PROJECT_DIR` at its folder:

```sh
make PROJECT_DIR=examples/ak_base_kit/uart/rs485
```

Build only the platform sources with:

```sh
make platform
```

The ELF, map, and binary files are written to `build` and named after the example folder.

### VI. References

1. [Renesas RA0E3](https://www.renesas.com/en/products/ra0e3): MCU overview and technical documents.
2. [FSP Architecture](https://renesas.github.io/fsp/_f_s_p__a_r_c_h_i_t_e_c_t_u_r_e.html): interfaces, instances, API conventions, build time configuration, and file structure.
3. [FSP Support for RA0E3](https://renesas.github.io/fsp/group___b_s_p___m_c_u___r_a0_e3.html): BSP configuration and peripheral modules supported by RA0E3.
