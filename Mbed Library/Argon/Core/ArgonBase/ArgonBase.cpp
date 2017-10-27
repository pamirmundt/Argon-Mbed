/* Includes ------------------------------------------------------------------*/
#include "ArgonBase.h"

#include "stm32f4xx_hal.h"

#include <stdbool.h>


/* External fucnitons --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
extern void MX_GPIO_Init(void);
extern void MX_TIM1_Init(void);
extern void MX_TIM3_Init(void);
extern void MX_TIM4_Init(void);
extern void MX_TIM8_Init(void);
extern void MX_TIM2_Init(void);
extern void MX_TIM6_Init(void);

/* Private Variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim8;

/* Prototype Functions -------------------------------------------------------*/
void baseInit(void);
void baseEncoderStart(void);
void baseRpmStart(void);
void basePwmStart(void);

/* Functions ---------------------------------------------------------------- */
void baseInit(void){
    //initialize GPIO and Timers
    MX_GPIO_Init();
    MX_TIM1_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
    MX_TIM8_Init();
    MX_TIM2_Init();
    MX_TIM6_Init();
    
    //Start PWM Timers
    basePwmStart();
    //Start Encoder Timers
    baseEncoderStart();
    //Start RPM Calculation Timer
    baseRpmStart();
}

void baseEncoderStart(void){
    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_ALL);  
}

void baseRpmStart(void){
    HAL_TIM_Base_Start_IT(&htim6);  
}

void basePwmStart(void){
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4); 
}

float ArgonBase::getWheelRadius(void){
	return wheelRadius;
}

float ArgonBase::getGearRatio(void){
	return gearRatio;
}

float ArgonBase::getLengthBetweenFrontAndRearWheels(void){
	return lengthBetweenFrontAndRearWheels;
}

float ArgonBase::getLengthBetweenFrontWheels(void){
	return lengthBetweenFrontWheels;
}

void ArgonBase::getVelocity(float & longitudinalVelocity, float &  transversalVelocity, float & angularVelocity){
	float jointRPM1 = this->frontLeft.getJointRPM();
	float jointRPM2 = this->frontRight.getJointRPM();
	float jointRPM3 = this->rearLeft.getJointRPM();
	float jointRPM4 = this->rearRight.getJointRPM();

	this->kinematics.wheelVelocitiesToCartesianVelocity(jointRPM1, jointRPM2, jointRPM3, jointRPM4, longitudinalVelocity, transversalVelocity, angularVelocity);
}

float ArgonBase::getLongitudinalVelocity(void){
	float longitudinalVelocity, transversalVelocity, angularVelocity;
	this->getVelocity(longitudinalVelocity, transversalVelocity, angularVelocity);
	return longitudinalVelocity;
}

float ArgonBase::getTransversalVelocity(void){
	float longitudinalVelocity, transversalVelocity, angularVelocity;
	this->getVelocity(longitudinalVelocity, transversalVelocity, angularVelocity);
	return transversalVelocity;
}

float ArgonBase::getAngularVelocity(void){
	float longitudinalVelocity, transversalVelocity, angularVelocity;
	this->getVelocity(longitudinalVelocity, transversalVelocity, angularVelocity);
	return angularVelocity;
}

void ArgonBase::getPosition(float & longitudinalPosition, float & transversalPosition, float & angularPosition){
	longitudinalPosition = this->longitudinalPosition;
	transversalPosition = this->transversalPosition;
	angularPosition = this->angularPosition;
}

float ArgonBase::getLongitudinalPosition(void){
	return this->longitudinalPosition;
}

float ArgonBase::getTransversalPosition(void){
	return this->transversalPosition;
}

float ArgonBase::getAngularPosition(void){
	return this->angularPosition;
}

void ArgonBase::updatePosition(void){
	int16_t jointEncoder1 = this->frontLeft.getEncoderCount();
	int16_t jointEncoder2 = this->frontRight.getEncoderCount();
	int16_t jointEncoder3 = this->rearLeft.getEncoderCount();
	int16_t jointEncoder4 = this->rearRight.getEncoderCount();

	this->kinematics.wheelPositionsToCartesianPosition(jointEncoder1, jointEncoder2, jointEncoder3, jointEncoder4, this->longitudinalPosition, this->transversalPosition, this->angularPosition);
}
