#ifndef MOTOR_H
#define MOTOR_H

#include "stm32f4xx_hal.h"

enum jointDirections {
    counterClockWise,
    clockWise,
};

enum mecanumWheels {
    noWheel,
    frontLeft,      //WheelNumber 1
    frontRight,     //WheelNumber 2
    rearLeft,       //WheelNumber 3
    rearRight,      //WheelNumber 4
};

class ArgonJoint{
	ArgonJoint(){};
	public:
		static ArgonJoint& frontLeftJointInstance(){
			static ArgonJoint frontLeftJoint;
			return frontLeftJoint;
		}
		static ArgonJoint& frontRightJointInstance(){
			static ArgonJoint frontRightJoint;
			return frontRightJoint;
		}
		static ArgonJoint& rearLeftJointInstance(){
			static ArgonJoint rearLeftJoint;
			return rearLeftJoint;
		}
		static ArgonJoint& rearRightJointInstance(){
			static ArgonJoint rearRightJoint;
			return rearRightJoint;
		}
		//Sets
		//Inits
		void 									setName(char *);
		void 									setNumber(uint8_t);
		void 									setWheelRadius(float);
		void 									setGearRatio(float);
		void 									setEncoderTicksPerRound(float);
		void 									setQuadEncoderTicksPerRound(float);
		void 									setMaximumRPM(float);
		void 									setMaximumAngularVelocity(float);
		//PWM Timer Inits
		void 									setPWMTimer(TIM_HandleTypeDef, uint32_t);	//Timer, Channel
		//Direction Inits
		void 									setDefaultDirection(uint8_t);
		void 									setDirectionGPIO(GPIO_TypeDef*,uint16_t );	//Port, Pin
		//Encoder Timer
		void 									setEncoderTimer(TIM_HandleTypeDef);
		//General Use
		void 									setPWM(int16_t PWM);
		void 									setDirection(uint8_t direction);
		void									setPower(float power);
		//RPM Calculation
		void	 								setPrevEncoderCount(int16_t);
		void									setPrevRPM(float);
		void									setPrevFilteredRPM(float);
		//Position Calculation
		void									setPrevMotorPosition(float);

		//Gets
		//inits
		const char*							getName(void) const;
		uint8_t 							getNumber(void);
		float 								getWheelRadius(void);
		float 								getGearRatio(void);
		float 								getEncoderTicksPerRound(void);
		float	 							getQuadEncoderTicksPerRound(void);
		float 								getMaximumRPM(void);
		float 								getMaximumAngularVelocity(void);
		//Timer Inits
		TIM_HandleTypeDef 					getPWMTimer(void);
		uint32_t 							getPWMTimerChannel(void);
		//Direction
		uint8_t								getDirection(void);
		uint8_t 							getDefaultDirection(void);
		const GPIO_TypeDef* 				getDirectionPort(void) const;
		uint16_t 							getDirectionPin(void);
		//Encoder Timer
		TIM_HandleTypeDef 					getEncoderTimer(void);

		//General Use
		int16_t 							getPWM(void);
		float								getPower(void);
		int16_t 							getEncoderCount(void);

		float 								getJointRPM(void);
		float 								getMotorRPM(void);
		
		float 								getJointAngVel(void);
		float 								getMotorAngVel(void);

		float 								getJointPosition(void);
		float 								getMotorPosition(void);
		
		//RPM Calculation
		int16_t 							getPrevEncoderCount(void);
		float								getPrevFilteredRPM(void);

		//Position
		float								getPrevMotorPosition(void);
	
	private:
		char *								_jointName;
		uint8_t 							_motorNumber;
		float 								_wheelRadius;
		float								_gearRatio;
		float								_encoderTicksPerRound;
		float								_quadEncoderTicksPerRound;
		float								_maximumRPM;
		float								_maximumAngularVelocity;
	
		//PWM Timer
		TIM_HandleTypeDef 					_timerPWM;
		uint32_t 							_timerChannelPWM;
	
		//Direction
		uint8_t								_direction;
		uint8_t 							_defaultDirection;
		GPIO_TypeDef * 						_directionGpioPort;
		uint16_t 							_directionGpioPin;
	
		//Encoder
		TIM_HandleTypeDef 					_timerEncoder;
	
		//RPM Calculation
		int16_t 							_prevEncoderCount;
		float								_prevRPM;
		float								_prevFilteredRPM;

		//Position
		float								_prevMotorPosition;
};

#endif /* MOTOR_H */

