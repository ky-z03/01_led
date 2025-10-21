
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "LED.h"
#include "GPTIMER.h"


void app_main(void)
{
    uint8_t record;
    esp_err_t ret;
    gptimer_event_t g_tim_evente;
    
    ret = nvs_flash_init();                                                                   /* 初始化NVS */

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    
    led_init();                                                                               /* 初始化LED */
    gptim_int_init(100, 1000000);                                                             /* 初始化通用定时器 */
    
    while (1)
    {
        record = 1;

        if (xQueueReceive(queue, &g_tim_evente, 2000))
        {
            ESP_LOGI("GPTIMER_ALARM", "定时器报警, 计数值： %llu", g_tim_evente.event_count);   /* 打印通用定时器发生一次计数事件后获取到的值 */
            record--;
        }
        else
        {
            ESP_LOGW("GPTIMER_ALARM", "错过一次计数事件");
        }
    }
    vQueueDelete(queue);
}
