#include "rcc.h"
#include "gpio.h"
#include "uart.h"
#include "utils.h"

static void delay(volatile uint32_t n) { while (n--); }

int main(void)
{
    uart1_init_hz(9600, 8000000);

    while (1)
    {
        uart1_send_string("STM32 UART OK\r\n");

        for (volatile uint32_t i = 0; i < 800000; i++);
    }
}
