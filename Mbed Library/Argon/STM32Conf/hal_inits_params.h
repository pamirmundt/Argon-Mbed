#ifndef HAL_INITS_PARAMS_H
#define HAL_INITS_PARAMS_H

#include "mbed.h"

namespace HalInitParams{
    // Timer 2 (90Mhz)  - Input Capture
    extern TIM_HandleTypeDef htim2;
    extern const uint16_t timer2_prescaler;
    extern const uint16_t timer2_period;
    
    // Timer 3 (90Mhz)  - Input Capture
    extern TIM_HandleTypeDef htim3;
    extern const uint16_t timer3_prescaler;
    extern const uint16_t timer3_period;
    
    // Timer 4 (90Mhz)  - Input Capture
    extern TIM_HandleTypeDef htim4;
    extern const uint16_t timer4_prescaler;
    extern const uint16_t timer4_period;
    
    // Timer 6 (90Mhz)  - Interrupt
    extern TIM_HandleTypeDef htim6;
    extern const uint32_t timer6_freq;
    extern const uint16_t timer6_prescaler;
    extern const uint16_t timer6_period;
    
    // Timer 8 (180Mhz) - PWM
    extern TIM_HandleTypeDef htim8;
    extern const uint16_t timer8_prescaler;
    extern const uint16_t timer8_period;
    
    
    // Timer 12 (90Mhz) - PWM
    extern TIM_HandleTypeDef htim12;
    extern const uint16_t timer12_prescaler;
    extern const uint16_t timer12_period;
}

#endif