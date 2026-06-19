#include "adc.h"
#include "gpio.h"
#include "system.h"

static bool is_dark = false;
static bool adc_enabled = false; 
extern uint32_t system_frequency;

system_result_t timer2_pwm_enable() {
    apb1_enable_t enable1 = RCC_APB1_TIMER2_EN_MASK;
    system_result_t result = APB1_enable_clock(enable1);
    if (result != RESULT_SUCCESS) {
        return result;
    }

    apb2_enable_t enable2 = RCC_APB2_GPIOA_EN_MASK | RCC_APB2_ADC1_EN_MASK;
    result = APB2_enable_clock(enable2);
    return result;
}

system_result_t timer2_init() {
    system_result_t result = gpio_configure(GPIO_PORT_A, GPIO_PIN_0, AFO_OUTPUT_PUSH_PULL, GPIO_OUTPUT_50MHz);
    if (result != RESULT_SUCCESS) {
        return result;
    }

    // STM32 Timer frequency is 72 MHz, PWM frequency is 72 MHz / ((PSC + 1) * (ARR + 1)). So it is based on cpu frequency

    TIMER2_REGISTERS->TIMx_PSC = (system_frequency / ONE_MHZ_FREQUENCY) - 1;    // prescaler -> divide the timer clock. It is 0 indexed.
    TIMER2_REGISTERS->TIMx_ARR = TIMER_AUTO_RELOAD_VAL;   // Auto reload register. It is 0 indexed.

    TIMER2_REGISTERS->TIMx_CCR1 = TIMER_INIT_DUTY_CYCLE;  // Duty cycle

    // CH1 PWM mode 1
    uint32_t ccmr1_val = TIMER2_REGISTERS->TIMx_CCMR1;

    ccmr1_val &= ~TIMx_CCMR1_OUT_OC1M_MASK;                    // OC1M = 110, PWM mode 1
    ccmr1_val |= (PWM_MODE_1 << TIMx_CCMR1_OUT_OC1M_POS);      // OC1PE enable preload

    TIMER2_REGISTERS->TIMx_CCMR1 = ccmr1_val;

    // Enable channel 1 output
    TIMER2_REGISTERS->TIMx_CCER |= TIMx_CCER_CC1E_MASK;

    // Enable auto-reload enable
    TIMER2_REGISTERS->TIMx_CR1 |= TIMx_CR1_ARPE_MASK;
    
    // Update event to load registers
    TIMER2_REGISTERS->TIMx_EGR |= TIMx_EGR_UG_MASK;

    // Enable counter
    TIMER2_REGISTERS->TIMx_CR1 |= TIMx_CR1_CEN_MASK;

    return RESULT_SUCCESS;
}


system_result_t set_dutycycle_timer2(uint16_t dutycycle) {
    if (dutycycle > TIMER_AUTO_RELOAD_VAL) {
        dutycycle = TIMER_AUTO_RELOAD_VAL;
    }

    TIMER2_REGISTERS->TIMx_CCR1 = dutycycle;
    return RESULT_SUCCESS;
}