#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "LED.h"
#include "EXIT.h"

void app_main(void)
{
    led_init();             
    exit_init();

    while(1)
    {
        
    }
}
