#include <stdio.h>
#include <math.h>
#include <pico/stdlib.h>
#include <hardware/adc.h>

#define FIRST_LED_PIN 2
#define LED_COUNT 7
#define LED_MASK ((1 << LED_COUNT)-1) << FIRST_LED_PIN

uint16_t time_ms = 1000;

int main()
{
	stdio_init_all();

	adc_init();
	adc_gpio_init(26);
	adc_select_input(0);

	gpio_init_mask(LED_MASK);
	gpio_set_dir_out_masked(LED_MASK);

	uint32_t led_lauf = 1;

	while(1)
	{
		uint16_t result = adc_read();
		time_ms = (result >> 4) + 10;

		gpio_put_masked(LED_MASK, led_lauf << FIRST_LED_PIN);
		led_lauf <<= 1;
		if(led_lauf == (1 << LED_COUNT))
			led_lauf = 1;

		sleep_ms(time_ms);
	}
}
