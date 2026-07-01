#ifndef SPI_H
#define SPI_H
#include "utils.h"
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

// ===================== SPI1 - Control Register 1 - Bits ======================
#define SPI_CR1_CPHA BIT(0)          // Clock Phase
#define SPI_CR1_CPOL BIT(1)          // Clock Polarity
#define SPI_CR1_MSTR BIT(2)          // Master Selection
#define SPI_CR1_BR_DIV2 BITS(0, 3)   // Baud rate control  f_clk / 2
#define SPI_CR1_BR_DIV4 BITS(1, 3)   // f_clk / 4
#define SPI_CR1_BR_DIV8 BITS(2, 3)   // f_clk / 8
#define SPI_CR1_BR_DIV16 BITS(3, 3)  // f_clk / 16
#define SPI_CR1_BR_DIV32 BITS(4, 3)  // f_clk / 32
#define SPI_CR1_BR_DIV64 BITS(5, 3)  // f_clk / 64
#define SPI_CR1_BR_DIV128 BITS(6, 3) // f_clk / 128
#define SPI_CR1_BR_DIV256 BITS(7, 3) // f_clk / 256
#define SPI_CR1_SPE BIT(6)           // SPI Enable
#define SPI_CR1_LSBF BIT(7)          // Frame Format
#define SPI_CR1_SSI BIT(8)           // Internal Select
#define SPI_CR1_SSM BIT(9)           // Software Slave Management Enable
#define SPI_CR1_RXONLY BIT(10)       // Receive Only
#define SPI_CR1_DFF BIT(11)          // Data Frame Format
#define SPI_CR1_CRCNEXT BIT(12)      // CRC transfer next
#define SPI_CR1_CRCEN BIT(13)        // Hardware CRC calculation enable
#define SPI_CR1_BIDIOE BIT(14)       // Output enable in bidirectional mode
#define SPI_CR1_BIDIMODE BIT(15)     // Bidirectional data mode enable

//==================== SPI1 - Control Register 2 - Bits
#define SPI_CR2_TXEIE BIT(7)   // Tx Buffer empty interrupt enable
#define SPI_CR2_RXNEIE BIT(6)  // Rx Buffer not empty interrupt enable
#define SPI_CR2_ERRIE BIT(5)   // Error interrupt enable
#define SPI_CR2_SSOE BIT(2)    // SS output enable
#define SPI_CR2_TXDMAEN BIT(1) // Tx buffer DMA enable
#define SPI_CR2_RXDMAEN BIT(0) // Rx buffer DMA enable

//==================== SPI1 - Status Register - Bits
#define SPI_SR_BSYR BIT(7)   // Busy flag
#define SPI_SR_OVR BIT(6)    // Overrun flag
#define SPI_SR_MODF BIT(5)   // Mode fault
#define SPI_SR_CRCERR BIT(4) // CRC error flag
#define SPI_SR_UDR BIT(3)    // Underrun
#define SPI_SR_CHSIDE BIT(2) // Channel side
#define SPI_SR_TXE BIT(1)    // Transmit buffer empty
#define SPI_SR_RXNE BIT(0)   // Receive buffer not empty

// ================= SPI1 - SPI_I2S Configuration register - Bits
#define SPI_I2SCFG_I2SMOD BIT(11) // I2S mode selection
#define SPI_I2SCFG_I2SE BIT(10)   // I2S Enable
#define SPI_I2SCFG_I2SCFG_ST                                                   \
  BITS(0, 9) // I2S Configuration mode - Slave - transmit
#define SPI_I2SCFG_I2SCFG_SR BITS(1, 9) // Slave - receive
#define SPI_I2SCFG_I2SCFG_MT BITS(2, 9) // Master - transmit
#define SPI_I2SCFG_I2SCFG_MR BITS(3, 9) // Master - receive
#define SPI_I2SCFG_PCMSYNC BIT(7)       // PCM frame synchronization
#define SPI_I2SCFG_I2SSTD_I2S                                                  \
  BITS(0, 5) // I2S standard selection - I2S Philips standard
#define SPI_I2SCFG_I2SSTD_MSB BITS(1, 5) // MSB justified standard
#define SPI_I2SCFG_I2SSTD_LSB BITS(2, 5) // LSB justified standard
#define SPI_I2SCFG_I2SSTD_PCM BITS(3, 5) // PCM standard
#define SPI_I2SCFG_I2SSTD_CKPOL BIT(3)   // Steady state clock polarity
#define SPI_I2SCFG_DATLEM_16BIT                                                \
  BITS(0, 2) // Data length to be transferred - 16-bit data length
#define SPI_I2SCFG_DATLEM_24BIT BITS(1, 2) // 24-bit data length
#define SPI_I2SCFG_DATLEM_32BIT BITS(2, 2) // 32-bit data length
#define SPI_I2SCFG_CHLEN                                                       \
  BIT(0) // Channel length (number of bits per audio channeil)

//=============== Prescaler register ==================
#define SPI_I2SPR_MCKOE BIT(9) // Master clock output enable
#define SPI_I2SPR_ODD BIT(8)   // Odd factor for the Prescaler

// CS control — caller defines which pin
// Usage: SPI1_CS_LOW(GPIOA, 4)
#define SPI_CS_LOW(port, pin) SET_BIT((port)->BSRR, (pin) + 16)
#define SPI_CS_HIGH(port, pin) SET_BIT((port)->BSRR, (pin))

typedef struct {
  uint8_t mode;      // 0,1,2,3 → CPOL/CPHA combination
  uint32_t baudrate; // use SPI_CR1_BR_DIVx defines
  uint8_t datasize;  // 8 or 16
} SPI_Config;

void spi1_init(SPI_Config cfg);
uint8_t spi1_transfer(uint8_t data);
void spi1_send(const uint8_t *buf, uint32_t len);
void spi1_recv(uint8_t *buf, uint32_t len);
void spi1_transfer_buf(const uint8_t *tx, uint8_t *rx, uint32_t len);

#endif // !SPI_T
