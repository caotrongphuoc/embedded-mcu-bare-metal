# Renesas Flexible Software Package

This study examines how the Renesas Flexible Software Package organizes its source code and hardware abstraction interfaces. The RA0E3 is the reference MCU used to follow device specific files through the package.

## Study scope

1. FSP source tree
2. Board Support Package
3. Startup and application entry through `hal_entry`
4. Module interfaces and implementations
5. Control, configuration, API, and instance structures
6. Generated configuration in `ra_cfg` and `ra_gen`
7. GPIO call flow through the I/O port interface
8. Build time module selection

## References

1. [Renesas RA0E3](https://www.renesas.com/en/products/ra0e3)
2. [Renesas Flexible Software Package](https://renesas.github.io/fsp/)
