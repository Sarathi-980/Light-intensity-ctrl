#include "system.h"
#include "gpio.h"
#include <stdint.h>
#include "f103c6t6_regs.h" 
#include "system_exceptions.h" 

// extern volatile uint32_t seconds; 

// void light_off() {
// 	GPIO_CFG_REG(GPIO_A_BASE, GPIO_CONFIG_BSRR_OFFSET) = (1 << (GPIO_PIN_0 + 16));
// }
 
// void pwm_set_percent(uint32_t percent)
// {
//     TIMER_CFG(0x34) = (TIMER_CFG(0x2c) + 1) * percent / 100;
// }

// void light_on() {
// 	GPIO_CFG_REG(GPIO_A_BASE, GPIO_CONFIG_BSRR_OFFSET) = (1 << GPIO_PIN_0);
// }

// typedef enum {
// 	LED_ON_SECOND = 0,
// 	LED_BRIGHT_START_SECOND = 3600 * 4,
// 	LED_DIM_EIGHT_HOURS_SECOND = LED_BRIGHT_START_SECOND + (3600 * 8),
// 	LED_BRIGHT_MORNING_SECOND = LED_DIM_EIGHT_HOURS_SECOND + (3600 * 2),
// 	LED_OFF_SECOND = (3600 * 24) - LED_BRIGHT_START_SECOND + LED_DIM_EIGHT_HOURS_SECOND + LED_BRIGHT_MORNING_SECOND - 300,
// 	RESET_SECOND = LED_OFF_SECOND + 300
// }	led_time_t;

// typedef enum {
// 	LED_START,
// 	LED_BRIGHT,
// 	LED_DIM,
// 	LED_STOP
// }	led_state_t;

int main(void) {
	system_result_t status = system_init();  

	apb2_enable_t enable = GPIOC_CLOCK_ENABLE | GPIOA_CLOCK_ENABLE | AFIO_CLOCK_ENABLE;
	status = APB2_enable_clock(enable);

	led_indicate_state(status);

	while (1) {
		delay(300);
	}

	// gpio_configure(GPIO_PORT_A, GPIO_PIN_0, GPIO_OUTPUT_2MHz, AFO_PUSH_PULL);
	// timer_2_enable();
	// led_state_t led_state = LED_STOP;
	// while (1)
	// {
	// 	if (seconds <= LED_BRIGHT_START_SECOND) {
	// 		if (led_state != LED_START) { 
 	// 			light_on();
	// 			pwm_set_percent(100);
	// 			led_state = LED_START;
	// 		}
	// 	}
	// 	else if (seconds <= LED_DIM_EIGHT_HOURS_SECOND)
	// 	{ 
	// 		if (led_state != LED_DIM) {
	// 			pwm_set_percent(68);
	// 			led_state = LED_DIM;
	// 		} 
	// 	}
	// 	else if (seconds <= LED_BRIGHT_MORNING_SECOND)
	// 	{	
	// 		if (led_state != LED_BRIGHT) { 
	// 			pwm_set_percent(100);
	// 			led_state = LED_BRIGHT;
	// 		}
	// 	}
	// 	else if (seconds <= LED_OFF_SECOND) { 
	// 		if (led_state != LED_STOP) { 
	// 			light_off();
	// 			pwm_set_percent(0);
	// 			led_state = LED_STOP; 
	// 		}  
	// 	}
	// 	else {
	// 		seconds = 0;
	// 	}
	// }
	return 0;
}