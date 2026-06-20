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

#define TIMER2_BASE             (0x40000000UL)

typedef struct
{
    // Timer control registers
    volatile uint32_t TIMx_CR1;
    volatile uint32_t TIMx_CR2;
    // Slave mode control register
    volatile uint32_t TIMx_SMCR;
    // DMA / interrupt enable register
    volatile uint32_t TIMx_DIER;
    // Status register
    volatile uint32_t TIMx_SR;
    // Event generation register
    volatile uint32_t TIMx_EGR;
    // Capture / Compare mode register
    volatile uint32_t TIMx_CCMR1;
    volatile uint32_t TIMx_CCMR2;
    // Capture / Compare enable register
    volatile uint32_t TIMx_CCER;
    // Counter value [15 : 0]
    volatile uint32_t TIMx_CNT;
    // Prescaler value. The counter clock frequency CK_CNT is equal to timer_input_clock / (PSC + 1) 
    volatile uint32_t TIMx_PSC;
    // Auto reload register holds prescaler value [15 : 0], will be loaded into actual auto-reload register
    volatile uint32_t TIMx_ARR;
    // Capture/Compare registers, value[15 : 0] based configured as capture mode or compare mode.
    volatile uint32_t TIMx_CCR1;
    volatile uint32_t TIMx_CCR2;
    volatile uint32_t TIMx_CCR3;
    volatile uint32_t TIMx_CCR4;
    /* TIMx_DCR : DMA control register. It contains DBL - DMA burst length and
       DBA - DMA base address. If DBL is 5 transfers and DBA is TIMx_CR1 then
       transfer done from/to 5 registers from the TIMx_CR1 address.*/    
    volatile uint32_t TIMx_DCR;
    /*  TIMx_DMAR: Timer x DMA address for full transfer. 
        offset: 0x4C, DMAB[15 : 0] DMA register for burst accesses.
        A read or write operation to this register accesses the 
        register located at the address (TIMx_CR1 address) + (DBA + DMA index) * 4
        CR1 -> address of control register 1.
        DBA -> address of DMA base address.
        DMA index -> automatically controlled by the DMA transfer.
    */
    volatile uint32_t TIMx_DMAR;
}   TIMx_registers_t;

#define TIMER1_BASE_ADDRESS         (0x40012C00U)
#define TIMER2_BASE_ADDRESS         (0x40000000U)
#define TIMER3_BASE_ADDRESS         (0x40000400U)
#define TIMER4_BASE_ADDRESS         (0x40000800U)
#define TIMER5_BASE_ADDRESS         (0x40000C00U)
#define TIMER6_BASE_ADDRESS         (0x40001000U)
#define TIMER7_BASE_ADDRESS         (0x40001400U)
#define TIMER8_BASE_ADDRESS         (0x40013400U)
#define TIMER9_BASE_ADDRESS         (0x40014C00U)
#define TIMER10_BASE_ADDRESS        (0x40015000U)
#define TIMER11_BASE_ADDRESS        (0x40015400U)
#define TIMER12_BASE_ADDRESS        (0x40001800U)
#define TIMER13_BASE_ADDRESS        (0x40001C00U)
#define TIMER14_BASE_ADDRESS        (0x40002000U)

#define GENERAL_TIMER_REGISTERS(base)       ((TIMx_registers_t *) (base))

// Control register 1
#define TIMx_CR1_CKD_MASK           (0x3 << 8)      // Clock division value between timer clock and sampling clock
#define TIMx_CR1_APRE_MASK          (1UL << 7UL)    // Auto-reload preload enable
#define TIMx_CR1_ARPE_MASK          (1UL << 7UL)    // Auto-reload preload enable
#define TIMx_CR1_CMS_MASK           (3UL << 5UL)    // Center Aligned Mode value
#define TIMx_CR1_DIR_MASK           (1UL << 4UL)    // Direction of counter
#define TIMx_CR1_OPM_MASK           (1UL << 3UL)    // One pulse mode
#define TIMx_CR1_URS_MASK           (1UL << 2UL)    // Update request source
#define TIMx_CR1_UDIS_MASK          (1UL << 1UL)    // Update disable
#define TIMx_CR1_CEN_MASK           (1UL << 0UL)    // Counter enable

// Timer Capture Compare Mode register 1, address offset : 0x18
// This channel can be used in input (capture mode) and in output (compare mode).

// Output compare mode 

#define TIMx_CCMR1_CC1S_POS         (0U)
#define TIMx_CCMR1_OUT_OC1FE_POS    (2U)
#define TIMx_CCMR1_OUT_OC1PE_POS    (3U)
#define TIMx_CCMR1_OUT_OC1M_POS     (4U)
#define TIMx_CCMR1_OUT_OC1CE_POS    (7U)

#define TIMx_CCMR1_OUT_CC2S_POS     (8U)
#define TIMx_CCMR1_OUT_OC2FE_POS    (10U)
#define TIMx_CCMR1_OUT_OC2PE_POS    (11U)
#define TIMx_CCMR1_OUT_OC2M_POS     (12U)
#define TIMx_CCMR1_OUT_OC2CE_POS    (15U)

#define TIMx_CCMR1_CC1S_MASK        (3U << TIMx_CCMR1_CC1S_POS)             // channel 1 direction selection
#define TIMx_CCMR1_OUT_OC1FE_MASK   (1U << TIMx_CCMR1_OUT_OC1FE_POS)        // Output compare 1 fast enable
#define TIMx_CCMR1_OUT_OC1PE_MASK   (1U << TIMx_CCMR1_OUT_OC1PE_POS)        // Output compare 1 preload enable
#define TIMx_CCMR1_OUT_OC1M_MASK    (7U << TIMx_CCMR1_OUT_OC1M_POS)         // Output compare 1 mode
#define TIMx_CCMR1_OUT_OC1CE_MASK   (1U << TIMx_CCMR1_OUT_OC1CE_POS)        // Output compare 1 clear enable

