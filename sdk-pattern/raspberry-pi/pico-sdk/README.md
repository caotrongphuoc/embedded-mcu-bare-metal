# Raspberry Pi Pico SDK

This study examines how the Raspberry Pi Pico SDK organizes its source code and hardware access libraries. The RP2040 is the reference MCU used to follow platform specific files through the SDK.

## Study scope

1. Pico SDK source tree
2. Platform and board support
3. Startup, runtime initialization, and application entry through `main`
4. Public hardware library interfaces
5. Peripheral driver implementations
6. Generated register definitions
7. GPIO call flow through `hardware_gpio`
8. CMake library composition

## References

1. [Raspberry Pi microcontroller chips](https://www.raspberrypi.com/documentation/microcontrollers/microcontroller-chips.html)
2. [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk)
