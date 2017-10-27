#include "ArgonJoint.h"

#include <stdlib.h>
#include "Inits.h"
#include "params.h"


/* External variables --------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/
#ifndef M_PI
#define M_PI        3.14159265358979323846f
#endif

#ifndef RPM2RAD
#define RPM2RAD     ((2.0f*M_PI)/60.0f)
#endif

#ifndef TICK2RAD
#define TICK2RAD    ((360.0f/encoder_resolution/encoder_mode)*(M_PI/180.0f))
#endif

/*******************************************************************************
    RPM Resolution per encoder tick
        (Encoder tick/sec) to RPM
    Example:  1  encoder tick per second = 187,5 RPM
              2  encoder tick per second = 375,0 RPM

                        60sec * (Frequency of RPM calculation timer)
    RPM_res_per_tick = ----------------------------------------------
                        Encoder Resolution * Encoder Reading Mode(x4)
*******************************************************************************/
#define RPM_res_per_tick (60.0f * Timer6Frequency) / (encoder_resolution*encoder_mode)

/* Sets --------------------------------------------------------------------- */

void ArgonJoint::setName(char * jointName){
	this->_jointName = jointName;
}

void ArgonJoint::setNumber(uint8_t motorNumber){
	this->_motorNumber = motorNumber;
}

void ArgonJoint::setWheelRadius(float wheelRad){	//-> Change Here
	this->_wheelRadius = wheelRad;
}

void ArgonJoint::setGearRatio(float gearRati){	//-> Change Here
	this->_gearRatio = gearRati;
}

void ArgonJoint::setEncoderTicksPerRound(uint16_t encoderTicksPerRound){
	this->_encoderTicksPerRound = encoderTicksPerRound;
}

void ArgonJoint::setQuadEncoderTicksPerRound(uint16_t quadEncoderTicksPerRound){
	this->_quadEncoderTicksPerRound = quadEncoderTicksPerRound;
}

void ArgonJoint::setMaximumRPM(float maximumRPM){
	this->_maximumRPM = maximumRPM;
}

void ArgonJoint::setMaximumAngularVelocity(float maximumAngularVelocity){
	this->_maximumAngularVelocity = maximumAngularVelocity;
}

void ArgonJoint::setPWMTimer(TIM_HandleTypeDef timerPWM, uint32_t timerChannelPWM){
	this->_timerPWM = timerPWM;
	this->_timerChannelPWM = timerChannelPWM;
}

void ArgonJoint::setDefaultDirection(uint8_t defaultDirection){
	this->_defaultDirection = defaultDirection;
}

void ArgonJoint::setDirectionGPIO(GPIO_TypeDef* directionGpioPort, uint16_t directionGpioPin){
	this->_directionGpioPort = directionGpioPort;
	this->_directionGpioPin = directionGpioPin;
}

void ArgonJoint::setEncoderTimer(TIM_HandleTypeDef timerEncoder){
	this->_timerEncoder = timerEncoder;
}

void ArgonJoint::setPWM(int16_t PWM){
	//Direction
	if(PWM >= 0){
		setDirection(counterClockWise);
		this->_direction = counterClockWise;
	}
	else{
		setDirection(clockWise);
		this->_direction = clockWise;
	}

	//Write PWM
	__HAL_TIM_SET_COMPARE(&this->_timerPWM, this->_timerChannelPWM, abs(PWM));
}

void ArgonJoint::setDirection(uint8_t direction){
	GPIO_PinState state = GPIO_PIN_RESET;
	if(this->_defaultDirection == counterClockWise)
		if(direction == counterClockWise)
			state = GPIO_PIN_RESET;
		else
			state = GPIO_PIN_SET;
	else
		if(direction)
			state = GPIO_PIN_RESET;
		else
			state = GPIO_PIN_SET;

	HAL_GPIO_WritePin(this->_directionGpioPort, this->_directionGpioPin, state);
}

void ArgonJoint::setPrevEncoderCount(int16_t prevMotorEncoderCount){
	this->_prevEncoderCount = prevMotorEncoderCount;
}

void ArgonJoint::setPrevRPM(float prevRPM){
	this->_prevRPM = prevRPM;
}

void ArgonJoint::setPrevFilteredRPM(float prevFilteredRPM){
	this->_prevFilteredRPM = prevFilteredRPM;
}

