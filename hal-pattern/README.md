# HAL pattern

Two things live here:

1. **A driver-access progression** in folders 00 to 04. Same LED blink, one new technique per step. The diff from one folder to the next shows the new concept.
2. **The HAL project** in folder 05. A layered HAL you can port to more than one MCU. LED blink is its first working module, more come later.

## Subfolders

<div align="center">

| # | Folder | Topic |
|:-:|:------:|:-----:|
| 00 | [`00-register-macro/`](00-register-macro/) | Macro-based register access |
| 01 | [`01-register-struct/`](01-register-struct/) | Struct-based register access |
| 02 | [`02-cmsis-device/`](02-cmsis-device/) | CMSIS-Device vendor headers |
| 03 | [`03-hal-blocking/`](03-hal-blocking/) | HAL with blocking `HAL_Delay` |
| 04 | [`04-hal-nonblocking/`](04-hal-nonblocking/) | HAL with non-blocking `HAL_GetTick` |
| 05 | [`05-platform/`](05-platform/) | Layered HAL project: API + instance drivers + BSP + per-project config |

</div>

## Before you start

Read [`arm-cortex-m/00-systick`](../arm-cortex-m/00-systick/) first. Folders 00 to 04 use SysTick for the 1 ms tick.

## Reading order

Read 00 to 04 in order. Each step wraps the previous one and prepares you for 05.

Folder 05 is where the HAL itself lives. It is not the same LED blink pattern, it is a full project with its own API, driver instances, BSP layer, and per-project config. First working module: GPIO on AK Base Kit. More modules (UART, ADC, and so on) come as new examples.
