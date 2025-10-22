#ifndef __PWM_H
#define __PWM_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

#define LEDC_PWM_TIMER LEDC_TIMER_1 /* 使用定时器 1 */
#define LEDC_PWM_CH0_GPIO GPIO_NUM_1 /* LED 控制器通道对应 GPIO */
#define LEDC_PWM_CH0_CHANNEL LEDC_CHANNEL_1 /* LED 控制器通道号 */

void pwm_init(uint8_t resolution, uint16_t freq);
void pwm_set_duty(uint16_t duty);

#endif