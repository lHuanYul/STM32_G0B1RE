#include "main/main.h"
#include "main/mod_cfg.h"
#include "HY_MOD/main/variable_cal.h"
#include "HY_MOD/packet/json.h"
#include "HY_MOD/connectivity/spi1/callback.h"
#include "HY_MOD/connectivity/spi1/main.h"

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if (hspi == spi1_h.const_h.hspix)
    {
        spi1_rx_callback(&spi1_h, &json_pkt_pool, &spi_recv_buf);
    }
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if (hspi == spi1_h.const_h.hspix)
    {
        spi1_tx_callback(&spi1_h, &json_pkt_pool, &spi_trsm_buf);
    }
}

uint8_t spi_test = 0;
void StartSpi1Task(void *argument)
{
    json_pkt_pool_init(&json_pkt_pool);
    SpiParametar *spi = &spi1_h;
    spi_init(spi);

    JsonPkt *my_tx = RESULT_UNWRAP_HANDLE(json_pkt_pool_alloc(&json_pkt_pool));
    json_pkt_set_len(my_tx, sizeof(SPI_MASTER_ASK));
    memcpy(my_tx->data, SPI_MASTER_ASK, my_tx->len);

    const char json_response[] = "{\"TR\":\"SC\"}";

    osDelay(5000);
    for(;;)
    {
        switch (spi1_h.state)
        {
            case SPI_STATE_ERROR:
            {
                while(1) osDelay(1000);
                spi1_h.state = SPI_STATE_FINISH; 
                goto next_loop;
            }
            case SPI_STATE_FINISH:
            {
                if (spi_test) goto next_loop;
                spi_test++;
                spi->tx_buf_len = my_tx->len;
                memcpy(spi->tx_buf, my_tx->data, my_tx->len);
                RESULT_CHECK_GOTO(spi_start_transmit(spi), next_loop);
                osDelay(100);
                break;
            }
            case SPI_STATE_RECV_HEADER:
            {
                spi->rx_buf_len = sizeof(SPI_LENGTH_H);
                RESULT_CHECK_GOTO(spi_start_receive(spi), next_loop);
                if (spi1_h.state != SPI_STATE_RECV_BODY)
                {
                    goto next_loop;
                }
                osDelay(100);
                break;
            }
            case SPI_STATE_RECV_BODY:
            {
                RESULT_CHECK_GOTO(spi_start_receive(spi), next_loop);
                if (spi1_h.state != SPI_STATE_FINISH)
                {
                    goto next_loop;
                }
                osDelay(100);
                break;
            }
            case SPI_STATE_TRSM_HEADER:
            {
                spi->tx_buf_len = sizeof(SPI_LENGTH_H);
                memcpy(spi->tx_buf, SPI_LENGTH_H, spi->tx_buf_len);
                var_u16_to_u8_be((uint16_t)strlen(json_response), (uint8_t *)(spi->tx_buf + 3));
                RESULT_CHECK_GOTO(spi_start_transmit(spi), next_loop);
                if (spi1_h.state != SPI_STATE_TRSM_BODY)
                {
                    goto next_loop;
                }
                osDelay(100);
                break;
            }
            case SPI_STATE_TRSM_BODY:
            {
                spi->tx_buf_len = (uint16_t)strlen((char*)json_response);
                memcpy(spi->tx_buf, json_response, spi->tx_buf_len);
                RESULT_CHECK_GOTO(spi_start_transmit(spi), next_loop);
                if (spi1_h.state != SPI_STATE_FINISH)
                {
                    goto next_loop;
                }
                osDelay(100);
                break;
            }
        }
        continue;
next_loop:
        osDelay(1000);
    }

    json_pkt_pool_free(&json_pkt_pool, my_tx);
}
