# 01-register-struct - Register access with `typedef struct`

Blink LED PB8 with a 1 ms SysTick tick. Same behavior as [`arm-cortex-m/00-systick/`](../../arm-cortex-m/00-systick/) and [`00-register-macro/`](../00-register-macro/); the only thing that changes is how the registers are declared.

Instead of one `#define` per register, the registers belonging to a peripheral are collected into a `typedef struct` that mirrors the peripheral's memory layout, and the base address is cast once to a pointer of that struct type.

Demo clip for every example lives in the [root README](../../README.md#demo).

## Register declarations

The struct fields are listed in the exact order of the RM0038 offsets - the layout of the struct has to match the layout of the peripheral in memory:

```c
typedef struct
{
    volatile uint32_t MODER;   // 0x00
    volatile uint32_t OTYPER;  // 0x04
    volatile uint32_t OSPEEDR; // 0x08
    volatile uint32_t PUPDR;   // 0x0C
    volatile uint32_t IDR;     // 0x10
    volatile uint32_t ODR;     // 0x14
} GPIO_TypeDef;
```

Then the base address is turned into a pointer to that struct:

```c
#define GPIOB ((GPIO_TypeDef*)0x40020400UL)
```

## Access

Registers are reached through the base pointer, so the base address only appears once:

```c
RCC->AHBENR |= (1U << 1);
GPIOB->MODER |= (1U << (LED_PIN * 2));
GPIOB->ODR ^= (1U << LED_PIN);
```

`GPIOB->ODR` compiles to `base + offsetof(GPIO_TypeDef, ODR)` = `0x40020400 + 0x14` = `0x40020414` - the same final address as the `#define` in `00-register-macro`, but computed by the compiler from the struct layout.

## Build / Flash / Debug

```bash
make
make flash
make debug
```

The struct captures the memory layout of a peripheral once, and every register on that peripheral becomes a field on the same base pointer. This is exactly the pattern the CMSIS device headers use - [`02-cmsis-device/`](../02-cmsis-device/) replaces these hand-written structs with ST's `stm32l151xb.h`, which does the same thing for the whole chip. Compare with [`00-register-macro/`](../00-register-macro/), where each register is a separate `#define` at a hard-coded address.
