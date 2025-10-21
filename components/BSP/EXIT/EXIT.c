#include "EXIT.h"


static void IRAM_ATTR exit_gpio_isr_handler(void *arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    if(gpio_num == BOOT_INT_PIN)
    {
        LED_TOGGLE();
    }
}


void exit_init()
{
    gpio_config_t gpio_init_struct;
    gpio_init_struct.mode        = GPIO_MODE_INPUT;
    gpio_init_struct.pull_up_en  = GPIO_PULLUP_ENABLE;
    gpio_init_struct.pull_down_en= GPIO_PULLDOWN_DISABLE;
    gpio_init_struct.intr_type   = GPIO_INTR_NEGEDGE;
    gpio_init_struct.pin_bit_mask= 1ull << BOOT_INT_PIN;
    gpio_config(&gpio_init_struct);

    gpio_install_isr_service(ESP_INTR_FLAG_EDGE);

    gpio_isr_handler_add(BOOT_INT_PIN, exit_gpio_isr_handler,
                        (void*)BOOT_INT_PIN);

    gpio_intr_enable(BOOT_INT_PIN);
}