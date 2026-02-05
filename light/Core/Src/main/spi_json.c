#include "main/spi_json.h"
#include "spi.h"

SpiJsonParametar spi1_h = {
    .spi_p = {
        .const_h = {
            .hspix = &hspi1,
            .MISO = { GPIOA, GPIO_PIN_11 },
            .MOSI = { GPIOA, GPIO_PIN_12 },
            .SCK  = { GPIOD, GPIO_PIN_8  },
            .NSS  = { GPIOD, GPIO_PIN_9  },
        },
        .rx.attr = {
            .name = "spiRxSem"
        },
        .tx.attr = {
            .name = "spiTxSem"
        },
    },
};

JsonPktPool json_pkt_pool;

static JsonPkt* recv_pkts[JSON_RECV_BUF_CAP];
JsonPktBuf spi_recv_buf = {
    .buf = recv_pkts,
    .cap = JSON_RECV_BUF_CAP,
};

static JsonPkt* trsm_pkts[JSON_TRSM_BUF_CAP];
JsonPktBuf spi_trsm_buf = {
    .buf = trsm_pkts,
    .cap = JSON_TRSM_BUF_CAP,
};
