
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "LED.h"
#include "KEY.h"
#include "WDT.h"

void app_main(void)
{
    esp_err_t rets;
    
    rets = nvs_flash_init();            /* 初始化NVS */

    if (rets == ESP_ERR_NVS_NO_FREE_PAGES || rets == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        rets = nvs_flash_init();
    }
    led_init(); 
    key_init(); 
    wdt_init(3000000); 
    LED_show(); 
    while (1)
    {
        if (key_scan()) 
        {
            restart_timer(3000000); /* 喂狗 */
        }
        vTaskDelay(10); 
    }
}
