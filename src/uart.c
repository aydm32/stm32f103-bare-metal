#include "utils.h"
#include "uart.h"
#include "rcc.h"
#include "gpio.h"


void uart1_init_hz(uint32_t baud, uint32_t apb2_clock_hz)
{
  // 1. Clocks 
 SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPA); // Enable clock for port A 
 SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1);  // Enable clock for USART 1

  // 2. PA9 TX → AF push-pull, PA10 RX → floating input
gpio_set_mode(PIN('A', 9), GPIO_CNF_OUT_AFPP, GPIO_MODE_OUT_50MHZ);
gpio_set_mode(PIN('A', 10),GPIO_CNF_IN_FLOAT,GPIO_MODE_INPUT);
 
 // 3. Baud rate 
USART1->BRR = apb2_clock_hz / baud;

// 4. Enable TX + RX + USART 
SET_BIT(USART1->CR1,USART_CR1_TE | USART_CR1_RE | USART_CR1_UE);
}

void uart1_init(uint32_t baud)
{
  // Default path — assumes rcc_init() succeeded and APB2 is running at 72MHz.
  uart1_init_hz(baud, 72000000UL);
}

void uart1_send_byte(uint8_t c) {
    while (!READ_BIT(USART1->SR, USART_SR_TXE));
    USART1->DR = c;
}

uint8_t uart1_recv_byte(void) {
    while (!READ_BIT(USART1->SR, USART_SR_RXNE));
    return (uint8_t)USART1->DR;
}

void uart1_send_string(const char *s) {
    while (*s) uart1_send_byte((uint8_t)*s++);
 }

static char nibble_to_hex(uint8_t n) {
    return (n < 10) ? ('0' + n) : ('A' + (n - 10));
}
 
void uart1_send_hex_byte(uint8_t val) {
    uart1_send_string("0x");
    uart1_send_byte((uint8_t)nibble_to_hex((val >> 4) & 0xF));
    uart1_send_byte((uint8_t)nibble_to_hex(val & 0xF));
}

