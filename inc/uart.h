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

#define USART1 ((USARTx_t *)0x40013800UL)
#define USART2 ((USARTx_t *)0x40004400UL)

//============= Status Register (SR) =============
#define USART_SR_RXNE BIT(5) // Read data register not empty
#define USART_SR_TXE BIT(7)  // Transmit data register empty

//============= Control Register (CR1) ===============
#define USART_CR1_UE BIT(13) // USART enable
#define USART_CR1_TE BIT(3)  // Transmitter enable
#define USART_CR1_RE BIT(2)  // Receiver enable

void uart1_init(uint32_t baud);
void uart1_init_hz(uint32_t baud, uint32_t apb2_clock_hz);
void uart1_send_byte(uint8_t c);
void uart1_send_string(const char *s);
uint8_t uart1_recv_byte(void);

#endif // !UART_H
