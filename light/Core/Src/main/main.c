#include "main/main.h"
#include "main/spi_json.h"
#include "HY_MOD/spi_json/callback.h"

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
    spi_json_rx_cb(&spi1_h, hspi, &json_pkt_pool, &spi_recv_buf);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    spi_json_tx_cb(&spi1_h, hspi, &json_pkt_pool, &spi_trsm_buf);
}
