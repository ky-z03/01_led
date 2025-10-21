#include "WDT.h"

esp_timer_handle_t esp_tim_handle;                          /* 定时器回调函数句柄 */

void wdt_init(uint64_t tps)
{
    esp_timer_create_args_t tim_periodic_arg = {
    .callback =	&wdt_isr_handler,                           /* 设置回调函数 */
    .arg = NULL,                                            /* 不携带参数 */
    };
    /* 创建定时器事件 */
    esp_timer_create(&tim_periodic_arg, &esp_tim_handle);   /* 创建一个事件 */
    esp_timer_start_periodic(esp_tim_handle, tps);          /* 每周期内触发一次 */
}

void restart_timer(uint64_t timeout)
{
    esp_timer_restart(esp_tim_handle, timeout);             /* 重新启动当前运行的计时器，用以模拟喂狗过程 */
}

void IRAM_ATTR wdt_isr_handler(void *arg)
{
    esp_restart();                                          /* 若没有及时进行喂狗，那么芯片将一直进行复位 */
}
