#include "gpio.h"
#include "utils.h"
#include "rcc.h"

void gpio_set_mode(uint32_t pin, uint8_t cnf, uint8_t mode) {
  uint16_t n = PINNO(pin);
  uint16_t bank = PINBANK(pin);
  SET_BIT(RCC->APB2ENR, BIT(bank + 2));
  GPIOx_t *gpio = GPIO(bank);
  volatile uint32_t *cr = (n > 7) ? &gpio->CRH : &gpio->CRL;
  uint8_t shift = (n % 8) * 4;
  MODIFY_REG(*cr, 0xFUL << shift, ((cnf << 2) | mode) << shift);
}

void gpio_set(uint32_t pin, uint8_t state) {
  uint16_t n = PINNO(pin);
  uint16_t bank = PINBANK(pin);
  GPIOx_t *gpio = GPIO(bank);
  SET_BIT(gpio->BSRR, BIT((state == HIGH) ? n : n + 16));
}

uint8_t gpio_read(uint32_t pin) {
  return (READ_BIT(GPIO(PINBANK(pin))->IDR, BIT(PINNO(pin))) != 0) ? HIGH : LOW;
}
