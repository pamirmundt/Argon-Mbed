#include "stm32f4xx_hal.h"
#include "ArgonBase.h"
#include "hal_inits.h"

using namespace argon;

void ArgonBase::baseInit(void){
    
    // GPIO init
    MX_GPIO_Init();
    
    // ADC init
    //MX_ADC1_Init();
    
    // Timer 2 - IC init
    MX_TIM2_Init();

    // Timer 3 - IC init
    MX_TIM3_Init();
    
    // Timer 4 - IC init
    //MX_TIM4_Init();
    
    // Timer 6 - RPM Calculation Interrupt
    MX_TIM6_Init();

    // Timer 8 - PWM init
    MX_TIM8_Init();
    
    //Timer 12 - PWM init
    //MX_TIM12_Init();
    
    // Timer 2 - Start IC IT
    HAL_TIM_IC_Start_IT(joint1._getICTimer(), joint1._getICTimerChannelA());
    HAL_TIM_IC_Start_IT(joint1._getICTimer(), joint1._getICTimerChannelB());
    HAL_TIM_IC_Start_IT(joint2._getICTimer(), joint2._getICTimerChannelA());
    HAL_TIM_IC_Start_IT(joint2._getICTimer(), joint2._getICTimerChannelB());
    
    // Timer 3 - Start IC IT
    HAL_TIM_IC_Start_IT(joint3._getICTimer(), joint3._getICTimerChannelA());
    HAL_TIM_IC_Start_IT(joint3._getICTimer(), joint3._getICTimerChannelB());
    HAL_TIM_IC_Start_IT(joint4._getICTimer(), joint4._getICTimerChannelA());
    HAL_TIM_IC_Start_IT(joint4._getICTimer(), joint4._getICTimerChannelB());
    
    // Timer 4 - Start IC IT
    //HAL_TIM_IC_Start_IT(joint5._getICTimer(), joint5._getICTimerChannelA());
    //HAL_TIM_IC_Start_IT(joint5._getICTimer(), joint5._getICTimerChannelB());
    //HAL_TIM_IC_Start_IT(joint6._getICTimer(), joint6._getICTimerChannelA());
    //HAL_TIM_IC_Start_IT(joint6._getICTimer(), joint6._getICTimerChannelB());
    
    // Timer 6 - RPM calculation interrupt
    HAL_TIM_Base_Start_IT(_getRpmCalcTimer());
    
    // Timer 8 - Start PWM
    HAL_TIM_PWM_Start(joint1._getPwmTimer(), joint1._getPwmTimerChannel());
    HAL_TIM_PWM_Start(joint2._getPwmTimer(), joint2._getPwmTimerChannel());
    HAL_TIM_PWM_Start(joint3._getPwmTimer(), joint3._getPwmTimerChannel());
    HAL_TIM_PWM_Start(joint4._getPwmTimer(), joint4._getPwmTimerChannel());
    
    // Enable PWM - Timer 12
    //HAL_TIM_PWM_Start(joint5._getPwmTimer(), joint5._getPwmTimerChannel());
    //HAL_TIM_PWM_Start(joint6._getPwmTimer(), joint6._getPwmTimerChannel());
    
}

ArgonJoint* ArgonBase::getJoint(uint8_t jointNum){
    ArgonJoint * retJoint;
    switch (jointNum){
        case 2:
            retJoint = &ArgonJoint::joint2_Instance();
            break;
        case 3:
            retJoint = &ArgonJoint::joint3_Instance();
            break;
        case 4:
            retJoint = &ArgonJoint::joint4_Instance();
            break;            
        // else return joint1
        default:
            retJoint = &ArgonJoint::joint1_Instance();
            break;
    }    
    return retJoint;
}


/* Sets */
//Config
//void _setWheelRadius(void);
//void _setLengthBetweenFrontAndRearWheels(void);
//void _setLengthBetweenFrontWheels(void);

/* Gets */
//Config
float ArgonBase::getWheelRadius(void){
    return _wheelRadius;
}
    
float ArgonBase::getLengthBetweenFrontAndRearWheels(void){
    return _lengthBetweenFrontAndRearWheels;
}

float ArgonBase::getLengthBetweenFrontWheels(void){
    return _lengthBetweenFrontWheels;
}

float ArgonBase::getGeomFactor(void){
    return _geomFactor;
}

//------------------------------------------------------------------------------
// Joint Extension
//------------------------------------------------------------------------------
// Sets
void ArgonBase::setPWM(uint8_t jointNum,int16_t PWM){
    getJoint(jointNum)->setPWM(PWM);
}

void ArgonBase::setPower(uint8_t jointNum, float power){
    getJoint(jointNum)->setPower(power);
}

// Gets
bool ArgonBase::getAvailable(uint8_t jointNum){
    return getJoint(jointNum)->getAvailable();
}

uint8_t ArgonBase::getNumber(uint8_t jointNum){
    return getJoint(jointNum)->getNumber();
}

float ArgonBase::getGearRatio(uint8_t jointNum){
    return getJoint(jointNum)->getGearRatio();
}

uint16_t ArgonBase::getEncoderTicksPerRound(uint8_t jointNum){
    return getJoint(jointNum)->getEncoderTicksPerRound();
}

uint8_t ArgonBase::getEncodingMode(uint8_t jointNum){
    return getJoint(jointNum)->getEncodingMode();
}

int16_t ArgonBase::getPwm(uint8_t jointNum){
    return getJoint(jointNum)->getPwm();
}

uint16_t ArgonBase::getPwmResolution(uint8_t jointNum){
    return getJoint(jointNum)->getPwmResolution();
}

float ArgonBase::getPower(uint8_t jointNum){
    return getJoint(jointNum)->getPower();
}

int8_t ArgonBase::getDirection(uint8_t jointNum){
    return getJoint(jointNum)->getDirection();
}

int32_t ArgonBase::getEncoderCount(uint8_t jointNum){
    return getJoint(jointNum)->getEncoderCount();
}

float ArgonBase::getJointPosition(uint8_t jointNum){
    return getJoint(jointNum)->getJointPosition();
}

float ArgonBase::getMotorPosition(uint8_t jointNum){
    return getJoint(jointNum)->getMotorPosition();
}

float ArgonBase::getMotorRPM(uint8_t jointNum){
    return getJoint(jointNum)->getMotorRPM();
}

float ArgonBase::getJointRPM(uint8_t jointNum){
    return getJoint(jointNum)->getJointRPM();
}

float ArgonBase::getMotorAngVel(uint8_t jointNum){
    return getJoint(jointNum)->getMotorAngVel();
}

float ArgonBase::getJointAngVel(uint8_t jointNum){
    return getJoint(jointNum)->getJointAngVel();
}
