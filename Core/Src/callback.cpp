#include "main.h"
#include "usart.h"
#include <string.h>

extern uint8_t rx_buf[18];
uint8_t last_buf[18];
volatile uint8_t data_ready = 0;
volatile uint32_t last_receive_tick = 0;
extern uint8_t is_connected;

extern UART_HandleTypeDef huart3;

// ----------------- 启动 HALEx DMA -----------------
// ----------------- DMA + 空闲回调 -----------------
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if(huart->Instance != USART3) return;

    // 拷贝数据到 last_buf
    memcpy(last_buf, rx_buf, Size);
    data_ready = 1;

    // 更新接收时间戳
    last_receive_tick = HAL_GetTick();

    // 继续接收下一帧
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rx_buf, 18);
}

// ----------------- 主循环处理 -----------------
void DMA_MainLoopTask(void)
{
    // 通过 HAL_GetTick() 判断连接状态
     is_connected = (HAL_GetTick() - last_receive_tick <= 1000) ? 1 : 0;
    // data_ready 可用于触发调试观察
    if(data_ready)
    {
        data_ready = 0;
    }

}