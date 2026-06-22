#include "adc.h"
#include "system.h"
#include "f103c6t6_regs.h"
#include "gpio.h"

static bool adc_enabled = false; 

system_result_t adc1_init() {
    if (adc_enabled) {
        return RESULT_NOT_ALLOWED;
    }
    system_result_t result = ADC_config_clock();
    if (result != RESULT_SUCCESS) {
        return result;
    }

    // ADC base register address
    volatile ADCx_registers_t *adc1_base = ADC1_REGISTERS;

    // ADC power on
    adc1_base->ADC_CR2 |= ADC_CR2_ADON_MASK;

    delay(MS_TO_TICKS(10));   // delay for ADC to stable

    // Reset calibration register. set by software, cleared by hardware
    adc1_base->ADC_CR2 |= ADC_CR2_RSTCAL_MASK;  // Initialize calibration register
    while (adc1_base->ADC_CR2 & ADC_CR2_RSTCAL_MASK);      // wait until initialization finishes

    // A/D   calibration register. set by software, cleared by hardware
    adc1_base->ADC_CR2 |= ADC_CR2_CAL_MASK;         // Enable calibration
    while (adc1_base->ADC_CR2 & ADC_CR2_CAL_MASK);  // wait until hardware finishes calibration and mark it by clearing bit

    // For right alignment we clear the align bit. 0 - right, 1 - left
    adc1_base->ADC_CR2 &= ~ADC_CR2_ALIGN_MASK;

    // Continuous conversion until this bit reset
    adc1_base->ADC_CR2 &= ~ADC_CR2_CONT_MASK;

    // External event select used to trigger start of conversion
    adc1_base->ADC_CR2 &= ~ADC_CR2_EXTSEL_MASK;
    adc1_base->ADC_CR2 |= (ADC_EXTSEL_SWSTART << ADC_CR2_EXTSEL_POS);     // trigger adc by software
    adc1_base->ADC_CR2 |= ADC_CR2_EXTTRIG_MASK;     // conversion on external event enabled

    // Configure PIN for ADC
    gpio_config_req_t ldr_gpio_config = {
        .port = GPIO_PORT_A,
        .pin = GPIO_PIN_1,
        .pin_config = GPIO_INPUT_ANALOG,
        .mode = GPIO_INPUT
    };  

    result = gpio_configure(ldr_gpio_config);
    if (result != RESULT_SUCCESS) {
        return result;
    }

    adc_enabled = true;
    return RESULT_SUCCESS;
}

system_result_t adc1_read(adc_channel_t channel, ADC_seq_length_t seq_length, uint16_t *adc_value)
{
    if (!adc_value) {
        return RESULT_INVALID;
    }

    if (channel > ADC_CHANNEL_9) {
        return RESULT_INVALID;
    }

    volatile ADCx_registers_t *adc1_base = ADC1_REGISTERS;

    // Sample timer register. each channel holds 3 bits.
    adc1_base->ADC_SMPR2 &= ~ADC_SMPR2_SMP_MASK(channel);
    adc1_base->ADC_SMPR2 |= ADC_SMPR2_SMP_SET(LDR_ADC_SAMPLE_TIME, channel);        // adc sample cycles set

    
    // Setting number of conversions
    adc1_base->ADC_SQR1 &= ~ADC_SQR1_L_MASK;
    adc1_base->ADC_SQR1 = (seq_length << ADC_SQR1_L_POS);

    // sequence 1 clear and set the channel
    adc1_base->ADC_SQR3 &= ~ADC_SQR3_SQ1_MASK;
    adc1_base->ADC_SQR3 |= ((uint32_t)channel << ADC_SQR3_SQ1_POS);

    adc1_base->ADC_SR &= ~ADC_SR_EOC_MASK;

    // Start ADC
    adc1_base->ADC_CR2 |= ADC_CR2_SWSTART_MASK;

    // Checking conversion is complete. It is set by hardware
    while (!(adc1_base->ADC_SR & ADC_SR_EOC_MASK));

    // ADC regular data
    *adc_value = (uint16_t)(adc1_base->ADC_DR & 0x0FFFU);

    return RESULT_SUCCESS;
}