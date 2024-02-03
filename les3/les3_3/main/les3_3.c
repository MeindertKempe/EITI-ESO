#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/ledc_types.h"
#include <stdio.h>

void app_main(void) {
	gpio_set_direction(GPIO_NUM_2, GPIO_MODE_INPUT_OUTPUT);

	_Bool state = true;
	for (;;) {
		esp_err_t e = gpio_set_level(GPIO_NUM_2, state);

		printf("LED toggle\n");
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		state = !state;
	}
}
