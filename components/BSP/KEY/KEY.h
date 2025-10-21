#ifndef __KEY_H
#define __KEY_H

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BOOT_GPIO_PIN GPIO_NUM_0

#define BOOT gpio_get_level(BOOT_GPIO_PIN)

void key_init(void); 
uint8_t key_scan(); 



#endif