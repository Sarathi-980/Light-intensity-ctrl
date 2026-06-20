#ifndef ADC_H
#define ADC_H

#include "system.h"
 
#define VOLTAGE_DIV_R1              (10000U)   // 10K Resistor
#define VOLTAGE_DIV_R2              (40000U)   // 40K Resistor

#define TIMER_INIT_DUTY_CYCLE       (500U)

#define TIMER_INIT_AUTO_RELOAD_VAL  (999U)

typedef enum {
    TIMER_TIM1 = 0,
    TIMER_TIM2,
    TIMER_TIM3,
    TIMER_TIM4,
    TIMER_TIM5,
    TIMER_TIM6,
    TIMER_TIM7,
    TIMER_TIM8,
    TIMER_TIM9,
    TIMER_TIM10,
    TIMER_TIM11,
    TIMER_TIM12,
    TIMER_TIM13,
    TIMER_TIM14,

    TIMER_COUNT
} timer_id_t;

// Comparizon between TIMx_CCR1 and the TIMx_CNT
typedef enum {
    COMPARE_FROZEN  = 0,
    OC1REF_FORCE_HIGH_MATCH,
    OC1REF_FORCE_LOW_MATCH,
    OC1REF_TOGGLE_MATCH,
    OC1REF_FORCE_LOW,
    OC1REF_FORCE_HIGH,
    PWM_MODE_1,                 // In upcounting channel 1 is active as long as TIMx_CNT < TIMx_CCR1, In downcounting channel 1 is inactive as long as TIMx_CNT > TIMx_CCR1
    PWM_MODE_2                  // In upcounting Channel 1 is inactive as long as TIMx_CNT < TIMx_CCR1, In downcounting channel 1 is active as long as TIMx_CNT > TIMx_CCR1
}   TIMERx_CCMR1_OC1M_t;

typedef enum {
    TIMER_CC1_CONFIG_OUTPUT,
    TIMER_CC1_CONFIG_IC1_MAP_TI1,
    TIMER_CC1_CONFIG_IC1_MAP_TI2,
    TIMER_CC1_CONFIG_IC1_MAP_TRC
}   TIMx_CC1S_t;

typedef enum {
    TIMx_IC1PSC_NO_PRESCALER = 0,       // no prescaler, capture at each edge
    TIMx_IC1PSC_DIV_2,                  // Capture once every 2 events
    TIMx_IC1PSC_DIV_4,                  // Capture once every 4 events
    TIMx_IC1PSC_DIV_8                   // Capture once every 8 events
} TIMx_IC1PSC_t;

typedef enum {
    TIMx_IC1F_NO_FILTER     =   0,   // No filter, sampling at fDTS

    TIMx_IC1F_CK_INT_N2,            // fSAMPLING = fCK_INT, N = 2
    TIMx_IC1F_CK_INT_N4,            // fSAMPLING = fCK_INT, N = 4
    TIMx_IC1F_CK_INT_N8,            // fSAMPLING = fCK_INT, N = 8

    TIMx_IC1F_DTS_DIV2_N6,          // fSAMPLING = fDTS/2,  N = 6
    TIMx_IC1F_DTS_DIV2_N8,          // fSAMPLING = fDTS/2,  N = 8

    TIMx_IC1F_DTS_DIV4_N6,          // fSAMPLING = fDTS/4,  N = 6
    TIMx_IC1F_DTS_DIV4_N8,          // fSAMPLING = fDTS/4,  N = 8

    TIMx_IC1F_DTS_DIV8_N6,          // fSAMPLING = fDTS/8,  N = 6
    TIMx_IC1F_DTS_DIV8_N8,          // fSAMPLING = fDTS/8,  N = 8

    TIMx_IC1F_DTS_DIV16_N5,         // fSAMPLING = fDTS/16, N = 5
    TIMx_IC1F_DTS_DIV16_N6,         // fSAMPLING = fDTS/16, N = 6
    TIMx_IC1F_DTS_DIV16_N8,         // fSAMPLING = fDTS/16, N = 8

    TIMx_IC1F_DTS_DIV32_N5,         // fSAMPLING = fDTS/32, N = 5
    TIMx_IC1F_DTS_DIV32_N6,         // fSAMPLING = fDTS/32, N = 6
    TIMx_IC1F_DTS_DIV32_N8,         // fSAMPLING = fDTS/32, N = 8
} TIMx_IC1F_t;

typedef enum {
    CAPTURE_INP_RISING_EDGE = 0U,
    CAPTURE_INP_FALLING_EDGE = 1U,
    COMPARE_OUT_HIGH    =   0U,
    COMPARE_OUT_LOW     =   1U,
}   TIMx_CCP_t;

typedef enum {
    CAPTURE_INP_DISABLE = 0U,
    CAPTURE_INP_ENABLE  = 1U,
    COMPARE_OUT_DISABLE    =   0U,
    COMPARE_OUT_ENABLE     =   1U,
}   TIMx_CCPE_t;

#endif