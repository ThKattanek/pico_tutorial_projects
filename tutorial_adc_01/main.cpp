#include<stdio.h>
#include<pico/stdlib.h>
#include<hardware/adc.h>

int main()
{
	stdio_init_all();

	adc_init();
	adc_set_temp_sensor_enabled(true);
	adc_select_input(4);

	while(1)
	{
		uint16_t adc_value = adc_read();
		float adc_voltage = adc_value * (3.3f / (1 << 12));
		float temp_sensor = 27.0f - (adc_voltage - 0.706f) / 0.001721f;

		printf("ADC4=%d, U=%fV, Temp=%f\n", adc_value, adc_voltage, temp_sensor);
		sleep_ms(1000);
	}
}
