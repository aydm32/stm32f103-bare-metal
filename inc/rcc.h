#ifndef RCC_H
#define RCC_H

#include <stdint.h>

typedef struct {
  volatile uint32_t CR;       // 0x00
  volatile uint32_t CFGR;     // 0x04
  volatile uint32_t CIR;      // 0x08
  volatile uint32_t APB2RSTR; // 0x0C
  volatile uint32_t APB1RSTR; // 0x10
  volatile uint32_t AHBENR;   // 0x14
  volatile uint32_t APB2ENR;  // 0x18
  volatile uint32_t APB1ENR;  // 0x1C
  volatile uint32_t BDCR;     // 0x20
  volatile uint32_t CSR;      // 0x24
} RCC_t;

#define RCC ((RCC_t *)0x40021000UL)

/* ── Peripheral clock enable bits (APB2ENR) ── */
#define RCC_APB2ENR_IOPA BIT(2)    // GPIOA
#define RCC_APB2ENR_IOPB BIT(3)    // GPIOB
#define RCC_APB2ENR_IOPC BIT(4)    // GPIOC
#define RCC_APB2ENR_IOPD BIT(5)    // GPIOD
#define RCC_APB2ENR_IOPE BIT(6)    // GPIOE
#define RCC_APB2ENR_IOPF BIT(7)    // GPIOF
#define RCC_APB2ENR_IOPG BIT(8)    // GPIOG
#define RCC_APB2ENR_ADC1 BIT(9)    // ADC1
#define RCC_APB2ENR_ADC2 BIT(10)   // ADC2
#define RCC_APB2ENR_TIM1 BIT(11)   // TIM1
#define RCC_APB2ENR_SPI1 BIT(12)   // SPI1
#define RCC_APB2ENR_TIM8 BIT(13)   // TIM8
#define RCC_APB2ENR_USART1 BIT(14) // USART1
#define RCC_APB2ENR_ADC3 BIT(15)   // ADC3
#define RCC_APB2ENR_TIM9 BIT(19)   // TIM9
#define RCC_APB2ENR_TIM10 BIT(20)  // TIM10
#define RCC_APB2ENR_TIM11 BIT(21)  // TIM11

/* ── Peripheral clock enable bits (APB1ENR) ── */
#define RCC_APB1ENR_TIM2 BIT(0)    // TIM2
#define RCC_APB1ENR_TIM3 BIT(1)    // TIM3
#define RCC_APB1ENR_TIM4 BIT(2)    // TIM4
#define RCC_APB1ENR_TIM5 BIT(3)    // TIM5
#define RCC_APB1ENR_TIM6 BIT(4)    // TIM6
#define RCC_APB1ENR_TIM7 BIT(5)    // TIM7
#define RCC_APB1ENR_TIM12 BIT(6)   // TIM12
#define RCC_APB1ENR_TIM13 BIT(7)   // TIM13
#define RCC_APB1ENR_TIM14 BIT(8)   // TIM14
#define RCC_APB1ENR_WWDG BIT(11)   // Window watchdog
#define RCC_APB1ENR_SPI2 BIT(14)   // SPI2
#define RCC_APB1ENR_SPI3 BIT(15)   // SPI3
#define RCC_APB1ENR_USART2 BIT(17) // USART2
#define RCC_APB1ENR_USART3 BIT(18) // USART3
#define RCC_APB1ENR_UART4 BIT(19)  // UART4
#define RCC_APB1ENR_UART5 BIT(20)  // UART5
#define RCC_APB1ENR_I2C1 BIT(21)   // I2C1
#define RCC_APB1ENR_I2C2 BIT(22)   // I2C2
#define RCC_APB1ENR_USB BIT(23)    // USB
#define RCC_APB1ENR_CAN BIT(25)    // CAN
#define RCC_APB1ENR_BKP BIT(27)    // Backup interface
#define RCC_APB1ENR_PWR BIT(28)    // Power control

/* ── CFGR bits used during clock configuration ── */
#define RCC_CFGR_PLLSRC_HSE BIT(16)
#define RCC_CFGR_PLLMUL9 (7UL << 18) // HSE(8MHz) * 9 = 72MHz
#define RCC_CFGR_SW_PLL (2UL << 0)
#define RCC_CFGR_SWS_MASK (3UL << 2)
#define RCC_CFGR_SWS_PLL (2UL << 2)
#define RCC_CFGR_PPRE1_DIV2 (4UL << 8)

/* ── Flash access control register (needed for wait states) ── */
#define FLASH_ACR (*(volatile uint32_t *)0x40022000UL)

typedef enum {
  RCC_OK = 0,
  RCC_ERR_HSE_TIMEOUT,
  RCC_ERR_PLL_TIMEOUT,
} rcc_status_t;

rcc_status_t rcc_init(void);

#endif // RCC_H
