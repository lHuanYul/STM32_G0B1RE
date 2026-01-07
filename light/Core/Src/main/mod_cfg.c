#include "main/mod_cfg.h"
#include "HY_MOD/connectivity/spi1/basic.h"
#include "spi.h"

__attribute__((aligned(32))) static uint8_t rx_buf[JSON_PKT_LEN + 32];
__attribute__((aligned(32))) static uint8_t tx_buf[JSON_PKT_LEN + 32];

SpiParametar spi1_h = {
    .const_h = {
        .hspix = &hspi1,
        .MISO = {GPIOA, GPIO_PIN_6},
        .MOSI = {GPIOA, GPIO_PIN_7},
        .SCK = {GPIOD, GPIO_PIN_8},
        .NSS = {GPIOD, GPIO_PIN_9},
    },
    .rx_handle_attr = {
        .name = "spiRxSem"
    },
    .rx_buf = rx_buf,
    .tx_handle_attr = {
        .name = "spiTxSem"
    },
    .tx_buf = tx_buf,
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
