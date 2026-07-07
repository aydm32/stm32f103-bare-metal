#include "rcc.h"
#include "gpio.h"
#include "uart.h"
#include "utils.h"

static void delay(volatile uint32_t n) { while (n--); }

int main(void) {
    rcc_status_t clk = rcc_init();

    gpio_set_mode(PIN('C', 13), GPIO_CNF_OUT_PP, GPIO_MODE_OUT_2MHZ);

    if (clk != RCC_OK) {
        // fast blink = rcc failed
        while (1) {
            gpio_set(PIN('C', 13), LOW);
            delay(100000);
            gpio_set(PIN('C', 13), HIGH);
            delay(100000);
        }
    }

    // slow blink = rcc ok, uart running
    uart1_init(9600);
    uart1_send_string("boot ok\r\n");

    while (1) {
        gpio_set(PIN('C', 13), LOW);
        delay(500000);
        gpio_set(PIN('C', 13), HIGH);
        delay(500000);
        uart1_send_string("tick\r\n");
    }
}
