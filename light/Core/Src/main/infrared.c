#include "main/infrared.h"
#include "tim.h"
#include "HY_MOD/main/tim.h"

IRParameter infrared_h = {
    .const_h = {
        .Master_htimx = &htim17,
        .Master_TIM_CHANNEL_x = TIM_CHANNEL_1,
        .Master_tim_clk = &tim_clk_APB1,
        // PC1     ------> TIM15_CH1
        .Slave_htimx = &htim15,
        .Slave_TIM_CHANNEL_x = TIM_CHANNEL_1,
    },
};
