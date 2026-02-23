#include "main/light.h"
#include "HY_MOD/light/basic.h"

LightCtrl light_h = {
    .const_h = {
        .SER = {
            .GPIOx = GPIOA,
            .Pin = GPIO_PIN_0
        },
        .OE = {
            .GPIOx = GPIOA,
            .Pin = GPIO_PIN_1
        },
        .SRCLK = {
            .GPIOx = GPIOA,
            .Pin = GPIO_PIN_4
        },
        .RCLK = {
            .GPIOx = GPIOB,
            .Pin = GPIO_PIN_1
        },
    },
    .lights = {
        .a = {
            .id = LIGHT_MAIN,
            .gpio = { GPIOB, GPIO_PIN_4 },
            .cd = LIGHT_BUTTON_CD,
        },
        .b = {
            .id = LIGHT_STORAGE,
            .gpio = { GPIOB, GPIO_PIN_5 },
            .cd = LIGHT_BUTTON_CD,
        },
        .c = {
            .id = 7,
            .gpio = { GPIOB, GPIO_PIN_3 },
            .cd = LIGHT_BUTTON_CD,
        },
    },
    .flags = 0x02,
};
