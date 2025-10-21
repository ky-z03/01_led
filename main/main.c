#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "LED.h"
#include "UART.h"

void app_main(void)
{
    esp_err_t ret;   
    uint8_t len = 0;
    unsigned char receive_data[20] = {0};
    unsigned char send_data[20] = {01,02,03,04,05,06,07};
    ret = nvs_flash_init(); /* 初始化NVS */
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    led_init();             
    uart_init(115200);
    while(1)
    {
        // uart_write_bytes(USART_UX,
        //                 (const char*)send_data,
        //                 strlen((const char*)send_data)); /* 写数据 */   
        // uart_wait_tx_done(USART_UX, portMAX_DELAY);
        
        uart_get_buffered_data_len(USART_UX, (size_t*) &len);
        if(len)
        {
            uart_read_bytes(USART_UX, receive_data, len, 100);
            uart_write_bytes(USART_UX,
            (const char*)receive_data,
            strlen((const char*)receive_data)); /* 写数据 */   
            uart_wait_tx_done(USART_UX, portMAX_DELAY);
            memset(receive_data, 0, 20);
        }
        vTaskDelay(1000);         
    }
}
