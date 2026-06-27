#include <stdint.h>
// Stack and vector table
extern uint32_t _estack;
extern uint32_t _sdata, _edata, _sidata;
extern uint32_t _sbss, _ebss;

int main(void);
void Reset_Handler(void);
void Default_Handler(void) {
  while (1)
    ;
}

// Minimal vector table
__attribute__((section(".isr_vector"))) uint32_t vectors[] = {
    (uint32_t)&_estack,         // stack pointer
    (uint32_t)&Reset_Handler,   // reset
    (uint32_t)&Default_Handler, // NMI
    (uint32_t)&Default_Handler, // HardFault
};

void Reset_Handler(void) {
  uint32_t *src = &_sidata, *dst = &_sdata;
  while (dst < &_edata)
    *dst++ = *src++;
  dst = &_sbss;
  while (dst < &_ebss)
    *dst++ = 0;
  main();
}
