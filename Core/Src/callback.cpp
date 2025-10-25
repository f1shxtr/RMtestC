#include "main.h"
#include "usart.h"
#include <string.h>
#include "rc.h"


RC_Class rc;

void init() {
    rc.init();
}
extern UART_HandleTypeDef huart3;

// ----------------- 启动 HALEx DMA -----------------
// ----------------- DMA + 空闲回调 -----------------
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if(huart->Instance != USART3) return;

    // 拷贝数据到 last_buf
    memcpy(rc.pData, rc.rx_buf, Size);
    rc.data_ready = 1;

    // 更新接收时间戳
    rc.last_receive_tick = HAL_GetTick();

    // 继续接收下一帧
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rc.rx_buf, 18);
}

// ----------------- 主循环处理 -----------------
void DMA_MainLoopTask(void)
{
    // 通过 HAL_GetTick() 判断连接状态
     rc.is_connected = (HAL_GetTick() - rc.last_receive_tick <= 1000) ? 1 : 0;
    // data_ready 可用于触发调试观察
    if(rc.data_ready)
    {
        rc.handle();
        rc.data_ready = 0;
    }

}