#ifndef __PWM_H
#define __PWM_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"


// #define LEDC_PWM_TIMER LEDC_TIMER_1 /* 使用定时器 1 */
// #define LEDC_PWM_CH0_GPIO GPIO_NUM_1 /* LED 控制器通道对应 GPIO */
// #define LEDC_PWM_CH0_CHANNEL LEDC_CHANNEL_1 /* LED 控制器通道号 */
/*硬件修改PWM占空比*/
#define LEDC_PWM_TIMER LEDC_TIMER_0 /* 使用定时器 0 */
#define LEDC_PWM_MODE LEDC_LOW_SPEED_MODE/* 模式设定必须使用 LEDC 低速模式 */
#define LEDC_PWM_CH0_GPIO GPIO_NUM_1 /* LED 控制器通道对应 GPIO */
#define LEDC_PWM_CH0_CHANNEL LEDC_CHANNEL_0 /* LED 控制器通道号 */
#define LEDC_PWM_DUTY 8000 /* 渐变的变大最终目标占空比 */
#define LEDC_PWM_FADE_TIME 3000 /* 变化时长 */

void pwm_init(uint8_t resolution, uint16_t freq);
void pwm_set_duty(uint16_t duty);

#endif