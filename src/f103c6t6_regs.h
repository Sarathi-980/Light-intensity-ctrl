#ifndef F103C6T6_REGS_H
#define F103C6T6_REGS_H

#include <stdint.h>

// ==============================================================
// Peripheral Base Addresses and register access
// ==============================================================
#define RCC_BASE	                (0x40021000U)    // Reset and Clock Control peripheral 
typedef struct
{
    volatile uint32_t RCC_CR;           // Clock control register. reset value - 0x00
    volatile uint32_t RCC_CFGR;         // clock configuration register. reset value - 0x00
    volatile uint32_t RCC_CIR;          // clock interrupt register. reset value - 0x00
    volatile uint32_t RCC_APB2RSTR;     // APB2 peripheral reset register. reset value - 0x00
    volatile uint32_t RCC_APB1RSTR;     // APB1 peripheral reset register. reset value - 0x00
    volatile uint32_t RCC_AHBENR;       // AHB peripheral enable register. reset value - 0x14
    volatile uint32_t RCC_APB2ENR;      // APB2 peripheral enable register. reset value - 0x00
    volatile uint32_t RCC_APB1ENR;      // APB1 peripheral enable register. reset value - 0x00
    volatile uint32_t RCC_BDCR;         // Backup domain control register. reset value - 0x00
    volatile uint32_t RCC_CSR;          // Control status register. reset value - 0x0C000000
}   RCC_registers_t;

#define RCC_REGISTERS_ADDR          ((RCC_registers_t *) RCC_BASE)   // RCC struct base address, can able to access registers using offset of struct members.

// RCC clock register
#define RCC_CR_PLL_READY_MASK       (1U << 25U)     // The flag set by hardware to indicate PLL clock is locked.
#define RCC_CR_PLL_ON_MASK          (1U << 24U)     // Set by software to enable PLL clock.
#define RCC_CR_CSS_ON_MASK          (1U << 19U)     // set by software to enable clock security system. it monitors HSE and produce NMI if instability in HSE
// Set by software to bypass the oscillator with external clock. 
// Using this we can stop internal amplifier, because external HSE (IC's) no need of power input from MCU
#define RCC_CR_HSEBYP_MASK          (1U << 18U)    
#define RCC_CR_HSE_READY_FLAG_MASK  (1U << 17U)     // The flag set by hardware to indicate HSE(high speed clock) is enabled.
#define RCC_CR_HSE_ENABLE_MASK      (1U << 16U)     // Enabling HSE clock
#define RCC_CR_HSI_READY_FLAG_MASK  (1U << 1U)     // The flag set by hardware to indicate HSI(internal clock) is enabled.
#define RCC_CR_HSI_ENABLE_MASK      (1U << 0U)     // Enabling HSI clock

// RCC clock configuration register
#define RCC_CFG_PLL_SRC_HSI_EN      (0 << 15)       // enabling HSI
#define RCC_CFG_PLL_SRC_HSE_EN      (1 << 16)       // setting prediv1 EN_MASKs HSE

#define RCC_PLL_CLOCK_EN_MASK       (1 << 24)       // Enabling PLL using Clock control register

// Rcc configuration register
#define RCC_CFG_MCO_MASK            (0x7 << 24U)    // MCU clock output, outputs clock signal via pin PA8. used to verify the clock signal.
#define RCC_CFG_USB_PRESCALSE_MASK  (1U << 22U)     // Used to generate 48 MHz USB clock signal. this must be valid before enable USB clock in APB1.
#define RCC_CFG_PLL_MUL_MASK        (0xFU << 18U)   // bits [21:18]. The PLL multiplication factor only writable when PLL is disabled.
#define RCC_CFG_PLLXPRE_MASK        (1U << 17U)     // Used to divide the PLL clock frequency by 2. PLL must be disabled before write.
#define RCC_CFG_PLL_SRC_MASK        (1U << 16U)     // Which clock is selected as source of PLL.
#define RCC_CFG_ADCPRE_MASK         (3U << 14U)     // Frequency of the clock to the ADC
#define RCC_CFG_PPRE2_MASK          (7U << 11U)     // controls factor of the APB2 high speed clock
#define RCC_CFG_PPRE1_MASK          (3U << 8U)      // controls factor of the APB1 low speed clock
#define RCC_CFG_HPRE_MASK           (0xF << 4U)     // controls factor of the AHB high speed clock
#define RCC_CFG_SWS_MASK            (3U << 2U)      // set by hardware to indicate which clock source is selected as system clock
#define RCC_CFG_SW_MASK             (3U << 0U)      // selecting system clock source either HSI, HSE, PLL   

