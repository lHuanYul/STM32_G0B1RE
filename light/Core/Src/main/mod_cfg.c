#include "main/mod_cfg.h"
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

LightCtrl light_h0 = {
    .const_h = {
        .SRCLK = {
            .GPIOx = GPIOA,
            .GPIO_Pin_x = GPIO_PIN_4
        },
        .RCLK = {
            .GPIOx = GPIOB,
            .GPIO_Pin_x = GPIO_PIN_1
        },
        .OE = {
            .GPIOx = GPIOA,
            .GPIO_Pin_x = GPIO_PIN_1
        },
        .SER = {
            .GPIOx = GPIOA,
            .GPIO_Pin_x = GPIO_PIN_0
        },
    },
    .light0 = 0b00000001,
    .light1 = 0b00000010,
    .light2 = 0b00000100,
    .light3 = 0b00001000,
    .light4 = 0b00010000,
    .light5 = 0b00100000,
    .light6 = 0b01000000,
    .light7 = 0b10000000,
};
