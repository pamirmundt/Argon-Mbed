#ifndef ARGONJOINTPARAMS_H
#define ARGONJOINTPARAMS_H

#include "mbed.h"

namespace ArgonJointParams
{
    //RPM Calculation
    extern TIM_HandleTypeDef * rpm_calc_timer;
    extern const float rpm_calc_freq;
    
    //Joint 1
    extern const uint8_t joint1_number;
    extern TIM_HandleTypeDef * joint1_PWM_timer;
    extern const uint32_t joint1_PWM_channel;
    extern TIM_HandleTypeDef * joint1_ic_timer;
    extern const uint32_t joint1_ic_timer_CH_A;
    extern const uint32_t joint1_ic_timer_CH_B;
    extern const uint32_t joint1_ic_timer_act_CH_A;
    extern const uint32_t joint1_ic_timer_act_CH_B;
    extern GPIO_TypeDef * joint1_direction_port;
    extern uint16_t joint1_direction_pin;
    
    //Joint 2
    extern const uint8_t joint2_number;
    extern TIM_HandleTypeDef * joint2_PWM_timer;
    extern const uint32_t joint2_PWM_channel;
    extern TIM_HandleTypeDef * joint2_ic_timer;
    extern const uint32_t joint2_ic_timer_CH_A;
    extern const uint32_t joint2_ic_timer_CH_B;
    extern const uint32_t joint2_ic_timer_act_CH_A;
    extern const uint32_t joint2_ic_timer_act_CH_B;
    extern GPIO_TypeDef * joint2_direction_port;
    extern uint16_t joint2_direction_pin;

    //Joint 3
    extern const uint8_t joint3_number;
    extern TIM_HandleTypeDef * joint3_PWM_timer;
    extern const uint32_t joint3_PWM_channel;
    extern TIM_HandleTypeDef * joint3_ic_timer;
    extern const uint32_t joint3_ic_timer_CH_A;
    extern const uint32_t joint3_ic_timer_CH_B;
    extern const uint32_t joint3_ic_timer_act_CH_A;
    extern const uint32_t joint3_ic_timer_act_CH_B;
    extern GPIO_TypeDef * joint3_direction_port;
    extern uint16_t joint3_direction_pin;

    //Joint 4
    extern const uint8_t joint4_number;
    extern TIM_HandleTypeDef * joint4_PWM_timer;
    extern const uint32_t joint4_PWM_channel;
    extern TIM_HandleTypeDef * joint4_ic_timer;
    extern const uint32_t joint4_ic_timer_CH_A;
    extern const uint32_t joint4_ic_timer_CH_B;
    extern const uint32_t joint4_ic_timer_act_CH_A;
    extern const uint32_t joint4_ic_timer_act_CH_B;
    extern GPIO_TypeDef * joint4_direction_port;
    extern uint16_t joint4_direction_pin;

    //Joint 5
    extern const uint8_t joint5_number;
    extern TIM_HandleTypeDef * joint5_PWM_timer;
    extern const uint32_t joint5_PWM_channel;
    extern TIM_HandleTypeDef * joint5_ic_timer;
    extern const uint32_t joint5_ic_timer_CH_A;
    extern const uint32_t joint5_ic_timer_CH_B;
    extern const uint32_t joint5_ic_timer_act_CH_A;
    extern const uint32_t joint5_ic_timer_act_CH_B;
    extern GPIO_TypeDef * joint5_direction_port;
    extern uint16_t joint5_direction_pin;

    //Joint 6
    extern const uint8_t joint6_number;
    extern TIM_HandleTypeDef * joint6_PWM_timer;
    extern const uint32_t joint6_PWM_channel;
    extern TIM_HandleTypeDef * joint6_ic_timer;
    extern const uint32_t joint6_ic_timer_CH_A;
    extern const uint32_t joint6_ic_timer_CH_B;
    extern const uint32_t joint6_ic_timer_act_CH_A;
    extern const uint32_t joint6_ic_timer_act_CH_B;
    extern GPIO_TypeDef * joint6_direction_port;
    extern uint16_t joint6_direction_pin;
}

#endif