#define RCC_CFG_PLL_MUL_POS         (18U)
#define RCC_CFG_PPRE1_POS           (8U)

// AHB peripheral clock enable register
#define RCC_AHB_SDIO_EN_MASK        (1U << 10U)     // secure digital input output clock 
#define RCC_AHB_FSMC_EN_MASK        (1U << 8U)      // Flexible static memory controller
#define RCC_AHB_CRC_EN_MASK         (1U << 6U)      // CRC clock, verify data integrity without software
#define RCC_AHB_FLITF_EN_MASK       (1U << 4U)      // FLASH interface clock enable during sleep, enabled by default, if disabled the interrupt latency will occur when it wake up from sleep.
#define RCC_AHB_SRAM_EN_MASK        (1U << 2U)      // SRAM interface clock enable during sleep, enabled by default, if disabled delayed execution when it wake up from sleep and DMA error will occur.
#define RCC_AHB_DMA2_EN_MASK        (1U << 1U)      // DMA2 enable 
#define RCC_AHB_DMA1_EN_MASK        (1U << 0)       // DMA1 enable

// APB2 peripheral clock enable register
#define RCC_APB2_TIMER11_EN_MASK    (1U << 21U)
#define RCC_APB2_TIMER10_EN_MASK    (1U << 20U)
#define RCC_APB2_TIMER9_EN_MASK     (1U << 19U)
#define RCC_APB2_ADC3_EN_MASK       (1U << 15U)
#define RCC_APB2_USART1_EN_MASK     (1U << 14U)
#define RCC_APB2_TIMER8_EN_MASK     (1U << 13U)
#define RCC_APB2_SPI1_EN_MASK       (1U << 12U)
#define RCC_APB2_TIMER1_EN_MASK     (1U << 11U)
#define RCC_APB2_ADC2_EN_MASK       (1U << 10U)
#define RCC_APB2_ADC1_EN_MASK       (1U << 9U)
#define RCC_APB2_GPIOG_EN_MASK      (1U << 8U)
#define RCC_APB2_GPIOF_EN_MASK      (1U << 7U)
#define RCC_APB2_GPIOE_EN_MASK      (1U << 6U)
#define RCC_APB2_GPIOD_EN_MASK      (1U << 5U)
#define RCC_APB2_GPIOC_EN_MASK      (1U << 4U)
#define RCC_APB2_GPIOB_EN_MASK      (1U << 3U)
#define RCC_APB2_GPIOA_EN_MASK      (1U << 2U)
#define RCC_APB2_AFIO_EN_MASK       (1U << 0)       // alternate function input output clock enable

