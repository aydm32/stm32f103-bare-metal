#include "utils.h"
#include "uart.h"
#include "rcc.h"


void uart1_init(uint32_t baud)
{
 SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPA);
 SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1); 
//TODO : we need to complete the uart function to get serial monitor work!! 
  




}
