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

#include "HY_MOD/infrared/basic.h"
#include "HY_MOD/infrared/callback.h"

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    ir_trsm_cb(&infrared_h, htim);
    
}

#define DEFAULT_TASK_DELAY_MS 1000
uint32_t default_running;
void StartDefaultTask(void *argument)
{
    ir_code_gen(&infrared_h, IR_CODE_HERAN_FAN_POWER);
    
    const uint32_t osPeriod = pdMS_TO_TICKS(DEFAULT_TASK_DELAY_MS);
    uint32_t next_wake = osKernelGetTickCount() + osPeriod;
    for (;;)
    {
        default_running = HAL_GetTick();
        osDelayUntil(next_wake);
        next_wake += osPeriod;
    }
}
