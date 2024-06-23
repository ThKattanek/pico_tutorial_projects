#include <stdio.h>
#include <math.h>
#include <pico/stdlib.h>
#include <hardware/adc.h>

const float conversion_factor = 3.275f / (1 << 12);

int main()
 {
	stdio_init_all();

	adc_init();
	adc_gpio_init(26);
	adc_select_input(0);

	while (1)
	{
		uint16_t result = adc_read();
		float voltage = result * conversion_factor;

		printf("Voltage: %f\n", voltage);
		sleep_ms(100);
	}
}
