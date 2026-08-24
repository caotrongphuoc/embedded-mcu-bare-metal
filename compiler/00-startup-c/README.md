# 00-startup-c - Bare-metal LED blink

Blink LED PB8 on the AK Embedded Base Kit (STM32L151CBT6). This is the first example in the series and the one every later example builds on - everything between reset and `main()` is written by hand: vector table, `Reset_Handler`, linker script.

No HAL, no CMSIS, no ST startup files - the point is to see exactly what the CPU needs before C code can run.

Demo clip for every example lives in the [root README](../../README.md#demo).

## The four pieces

### Vector table

The Cortex-M reset sequence reads two words from `0x08000000`: the initial stack pointer, then the address of `Reset_Handler`. Nothing else is needed to boot, so the table starts with exactly those two entries:

```c
__attribute__((section(".isr_vector"))) void (*const g_pfnVectors[2])(void) = {
    _estack,
    Reset_Handler,
};
```

`_estack` is a symbol exported by the linker script (the end of RAM); `Reset_Handler` is the function below. The `.isr_vector` section attribute is what places this array at the start of flash - the linker script pins that section first.

### Reset_Handler

The handler runs before any C runtime exists. It has to zero `.bss` (so uninitialized globals really are zero), copy `.data` from flash to RAM (so initialized globals get their values), then call `main()`:

```c
__attribute__((naked, noreturn)) void Reset_Handler(void)
{
    extern long _sbss, _ebss, _sdata, _edata, _sidata;

    for (long* dst = &_sbss; dst < &_ebss; dst++)
    {
        *dst = 0;
    }

    for (long *dst = &_sdata, *src = &_sidata; dst < &_edata;)
    {
        *dst++ = *src++;
    }

    main();
    for (;;)
    {
        (void)0;
    }
}
```

`naked` tells GCC not to emit a prologue/epilogue - there is no stack frame to save yet. `noreturn` promises the function never comes back, so the compiler will not insert a return instruction that would jump into garbage. The trailing `for (;;)` is a safety net in case `main()` ever returns; on a bare-metal MCU there is nothing above to return to.

### Linker script

`stm32l151xx.ld` declares where flash and RAM live on this chip, places sections into them, and exports the symbols the startup code needs:

```ld
MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 128K
    RAM   (rwx): ORIGIN = 0x20000000, LENGTH = 16K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);
```

`.isr_vector` is pinned first in FLASH so the reset vectors land at `0x08000000`. `.data` lives in RAM at runtime but is stored (`AT >`) in flash after `.text`, which is why `Reset_Handler` needs to copy it. `_sbss`/`_ebss`/`_sdata`/`_edata`/`_sidata` are the section boundaries the startup loop uses.

### main()

Once startup finishes, the actual blink is three register writes and a busy-loop delay:

```c
int main(void)
{
    RCC_AHBENR |= (1U << 1);
    GPIOB_MODER |= (1U << (LED_PIN * 2));

    for (;;)
    {
        GPIOB_BSRR = (1U << LED_PIN);
        delay(100000);
        GPIOB_BSRR = (1U << (LED_PIN + 16));
        delay(100000);
    }
    return 0;
}
```

Enable the GPIOB clock in `RCC_AHBENR`, set PB8 to output mode in `GPIOB_MODER`, then toggle with `GPIOB_BSRR`: the low half sets bits, the upper half (`LED_PIN + 16`) clears them - one atomic write per edge, no read-modify-write needed. `delay()` is just a `nop` loop, which is why timing here drifts with compiler optimization level - the next example ([`arm-cortex-m/00-systick`](../../arm-cortex-m/00-systick/)) replaces it with a real SysTick interrupt.

## Flow at a glance

1. CPU resets, loads `_estack` into SP and `Reset_Handler` into PC from the vector table at `0x08000000`.
2. `Reset_Handler` zeroes `.bss`, copies `.data` from flash to RAM, then calls `main()`.
3. `main()` enables the GPIOB clock, configures PB8 as output, and enters the blink loop.
4. Each iteration sets PB8 high, spins in `delay()`, clears PB8, spins again.

This is the "hello world" of bare-metal: vector table, stack setup, `.bss`/`.data` init, linker script, memory-mapped I/O. Every later example in the repo starts from this same skeleton and changes exactly one technique on top.

## Build / Flash / Debug

```bash
make
make flash
make debug
```
