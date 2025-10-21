#ifndef __EXIT_H
#define __EXIT_H

#include "driver/gpio.h"
#include "esp_system.h" 
#include "esp_log.h"
#include "sdkconfig.h"
#include "LED.h"

#define BOOT_INT_PIN GPIO_NUM_0

void exit_init();


#endif 