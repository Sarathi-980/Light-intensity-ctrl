#ifndef ADC_H
#define ADC_H

#include "system.h"
 
#define VOLTAGE_DIV_R1              (10000U)   // 10K Resistor
#define VOLTAGE_DIV_R2              (40000U)   // 40K Resistor

#define TIMER_INIT_DUTY_CYCLE       (500U)

#define TIMER_AUTO_RELOAD_VAL       (999U)

// Comparizon between TIMx_CCR1 and the TIMx_CNT
typedef enum {
    COMPARE_FROZEN,
    OC1REF_FORCE_HIGH_MATCH,
    OC1REF_FORCE_LOW_MATCH,
    OC1REF_TOGGLE_MATCH,
    OC1REF_FORCE_LOW,
    OC1REF_FORCE_HIGH,
    PWM_MODE_1,                 // In upcounting channel 1 is active as long as TIMx_CNT < TIMx_CCR1, In downcounting channel 1 is inactive as long as TIMx_CNT > TIMx_CCR1
    PWM_MODE_2                  // In upcounting Channel 1 is inactive as long as TIMx_CNT < TIMx_CCR1, In downcounting channel 1 is active as long as TIMx_CNT > TIMx_CCR1
}   TIMERx_CCMR1_OC1M_t;

#endif