// APB1 peripheral clock enable register
#define RCC_APB1_DAC_EN_MASK        (1U << 29U)     // DAC(digital to anablog) interface clock
#define RCC_APB1_POWER_EN_MASK      (1U << 28U)     // Power clock interface 
#define RCC_APB1_BKP_EN_MASK        (1U << 27U)     // backup interface clock
#define RCC_APB1_CAN_EN_MASK        (1U << 25U)     // CAN clock enable
#define RCC_APB1_USB_EN_MASK        (1U << 23U)     // USB clock enable
#define RCC_APB1_I2C2_EN_MASK       (1U << 22U)
#define RCC_APB1_I2C1_EN_MASK       (1U << 21U)
#define RCC_APB1_UART5_EN_MASK      (1U << 20U)
#define RCC_APB1_UART4_EN_MASK      (1U << 19U)
#define RCC_APB1_USART3_EN_MASK     (1U << 18U)
#define RCC_APB1_USART2_EN_MASK     (1U << 17U)
#define RCC_APB1_SPI3_EN_MASK       (1U << 15U)
#define RCC_APB1_SPI2_EN_MASK       (1U << 14U)
#define RCC_APB1_WWDGEN_MASK        (1U << 11U)     // window watchdog clock
#define RCC_APB1_TIMER14_EN_MASK    (1U << 8U)
#define RCC_APB1_TIMER13_EN_MASK    (1U << 7U)
#define RCC_APB1_TIMER12_EN_MASK    (1U << 6U)
#define RCC_APB1_TIMER7_EN_MASK     (1U << 5U)
#define RCC_APB1_TIMER6_EN_MASK     (1U << 4U)
#define RCC_APB1_TIMER5_EN_MASK     (1U << 3U)
#define RCC_APB1_TIMER4_EN_MASK     (1U << 2U)
#define RCC_APB1_TIMER3_EN_MASK     (1U << 1U)
#define RCC_APB1_TIMER2_EN_MASK     (1U << 0)

// Backup domain control register
#define RCC_BDCR_BDRST_EN_MASK      (1U << 16U)     // Backup domain software reset
#define RCC_BDCR_RTC_EN_MASK        (1U << 15U)     // RTC clock enable
#define RCC_BDCR_RTCSEL_MASK        (3U << 8U)      // RTC clock source selection
#define RCC_BDCR_LSEBYP_MASK        (1U << 2U)      // External low-speed oscillator bypass
#define RCC_BDCR_LSE_READY_MASK     (1U << 1U)      // External low-speed oscillator ready flag
#define RCC_BDCR_LSE_ON_MASK        (1U << 0)       // External low-speed oscillator enable


#define FLASH_ACR_REG                       (* (volatile uint32_t*) (0x40022000))    // Flash access control register, reset value : 0x30
#define FLASH_ACR_PREFETCH_BUF_STATUS_MASK  (1U << 5U)
#define FLASH_ACR_PREFETCH_BUF_EN_MASK      (1U << 4U)
#define FLASH_ACR_HALF_CYCLE_EN_MASK        (1U << 3U)
#define FLASH_ACR_LATENCY_MASK              (7U << 0)

// SCS register
#define SYSTEM_CONTROL_SPACE_REG_ADDR       (* (volatile uint32_t*) (0xE000E000))
#define SYSTICK_CONTROL_STATUS_REG_ADDR     (* (volatile uint32_t*) (0xE000E010))
#define SYSTICK_RELOAD_REG_ADDR             (* (volatile uint32_t*) (0xE000E014))       // bits[23 : 0] Reload value when timer reaches 0
#define SYSTICK_CURRENT_VAL_REG_ADDR        (* (volatile uint32_t*) (0xE000E018))       // Current value of the timer. write to clear register.
#define SYSTICK_TIMER_ENABLE_MASK           (1U << 0)       // Systick timer enable
#define SYSTICK_INTERRUPT_ENABLE_MASK       (1U << 1U)      // Tick interrupt generation enable
#define SYSTICK_CLK_SOURCE_MASK             (1U << 2U)      // clock source either processer clock or external clock
#define SYSTICK_COUNT_FLAG_MASK             (1U << 16U)     // set by hardware as 1 if counter reaches 0

// GPIO (general purpose input and output) and AFIO (alternate function input and output)
#define AFIO_BASE               (0x40010000UL)
#define EXTI_BASE               (0x40010400UL)

#define GPIOA_BASE              (0x40010800UL)
#define GPIOB_BASE              (0x40010C00UL)
#define GPIOC_BASE              (0x40011000UL)
#define GPIOD_BASE              (0x40011400UL)
#define GPIOE_BASE              (0x40011800UL)
#define GPIOF_BASE              (0x40011C00UL)
#define GPIOG_BASE              (0x40012000UL) 


#endif