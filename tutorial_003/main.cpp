#include<stdio.h>
#include<pico/stdlib.h>

#define PUSH_BUTTON_GPIO 17
#define LED_GPIO 16

void gpio_callback(uint gpio, uint32_t event_mask);

bool blink_state = false;

int main()
{
	stdio_init_all();

	gpio_init(PUSH_BUTTON_GPIO);
	gpio_disable_pulls(PUSH_BUTTON_GPIO);
	gpio_set_input_hysteresis_enabled(PUSH_BUTTON_GPIO, true);

	gpio_init(LED_GPIO);
	gpio_set_dir(LED_GPIO, true);

	gpio_set_irq_enabled_with_callback(PUSH_BUTTON_GPIO, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, gpio_callback);

	while(1)
	{
		if(blink_state)
		{
			gpio_put(LED_GPIO, true);
			sleep_ms(70);
			gpio_put(LED_GPIO, false);
			sleep_ms(70);
		}
	}
}

void gpio_callback(uint gpio, uint32_t event_mask)
{
	if(gpio == PUSH_BUTTON_GPIO)
	{
		if(event_mask & GPIO_IRQ_EDGE_RISE)
		{
			blink_state = false;
		}

		if(event_mask & GPIO_IRQ_EDGE_FALL)
		{
			blink_state = true;
		}
	}
}