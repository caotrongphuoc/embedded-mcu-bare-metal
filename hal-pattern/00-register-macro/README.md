# 00-register-macro - Register access with `#define` macros

Blink LED PB8 with a 1 ms SysTick tick. The behavior is the same as [`arm-cortex-m/00-systick/`](../../arm-cortex-m/00-systick/); the only thing that changes is how the registers are declared and used.

This is the first pattern in the series: one `#define` per register, each one a dereferenced pointer to a fixed memory address. Nothing else - no structs, no vendor headers, no HAL.

Demo clip for every example lives in the [root README](../../README.md#demo).

## Register declarations

Every register is a `volatile uint32_t` pointer cast from the address that RM0038 gives for it (peripheral base plus register offset), then dereferenced so it can be used like a plain variable:

```c
#define RCC_AHBENR (*(volatile uint32_t*)0x4002381C)
#define GPIOB_MODER (*(volatile uint32_t*)0x40020400)
#define GPIOB_ODR (*(volatile uint32_t*)0x40020414)
```

`volatile` is what keeps the compiler from optimizing the accesses away - every read or write shows up as a real load/store to that address.

## Access

Reads and writes go straight to the mapped address:

```c
RCC_AHBENR |= (1U << 1);
GPIOB_MODER |= (1U << (LED_PIN * 2));
GPIOB_ODR ^= (1U << LED_PIN);
```

Each line is a raw read-modify-write on the peripheral - no abstraction in between.

## Build / Flash / Debug

```bash
make
make flash
make debug
```

This is about as simple as register access gets from C: give it an address, cast to `volatile uint32_t*`, dereference. Every other pattern in this folder builds on top of this one - [`01-register-struct/`](../01-register-struct/) is the next step, grouping the same registers by peripheral into a struct so the base address only appears once.
