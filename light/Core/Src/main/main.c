#include "main/main.h"
#include "HY_MOD/connectivity/spi1/callback.h"

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if (hspi == spi1_h.const_h.hspix)
    {
        spi1_rx_callback();
    }
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if (hspi == spi1_h.const_h.hspix)
    {
        spi1_tx_callback();
    }
}
