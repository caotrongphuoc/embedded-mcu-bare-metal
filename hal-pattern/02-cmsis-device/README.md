# 02-cmsis-device - CMSIS device headers

Blink LED PB8 with a 1 ms SysTick tick, same behavior as [`01-register-struct`](../01-register-struct/). The hand-written peripheral structs are replaced by CMSIS headers from ARM (core) and ST (device), which define the same kind of structs for the entire chip.

Still no HAL, no ST startup files - only the register declarations move from `led_blink.h` into vendor headers.

Demo clip for every example lives in the [root README](../../README.md#demo).

## What changed from 01-register-struct

All the hand-written register structs and base pointers collapse into a single include:

```diff
-typedef struct
-{
-    volatile uint32_t MODER;
-    volatile uint32_t OTYPER;
-    volatile uint32_t OSPEEDR;
-    volatile uint32_t PUPDR;
-    volatile uint32_t IDR;
-    volatile uint32_t ODR;
-} GPIO_TypeDef;
-
-typedef struct
-{
-    volatile uint32_t CR;
-    volatile uint32_t ICSCR;
-    volatile uint32_t CFGR;
-    volatile uint32_t CIR;
-    volatile uint32_t AHBRSTR;
-    volatile uint32_t APB2RSTR;
-    volatile uint32_t APB1RSTR;
-    volatile uint32_t AHBENR;
-} RCC_TypeDef;
-
-typedef struct
-{
-    volatile uint32_t SYST_CSR;
-    volatile uint32_t SYST_RVR;
-    volatile uint32_t SYST_CVR;
-    volatile uint32_t SYST_CALIB;
-} SysTick_TypeDef;
-
-#define GPIOB   ((GPIO_TypeDef*)0x40020400UL)
-#define RCC     ((RCC_TypeDef*)0x40023800UL)
-#define SysTick ((SysTick_TypeDef*)0xE000E010UL)
+#include "stm32l1xx.h"
```

The raw shift for the GPIOB clock bit becomes a named macro from the device header, which reads much closer to the reference manual:

```diff
-RCC->AHBENR |= (1U << 1);
+RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
```

And the SysTick setup is replaced by a CMSIS-Core helper that programs `RVR`, `CVR`, and `CSR` in one call:

```diff
-SysTick->SYST_RVR = (SYSCLK_HZ / TICK_HZ) - 1U;
-SysTick->SYST_CVR = 0U;
-SysTick->SYST_CSR = (1U << 0) | (1U << 1) | (1U << 2);
+SysTick_Config(SYSCLK_HZ / TICK_HZ);
```

Two new bits go into the Makefile so the compiler can find the headers and pick the right device:

```diff
-CFLAGS = -mcpu=cortex-m3 -mthumb ... -DAPP_START_ADDR=$(APP_START_ADDR)
+CFLAGS = -mcpu=cortex-m3 -mthumb ... -DAPP_START_ADDR=$(APP_START_ADDR) -I./cmsis -DSTM32L151xB
```

`-I./cmsis` points the compiler at the vendored headers, and `-DSTM32L151xB` tells `stm32l1xx.h` which STM32L1 device header to pull in.

## CMSIS files

The CMSIS files are vendored in [`cmsis/`](./cmsis/) so the build has no external dependency.

| File | Source | Provides |
|------|--------|----------|
| `core_cm3.h` | ARM CMSIS-Core | Cortex-M3 core registers, `SysTick`, `SysTick_Config()`, `NVIC_*` |
| `cmsis_gcc.h` | ARM CMSIS-Core | GCC compiler intrinsics |
| `cmsis_compiler.h` | ARM CMSIS-Core | compiler abstraction macros |
| `cmsis_version.h` | ARM CMSIS-Core | CMSIS version macros |
| `mpu_armv7.h` | ARM CMSIS-Core | ARMv7-M MPU definitions |
| `stm32l1xx.h` | ST CMSIS-Device | device selection entry point |
| `stm32l151xb.h` | ST CMSIS-Device | STM32L151xB registers, structs, base addresses, bit masks |
| `system_stm32l1xx.h` | ST CMSIS-Device | system clock declarations |

## How it works

`stm32l1xx.h` reads the `STM32L151xB` macro from the Makefile and uses it to include `stm32l151xb.h`. That header defines the same kind of register structs used in `01-register-struct`, but for the full chip - so `GPIOB->MODER`, `RCC->AHBENR`, and named bit masks like `RCC_AHBENR_GPIOBEN` all come from there.

The Cortex-M3 core side - `SysTick` and `SysTick_Config()` - comes from `core_cm3.h`.

## Build / Flash / Debug

```bash
make
make flash
make debug
```

CMSIS only replaces the hand-written register declarations; the code still writes registers directly and there is no HAL layer yet. The difference is that the structs, base addresses, and bit masks now come from vendor headers, which makes the code portable to any STM32L1 device by changing only the `-D` macro.
