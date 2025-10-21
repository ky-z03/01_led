#include "GPTIMER.h"
#include "LED.h"

QueueHandle_t queue;

void gptim_int_init(uint16_t counts, uint32_t resolution)
{
    gptimer_config_t g_tim_handle;
    gptimer_alarm_config_t alarm_config;
    gptimer_event_callbacks_t g_tim_callbacks;

    uint64_t count;

    /* 配置通用定时器 */
    ESP_LOGI("GPTIMER_ALARM", "配置通用定时器");                                         /* 创建通用定时器句柄 */
    gptimer_handle_t g_tim = NULL;
    g_tim_handle.clk_src = GPTIMER_CLK_SRC_DEFAULT;                                     /* 选择定时器时钟源 */
    g_tim_handle.direction = GPTIMER_COUNT_UP;                                          /* 递增计数模式 */         
    g_tim_handle.resolution_hz = resolution;                                            /* 计数器分辨率 */
    g_tim_callbacks.on_alarm = gptimer_callback;                                        /* 注册用户回调函数 */ 
    alarm_config.alarm_count = 1000000;                                                 /* 报警目标计数值 */
    ESP_ERROR_CHECK(gptimer_new_timer(&g_tim_handle, &g_tim));                          /* 创建新的通用定时器，并返回句柄 */

    queue = xQueueCreate(10, sizeof(gptimer_event_t));                                  /* 创建一个队列，并引入一个事件 */

    if (!queue)
    {
        ESP_LOGE("GPTIMER_ALARM", "创建队列失败");                                       /* 创建队列失败 */

        return;
    }

    /* 设置和获取计数值 */
    ESP_LOGI("GPTIMER_ALARM", "设置计数值");
    ESP_ERROR_CHECK(gptimer_set_raw_count(g_tim, counts));                              /* 设置计数值 */
    ESP_LOGI("GPTIMER_ALARM", "获取计数值");
    ESP_ERROR_CHECK(gptimer_get_raw_count(g_tim, &count));                              /* 获取计数值 */
    ESP_LOGI("GPTIMER_ALARM", "定时器计数值： %llu", count);

    /* 注册事件回调函数 */
    ESP_ERROR_CHECK(gptimer_register_event_callbacks(g_tim, &g_tim_callbacks, queue));  /* 配置通用定时器回调函数 */

    /* 设置报警动作 */
    ESP_LOGI("GPTIMER_ALARM", "使能通用定时器");
    ESP_ERROR_CHECK(gptimer_enable(g_tim));                                             /* 使能通用定时器 */
    ESP_ERROR_CHECK(gptimer_set_alarm_action(g_tim, &alarm_config));                    /* 配置通用定时器报警事件 */
    ESP_ERROR_CHECK(gptimer_start(g_tim));                                              /* 启动通用定时器 */
}

bool IRAM_ATTR gptimer_callback(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_data)
{
    LED_TOGGLE();
    BaseType_t high_task_awoken = pdFALSE;
    queue = (QueueHandle_t)user_data;

    /* 从事件数据中检索计数值 */
    gptimer_event_t ele = {
        .event_count = edata->count_value
    };

    /* 可选：通过操作系统队列将事件数据发送到其他任务 */
    xQueueSendFromISR(queue, &ele, &high_task_awoken);
    
    /* 重新配置报警值 */ 
    gptimer_alarm_config_t alarm_config = {
        .alarm_count = edata->alarm_value + 1000000, /* 在接下来的1秒内报警 */ 
    };
    gptimer_set_alarm_action(timer, &alarm_config);
    
    /* 返回是否需要在ISR结束时让步 */ 
    return high_task_awoken == pdTRUE;
}
