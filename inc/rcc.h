#ifndef RCC_H
#define RCC_H
#include <stdint.h>
typedef struct {
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t BDCR;
  volatile uint32_t CSR;
} RCC_t;

#define RCC ((RCC_t *)0x40021000UL)

#define RCC_APB2ENR_IOPA BIT(2) // IO port A clock enable
#define RCC_APB2ENR_IOPB BIT(3) // IO port B clock enable
#define RCC_APB2ENR_IOPC BIT(4) // IO port C clock enable

#define RCC_APB2ENR_SPI1 BIT(12) // SPI1 Clock enable

#endif // !RCC_H
