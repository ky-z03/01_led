#ifndef __LED_H_
#define __LED_H_

#include "driver/gpio.h"

#define LED_GPIO_PIN    GPIO_NUM_1  

/*LED低电平驱动*/
#define LED_show()   do {gpio_set_level(LED_GPIO_PIN, 0);} while(0)  
#define LED_close()  do {gpio_set_level(LED_GPIO_PIN, 1);} while(0)  

/* LED翻转*/
#define LED_TOGGLE() do { gpio_set_level(LED_GPIO_PIN, !gpio_get_level(LED_GPIO_PIN)); } while(0)  /* LED翻转 */

void led_init(void);    

#endif
