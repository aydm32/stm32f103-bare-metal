#include "spi.h"
#include "rcc.h"
#include "gpio.h" 
#include "utils.h"


void spi1_init(SPI_Config cfg)
{
   // 1. Clocks
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPA);
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1);

    // 2. GPIO
    // cfg.cs_pin → output PP manual CS (caller picks the pin; SCK/MISO/MOSI
    //              stay fixed to PA5/PA6/PA7 since those are wired to the
    //              SPI1 peripheral itself and can't move)
    // PA5 SCK  → AF push-pull
    // PA6 MISO → floating input
    // PA7 MOSI → AF push-pull
    gpio_set_mode(cfg.cs_pin,  GPIO_CNF_OUT_PP,   GPIO_MODE_OUT_50MHZ);
    gpio_set_mode(PIN('A', 5), GPIO_CNF_OUT_AFPP, GPIO_MODE_OUT_50MHZ);
    gpio_set_mode(PIN('A', 6), GPIO_CNF_IN_FLOAT,  GPIO_MODE_INPUT);
    gpio_set_mode(PIN('A', 7), GPIO_CNF_OUT_AFPP, GPIO_MODE_OUT_50MHZ);

    // CS idle high
    gpio_set(cfg.cs_pin, HIGH);

    // 3. Configure SPI1
    SPI1->CR1 = 0;
    SPI1->CR2 = 0;

    // 4. Mode (CPOL + CPHA)
    switch (cfg.mode) {
        case 0: break;
        case 1: SET_BIT(SPI1->CR1, SPI_CR1_CPHA); break;
        case 2: SET_BIT(SPI1->CR1, SPI_CR1_CPOL); break;
        case 3: SET_BIT(SPI1->CR1, SPI_CR1_CPOL | SPI_CR1_CPHA); break;
    }

    // 5. Baud rate
    MODIFY_REG(SPI1->CR1, BITS(0x7, 3), cfg.baudrate);

    // 6. Master + software NSS
    SET_BIT(SPI1->CR1, SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI);

    // 7. Data size
    if (cfg.datasize == 16)
        SET_BIT(SPI1->CR1, SPI_CR1_DFF);

    // 8. Enable — last
    SET_BIT(SPI1->CR1, SPI_CR1_SPE);
}

// Bare transfer, no error-flag checking. During bring-up you want this path
// as short as possible: TXE wait -> write -> RXNE wait -> read -> BSY wait.
// If SPI comes back wrong here, the bug is almost always wiring, clock mode,
// or baud rate — not MODF/OVR — so checking those flags on every byte just
// adds cycles without adding information at this stage.
uint8_t spi1_transfer(uint8_t data) {
    while (!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = data;
    while (!(SPI1->SR & SPI_SR_RXNE));
    uint8_t rx = (uint8_t)SPI1->DR;
    while (SPI1->SR & SPI_SR_BSY);
    return rx;
}

// Explicit fault recovery — call this yourself if you suspect a bus error
// (e.g. after adding a second SPI master on the bus in a later phase, where
// MODF becomes a real possibility). Reading SR then DR clears MODF/OVR/
// CRCERR per the reference manual; toggling SPE reinitializes the shift
// logic in case a transfer was left mid-frame.
void spi1_clear_errors(void) {
    if (SPI1->SR & (SPI_SR_OVR | SPI_SR_MODF | SPI_SR_CRCERR)) {
        (void)SPI1->SR;
        (void)SPI1->DR;
        CLEAR_BIT(SPI1->CR1, SPI_CR1_SPE);
        SET_BIT(SPI1->CR1, SPI_CR1_SPE);
    }
}

void spi1_send(const uint8_t *buf, uint32_t len)
{
  for(uint32_t i = 0 ; i < len ; ++i)
  {
    spi1_transfer(buf[i]);
  }
}

void spi1_recv(uint8_t *buf, uint32_t len)
{
  for (uint32_t i = 0 ; i < len ; ++i) {
  buf[i] = spi1_transfer(0xFF);
  }
}

void spi1_transfer_buf(const uint8_t *tx, uint8_t *rx, uint32_t len)
{
  for (uint32_t i = 0 ; i < len; i++) {
    rx[i] = spi1_transfer(tx[i]);
  }
}

/* 
  uint16_t spi1_transfer16(uint16_t data) {
    while (!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = data;  // 16‑bit write
    while (!(SPI1->SR & SPI_SR_RXNE));
    uint16_t rx = (uint16_t)SPI1->DR;
    while (SPI1->SR & SPI_SR_BSYR);
    return rx;
}

void spi1_send16(const uint16_t *buf, uint32_t len) {
    for (uint32_t i = 0; i < len; i++)
        spi1_transfer16(buf[i]);
}

void spi1_recv16(uint16_t *buf, uint32_t len) {
    for (uint32_t i = 0; i < len; i++)
        buf[i] = spi1_transfer16(0xFFFF);
}

void spi1_transfer_buf16(const uint16_t *tx, uint16_t *rx, uint32_t len) {
    for (uint32_t i = 0; i < len; i++)
        rx[i] = spi1_transfer16(tx[i]);
}

*/











