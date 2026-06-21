#include "timer.h"
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

typedef struct {
    TIMERx_CCMR1_OC1M_t compare_mode;
    uint32_t            compare_value;
}   channel_output_req_t;

typedef struct {
    TIMx_IC1PSC_t  input_prescaler;
    TIMx_IC1F_t    input_filter;
}   channel_input_req_t;

typedef union {
    channel_output_req_t out;
    channel_input_req_t inp;
}   timer_cc_config_t;

typedef struct {
    // Output compare mode
    uint32_t ocxm_pos;
    // Output compare preload enable
    uint32_t ocxpe_mask;
    // Enable capture compare output
    uint32_t ccxe_mask;
}   channel_config_output_req_t;

typedef struct {
    uint32_t    icxpsc_pos;
    uint32_t    icxf_pos;
}   channel_config_input_req_t;

typedef union {
    channel_config_output_req_t output_cfg;
    channel_config_input_req_t input_cfg;
}   channel_io_req_t;
  

typedef struct {
    volatile TIMx_registers_t   *config_timer;
    timer_channel_t             config_channel;
    TIMx_CCxS_t                 channel_direction;     // Channel capture compare direction select
    timer_cc_config_t           capture_compare_cfg;
}   channel_config_req_t;

system_result_t timer_configure_channel(channel_config_req_t configs)
{   
    if (configs.config_timer == 0) {
        return RESULT_INVALID;
    }
    // Capture compare selection position
    uint32_t ccxs_pos;

    // Capture compare register
    volatile uint32_t*  ccr_reg;
    // Capture compare mode register
    volatile uint32_t*  ccmr_reg;
    
    channel_io_req_t input_output_cfg;

    uint32_t ccxe_pos;

    switch (configs.config_channel)
    {
        case TIMER_CHANNEL_1:
            ccr_reg = &configs.config_timer->TIMx_CCR1;
            ccmr_reg = &configs.config_timer->TIMx_CCMR1;
            ccxs_pos = TIMx_CCMR1_OUT_CC1S_POS;
            ccxe_pos = TIMx_CCER_CC1E_POS;
            if (configs.channel_direction == TIMER_CCx_CONFIG_OUTPUT) {
                input_output_cfg.output_cfg.ocxm_pos = TIMx_CCMR1_OUT_OC1M_POS;
                input_output_cfg.output_cfg.ocxpe_mask = TIMx_CCMR1_OUT_OC1PE_MASK;
            }
            else {
                input_output_cfg.input_cfg.icxf_pos = TIMx_CCMR1_INP_IC1F_POS;
                input_output_cfg.input_cfg.icxpsc_pos = TIMx_CCMR1_INP_IC1PSC_POS; 
            }
             
            break;
        
        case TIMER_CHANNEL_2:
            ccr_reg = &configs.config_timer->TIMx_CCR2;
            ccmr_reg = &configs.config_timer->TIMx_CCMR1;
            ccxs_pos = TIMx_CCMR1_OUT_CC2S_POS;
            ccxe_pos = TIMx_CCER_CC2E_POS;
            if (configs.channel_direction == TIMER_CCx_CONFIG_OUTPUT) {
                input_output_cfg.output_cfg.ocxm_pos = TIMx_CCMR1_OUT_OC2M_POS;
                input_output_cfg.output_cfg.ocxpe_mask = TIMx_CCMR1_OUT_OC2PE_MASK; 
            }
            else {
                input_output_cfg.input_cfg.icxf_pos = TIMx_CCMR1_INP_IC2F_POS;
                input_output_cfg.input_cfg.icxpsc_pos = TIMx_CCMR1_INP_IC2PSC_POS; 
            }
            break;

        case TIMER_CHANNEL_3:
            ccr_reg = &configs.config_timer->TIMx_CCR3;
            ccmr_reg = &configs.config_timer->TIMx_CCMR2; 
            ccxs_pos = TIMx_CCMR2_OUT_CC3S_POS;
            ccxe_pos = TIMx_CCER_CC3E_POS;
            if (configs.channel_direction == TIMER_CCx_CONFIG_OUTPUT) {
                input_output_cfg.output_cfg.ocxm_pos = TIMx_CCMR2_OUT_OC3M_POS;
                input_output_cfg.output_cfg.ocxpe_mask = TIMx_CCMR2_OUT_OC3PE_MASK; 
            }
            else {
                input_output_cfg.input_cfg.icxf_pos = TIMx_CCMR2_INP_IC3F_POS;
                input_output_cfg.input_cfg.icxpsc_pos = TIMx_CCMR2_INP_IC3PSC_POS; 
            }
            break;
        
        case TIMER_CHANNEL_4:
            ccr_reg = &configs.config_timer->TIMx_CCR4;
            ccmr_reg = &configs.config_timer->TIMx_CCMR2;
            ccxs_pos = TIMx_CCMR2_OUT_CC4S_POS;
            ccxe_pos = TIMx_CCER_CC4E_POS;
            if (configs.channel_direction == TIMER_CCx_CONFIG_OUTPUT) {
                input_output_cfg.output_cfg.ocxm_pos = TIMx_CCMR2_OUT_OC4M_POS;
                input_output_cfg.output_cfg.ocxpe_mask = TIMx_CCMR2_OUT_OC4PE_MASK; 
            }
            else {
                input_output_cfg.input_cfg.icxf_pos = TIMx_CCMR2_INP_IC4F_POS;
                input_output_cfg.input_cfg.icxpsc_pos = TIMx_CCMR2_INP_IC4PSC_POS; 
            }
            break;
        
        default:
            return RESULT_INVALID;
    }

    // Disable channel before changing mode.
    configs.config_timer->TIMx_CCER &= ~TIMx_CCER_CCxE_MASK(ccxe_pos);

    if (configs.channel_direction == TIMER_CCx_CONFIG_OUTPUT) {
        *ccr_reg = configs.capture_compare_cfg.out.compare_value;
    }

    uint32_t ccmr_val = *ccmr_reg;
    ccmr_val &= ~TIMx_CCMRx_OUT_CCxS_MASK(ccxs_pos);
    ccmr_val |= TIMx_CCMRx_OUT_CCxS_SET(configs.channel_direction, ccxs_pos);

    if (configs.channel_direction == TIMER_CCx_CONFIG_OUTPUT) {
        ccmr_val &= ~TIMx_CCMRx_OUT_OCxM_MASK(input_output_cfg.output_cfg.ocxm_pos);
        ccmr_val |= TIMx_CCMRx_OUT_OCxM_SET(configs.capture_compare_cfg.out.compare_mode, input_output_cfg.output_cfg.ocxm_pos);

        // Output compare preload enable
        ccmr_val |= input_output_cfg.output_cfg.ocxpe_mask;
    }
    else {
        ccmr_val &= ~TIMx_CCMRx_INP_ICxPSC_MASK(input_output_cfg.input_cfg.icxpsc_pos);
        ccmr_val &= ~TIMx_CCMRx_INP_ICxF_MASK(input_output_cfg.input_cfg.icxf_pos);

        ccmr_val |= TIMx_CCMRx_INP_ICxPSC_SET(configs.capture_compare_cfg.inp.input_prescaler, input_output_cfg.input_cfg.icxpsc_pos);
        // Input capture filter - frequency used to sample TI1 input and length of the digital filter
        ccmr_val |= TIMx_CCMRx_INP_ICxF_SET(configs.capture_compare_cfg.inp.input_filter, input_output_cfg.input_cfg.icxf_pos);
    }
    
    *ccmr_reg = ccmr_val;

    // Enable selected output channel
    configs.config_timer->TIMx_CCER |= TIMx_CCER_CCxE_MASK(ccxe_pos);
    return RESULT_SUCCESS;
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

    channel_config_req_t channel_config_req = {
        .config_timer = timer,
        .config_channel = channel,
        .config_type = CHANNEL_CONFIG_OUTPUT, 
    };
    timer_configure_channel()
    
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