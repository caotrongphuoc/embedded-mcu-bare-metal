# 05 HAL

This topic builds a HAL that can support more than one MCU and board. The STM32L151 and AK Embedded Base Kit are the first target used to test the design.

## Source structure

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

`hal/inc/api` contains interfaces that do not depend on an MCU.

`hal/inc/instances` declares the implementations available for each interface.

`hal/src` contains the implementation of each MCU peripheral.

`hal/src/bsp/mcu` contains startup, clock, interrupt, and memory support for an MCU family.

`hal/src/bsp/board` contains the pin and peripheral assignments of each board.

`hal_cfg` contains build time options.

`hal_gen` contains the control, configuration, and instance objects selected for a board. These files are written by hand.

`driver` contains drivers for external devices such as an LED, button, display, or external flash. A device driver uses HAL interfaces and does not access MCU registers.

`cmsis` contains the Cortex M core and MCU register definitions.

## Board bring up

For another board using STM32L151, add its board BSP and provide its configuration and instance objects in `hal_gen`. The STM32L1 peripheral implementation does not change.

For another MCU, add its device definitions, MCU BSP, peripheral implementations, linker configuration, and board BSP. The HAL interfaces and reusable device drivers do not change.

Application code can be reused when the new target implements every interface required by the application.

## First target

```text
MCU    STM32L151CBT6
Board  AK Embedded Base Kit
LED    PB8
```

The first example uses GPIO and a system tick to blink the LED. Other peripheral modules are added only when they have an example that can be built and tested.

## References

1. [Renesas RA0E3](https://www.renesas.com/en/products/ra0e3)
2. [Renesas FSP architecture](https://renesas.github.io/fsp/_f_s_p__a_r_c_h_i_t_e_c_t_u_r_e.html)
3. [Raspberry Pi microcontroller chips](https://www.raspberrypi.com/documentation/microcontrollers/microcontroller-chips.html)
4. [AK Embedded Base Kit STM32L151](https://github.com/the-ak-foundation/ak-base-kit-stm32l151)
