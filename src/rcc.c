#include "rcc.h"
#include "utils.h"

void rcc_init(void) {
    // 1. Enable HSE (external 8 MHz crystal)
    SET_BIT(RCC->CR, BIT(16));          // HSEON
    while (!READ_BIT(RCC->CR, BIT(17))) // wait for HSE ready
        ;

    // 2. Configure Flash latency (for 72 MHz)
    //    (Flash access control register is at 0x40022000)
    #define FLASH_ACR (*(volatile uint32_t *)0x40022000)
    MODIFY_REG(FLASH_ACR, 0x3, 0x2);    // 2 wait states for 72 MHz

    // 3. Set PLL: HSE * 9 = 72 MHz (HSE 8 MHz * 9 = 72 MHz)
    //    PLL source = HSE (bit 16), PLL multiplier = 9 (bits 18-21)
    #define RCC_CFGR_PLLSRC_HSE BIT(16)
    #define RCC_CFGR_PLLMUL9    (7 << 18)  // 0x7 << 18 = 0x1C0000
    MODIFY_REG(RCC->CFGR, (BIT(16) | (0xF << 18)), 
               (RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMUL9));

    // 4. Enable PLL
    SET_BIT(RCC->CR, BIT(24));          // PLLON
    while (!READ_BIT(RCC->CR, BIT(25))) // wait for PLL ready
        ;

    // 5. Switch system clock to PLL
    #define RCC_CFGR_SW_PLL (2 << 0)
    MODIFY_REG(RCC->CFGR, (3 << 0), RCC_CFGR_SW_PLL);

    // 6. Wait until PLL is used as system clock
    while (READ_BIT(RCC->CFGR, (3 << 2)) != (2 << 2))
        ;

    // Optional: Set APB1 prescaler to /2 (so APB1 runs at 36 MHz)
    // (not needed for SPI1, but good for I2C/USART)
    #define RCC_CFGR_PPRE1_DIV2 (4 << 8)
    SET_BIT(RCC->CFGR, RCC_CFGR_PPRE1_DIV2);
}
