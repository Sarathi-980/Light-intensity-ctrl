#include "system.h"
#include "gpio.h"
#include <stdint.h>
#include "f103c6t6_regs.h" 
#include "system_exceptions.h" 

extern volatile uint32_t seconds; 

void light_off() {
	GPIOx_config_regs(GPIOC_BASE)->BSRR = (1 << (GPIO_PIN_0 + 16));
}
 
int main(void) {
	system_result_t status = system_init();  

	apb2_enable_t enable = GPIOC_CLOCK_ENABLE | GPIOA_CLOCK_ENABLE | AFIO_CLOCK_ENABLE;
	status = APB2_enable_clock(enable);

	led_indicate_state(status);

	while (1) {
		delay(300);
	}

	return 0;
}