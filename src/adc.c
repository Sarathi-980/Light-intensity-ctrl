#include "adc.h"
#include "gpio.h"
#include "system.h"

static bool is_dark = false;
static bool adc_enabled = false; 
extern uint32_t system_frequency;

static const uint32_t timer_base_address_table[TIMER_COUNT] = {
    [TIMER_TIM1]  = TIMER1_BASE_ADDRESS,
    [TIMER_TIM2]  = TIMER2_BASE_ADDRESS,
    [TIMER_TIM3]  = TIMER3_BASE_ADDRESS,
    [TIMER_TIM4]  = TIMER4_BASE_ADDRESS,
    [TIMER_TIM5]  = TIMER5_BASE_ADDRESS,
    [TIMER_TIM6]  = TIMER6_BASE_ADDRESS,
    [TIMER_TIM7]  = TIMER7_BASE_ADDRESS,
    [TIMER_TIM8]  = TIMER8_BASE_ADDRESS,
    [TIMER_TIM9]  = TIMER9_BASE_ADDRESS,
    [TIMER_TIM10] = TIMER10_BASE_ADDRESS,
    [TIMER_TIM11] = TIMER11_BASE_ADDRESS,
    [TIMER_TIM12] = TIMER12_BASE_ADDRESS,
    [TIMER_TIM13] = TIMER13_BASE_ADDRESS,
    [TIMER_TIM14] = TIMER14_BASE_ADDRESS,
};

static inline void timer_configure_channel1_output( 
    volatile TIMx_registers_t *timer,   
    TIMERx_CCMR1_OC1M_t compare_mode,
    uint32_t compare_value
)
{ 
    // Disable channel before changing mode.
    timer->TIMx_CCER &= ~TIMx_CCER_CC1E_MASK;

    timer->TIMx_CCR1 = compare_value;

    uint32_t ccmr1_val = timer->TIMx_CCMR1;

    ccmr1_val &= ~TIMx_CCMR1_CC1S_MASK;
    ccmr1_val &= ~TIMx_CCMR1_OUT_OC1M_MASK;

    ccmr1_val |= ((uint32_t)TIMER_CC1_CONFIG_OUTPUT << TIMx_CCMR1_CC1S_POS);
    ccmr1_val |= ((uint32_t)compare_mode << TIMx_CCMR1_OUT_OC1M_POS);

    // Output compare preload enable
    ccmr1_val |= TIMx_CCMR1_OUT_OC1PE_MASK;

    timer->TIMx_CCMR1 = ccmr1_val;

    timer->TIMx_CCER |= TIMx_CCER_CC1E_MASK;
}   

static inline void timer_configure_channel1_input(
    volatile TIMx_registers_t *timer,
    TIMx_CC1S_t input_select,
    TIMx_IC1PSC_t input_prescaler,
    TIMx_IC1F_t input_filter
)
{ 
    // Disable channel before changing CC1S.
    timer->TIMx_CCER &= ~TIMx_CCER_CC1E_MASK;

    uint32_t ccmr1_val = timer->TIMx_CCMR1;

    ccmr1_val &= ~TIMx_CCMR1_CC1S_MASK;
    ccmr1_val &= ~TIMx_CCMR1_INP_IC1PSC_MASK;
    ccmr1_val &= ~TIMx_CCMR1_INP_IC1F_MASK;

    ccmr1_val |= ((uint32_t)input_select << TIMx_CCMR1_CC1S_POS);
    // Input capture prescaler 
    ccmr1_val |= ((uint32_t)input_prescaler << TIMx_CCMR1_INP_IC1PSC_POS);
    // Input capture filter - frequency used to sample TI1 input and length of the digital filter
    ccmr1_val |= ((uint32_t)input_filter << TIMx_CCMR1_INP_IC1F_POS);

    timer->TIMx_CCMR1 = ccmr1_val;

    timer->TIMx_CCER |= TIMx_CCER_CC1E_MASK;
}

/**
 * Function enables timer and configures channel for input/output.
 * Before calling this function, we must enable the corresponding peripheral clock.
 * GPIO configuration must be "alternate function output push-pull" for PWM output.
 * 
 * @param   id          Timer ID need to be configure
 * @param   channel     Timer channel need to be configure
 * @param   configs     gpio configuration need to be configure
 */
system_result_t general_timer_init(timer_id_t id, timer_channel_t channel, gpio_config_req_t configs) 
{
    if (id < TIMER_TIM2 || id > TIMER_TIM5) {
        return RESULT_INVALID;
    }
    system_result_t result = gpio_configure(configs);
    if (result != RESULT_SUCCESS) {
        return result;
    }
    
    uint32_t timer_base = timer_base_address_table[id];
    if (timer_base == 0U) {
        return RESULT_INVALID;
    }

    volatile TIMx_registers_t* timer = GENERAL_TIMER_REGISTERS(timer_base);

    // STM32 Timer frequency is 72 MHz, PWM frequency is 72 MHz / ((PSC + 1) * (ARR + 1)). So it is based on cpu frequency
    /*
        Timer frequency = timer clock / ((Prescaler + 1) * (Auto reload + 1))
        If timer clock is 72 MHz and PSC is 71 then timer counter clock is 1 MHz.
    */
    timer->TIMx_PSC = (system_frequency / ONE_MHZ_FREQUENCY) - 1U;
    timer->TIMx_ARR = TIMER_INIT_AUTO_RELOAD_VAL;
    
    // Enable auto-reload enable
    timer->TIMx_CR1 |= TIMx_CR1_ARPE_MASK;
    
    // Update event to load registers
    timer->TIMx_EGR = TIMx_EGR_UG_MASK;

    // Enable counter
    timer->TIMx_CR1 |= TIMx_CR1_CEN_MASK;

    return RESULT_SUCCESS;
}

// system_result_t set_dutycycle_timer2(uint16_t dutycycle) {
//     if (dutycycle > TIMER_AUTO_RELOAD_VAL) {
//         dutycycle = TIMER_AUTO_RELOAD_VAL;
//     }

//     TIMER2_REGISTERS->TIMx_CCR1 = dutycycle;
//     return RESULT_SUCCESS;
// }