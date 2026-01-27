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
