# 03-clock-c — PLL clock setup (32 MHz)

Same LED blink as [`02-struct-c`](../02-struct-c/). The only change: SYSCLK now runs at 32 MHz (STM32L1 maximum) instead of the 2.097 MHz MSI default. The new code is one `clock_init()` function called at the top of `main()`.

## Result

<!-- Add LED blink video / gif here. Blink cadence stays 100 ms on / 100 ms off — the visual is the same but the CPU runs 15× faster. -->

## How it works

`clock_init()` walks the sequence from RM0038 §6.3. The order matters — swapping any two steps either bricks the switch or crashes the first flash fetch at the new speed.

1. **Enable the PWR peripheral clock** (`RCC->APB1ENR` bit 28). Its clock is gated off at reset; without this, writes to `PWR->CR` are silently dropped.
2. **Voltage scaling range 1** (`PWR->CR` VOS = 01). Range 1 is 1.8 V and is the only range that allows 32 MHz. Wait for `PWR->CSR` VOSF to clear — the regulator takes a moment to settle.
3. **Flash access at 32 MHz** — set `FLASH->ACR` ACC64 (64-bit reads), then PRFTEN + LATENCY = 1 (one wait state). Above 16 MHz the flash cannot answer at CPU speed without these.
4. **Turn on HSI** (16 MHz internal RC), wait for HSIRDY.
5. **Configure PLL**: PLLSRC = HSI, PLLMUL = ×4, PLLDIV = /2 → 16 × 4 / 2 = 32 MHz. The PLL must be off while writing these bits.
6. **Enable PLL** (`RCC->CR` PLLON), wait for PLLRDY.
7. **Switch SYSCLK to PLL** (`RCC->CFGR` SW = 11). Confirm by reading back SWS.

`SYSCLK_HZ` is redefined from 2 097 000 to 32 000 000. The SysTick reload becomes 31 999, still well below the 24-bit counter limit.

Build / flash / debug:
```bash
make && make flash
make debug
```

## Meaning

Every real STM32 firmware does this dance. Changing one number (the CPU clock) touches four peripherals:

- **RCC** — the clock tree itself.
- **PWR** — voltage scaling gates the maximum SYSCLK allowed.
- **FLASH** — the flash controller needs to know how fast reads come in.
- **SysTick** — its reload value depends on SYSCLK, so anything timing-related breaks when the clock changes.

The code is still fully hand-written — no CMSIS, no HAL. The next example (`04-cmsis-core-c`) folds in the CMSIS-Core headers so we stop writing SysTick and NVIC access by hand.
