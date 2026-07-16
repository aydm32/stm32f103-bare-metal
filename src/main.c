#include "uart.h"

static void delay(volatile uint32_t n) { while (n--); }
// This Code is for testing UART driver 
int main(void)
{
    uart1_init_hz(9600, 8000000);

    while (1)
    {
        uart1_send_string("STM32 UART OK\r\n");
        delay(800000);
    }
}
