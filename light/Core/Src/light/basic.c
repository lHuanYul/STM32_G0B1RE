#include "light/basic.h"

LightCtrl light_h0 = {
    .const_h = {
        .SER = {
            .GPIOx = GPIOA,
            .GPIO_Pin_x = GPIO_PIN_0
        },
        .SRCLK = {
            .GPIOx = GPIOA,
            .GPIO_Pin_x = GPIO_PIN_0
        },
        .RCLK = {
            .GPIOx = GPIOA,
            .GPIO_Pin_x = GPIO_PIN_0
        },
        .OE = {
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