void ArgonJoint::setPrevMotorPosition(float prevMotorPosition){
	this->_prevMotorPosition = prevMotorPosition;
}

/* Gets --------------------------------------------------------------------- */

const char* ArgonJoint::getName(void) const{
	return this->_jointName;
}

uint8_t ArgonJoint::getNumber(void){
	return this->_motorNumber;
}

float ArgonJoint::getWheelRadius(void){
	return this->_wheelRadius;
}

float ArgonJoint::getGearRatio(void){
	return this->_gearRatio;
}

uint16_t ArgonJoint::getEncoderTicksPerRound(void){
	return this->_encoderTicksPerRound;
}

uint16_t ArgonJoint::getQuadEncoderTicksPerRound(void){
	return this->_quadEncoderTicksPerRound;
}

float ArgonJoint::getMaximumRPM(void){
	return this->_maximumRPM;
}

float ArgonJoint::getMaximumAngularVelocity(void){
	return this->_maximumAngularVelocity;
}

TIM_HandleTypeDef ArgonJoint::getPWMTimer(void){
	return this->_timerPWM;
}

uint32_t ArgonJoint::getPWMTimerChannel(void){
	return this->_timerChannelPWM;
}

uint8_t ArgonJoint::getDirection(void){
	return this->_direction;
}

uint8_t ArgonJoint::getDefaultDirection(void){
	return this->_defaultDirection;
}

const GPIO_TypeDef* ArgonJoint::getDirectionPort(void) const{
	return this->_directionGpioPort;
}

uint16_t ArgonJoint::getDirectionPin(void){
	return this->_directionGpioPin;
}

TIM_HandleTypeDef ArgonJoint::getEncoderTimer(void){
	return this->_timerEncoder;
}

int16_t ArgonJoint::getPWM(void){
	int16_t PWM = (int16_t)__HAL_TIM_GET_COMPARE(&this->_timerPWM, this->_timerChannelPWM);

	if(this->_defaultDirection == counterClockWise)
		if(this->_direction == counterClockWise)
			return PWM;
		else
			return -PWM;
	else
		if(this->_direction == counterClockWise)
			return PWM;
		else
			return -PWM;
}

int16_t ArgonJoint::getEncoderCount(void){
	if(this->_defaultDirection)
		return (this->_timerEncoder.Instance->CNT);
	else
		return (65536 - this->_timerEncoder.Instance->CNT);
}

float ArgonJoint::getJointRPM(void){
	if(RPM_MAF)
		return this->_prevFilteredRPM / gearRatio;
	else
		return this->_prevRPM / gearRatio;
}

float ArgonJoint::getMotorRPM(void){
	if(RPM_MAF)
		return this->_prevFilteredRPM;
	else
		return this->_prevRPM;
}

float ArgonJoint::getJointAngVel(void){
	return (this->getJointRPM() * RPM2RAD);
}

float ArgonJoint::getMotorAngVel(void){
	return (this->getMotorRPM() * RPM2RAD);
}

float ArgonJoint::getJointPosition(void){
	return this->getPrevMotorPosition() / gearRatio;
}

float ArgonJoint::getMotorPosition(void){
	return this->getPrevMotorPosition();
}

int16_t ArgonJoint::getPrevEncoderCount(void){
	return this->_prevEncoderCount;
}

float ArgonJoint::getPrevFilteredRPM(void){
	return this->_prevFilteredRPM;
}

float ArgonJoint::getPrevMotorPosition(void){
	return this->_prevMotorPosition;
}

