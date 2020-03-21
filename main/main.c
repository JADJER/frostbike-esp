/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include "display.h"

void app_main(void) {
  printf("Hello world!\n");

  gpio_config_t led_pin;
  led_pin.intr_type = 0;
  led_pin.pin_bit_mask = GPIO_SEL_2;
  led_pin.mode = GPIO_MODE_OUTPUT;
  led_pin.pull_down_en = 1;
  led_pin.pull_up_en = 0;
  gpio_config(&led_pin);

  gpio_set_level(GPIO_NUM_2, 1);

  display_config_t *display = display_init(1, 2);

  /* Print chip information */
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);
  printf("This is %s chip with %d CPU cores, WiFi%s%s, ",
         CONFIG_IDF_TARGET,
         chip_info.cores,
         (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
         (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

  printf("silicon revision %d, ", chip_info.revision);

  printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
         (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

  for (int i = 10; i >= 0; i--) {
    printf("Restarting in %d seconds...\n", i);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  printf("Restarting now.\n");

  gpio_set_level(2, 0);

  fflush(stdout);

  esp_restart();
}
