#include "system.h"
#include "gpio.h"
#include <stdint.h>
#include "f103c6t6_regs.h" 
#include "system_exceptions.h" 
#include "led.h"
#include "timer.h"

extern volatile uint32_t seconds; 

 
int main(void) {
	system_result_t result = system_init();  

	apb2_enable_t enable = GPIOC_CLOCK_ENABLE | GPIOA_CLOCK_ENABLE | AFIO_CLOCK_ENABLE;
	result = APB2_enable_clock(enable);
	if (result != RESULT_SUCCESS) {
        return result;
    }

	channel_config_req_t channel_req_configs = {
		.config_channel = TIMER_CHANNEL_1,
		.capture_compare_cfg.out = {
			.compare_mode = PWM_MODE_1,
			.compare_value = TIMER_INIT_DUTY_CYCLE
		},
		.channel_direction = TIMER_CCx_CONFIG_OUTPUT
	};
	gpio_config_req_t gpio_configs = {
		.port = GPIO_PORT_A,
		.pin = GPIO_PIN_0,
		.pin_config = AFO_OUTPUT_PUSH_PULL,
		.mode = GPIO_OUTPUT_2MHz
	};
	result = general_timer_init(TIMER_TIM2, channel_req_configs, gpio_configs);
	if (result != RESULT_SUCCESS) {
        return result;
    }

	while (1) {
		update_led_from_daylight(TIMER_TIM2, TIMER_CHANNEL_1);
		delay(MS_TO_TICKS(10000));
	}

	// never arrives
	return 0;
}