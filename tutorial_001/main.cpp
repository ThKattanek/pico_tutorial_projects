#include<stdio.h>
#include<pico/stdlib.h>

#define LED_PIN 16
#define PUSH_BUTTON 17
#define LED_TIME 3000

int main()
{
	stdio_init_all();
	printf("Test\n");

	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, true);
	
	gpio_init(PUSH_BUTTON);
	gpio_set_pulls(PUSH_BUTTON, false, true);

	while(1)
	{
		if(gpio_get(PUSH_BUTTON))
		{
			gpio_put(LED_PIN, true);
			sleep_ms(LED_TIME);
			gpio_put(LED_PIN, false);
		}
	}
}