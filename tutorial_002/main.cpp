#include<stdio.h>
#include<pico/stdlib.h>

#define PUSH_BUTTON_GPIO 17
#define LED_GPIO 16

int main()
{
	stdio_init_all();

	gpio_init(PUSH_BUTTON_GPIO);
	gpio_pull_down(PUSH_BUTTON_GPIO);

	gpio_init(LED_GPIO);
	gpio_set_dir(LED_GPIO, true);

	bool new_gpio_state = false;
	bool old_gpio_state = false;

	bool new_push_button_state = false;
	bool old_push_button_state = false;

	while(1)
	{
		new_gpio_state = gpio_get(PUSH_BUTTON_GPIO);

		if(new_gpio_state != old_gpio_state)
		{
			sleep_ms(1);

			new_push_button_state = gpio_get(PUSH_BUTTON_GPIO);
			if(new_push_button_state == false && old_push_button_state == true)
			{
				gpio_xor_mask(1 << LED_GPIO);
			}
			old_push_button_state = new_push_button_state;
		}

		old_gpio_state = new_gpio_state;
	}
}
