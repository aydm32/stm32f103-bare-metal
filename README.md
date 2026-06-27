# STM32F103C8T6 Bare-Metal Peripheral Library

A from-scratch peripheral driver library for the STM32F103C8T6 (Blue Pill),
written in C without HAL, CubeMX, or any vendor abstraction layer.
This library is developed to build a solid bare-metal firmware foundation
for embedded systems projects — starting with RF communication modules
and eventually targeting flight controller hardware.
Written entirely from reference manuals without vendor abstractions.

## Philosophy

Most STM32 tutorials rely on ST's HAL or CubeMX-generated code. This library
goes directly to the registers — every peripheral is configured by reading the
reference manual and writing to memory-mapped I/O manually. This approach gives
full control over timing, interrupt behavior, and memory layout, which is
essential in resource-constrained embedded systems.

---

## What's Implemented

| Module | File | Status |
|--------|------|--------|
| GPIO | `src/gpio.c` | ✅ Complete |
| RCC (clock configuration) | `inc/rcc.h` | ✅ Complete |
| SPI | `src/spi.c` | 🔧 In progress |
| NRF24L01 RF driver | — | 📋 Planned |

---

## Project Structure

├── src/          # Driver implementations

├── inc/          # Header files

├── linker/       # Custom linker script (stm32f103c8.ld)

├── build/        # Compiled output (ELF, BIN)

├── Makefile      # Bare-metal build system

└── startup.c     # Hand-written vector table and reset handler

---

## Toolchain

- Compiler: `arm-none-eabi-gcc`
- Build system: GNU Make
- Flashing: `st-flash` (ST-Link v2)
- OS: Void Linux (works on any Linux distro)
- No IDE, no CubeMX, no HAL

---

## Build

```bash
make        # compile
make flash  # flash to board via ST-Link
make clean  # clean build artifacts
```

---

## Hardware

- **MCU:** STM32F103C8T6 (Blue Pill, 72MHz Cortex-M3)
- **Programmer:** ST-Link V2
- **Planned:** NRF24L01+ 2.4GHz RF module over SPI

---

## Roadmap

- [x] GPIO driver (input, output, alternate function)
- [x] RCC clock configuration
- [x] Custom startup file and vector table
- [x] Custom linker script
- [ ] SPI driver (in progress)
- [ ] NRF24L01 driver on top of SPI
- [ ] UART driver
- [ ] Timer / PWM driver
- [ ] I2C driver

---

## Context

This library is developed as part of the firmware stack for
**OrionSat** — a 3U CubeSat project led by a six-person undergraduate
team at ENSTSA (National Higher School of Autonomous Systems Technology),
Algeria. The goal is a fully hand-written embedded stack with no
vendor abstractions, suitable for flight software development.

---

## Author

Ayad Mohamed
[GitHub Profile] · [https://www.linkedin.com/in/mohamed-ayad-688269389/?lipi=urn%3Ali%3Apage%3Ad_flagship3_profile_view_base_contact_details%3BiOz%2BoE8YQy2uH4CehR4G7A%3D%3D]
