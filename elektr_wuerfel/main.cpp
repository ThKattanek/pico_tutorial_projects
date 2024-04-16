#include<stdio.h>
#include<pico/stdlib.h>
#include<pico/rand.h>

#define PUSH_BUTTON_GPIO 15
#define FIRST_LED_GPIO 16

uint8_t char_rom[7] = {0x00, 0x40, 0x0c, 0x4c, 0x2d, 0x6d, 0x3f};

bool pressed_key = false;

void gpio_callback(uint gpio, uint32_t event_mask)
{
	if(gpio == PUSH_BUTTON_GPIO && event_mask == GPIO_IRQ_EDGE_RISE)
	{
		pressed_key = true;
	}
}

void set_number_to_led(uint8_t number)
{
	if(number >= 0 && number < 7)
	{
		gpio_put_masked(0x7f << FIRST_LED_GPIO, char_rom[number] << FIRST_LED_GPIO);
	}
}

int main()
{
	stdio_init_all();

	// init push button
	gpio_set_irq_enabled_with_callback(PUSH_BUTTON_GPIO, GPIO_IRQ_EDGE_RISE, true, gpio_callback);

	// init led's
	gpio_init_mask(0x7f << FIRST_LED_GPIO);
	gpio_set_dir_out_masked(0x7f << FIRST_LED_GPIO);

	set_number_to_led(0);

	uint8_t number;

	while(1)
	{
		if(pressed_key == true)
		{
			for(int i=0; i<25; i++)
			{
				number = get_rand_32()%6 + 1;
				set_number_to_led(number);
				sleep_ms(40);
			}

			pressed_key = false;
		}
	}
}
