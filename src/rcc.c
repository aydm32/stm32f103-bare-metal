#include "rcc.h"
#include "utils.h"

/* Loop-iteration budget for the two hardware-lock waits below. This isn't a
 * calibrated microsecond timeout — it's a "don't hang forever on dead
 * hardware" guard so a bad crystal or bench-power glitch gives you a status
 * code instead of a silent lockup with no serial output to explain why. */
#define RCC_LOCK_TIMEOUT 100000UL

rcc_status_t rcc_init(void) {
    uint32_t timeout;

    // 1. Enable HSE (external 8 MHz crystal)
    SET_BIT(RCC->CR, BIT(16)); // HSEON
    timeout = RCC_LOCK_TIMEOUT;
    while (!READ_BIT(RCC->CR, BIT(17))) { // wait for HSE ready
        if (--timeout == 0) return RCC_ERR_HSE_TIMEOUT;
    }

    // 2. Configure Flash latency (for 72 MHz)
    MODIFY_REG(FLASH_ACR, 0x3, 0x2);    // 2 wait states for 72 MHz

    // 3. Set PLL: HSE * 9 = 72 MHz
    //    PLL source = HSE (bit 16), PLL multiplier = 9 (bits 18-21)
    MODIFY_REG(RCC->CFGR, (BIT(16) | (0xFUL << 18)),
               (RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMUL9));

    // 4. Enable PLL
    SET_BIT(RCC->CR, BIT(24)); // PLLON
    timeout = RCC_LOCK_TIMEOUT;
    while (!READ_BIT(RCC->CR, BIT(25))) { // wait for PLL ready
        if (--timeout == 0) return RCC_ERR_PLL_TIMEOUT;
    }

    // 5. Switch system clock to PLL
    MODIFY_REG(RCC->CFGR, (3UL << 0), RCC_CFGR_SW_PLL);

    // 6. Wait until PLL is used as system clock
    //    (this one always resolves once step 5 lands, so no timeout needed)
    while (READ_BIT(RCC->CFGR, RCC_CFGR_SWS_MASK) != RCC_CFGR_SWS_PLL)
        ;

    // Optional: Set APB1 prescaler to /2 (so APB1 runs at 36 MHz)
    // (not needed for SPI1, but good for I2C/USART)
    SET_BIT(RCC->CFGR, RCC_CFGR_PPRE1_DIV2);

    return RCC_OK;
}

rcc_status_t rcc_init_hsi_only(void) {
    // HSI is already the running clock source at reset — nothing to enable.
    // This function exists purely so main.c has a symmetrical, obviously-
    // temporary call site to swap to for the isolation test. No PLL, no
    // wait-state change needed: 8 MHz Flash access needs 0 wait states,
    // which is already the reset default.
    return RCC_OK;
}
