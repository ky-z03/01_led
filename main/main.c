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
    uint8_t dir = 1;
    uint16_t ledrpwmval = 0;
    ret = nvs_flash_init();/* 初始化 NVS */
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
    ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    pwm_init(10, 1000); /* 初始化 PWM */
    while (1)
    {
        vTaskDelay(10);
        if (dir == 1)
        {
            /* dir==1,ledrpwmval 递增 */
            ledrpwmval += 5;
        }
        else
        {
            /* dir==0,ledrpwmval 递减 */
            ledrpwmval -= 5;
        }
        if (ledrpwmval > 1005)
        {
            /* ledrpwmval 到达 1005 后，方向改为递减 */
            dir = 0;
        }
        if (ledrpwmval < 5)
        {
            /* ledrpwmval 递减到 5 后，方向改为递增 */
            dir = 1;
        }
        /* 设置占空比 */
        pwm_set_duty(ledrpwmval);
    }
}