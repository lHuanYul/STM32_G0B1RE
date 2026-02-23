/*
#include "main/config.h"
*/
#pragma once

#include "HY_MOD/main/basic.h"

// ! SYSTEM config, Change CAREFULLY --------------------
// ! Also CHECK ALL basic.c file
// #include "arm_math.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

#include "stm32g0b1xx.h"
#include "stm32g0xx_hal.h"

#define STM32_DEVICE
#define STM32_G0
#define STM32G0B1RE
#define MCU_MOTOR_CTRL
// #include "connectivity/cmds.h"
#define FDCAN_FIFO0_FILTER0_ID_MIN  0x148
#define FDCAN_FIFO0_FILTER0_ID_MAX  0x14F
#define FDCAN_FIFO1_FILTER0_ID_MIN  0x140
#define FDCAN_FIFO1_FILTER0_ID_MAX  0x147
// #define FDCAN_FIFO1_FILTER0_ID_MIN  0x000
// #define FDCAN_FIFO1_FILTER0_ID_MAX  0x7FF

#define TIM_DTG_200ns   0x22
#define TIM_DTG_300ns   0x33
#define TIM_DTG_500ns   0x55
#define TIM_DTG_1us     0x95

#define TIM15_PSC   0
#define TIM15_ARR   420 // Max: 65535
#define TIM15_PWM1  TIM15_ARR / 3

#define TIM17_PSC   15
#define TIM17_ARR   65535 // Max: 65535

#define FDCAN_STD_FILTER_NBR    2
// #define FDCAN_RX0_NBR           16
// #define FDCAN_RX1_NBR           16
// #define FDCAN_RX_BUF_NBR        0
// #define FDCAN_TX_BUF_NBR        4
// #define FDCAN_TX_FIFO_NBR       16
// #define FDCAN_TX_EVT_NBR        (FDCAN_TX_BUF_NBR+FDCAN_TX_FIFO_NBR)
#define FDCAN_PKT_LEN       8
#define FDCAN_PKT_POOL_CAP  32
#define FDCAN_TRSM_BUF_CAP  10
#define FDCAN_RECV_BUF_CAP  10

#define HY_MOD_STM32_SPI_JSON
#define HY_MOD_STM32_JSON
#define JSON_PKT_LEN        1024
#define JSON_PKT_POOL_CAP   10
#define JSON_TRSM_BUF_CAP   4
#define JSON_RECV_BUF_CAP   4

#define HY_MOD_LIGHT
#define LIGHT_BUTTON_CD 8
#define LIGHT_MAIN      0
#define LIGHT_STORAGE   1

#define HY_MOD_IR_TRSM

// ! Also CHECK ALL basic.c file
// ! SYSTEM config END ------------------------------
