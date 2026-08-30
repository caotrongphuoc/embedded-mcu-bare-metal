# HAL for MCU Platforms

## Introduction

This example develops a reusable Hardware Abstraction Layer for MCU platforms. STM32L151 and the AK Embedded Base Kit are used for the first implementation and hardware test.

The HAL interface does not depend on a specific MCU or board. A new target supplies its own peripheral implementation, board support, and configuration.

### I. Source Structure

```text
05-hal/
    app/
    cmsis/
    driver/
    examples/

    hal/
        inc/
            api/
            instances/
        src/
            bsp/
                mcu/
                    stm32l1/
                board/
                    ak_base_kit/
            stm32l1_gpio/
            stm32l1_time/
            stm32l1_wdt/

    hal_cfg/
        bsp/
        driver/

    hal_gen/
```

### II. Source Directories

`app` contains the application entry point.

`cmsis` contains Cortex M core headers and MCU register definitions.

`driver` contains drivers for devices outside the MCU, such as LEDs, buttons, displays, and external flash.

`examples` contains small programs used to test each HAL module.

`hal/inc/api` contains interfaces shared by all MCU implementations.

`hal/inc/instances` declares the implementations available for those interfaces.

`hal/src` contains peripheral implementations and Board Support Packages.

`hal_cfg` contains build time options for the selected target.

`hal_gen` contains control, configuration, instance, and pin data for the selected board. These files are written by hand.

### III. Board Bring Up

For a new board using STM32L151, add its board support files and provide its instance and pin configuration in `hal_gen`. The STM32L1 peripheral implementation remains unchanged.

For a board using another MCU, provide:

1. MCU register definitions
2. MCU Board Support Package
3. Peripheral implementations
4. Linker and startup configuration
5. Board Support Package
6. Instance and pin configuration

The application and device drivers can be reused when the new target implements the required HAL interfaces.

### IV. First Target

```text
MCU    : STM32L151CBT6
Board  : AK Embedded Base Kit
LED    : PB8
```

The first example uses GPIO and a system tick to blink the LED. Other modules are added with an example that can be built and tested.

### V. References

1. [Renesas RA0E3](https://www.renesas.com/en/products/ra0e3)
2. [Renesas FSP Architecture](https://renesas.github.io/fsp/_f_s_p__a_r_c_h_i_t_e_c_t_u_r_e.html)
3. [Raspberry Pi Microcontroller Chips](https://www.raspberrypi.com/documentation/microcontrollers/microcontroller-chips.html)
4. [AK Embedded Base Kit STM32L151](https://github.com/the-ak-foundation/ak-base-kit-stm32l151)
