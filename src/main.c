#include "gpio.h"
#include "utils.h"
#include <stdint.h>

static void delay(volatile uint32_t n) {
  while (n--)
    ;
}

int main(void) {
  gpio_set_mode(PIN('A', 0), GPIO_CNF_OUT_PP, GPIO_MODE_OUT_2MHZ);
  gpio_set_mode(PIN('B', 15), GPIO_CNF_IN_PULLUPDN, GPIO_MODE_INPUT);
  while (1) {
    gpio_set(PIN('A', 0), gpio_read(PIN('B', 15)));
    delay(10000);
  }
}
