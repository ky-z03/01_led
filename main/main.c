#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "LED.h"
#include "PWM.h"

void app_main(void)
{
    esp_err_t ret;
    ret = nvs_flash_init();/* 初始化 NVS */
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
    ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    pwm_init(13, 5000); /* 初始化 PWM */
    while (1)
    {
        vTaskDelay(10);
        pwm_set_duty(LEDC_PWM_DUTY);
    }
}