#define TIMx_CCMR1_OUT_CC2S_MASK    (3U << TIMx_CCMR1_OUT_CC2S_POS)         // Output compare 2 selection
#define TIMx_CCMR1_OUT_OC2FE_MASK   (1U << TIMx_CCMR1_OUT_OC2FE_POS)        // Output compare 2 fast enable
#define TIMx_CCMR1_OUT_OC2PE_MASK   (1U << TIMx_CCMR1_OUT_OC2PE_POS)        // Output compare 2 preload enable
#define TIMx_CCMR1_OUT_OC2M_MASK    (7U << TIMx_CCMR1_OUT_OC2M_POS)         // Output compare 2 mode
#define TIMx_CCMR1_OUT_OC2CE_MASK   (1U << TIMx_CCMR1_OUT_OC2CE_POS)        // Output compare 2 clear enable
      

// Input capture mode  
#define TIMx_CCMR1_INP_IC1PSC_POS    (2U)
#define TIMx_CCMR1_INP_IC1F_POS      (4U)

#define TIMx_CCMR1_INP_CC2S_POS      (8U)
#define TIMx_CCMR1_INP_IC2PSC_POS    (10U)
#define TIMx_CCMR1_INP_IC2F_POS      (12U)

#define TIMx_CCMR1_INP_IC1PSC_MASK   (3U   << TIMx_CCMR1_INP_IC1PSC_POS)    // Input capture 1 prescaler
#define TIMx_CCMR1_INP_IC1F_MASK     (0xFU << TIMx_CCMR1_INP_IC1F_POS)      // Input capture 1 filter

#define TIMx_CCMR1_INP_CC2S_MASK     (3U   << TIMx_CCMR1_INP_CC2S_POS)      // Input Capture compare 2 selectioin
#define TIMx_CCMR1_INP_IC2PSC_MASK   (3U   << TIMx_CCMR1_INP_IC2PSC_POS)    // Input capture 2 prescaler
#define TIMx_CCMR1_INP_IC2F_MASK     (0xFU << TIMx_CCMR1_INP_IC2F_POS)      // Input capture 2 filter

// Timer CCER register
#define TIMx_CCER_CC1E_MASK         (1U << 0U)
#define TIMx_CCER_CC1P_MASK         (1U << 1U)

#define TIMx_CCER_CC2E_MASK         (1U << 4U)
#define TIMx_CCER_CC2P_MASK         (1U << 5U)

#define TIMx_CCER_CC3E_MASK         (1U << 8U)
#define TIMx_CCER_CC3P_MASK         (1U << 9U)

#define TIMx_CCER_CC4E_MASK         (1U << 12U)
#define TIMx_CCER_CC4P_MASK         (1U << 13U)

// TIMx_EGR register

#define TIMx_EGR_UG_MASK            (1U << 0U)
#define TIMx_EGR_CC1G_MASK          (1U << 1U)
#define TIMx_EGR_CC2G_MASK          (1U << 2U)
#define TIMx_EGR_CC3G_MASK          (1U << 3U)
#define TIMx_EGR_CC4G_MASK          (1U << 4U)
#define TIMx_EGR_COMG_MASK          (1U << 5U)
#define TIMx_EGR_TG_MASK            (1U << 6U)
#define TIMx_EGR_BG_MASK            (1U << 7U)
 

// Timer control register
#define TIMx_DCR_DBA_MASK           (0x1FU << 0U)       // Timer x Base address
#define TIMx_DCR_DBL_MASK           (0x1FU << 8U)       // DMA burst length

#define TIMx_DCR_DBA_VAL(value)     (((uint32_t) (value) << 0U) & TIMx_DCR_DBA_MASK)
#define TIMx_DCR_DBL_VAL(value)     (((uint32_t) (value) << 8U) & TIMx_DCR_DBL_MASK)

// 5 bit vector number defines the number of DMA transfers
#define TIMx_DCR_DBL_TRANSFERS(n)   TIMx_DCR_DBL_VAL((n) - 1U)

// 5 bit vector defines the base-address for DMA transfers
typedef enum {
    TIMx_DMA_BASE_CR1   = 0U,
    TIMx_DMA_BASE_CR2   = 1U,
    TIMx_DMA_BASE_SMCR  = 2U,
    TIMx_DMA_BASE_DIER  = 3U,
    TIMx_DMA_BASE_SR    = 4U,
    TIMx_DMA_BASE_EGR   = 5U,
    TIMx_DMA_BASE_CCMR1 = 6U,
    TIMx_DMA_BASE_CCMR2 = 7U,
    TIMx_DMA_BASE_CCER  = 8U,
    TIMx_DMA_BASE_CNT   = 9U,
    TIMx_DMA_BASE_PSC   = 10U,
    TIMx_DMA_BASE_ARR   = 11U,
    TIMx_DMA_BASE_RCR   = 12U,
    TIMx_DMA_BASE_CCR1  = 13U,
    TIMx_DMA_BASE_CCR2  = 14U,
    TIMx_DMA_BASE_CCR3  = 15U,
    TIMx_DMA_BASE_CCR4  = 16U,
    TIMx_DMA_BASE_BDTR  = 17U,
    TIMx_DMA_BASE_DCR   = 18U,
    TIMx_DMA_BASE_DMAR  = 19U
} TIMx_DCR_dma_base_addr_t;

#endif