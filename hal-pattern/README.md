# HAL pattern

Peripheral driver patterns: raw register access (macro and struct), CMSIS-Device, HAL blocking, and HAL non-blocking.

Same LED blink behavior in every subfolder - only the way registers are declared and touched changes.

## Subfolders

<div align="center">

| # | Folder | Topic |
|:-:|:------:|:-----:|
| 00 | [`00-register-macro/`](00-register-macro/) | Macro-based register access |
| 01 | [`01-register-struct/`](01-register-struct/) | Struct-based register access |
| 02 | [`02-cmsis-device/`](02-cmsis-device/) | CMSIS-Device vendor headers |
| 03 | [`03-hal-blocking/`](03-hal-blocking/) | HAL with blocking `HAL_Delay` |
| 04 | [`04-hal-nonblocking/`](04-hal-nonblocking/) | HAL with non-blocking `HAL_GetTick` |
| 05 | [`05-platform/`](05-platform/) | Layered platform HAL (STM32L1 + AK Base Kit) |

</div>

## Before you start

Read [`arm-cortex-m/00-systick`](../arm-cortex-m/00-systick/) first. Folders 00 to 04 use SysTick for the 1 ms tick.

## Reading order

Read 00 to 04 in order. Each step wraps the previous one.

Folder 05 is a separate track. It is a full platform HAL with per-instance driver folders and BSP layer, instead of a single blink pattern.

