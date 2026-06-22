#ifndef ADC_H
#define ADC_H

#include "system.h"
#include "gpio.h"
 
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
}   timer_id_t;

typedef enum {
    TIMER_CHANNEL_1 = 0,
    TIMER_CHANNEL_2,
    TIMER_CHANNEL_3,
    TIMER_CHANNEL_4,
    TIMER_CHANNEL_COUNT
} timer_channel_t;

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

// Note: input mapping to TIx depends on channel, either direct or indirect
typedef enum {
    TIMER_CCx_CONFIG_OUTPUT         = 0U,  // CCx channel is configured as output

    TIMER_CCx_CONFIG_INPUT_DIRECT   = 1U,  //  mapped to its own TIx
    TIMER_CCx_CONFIG_INPUT_INDIRECT = 2U,  // mapped to opposite TIx
    TIMER_CCx_CONFIG_INPUT_TRC      = 3U   // mapped to TRC
} TIMx_CCxS_t;

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
}   TIMx_CCER_t;

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
    timer_channel_t             config_channel;
    TIMx_CCxS_t                 channel_direction;     // Channel capture compare direction select
    timer_cc_config_t           capture_compare_cfg;
}   channel_config_req_t;

system_result_t general_timer_init(timer_id_t id, channel_config_req_t timer_configs, gpio_config_req_t gpio_configs);
system_result_t timer_set_channel_duty(timer_id_t timer_id, timer_channel_t channel, uint32_t duty);


#endif