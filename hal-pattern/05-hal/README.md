# HAL for MCU Platforms

## Introduction

This project develops a reusable Hardware Abstraction Layer for MCU platforms. STM32L151 and the AK Embedded Base Kit are the first target used to build and test it.

The interfaces are kept independent from the MCU and board. Porting to another target requires a peripheral implementation, board support, and target configuration.

### I. Design

Each peripheral is defined by an API, configuration data, runtime control data, and an instance that connects them. Application and device driver code use the API without accessing MCU registers.

CMSIS provides the STM32L151 register definitions. The HAL source owns the peripheral logic above those definitions.

### II. Repo Layout

```text
05-hal/
├── Makefile                         # build selected example and target
├── README.md                        # project overview and porting notes
├── cmsis/                           # Cortex M and MCU register definitions
├── driver/                          # LED, button, display and external devices
├── examples/
│   └── led-blink/                   # first hardware test
├── hal/
│   ├── inc/
│   │   ├── api/                     # interfaces shared by all MCUs
│   │   └── instances/               # available MCU implementations
│   └── src/
│       ├── bsp/
│       │   ├── mcu/
│       │   │   └── stm32l1/         # startup, clock, interrupt and memory
│       │   └── board/
│       │       └── ak_base_kit/     # board pins and peripheral assignments
│       ├── stm32l1_gpio/            # STM32L1 GPIO implementation
│       ├── stm32l1_time/            # STM32L1 system tick implementation
│       └── stm32l1_wdt/             # STM32L1 watchdog implementation
├── hal_cfg/
│   ├── bsp/                          # target build options
│   └── driver/                       # peripheral module options
└── hal_gen/                          # control, configuration and instances
```

Folders are added with their first working module. The repository does not keep empty source placeholders.

### III. Board Bring Up

A board using STM32L151 needs a board directory under `hal/src/bsp/board` and its pin and instance data in `hal_gen`. The STM32L1 peripheral source remains unchanged.

A board using another MCU also needs register definitions, an MCU BSP, peripheral implementations, startup code, and a linker configuration. Existing applications and device drivers can be reused when the new target provides the required interfaces.

### IV. First Target

```text
MCU    : STM32L151CBT6
Board  : AK Embedded Base Kit
LED    : PB8
```

The first example uses GPIO and the system tick to blink the LED. Another peripheral is added only with an example that can be built and tested.

### V. References

1. [FSP Architecture](https://renesas.github.io/fsp/_f_s_p__a_r_c_h_i_t_e_c_t_u_r_e.html): interface data structures, instances, API conventions, build time configuration, and file structure.
2. [FSP API Headers](https://github.com/renesas/fsp/tree/master/ra/fsp/inc/api): shared peripheral interface headers.
3. [FSP Instance Headers](https://github.com/renesas/fsp/tree/master/ra/fsp/inc/instances): implementation specific types and API declarations.
4. [FSP Peripheral Modules](https://github.com/renesas/fsp/tree/master/ra/fsp/src): one source directory for each peripheral implementation.
5. [FSP Board Support Package](https://github.com/renesas/fsp/tree/master/ra/fsp/src/bsp): MCU startup, clock, interrupt, and board support source.
6. [AK Kit I/O Configuration](https://github.com/the-ak-foundation/ak-base-kit-stm32l151/blob/main/application/sources/platform/stm32l/io_cfg.h): STM32L151 pin and peripheral assignments for the board.
