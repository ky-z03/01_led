#include "KEY.h"

volatile uint8_t g_key_state = 0;/*按键初始状态为松开*/

void key_init(void)
{
    gpio_config_t gpio_init_struct;
    gpio_init_struct.intr_type = GPIO_INTR_DISABLE;        /* 失能引脚中断 */
    gpio_init_struct.mode = GPIO_MODE_INPUT;               /* 输入模式 */
    gpio_init_struct.pull_up_en = GPIO_PULLUP_ENABLE;      /* 使能上拉 */
    gpio_init_struct.pull_down_en = GPIO_PULLDOWN_DISABLE; /* 失能下拉 */
    gpio_init_struct.pin_bit_mask = 1ull << BOOT_GPIO_PIN; /* BOOT 按键引脚 */
    gpio_config(&gpio_init_struct); /* 配置使能 */
}
uint8_t key_scan()
{
    uint8_t  keyval = 0;
    if(!BOOT && !g_key_state)
    {
        vTaskDelay(10);
        if(!BOOT && !g_key_state)
        {
            g_key_state = 1;/*按键按下*/
            keyval = 1;
        }
    }
    vTaskDelay(1);
    if(BOOT && g_key_state)
    {
        vTaskDelay(10);
        if(BOOT && g_key_state)
        {
            g_key_state = 0;/*按键松开*/
            keyval = 0;
        }
    } 

    return keyval; /* 返回键值 */
}