#include "main/main.h"
#include "main/mod_cfg.h"
#include "HY_MOD/main/variable_cal.h"
#include "HY_MOD/packet/json.h"
#include "HY_MOD/connectivity/spi1/callback.h"
#include "HY_MOD/connectivity/spi1/main.h"

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
    spi_rx_cb(&spi1_h, hspi, &json_pkt_pool, &spi_recv_buf);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    spi_tx_cb(&spi1_h, hspi, &json_pkt_pool, &spi_trsm_buf);
}

uint8_t spi_test = 0;
void StartSpi1Task(void *argument)
{
    json_pkt_pool_init(&json_pkt_pool);
    SpiParametar *spi = &spi1_h;
    spi_init(spi);

    JsonPkt *tx_header = RESULT_UNWRAP_HANDLE(json_pkt_pool_alloc(&json_pkt_pool));
    json_pkt_set_len(tx_header, sizeof(SPI_MASTER_ASK));
    memcpy(tx_header->data, SPI_MASTER_ASK, tx_header->len);

    const char json_response[] = "{\"TR\":\"SC\"}";
    JsonPkt *tx_normal = RESULT_UNWRAP_HANDLE(json_pkt_pool_alloc(&json_pkt_pool));
    json_pkt_set_len(tx_normal, (uint16_t)strlen(json_response));
    memcpy(tx_normal->data, json_response, tx_normal->len);
    RESULT_CHECK_HANDLE(json_pkt_buf_push(&spi_trsm_buf, tx_normal, &json_pkt_pool, 0));

    osDelay(5000);
    JsonPkt *tx_pkt = NULL;
    for(;;)
    {
        switch (spi1_h.state)
        {
            case SPI_STATE_ERROR:
            {
                // while(1) osDelay(1000);
                spi1_h.state = SPI_STATE_FINISH; 
                goto next_loop;
            }
            case SPI_STATE_FINISH:
            {
                if (spi_test) goto next_loop;
                spi_test++;
                spi->tx_buf_len = tx_header->len;
                memcpy(spi->tx_buf, tx_header->data, tx_header->len);
                RESULT_CHECK_GOTO(spi_start_transmit(spi), next_loop);
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
                break;
            }
            case SPI_STATE_RECV_BODY:
            {
                RESULT_CHECK_GOTO(spi_start_receive(spi), next_loop);
                if (spi1_h.state != SPI_STATE_FINISH)
                {
                    goto next_loop;
                }
                spi1_h.state = SPI_STATE_TRSM_HEADER;
                osDelay(900);
                break;
            }
            case SPI_STATE_TRSM_HEADER:
            {
                tx_pkt = RESULT_UNWRAP_GOTO(json_pkt_buf_get(&spi_trsm_buf), tx_skip);
                spi->tx_buf_len = sizeof(SPI_LENGTH_H);
                memcpy(spi->tx_buf, SPI_LENGTH_H, spi->tx_buf_len);
                var_u16_to_u8_be(tx_pkt->len, (uint8_t *)(spi->tx_buf + 3));
                RESULT_CHECK_GOTO(spi_start_transmit(spi), tx_skip);
                if (spi1_h.state != SPI_STATE_TRSM_BODY)
                {
                    goto tx_skip;
                }
                break;
            }
            case SPI_STATE_TRSM_BODY:
            {
                if (tx_pkt == NULL) goto next_loop;
                spi->tx_buf_len = tx_pkt->len;
                memcpy(spi->tx_buf, tx_pkt->data, spi->tx_buf_len);
                RESULT_CHECK_GOTO(spi_start_transmit(spi), tx_skip);
                if (spi1_h.state != SPI_STATE_FINISH)
                {
                    goto next_loop;
                }
                break;
            }
        }
        osDelay(100);
        continue;
tx_skip:
        tx_pkt = NULL;
next_loop:
        osDelay(1000);
    }

    json_pkt_pool_free(&json_pkt_pool, tx_header);
}
