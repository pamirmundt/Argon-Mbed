#include "ArgonJointParams.h"
#include "hal_inits_params.h"
#include "hal_inits.h"

using namespace HalInitParams;

namespace ArgonJointParams
{
    //--------------------------------------------------------------------------
    // RPM Calculation
    //--------------------------------------------------------------------------
    TIM_HandleTypeDef * rpm_calc_timer      = &htim6;
    const float rpm_calc_freq               = ((float)timer6_freq)/((float)(timer6_prescaler+1))/((float)(timer6_period+1));
    //const uint16_t rpm_calc_timer_prescaler = timer6_prescaler;
    //const uint16_t rpm_calc_timer_period    = timer6_period;
    
    //--------------------------------------------------------------------------
    // Front Left Wheel / Joint 1
    //--------------------------------------------------------------------------
    // PWM
    const uint8_t joint1_number             = 1;
    TIM_HandleTypeDef * joint1_PWM_timer    = &htim8;
    const uint32_t joint1_PWM_channel       = TIM_CHANNEL_1;
    // Input Capture - Encoder
    TIM_HandleTypeDef * joint1_ic_timer     = &htim2;
    const uint32_t joint1_ic_timer_CH_A     = TIM_CHANNEL_1;
    const uint32_t joint1_ic_timer_CH_B     = TIM_CHANNEL_2;
    
    const uint32_t joint1_ic_timer_act_CH_A = HAL_TIM_ACTIVE_CHANNEL_1;
    const uint32_t joint1_ic_timer_act_CH_B = HAL_TIM_ACTIVE_CHANNEL_2;
    
    GPIO_TypeDef * joint1_direction_port    = M1_DIR_PIN_GPIO_Port;
    uint16_t joint1_direction_pin           = M1_DIR_PIN_Pin;
    
    //--------------------------------------------------------------------------
    // Front Right heel / Joint 2
    //--------------------------------------------------------------------------
    // PWM
    const uint8_t joint2_number             = 2;
    TIM_HandleTypeDef * joint2_PWM_timer    = &htim8;
    const uint32_t joint2_PWM_channel       = TIM_CHANNEL_2;
    // Input Capture - Encoder
    TIM_HandleTypeDef * joint2_ic_timer     = &htim2;
    const uint32_t joint2_ic_timer_CH_A     = TIM_CHANNEL_3;
    const uint32_t joint2_ic_timer_CH_B     = TIM_CHANNEL_4;
    
    const uint32_t joint2_ic_timer_act_CH_A = HAL_TIM_ACTIVE_CHANNEL_3;
    const uint32_t joint2_ic_timer_act_CH_B = HAL_TIM_ACTIVE_CHANNEL_4;
    
    GPIO_TypeDef * joint2_direction_port    = M2_DIR_PIN_GPIO_Port;
    uint16_t joint2_direction_pin           = M2_DIR_PIN_Pin;
    
    //--------------------------------------------------------------------------
    // Rear Left Wheel / Joint 3
    //--------------------------------------------------------------------------
    const uint8_t joint3_number             = 3;
    TIM_HandleTypeDef * joint3_PWM_timer    = &htim8;
    const uint32_t joint3_PWM_channel       = TIM_CHANNEL_3;
    // Input Capture - Encoder
    TIM_HandleTypeDef * joint3_ic_timer     = &htim3;
    const uint32_t joint3_ic_timer_CH_A     = TIM_CHANNEL_1;
    const uint32_t joint3_ic_timer_CH_B     = TIM_CHANNEL_2;
    
    const uint32_t joint3_ic_timer_act_CH_A = HAL_TIM_ACTIVE_CHANNEL_1;
    const uint32_t joint3_ic_timer_act_CH_B = HAL_TIM_ACTIVE_CHANNEL_2;
    
    GPIO_TypeDef * joint3_direction_port    = M3_DIR_PIN_GPIO_Port;
    uint16_t joint3_direction_pin           = M3_DIR_PIN_Pin;
    
    //--------------------------------------------------------------------------
    // Rear Right Wheel / Joint 4
    //--------------------------------------------------------------------------
    const uint8_t joint4_number             = 4;
    TIM_HandleTypeDef * joint4_PWM_timer    = &htim8;
    const uint32_t joint4_PWM_channel       = TIM_CHANNEL_4;
    // Input Capture - Encoder
    TIM_HandleTypeDef * joint4_ic_timer     = &htim3;
    const uint32_t joint4_ic_timer_CH_A     = TIM_CHANNEL_3;
    const uint32_t joint4_ic_timer_CH_B     = TIM_CHANNEL_4;
    
    const uint32_t joint4_ic_timer_act_CH_A = HAL_TIM_ACTIVE_CHANNEL_3;
    const uint32_t joint4_ic_timer_act_CH_B = HAL_TIM_ACTIVE_CHANNEL_4;
    
    GPIO_TypeDef * joint4_direction_port    = M4_DIR_PIN_GPIO_Port;
    uint16_t joint4_direction_pin           = M4_DIR_PIN_Pin;
    
    //--------------------------------------------------------------------------
    // Joint 5
    //--------------------------------------------------------------------------
    const uint8_t joint5_number             = 5;
    TIM_HandleTypeDef * joint5_PWM_timer    = &htim12;
    const uint32_t joint5_PWM_channel       = TIM_CHANNEL_1;
    // Input Capture - Encoder
    TIM_HandleTypeDef * joint5_ic_timer     = &htim8;
    const uint32_t joint5_ic_timer_CH_A     = TIM_CHANNEL_1;
    const uint32_t joint5_ic_timer_CH_B     = TIM_CHANNEL_2;
    
    const uint32_t joint5_ic_timer_act_CH_A = HAL_TIM_ACTIVE_CHANNEL_1;
    const uint32_t joint5_ic_timer_act_CH_B = HAL_TIM_ACTIVE_CHANNEL_2;
    
    GPIO_TypeDef * joint5_direction_port    = M5_DIR_PIN_GPIO_Port;
    uint16_t joint5_direction_pin           = M5_DIR_PIN_Pin;
    
    //--------------------------------------------------------------------------
    // Joint 6
    //--------------------------------------------------------------------------
    const uint8_t joint6_number             = 6;
    TIM_HandleTypeDef * joint6_PWM_timer    = &htim12;
    const uint32_t joint6_PWM_channel       = TIM_CHANNEL_2;
    // Input Capture - Encoder
    TIM_HandleTypeDef * joint6_ic_timer     = &htim8;
    const uint32_t joint6_ic_timer_CH_A     = TIM_CHANNEL_3;
    const uint32_t joint6_ic_timer_CH_B     = TIM_CHANNEL_4;
    
    const uint32_t joint6_ic_timer_act_CH_A = HAL_TIM_ACTIVE_CHANNEL_3;
    const uint32_t joint6_ic_timer_act_CH_B = HAL_TIM_ACTIVE_CHANNEL_4;
    
    GPIO_TypeDef * joint6_direction_port    = M6_DIR_PIN_GPIO_Port;
    uint16_t joint6_direction_pin           = M6_DIR_PIN_Pin;
}
