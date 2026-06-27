#ifndef SPI_H
#define SPI_H
#include <stdint.h>

typedef struct {
  volatile uint32_t CR1;     // 0x00
  volatile uint32_t CR2;     // 0x04
  volatile uint32_t SR;      // 0x08
  volatile uint32_t DR;      // 0x0C
  volatile uint32_t CRCPR;   // 0x10
  volatile uint32_t RXCRCR;  // 0x14
  volatile uint32_t TXCRCR;  // 0x18
  volatile uint32_t I2SCFGR; // 0x1C
  volatile uint32_t I2SPR;   // 0x20
} SPIx_t;

#define SPI1 ((SPIx_t *)0x40013000UL)
#define SPI2 ((SPIx_t *)0x40003800UL)

#endif // !SPI_H
