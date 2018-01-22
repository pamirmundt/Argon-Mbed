#include "hal_inits_params.h"

namespace HalInitParams{
    // Timer 2 (90Mhz)  - Input Capture
    // Joint 1 - CH1/CH2 - PA0/PA1
    // Joint 2 - CH3/CH4 - PB10/PB2
    TIM_HandleTypeDef htim2;
    const uint16_t timer2_prescaler = 0;
    const uint16_t timer2_period    = 65535;
    
    // Timer 3 (90Mhz)  - Input Capture
    //Joint 3 - CH1/CH2 - PA6/PA7
    //Joint 4 - CH3/CH4 - PB0/PB1
    TIM_HandleTypeDef htim3;
    const uint16_t timer3_prescaler = 0;
    const uint16_t timer3_period    = 65535;
    
    // Timer 4 (90Mhz)  - Input Capture
    //Joint 5 - CH1/CH2 - PB6/PB7
    //Joint 6 - CH3/CH4 - PB8/PB9
    TIM_HandleTypeDef htim4;
    const uint16_t timer4_prescaler = 0;
    const uint16_t timer4_period    = 65535;
    
    // Timer 6 (90Mhz) - Interrupt timer - RPM Calculation
    // 90Mhz/(999+1)/(449+1) = 200Hz
    TIM_HandleTypeDef htim6;
    const uint32_t timer6_freq      = 90000000; // 90Mhz
    const uint16_t timer6_prescaler = 999;
    const uint16_t timer6_period    = 449;
    
    // Timer 8 (180Mhz) - PWM
    // Joint 1 - CH1 - PC6
    // Joint 2 - CH2 - PC7 
    // Joint 3 - CH3 - PC8
    // Joint 4 - CH4 - PC9
    TIM_HandleTypeDef htim8;
    const uint16_t timer8_prescaler = 1;
    const uint16_t timer8_period    = 4095;
    
    // Timer 12 (90Mhz) - PWM
    // Joint 5 - CH1 - PB14
    // Joint 6 - CH2 - PB15
    TIM_HandleTypeDef htim12;
    const uint16_t timer12_prescaler  = 0;
    const uint16_t timer12_period     = 4095;
}
