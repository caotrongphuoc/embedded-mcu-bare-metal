# SDK pattern

This topic studies how microcontroller vendors organize their SDK and HAL source code.

The study follows two vendor SDKs:

1. Renesas Flexible Software Package
2. Raspberry Pi Pico SDK

The goal is to identify how each SDK separates application code, board support, configuration, peripheral drivers, register definitions, and build support. The useful patterns will later be applied to a layered HAL example for the STM32L151 on the AK Embedded Base Kit.

## Contents

| Vendor | Study |
|:---|:---|
| Renesas | [`renesas/`](renesas/) |
| Raspberry Pi | [`raspberry-pi/`](raspberry-pi/) |

## Scope

Each SDK study covers:

1. Top level source tree
2. Application entry point
3. Board and device support
4. Public HAL interface
5. Peripheral driver implementation
6. Configuration and generated source
7. Build composition
8. GPIO call flow from application to register access

The study documents source organization. It does not copy either vendor SDK into this repository or require firmware to run on the reference MCUs.
