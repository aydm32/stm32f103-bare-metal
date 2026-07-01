#ifndef UART_H
#define UART_H

#include "utils.h"
#include <stdint.h>

typedef struct {
  volatile uint32_t SR;   //  Status register
  volatile uint32_t DR;   // Data register
  volatile uint32_t BRR;  // Baud rate register
  volatile uint32_t CR1;  // Control register 1
  volatile uint32_t CR2;  // Control register 2
  volatile uint32_t CR3;  // Control register 3
  volatile uint32_t GTPR; // Guard time and prescaler register
} USARTx_t;

#define USART1 ((USARTx_t *)0x40013800)
#define USART2 ((USARTx_t *)0x40004400)

//============= Status Register (SR) =============
#define USART_SR_PE BIT(0)   // Parity error
#define USART_SR_FE BIT(1)   // Framing error
#define USART_SR_NE BIT(2)   // Noise error flag
#define USART_SR_ORE BIT(3)  // Overrun error
#define USART_SR_IDLE BIT(4) // IDLE line detected
#define USART_SR_RXNE BIT(5) // Read data register not empty
#define USART_SR_TC BIT(6)   // Transmission complete
#define USART_SR_TXE BIT(7)  // Transmit data register empty
#define USART_SR_LBD BIT(8)  // LIN break detection flag
#define USART_SR_CTS BIT(9)  // CTS flag

//============= Control Register (CR1) ===============

#define USART_CR1_UE BIT(13)    // USART enable
#define USART_CR1_M BIT(12)     // Word length
#define USART_CR1_WAKE BIT(11)  // Wakeup method
#define USART_CR1_PCE BIT(10)   // Parity control enable
#define USART_CR1_PS BIT(9)     // Parity selection
#define USART_CR1_PEIE BIT(8)   // PE interrupt enable
#define USART_CR1_TXEIE BIT(7)  // TXE interrupt enable
#define USART_CR1_TCIE BIT(6)   // Transmission complete interrupt enable
#define USART_CR1_RXNEIE BIT(5) // RXNE interrupt enable
#define USART_CR1_IDLEIE BIT(4) // IDLE interrupt enable
#define USART_CR1_TE BIT(3)     // Transmitter enable
#define USART_CR1_RE BIT(2)     // Receiver enable
#define USART_CR1_RWU BIT(1)    // Receiver wakeup
#define USART_CR1_SBK BIT(0)    // Send break

void uart1_init(uint32_t baud);
void uart1_putc(char c);
void uart1_puts(const char *s);
void uart1_puthex8(uint8_t val);
void uart1_puthex32(uint32_t val);
void uart1_putdec(uint32_t val);
uint8_t uart1_getc(void);
uint8_t uart1_available(void);

#endif // !UART_H
