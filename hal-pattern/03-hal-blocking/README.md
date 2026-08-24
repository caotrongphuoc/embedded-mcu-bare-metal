# 03-hal-blocking - HAL layer

Blink LED PB8 with a 1 ms SysTick tick, same behavior as [`02-cmsis-device`](../02-cmsis-device/). Direct register writes are replaced by function calls into ST's HAL - the register writes still happen, just inside the HAL sources instead of in `led_blink.c`.

Still no ST startup files - reset handler and vector table are the same hand-written ones from earlier examples.

Demo clip for every example lives in the [root README](../../README.md#demo).

## What changed from 02-cmsis-device

Clock enable, GPIO configuration, and SysTick setup all become HAL calls:

```diff
-RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
-GPIOB->MODER |= (1U << (LED_PIN * 2));
-SysTick_Config(SYSCLK_HZ / TICK_HZ);
+HAL_Init();
+__HAL_RCC_GPIOB_CLK_ENABLE();
+GPIO_InitTypeDef gpio_init = {
+    .Pin   = LED_PIN,
+    .Mode  = GPIO_MODE_OUTPUT_PP,
+    .Pull  = GPIO_NOPULL,
+    .Speed = GPIO_SPEED_FREQ_LOW,
+};
+HAL_GPIO_Init(LED_PORT, &gpio_init);
```

One thing worth watching: `LED_PIN` is no longer the pin index `8` - HAL takes the bitmask `GPIO_PIN_8` (`1U << 8`), so the constant is redefined accordingly.

The main loop drops the manual `g_tick` comparison and calls `HAL_Delay` instead:

```diff
-uint32_t last_tick = g_tick;
-for (;;)
-{
-    if (g_tick - last_tick >= 100)
-    {
-        last_tick = g_tick;
-        GPIOB->ODR ^= (1U << LED_PIN);
-    }
-}
+for (;;)
+{
+    HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
+    HAL_Delay(TICK_MS);
+}
```

`SysTick_Handler` also stops incrementing our own `g_tick` and calls `HAL_IncTick`, which advances HAL's internal counter (`uwTick`) instead.

The Makefile picks up the HAL include path and the flag that tells the CMSIS device header to expose HAL:

```diff
-CFLAGS = ... -I./cmsis -DSTM32L151xB
+CFLAGS = ... -I./cmsis -I./hal -DSTM32L151xB -DUSE_HAL_DRIVER
```

## HAL files

The HAL sources are vendored in [`hal/`](./hal/), copied from ST's [`stm32l1xx_hal_driver`](https://github.com/STMicroelectronics/stm32l1xx_hal_driver) and [`cmsis_device_l1`](https://github.com/STMicroelectronics/cmsis_device_l1) repositories. Only five `.c` files are actually compiled - the minimum needed for this example:

<div align="center">

| File | Provides |
|:----:|:--------:|
| `stm32l1xx_hal.c` | `HAL_Init`, `HAL_Delay`, `HAL_IncTick`, `uwTick` |
| `stm32l1xx_hal_rcc.c` | RCC setup called by `HAL_Init` |
| `stm32l1xx_hal_gpio.c` | `HAL_GPIO_Init`, `HAL_GPIO_TogglePin` |
| `stm32l1xx_hal_cortex.c` | `HAL_NVIC_SetPriority` called by `HAL_Init` |
| `system_stm32l1xx.c` | `SystemCoreClock` (2 097 000 Hz, MSI default) |

</div>

Their headers - plus a handful pulled in transitively by the RCC code (`flash`, `pwr`, `Legacy/`) - are vendored next to them. `stm32l1xx_hal_conf.h` is ST's template with the 25 unused modules commented out so nothing else gets dragged in.

The CMSIS files under [`cmsis/`](./cmsis/) are exactly the same as in `02-cmsis-device`.

## How it works

`HAL_Init` sets the NVIC priority grouping and then calls `HAL_InitTick`, which programs SysTick for a 1 ms tick and enables its interrupt - same three registers that `SysTick_Config` wrote in the previous example, just wrapped in HAL.

Every 1 ms, `SysTick_Handler` runs and calls `HAL_IncTick`, which increments HAL's `uwTick` counter inside `stm32l1xx_hal.c`.

`HAL_Delay(TICK_MS)` reads `uwTick` in a loop and waits until it has advanced by `TICK_MS` milliseconds. That is what makes it a blocking call - the CPU spins in `HAL_Delay` for the full 100 ms and cannot do anything else. [`04-hal-nonblocking/`](../04-hal-nonblocking/) is the next step, which keeps the same tick source but replaces the blocking wait with a `HAL_GetTick` comparison so the loop is free to do other work.

## Build / Flash / Debug

```bash
make
make flash
make debug
```
