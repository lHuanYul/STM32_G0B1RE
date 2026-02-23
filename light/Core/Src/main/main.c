#include "main/main.h"

#include "main/spi_json.h"
#include "HY_MOD/spi/callback.h"

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
    spi_rx_cb(&spi1_h.spi_p, hspi);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    spi_tx_cb(&spi1_h.spi_p, hspi);
}

#include "main/infrared.h"
#include "HY_MOD/infrared/callback.h"

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    ir_trsm_cb(&infrared_h, htim);
}

#include "main/light.h"
#include "HY_MOD/light/main.h"

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
    light_button(&light_h, GPIO_Pin);
}

#define TASK_DELAY_MS 1000
uint32_t default_running;
void StartDefaultTask(void *argument)
{
    const uint32_t osPeriod = pdMS_TO_TICKS(TASK_DELAY_MS);
    uint32_t next_wake = osKernelGetTickCount() + osPeriod;
    for (;;)
    {
        default_running = HAL_GetTick();
        osDelayUntil(next_wake);
        next_wake += osPeriod;
    }
}
