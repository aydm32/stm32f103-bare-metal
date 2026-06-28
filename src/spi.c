#include "spi.h"
#include "rcc.h"
#include "gpio.h" 
#include "utils.h"


void spi1_init(SPI_Config cfg)
{
    // ── 1. Enable clocks ──────────────────────────────────────────
   SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1); 
   SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPA);
    // ── 2. Configure GPIO pins ────────────────────────────────────
    // SPI1 pins on Blue Pill:
    // PA5 = SCK  → AF push-pull output (CNF=10 MODE=11 = 0xB)
    // PA6 = MISO → floating input      (CNF=01 MODE=00 = 0x4)
    // PA7 = MOSI → AF push-pull output (CNF=10 MODE=11 = 0xB)
    // PA4 = NSS  → GPIO output manual  (CNF=00 MODE=11 = 0x3)
    GPIOx_t *GPIOA = GPIO('A'); 
    // Clear PA4, PA5, PA6, PA7 (bits 16-31 of CRL)
    GPIOA->CRL &= ~(0xFFFF << 16);

    GPIOA->CRL |= (0x3 << 16);   // PA4 output push-pull 50MHz (manual CS)
    GPIOA->CRL |= (0xB << 20);   // PA5 SCK  AF push-pull
    GPIOA->CRL |= (0x4 << 24);   // PA6 MISO floating input
    GPIOA->CRL |= (0xB << 28);   // PA7 MOSI AF push-pull

    // CS idle high
    GPIOA->BSRR = (1 << 4);

    // ── 3. Reset SPI1 before configuring ─────────────────────────
    SPI1->CR1 = 0;
    SPI1->CR2 = 0;
    
    // ── 4. Set clock mode (CPOL + CPHA) ──────────────────────────
    // Mode 0: CPOL=0 CPHA=0 
    // Mode 1: CPOL=0 CPHA=1
    // Mode 2: CPOL=1 CPHA=0
    // Mode 3: CPOL=1 CPHA=1
    switch (cfg.mode) {
        case 0: /* CPOL=0 CPHA=0 — default, nothing to set */ break;
        case 1: SET_BIT(SPI1->CR1, SPI1_CR1_CPHA); break;
        case 2: SET_BIT(SPI1->CR1, SPI1_CR1_CPOL); break;
        case 3: SET_BIT(SPI1->CR1, SPI1_CR1_CPHA | SPI1_CR1_CPOL); break;
    }

    // ── 5. Set baud rate ──────────────────────────────────────────
    // Baud divides APB2 clock (72MHz at full speed)
    // Use cfg.baudrate = SPI_CR1_BR_DIV8 for 9MHz
    SET_BIT(SPI1->CR1, cfg.baudrate);

    // ── 6. Master mode ────────────────────────────────────────────
    SET_BIT(SPI1->CR1,SPI_CR1_MSTR);

    // ── 7. Software NSS management ───────────────────────────────
    // We control CS manually via GPIO
    // SSM=1 + SSI=1 keeps internal NSS high → chip stays master
    SET_BIT(SPI1->CR1,SPI_CR1_SSM | SPI_CR1_SSI);

    // ── 8. Data frame size ────────────────────────────────────────
    if (cfg.datasize == 16) {
        SET_BIT(SPI1->CR1,SPI_CR1_DFF);   // 16-bit mode
    }
    // default is 8-bit, DFF=0

    // ── 9. Enable SPI — must be last  ─────────────────────────────
    SET_BIT(SPI1->CR1,SPI_CR1_SPE);
}
