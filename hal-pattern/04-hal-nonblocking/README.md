# 04-hal-nonblocking - HAL with non-blocking tick

Blink LED PB8 using `HAL_GetTick` instead of `HAL_Delay`. Same LED, same clock, same 1 ms tick source as [`03-hal-blocking`](../03-hal-blocking/) - the only thing that changes is the shape of the main loop, so the CPU is free to do other work between toggles.

Demo clip for every example lives in the [root README](../../README.md#demo).

## What changed from 03-hal-blocking

Only the main loop is different - init, HAL sources, and the SysTick handler are all untouched:

```diff
-for (;;)
-{
-    HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
-    HAL_Delay(TICK_MS);
-}
+uint32_t last_tick = HAL_GetTick();
+
+for (;;)
+{
+    if (HAL_GetTick() - last_tick >= TICK_MS)
+    {
+        last_tick = HAL_GetTick();
+        HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
+    }
+}
```

`HAL_GetTick` just reads HAL's internal `uwTick` and returns it - the same counter `HAL_Delay` was spinning on in the previous example. The difference is that now the reading happens in the main loop, so if the 100 ms window hasn't elapsed yet, control drops out of the `if` and the rest of the loop is free to run.

The subtraction is deliberate: doing `HAL_GetTick() - last_tick` on unsigned 32-bit values stays correct even when `uwTick` eventually wraps past `0xFFFFFFFF` - the same trick used with `g_tick` back in `arm-cortex-m/00-systick`.

## Why it matters

`HAL_Delay(100)` stops the CPU for the full 100 ms - nothing else can run in that window unless it comes from an interrupt.

`HAL_GetTick` plus an unsigned subtract lets the same loop check the time, toggle when the window has elapsed, and fall through to other work otherwise. This is the shape you want the moment there is more than one thing happening in the main loop - reading a sensor, driving a UART, servicing a button - and it is the pattern every later example in the series builds on.

## Build / Flash / Debug

```bash
make
make flash
make debug
```
