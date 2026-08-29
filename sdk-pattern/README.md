# SDK pattern

This topic studies how microcontroller vendors organize their software development kits and hardware abstraction layers.

The study follows two MCU platforms:

1. Renesas RA0E3 with the Flexible Software Package
2. Raspberry Pi RP series with the Pico SDK

Both platforms will be examined from startup code and board support to peripheral drivers and application APIs.

## Contents

| Vendor | Study |
|:---|:---|
| Renesas | [`renesas/`](renesas/) |
| Raspberry Pi | [`raspberry-pi/`](raspberry-pi/) |

## Study scope

Each MCU study will cover:

1. SDK source structure
2. Startup and system initialization
3. Board and device support
4. Register definitions and peripheral drivers
5. HAL API design
6. Build and configuration system
7. Application entry point
8. GPIO call flow from application to hardware
