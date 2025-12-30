#include "light/main.h"

void light_load(LightCtrl *light)
{
    GPIO_WRITE(light->const_h.RCLK, 0);
    uint8_t mask;
    bool bit_val;
    for (mask = 0b00000001; mask != 0; mask <<= 1) 
    {
        bit_val = (light->data & mask) ? 1 : 0;
        GPIO_WRITE(light->const_h.SER, bit_val);
        GPIO_WRITE(light->const_h.SRCLK, 0);
        GPIO_WRITE(light->const_h.SRCLK, 1);
    }
    GPIO_WRITE(light->const_h.RCLK, 1);
}
