#include "UART.h"


void uart_init(uint32_t baud)
{
    uart_config_t uart_init_struct;
    uart_init_struct.baud_rate = baud;
    uart_init_struct.data_bits = UART_DATA_8_BITS;
    uart_init_struct.parity     = UART_PARITY_DISABLE;   /* 无奇偶校验位 */
    uart_init_struct.stop_bits  = UART_STOP_BITS_1;      /* 一个停止位 */
    uart_init_struct.flow_ctrl  = UART_HW_FLOWCTRL_DISABLE; /* 无硬件控制流 */
    uart_init_struct.source_clk = UART_SCLK_APB;    /* 配置时钟源 */
    uart_init_struct.rx_flow_ctrl_thresh = 122;     /* 硬件控制流阈值 */
    uart_param_config(USART_UX, &uart_init_struct); /* 配置 uart 端口 */

    uart_set_pin(USART_UX,
                 USART_TX_GPIO_PIN,
                 USART_RX_GPIO_PIN,
                 UART_PIN_NO_CHANGE,
                 UART_PIN_NO_CHANGE);
    uart_driver_install(USART_UX,
                        RX_BUF_SIZE * 2,
                        RX_BUF_SIZE * 2,
                        20,
                        NULL,
                        0);             
}