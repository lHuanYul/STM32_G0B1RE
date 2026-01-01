#include "light/main.h"

void light_load(LightCtrl *light)
{
    GPIO_WRITE(light->const_h.RCLK, 0);
    uint8_t mask;
    bool bit_val;
    for (mask = 0b10000000; mask != 0; mask >>= 1) 
    {
        bit_val = (light->data & mask) ? 1 : 0;
        GPIO_WRITE(light->const_h.SER, bit_val);
        GPIO_WRITE(light->const_h.SRCLK, 0);
        GPIO_WRITE(light->const_h.SRCLK, 1);
    }
    GPIO_WRITE(light->const_h.RCLK, 1);
}

uint32_t defalt_running = 0;
void StartDefaultTask(void *argument)
{
    defalt_running++;
    GPIO_WRITE(light_h0.const_h.OE, 0);
    for (;;)
    {
        defalt_running++;
        // GPIO_TOGGLE(light_h0.const_h.SER);
        LIGHT_TOGGLE(light_h0, light_h0.light0);
        light_load(&light_h0);
        osDelay(2500);
    }
}
