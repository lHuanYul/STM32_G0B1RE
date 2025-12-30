#pragma once

#include "main/config.h"

typedef struct LightConst
{
    GPIOData SER;
    GPIOData SRCLK;
    GPIOData RCLK;
    GPIOData OE;
} LightConst;

typedef struct LightCtrl
{
    LightConst const_h;
    uint8_t data;
    const uint8_t light0;
    const uint8_t light1;
    const uint8_t light2;
    const uint8_t light3;
    const uint8_t light4;
    const uint8_t light5;
    const uint8_t light6;
    const uint8_t light7;
} LightCtrl;

extern LightCtrl light_h0;

#define LIGHT_ON(all,sel)       (all |= (sel))
#define LIGHT_OFF(all,sel)      (all &= ~(sel))
#define LIGHT_TOGGLE(all,sel)   (all ^= (sel))
