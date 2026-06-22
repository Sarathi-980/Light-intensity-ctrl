
#include "ldr.h"
#include "gpio.h"
#include "system.h"
#include "adc.h"

daylight_t daylight_status() {
    uint16_t adc_val = 0;

    system_result_t result = adc1_read(LDR_ADC_CHANNEL, ADC_SEQUENCE_LEN_1, &adc_val);
    if (result != RESULT_SUCCESS) {
        return RESULT_INVALID;
    }

    if (adc_val < LDR_DARK_THRESHOLD) {
        return DAYLIGHT_DARK;
    }
    else if (adc_val > LDR_BRIGHT_THRESHOLD) {
        return DAYLIGHT_BRIGHT;
    }
    else {
        return DAYLIGHT_LOW_BRIGHT;
    }
}