#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "LED.h"
#include "KEY.h"
void app_main(void)
{
    uint8_t key_num = 0;
    led_init();             
    key_init();

    while(1)
    {
        key_num = key_scan();
        if(key_num)
        {
            LED_TOGGLE(); 
        }
    }
}
