#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sdata, _edata, _sidata;
extern uint32_t _sbss,  _ebss;

int  main(void);
void Reset_Handler(void);

/* Any unhandled exception lands here and spins so a debugger can catch it */
void Default_Handler(void) { while (1); }

/* Weak aliases — define a real handler with the same name to override */
void NMI_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)    __attribute__((weak, alias("Default_Handler")));

/* STM32F103 peripheral IRQ handlers (weak — override as needed) */
void WWDG_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void PVD_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void TAMPER_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void RTC_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void FLASH_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void RCC_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void EXTI0_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void EXTI1_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void EXTI2_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void EXTI3_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void EXTI4_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void ADC1_2_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void USB_HP_CAN_TX_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USB_LP_CAN_RX0_IRQHandler(void)__attribute__((weak, alias("Default_Handler")));
void CAN_RX1_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void CAN_SCE_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void TIM1_UP_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void TIM1_TRG_COM_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void TIM2_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void TIM4_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void USART3_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler(void)     __attribute__((weak, alias("Default_Handler")));
void RTCAlarm_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void USBWakeUp_IRQHandler(void)     __attribute__((weak, alias("Default_Handler")));

__attribute__((section(".isr_vector")))
void (*const vectors[])(void) = {
    /* ── Cortex-M3 system exceptions ───────────────────────────── */
    (void (*)(void))&_estack,  /* 0x00: initial stack pointer       */
    Reset_Handler,             /* 0x04: reset                       */
    NMI_Handler,               /* 0x08: NMI                         */
    HardFault_Handler,         /* 0x0C: hard fault                  */
    MemManage_Handler,         /* 0x10: memory management fault     */
    BusFault_Handler,          /* 0x14: bus fault                   */
    UsageFault_Handler,        /* 0x18: usage fault                 */
    0, 0, 0, 0,                /* 0x1C-0x28: reserved               */
    SVC_Handler,               /* 0x2C: SVCall                      */
    DebugMon_Handler,          /* 0x30: debug monitor               */
    0,                         /* 0x34: reserved                    */
    PendSV_Handler,            /* 0x38: PendSV                      */
    SysTick_Handler,           /* 0x3C: SysTick                     */

    /* ── STM32F103 peripheral IRQs (position 0-42) ──────────────── */
    WWDG_IRQHandler,           /*  0 */
    PVD_IRQHandler,            /*  1 */
    TAMPER_IRQHandler,         /*  2 */
    RTC_IRQHandler,            /*  3 */
    FLASH_IRQHandler,          /*  4 */
    RCC_IRQHandler,            /*  5 */
    EXTI0_IRQHandler,          /*  6 */
    EXTI1_IRQHandler,          /*  7 */
    EXTI2_IRQHandler,          /*  8 */
    EXTI3_IRQHandler,          /*  9 */
    EXTI4_IRQHandler,          /* 10 */
    DMA1_Channel1_IRQHandler,  /* 11 */
    DMA1_Channel2_IRQHandler,  /* 12 */
    DMA1_Channel3_IRQHandler,  /* 13 */
    DMA1_Channel4_IRQHandler,  /* 14 */
    DMA1_Channel5_IRQHandler,  /* 15 */
    DMA1_Channel6_IRQHandler,  /* 16 */
    DMA1_Channel7_IRQHandler,  /* 17 */
    ADC1_2_IRQHandler,         /* 18 */
    USB_HP_CAN_TX_IRQHandler,  /* 19 */
    USB_LP_CAN_RX0_IRQHandler, /* 20 */
    CAN_RX1_IRQHandler,        /* 21 */
    CAN_SCE_IRQHandler,        /* 22 */
    EXTI9_5_IRQHandler,        /* 23 */
    TIM1_BRK_IRQHandler,       /* 24 */
    TIM1_UP_IRQHandler,        /* 25 */
    TIM1_TRG_COM_IRQHandler,   /* 26 */
    TIM1_CC_IRQHandler,        /* 27 */
    TIM2_IRQHandler,           /* 28 */
    TIM3_IRQHandler,           /* 29 */
    TIM4_IRQHandler,           /* 30 */
    I2C1_EV_IRQHandler,        /* 31 */
    I2C1_ER_IRQHandler,        /* 32 */
    I2C2_EV_IRQHandler,        /* 33 */
    I2C2_ER_IRQHandler,        /* 34 */
    SPI1_IRQHandler,           /* 35 */
    SPI2_IRQHandler,           /* 36 */
    USART1_IRQHandler,         /* 37 */
    USART2_IRQHandler,         /* 38 */
    USART3_IRQHandler,         /* 39 */
    EXTI15_10_IRQHandler,      /* 40 */
    RTCAlarm_IRQHandler,       /* 41 */
    USBWakeUp_IRQHandler,      /* 42 */
};

void Reset_Handler(void) {
    /* Copy .data section from flash to SRAM */
    uint32_t *src = &_sidata, *dst = &_sdata;
    while (dst < &_edata)
        *dst++ = *src++;

    /* Zero-initialise .bss section */
    dst = &_sbss;
    while (dst < &_ebss)
        *dst++ = 0;

    main();

    /* Should never reach here */
    while (1);
}
