#include "led.h"
#include "gpio.h"
#include "ldr.h"

void led_off() {
    // Turning OFF LED by setting 13th bit in lower 16 bits
    GPIOx_config_regs(GPIOC_BASE)->BSRR = (1 << GPIO_PIN_13);
}

void led_on() {
    // LED is active low.
    // Turning ON LED by setting 13th bit in upper 16 bits
    GPIOx_config_regs(GPIOC_BASE)->BSRR = (1 << (GPIO_PIN_13 + 16));
}

void led_indicate_state(system_result_t state) {
    static bool led_configured = false;
    if (!led_configured) {
        gpio_config_req_t configs = {
            .port = GPIO_PORT_C,
            .pin = GPIO_PIN_13,
            .mode = GPIO_OUTPUT_2MHz,
            .pin_config = GPIO_OUTPUT_PUSH_PULL
        };
        gpio_configure(configs);
        led_configured = true;
    }
    if (state != RESULT_SUCCESS) {
        while (1)
        {
            led_off();
            delay(MS_TO_TICKS(GPIO_LED_ERROR_BLINK_MS));
            led_on();
        }
    }
    else {
        // led stays on
        GPIOx_config_regs(GPIOC_BASE)->BSRR = (1 << (GPIO_PIN_13 + 16));
    }
}

void update_led_from_daylight(timer_id_t timer_id, timer_channel_t channel)
{ 
    daylight_t status = daylight_status();

    switch (status)
    {
        case DAYLIGHT_DARK:
            timer_set_channel_duty(timer_id, channel, 900);
            break;

        case DAYLIGHT_LOW_BRIGHT:
            timer_set_channel_duty(timer_id, channel, 500);
            break;

        case DAYLIGHT_BRIGHT:
            timer_set_channel_duty(timer_id, channel, 0);
            break;

        default:
            timer_set_channel_duty(timer_id, channel, 0);
            break;
    }
}