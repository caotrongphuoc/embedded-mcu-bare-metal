# 00-systick - SysTick LED blink

Blink LED PB8 on STM32L151CBT6 using SysTick instead of a busy-loop delay. The startup code, linker script, and raw register access are the same as [`compiler/00-startup-c`](../../compiler/00-startup-c/); two things change: the vector table grows from 2 entries to 16 so it can hold the SysTick slot, and delay logic moves from a `nop` loop into a 1 ms interrupt.

Still no HAL, no CMSIS headers, no ST startup files - everything is written by hand.

Demo clip for every example lives in the [root README](../../README.md#demo).

## What changed from 00-startup-c

### Vector table

`00-startup-c` only needed two entries:

```c
_estack,
Reset_Handler,
```

SysTick sits at exception slot 15, so the table has to be long enough to reach it. The 13 slots in between are unused exceptions - fill them with zeros:

```c
__attribute__((section(".isr_vector"))) void (*const g_pfnVectors[16])(void) = {
    _estack,
    Reset_Handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    SysTick_Handler,
};
```

### SysTick registers

SysTick lives in the Cortex-M system control space at `0xE000E010`:

```c
#define SYST_CSR (*(volatile uint32_t*)0xE000E010)
#define SYST_RVR (*(volatile uint32_t*)0xE000E014)
#define SYST_CVR (*(volatile uint32_t*)0xE000E018)
```

The reload value comes from the system clock and the desired tick rate:

```c
SYST_RVR = (SYSCLK_HZ / TICK_HZ) - 1U;
```

With the MSI default clock and a 1 kHz tick:

```c
#define SYSCLK_HZ 2097000U
#define TICK_HZ 1000U
```

the counter fires one interrupt every 1 ms.

### SysTick handler

The handler runs every 1 ms and just bumps a counter:

```c
volatile uint32_t g_tick;

void SysTick_Handler(void)
{
    g_tick++;
}
```

`g_tick` has to be `volatile` because it is written from an ISR and read from `main()` - without it the compiler is free to cache the value in a register and never see the update.

### Main loop

Instead of a `nop` delay, the loop watches `g_tick`:

```c
uint32_t last_tick = g_tick;

for (;;)
{
    if (g_tick - last_tick >= 100)
    {
        last_tick = g_tick;
        GPIOB_ODR ^= (1U << LED_PIN);
    }
}
```

The subtraction is done on unsigned values on purpose - when `g_tick` eventually wraps past `0xFFFFFFFF`, `g_tick - last_tick` still gives the correct elapsed count.

## Flow at a glance

1. `Reset_Handler` initializes `.bss` / `.data`, then jumps to `main()`.
2. `main()` enables the GPIOB clock and configures PB8 as output.
3. `main()` programs SysTick for a 1 ms tick and enables its interrupt.
4. SysTick fires forever in the background; the handler increments `g_tick`.
5. The main loop toggles PB8 whenever 100 ticks have passed.

This is the first example in the series that uses an interrupt, and every later example relies on the same 1 ms tick. Compared with a `nop` delay, the timing here is anchored to the hardware clock, so it no longer drifts with compiler optimization level.

## Build / Flash / Debug

```bash
make
make flash
make debug
```