/* Calculate RPM ------------------------------------------------------------ */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if(htim->Instance == TIM6){
		// Motor 1
		int16_t motorEncoderCount1 = ArgonJoint::frontLeftJointInstance().getEncoderCount();
		int16_t deltaMotorEncoderCount1 = motorEncoderCount1 - ArgonJoint::frontLeftJointInstance().getPrevEncoderCount();
		float motorRPM1 = RPM_res_per_tick * ((float)((int16_t)deltaMotorEncoderCount1));
		ArgonJoint::frontLeftJointInstance().setPrevRPM(motorRPM1);
		ArgonJoint::frontLeftJointInstance().setPrevEncoderCount(motorEncoderCount1);
		if (RPM_MAF){
			float filteredMotorRPM1 = (RPM_MAF_Alpha * motorRPM1) + (1.0f - RPM_MAF_Alpha) * ArgonJoint::frontLeftJointInstance().getPrevFilteredRPM();
			ArgonJoint::frontLeftJointInstance().setPrevFilteredRPM(filteredMotorRPM1);
		}
		// Motor 2
		int16_t motorEncoderCount2 = ArgonJoint::frontRightJointInstance().getEncoderCount();
		int16_t deltaMotorEncoderCount2 = motorEncoderCount2 - ArgonJoint::frontRightJointInstance().getPrevEncoderCount();
		float motorRPM2 = RPM_res_per_tick * ((float)((int16_t)(deltaMotorEncoderCount2)));
		ArgonJoint::frontRightJointInstance().setPrevRPM(motorRPM2);
		ArgonJoint::frontRightJointInstance().setPrevEncoderCount(motorEncoderCount2);
		if (RPM_MAF){
			float filteredMotorRPM2 = (RPM_MAF_Alpha * motorRPM2) + (1.0f - RPM_MAF_Alpha) * ArgonJoint::frontRightJointInstance().getPrevFilteredRPM();
			ArgonJoint::frontRightJointInstance().setPrevFilteredRPM(filteredMotorRPM2);
		}
		
		// Motor 3
		int16_t motorEncoderCount3 = ArgonJoint::rearLeftJointInstance().getEncoderCount();
		int16_t deltaMotorEncoderCount3 = motorEncoderCount3 - ArgonJoint::rearLeftJointInstance().getPrevEncoderCount();
		float motorRPM3 = RPM_res_per_tick * ((float)((int16_t)(deltaMotorEncoderCount3)));
		ArgonJoint::rearLeftJointInstance().setPrevRPM(motorRPM3);
		ArgonJoint::rearLeftJointInstance().setPrevEncoderCount(motorEncoderCount3);
		if (RPM_MAF){
			float filteredMotorRPM3 = (RPM_MAF_Alpha * motorRPM3) + (1.0f - RPM_MAF_Alpha) * ArgonJoint::rearLeftJointInstance().getPrevFilteredRPM();
			ArgonJoint::rearLeftJointInstance().setPrevFilteredRPM(filteredMotorRPM3);
		}
		
		// Motor 4
		int16_t motorEncoderCount4 = ArgonJoint::rearRightJointInstance().getEncoderCount();
		int16_t deltaMotorEncoderCount4 = motorEncoderCount4 - ArgonJoint::rearRightJointInstance().getPrevEncoderCount();
		float motorRPM4 = RPM_res_per_tick * ((float)((int16_t)(deltaMotorEncoderCount4)));
		ArgonJoint::rearRightJointInstance().setPrevRPM(motorRPM4);
		ArgonJoint::rearRightJointInstance().setPrevEncoderCount(motorEncoderCount4);
		if (RPM_MAF){
			float filteredMotorRPM4 = (RPM_MAF_Alpha * motorRPM4)+(1.0f - RPM_MAF_Alpha) * ArgonJoint::rearRightJointInstance().getPrevFilteredRPM();
			ArgonJoint::rearRightJointInstance().setPrevFilteredRPM(filteredMotorRPM4);
		}

		//Wheel Positions Update (radians)
		float frontLeftPosition = (TICK2RAD * ((float)deltaMotorEncoderCount1)) + ArgonJoint::frontLeftJointInstance().getPrevMotorPosition();
		float frontRightPosition = (TICK2RAD * ((float)deltaMotorEncoderCount2)) + ArgonJoint::frontRightJointInstance().getPrevMotorPosition();
		float rearLeftPosition = (TICK2RAD * ((float)deltaMotorEncoderCount3)) + ArgonJoint::rearLeftJointInstance().getPrevMotorPosition();
		float rearRightPosition = (TICK2RAD * ((float)deltaMotorEncoderCount4)) + ArgonJoint::rearRightJointInstance().getPrevMotorPosition();
		ArgonJoint::frontLeftJointInstance().setPrevMotorPosition(frontLeftPosition);
		ArgonJoint::frontRightJointInstance().setPrevMotorPosition(frontRightPosition);
		ArgonJoint::rearLeftJointInstance().setPrevMotorPosition(rearLeftPosition);
		ArgonJoint::rearRightJointInstance().setPrevMotorPosition(rearRightPosition);
	}
}

