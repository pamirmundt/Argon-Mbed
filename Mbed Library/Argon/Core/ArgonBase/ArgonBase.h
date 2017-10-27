#ifndef BASE_H
#define BASE_H


/* Includes ------------------------------------------------------------------*/
#include "ArgonJoint.h"
#include "Inits.h"
#include "params.h"
#include "base_kinematics.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Prototype functions ------------------------------------------------------ */
void baseInit(void);
//void baseEncoderStart(void);
//void baseRpmStart(void);
//void basePwmStart(void);

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim8;

class ArgonBase{
	public:
	baseKinematics kinematics;
	ArgonJoint & frontLeft;
	ArgonJoint & frontRight;
	ArgonJoint & rearLeft;
	ArgonJoint & rearRight;
	ArgonBase():frontLeft(ArgonJoint::frontLeftJointInstance()),
				frontRight(ArgonJoint::frontRightJointInstance()),
				rearLeft(ArgonJoint::rearLeftJointInstance()),
				rearRight(ArgonJoint::rearRightJointInstance()),
				longitudinalPosition(0.0f),
				transversalPosition(0.0f),
				angularPosition(0.0f)
	{
		baseInit();

		//Front Left Wheel
		this->frontLeft.setNumber(1);
		this->frontLeft.setName((char *)"frontLeft");
		this->frontLeft.setGearRatio(gearRatio);
		this->frontLeft.setEncoderTicksPerRound(encoder_resolution);
		this->frontLeft.setPWMTimer(htim2, TIM_CHANNEL_1);
		this->frontLeft.setDefaultDirection(counterClockWise);
		this->frontLeft.setDirectionGPIO(motorDirection1_GPIO_Port, motorDirection1_Pin);
		this->frontLeft.setEncoderTimer(htim1);
		//Front Right Wheel
		this->frontRight.setNumber(2);
		this->frontRight.setName((char *)"frontRight");
		this->frontRight.setGearRatio(gearRatio);
		this->frontRight.setEncoderTicksPerRound(encoder_resolution);
		this->frontRight.setPWMTimer(htim2, TIM_CHANNEL_2);
		this->frontRight.setDefaultDirection(clockWise);
		this->frontRight.setDirectionGPIO(motorDirection2_GPIO_Port, motorDirection2_Pin);
		this->frontRight.setEncoderTimer(htim3);
		//Rear Left Wheel
		this->rearLeft.setNumber(3);
		this->rearLeft.setName((char *)"rearLeft");
		this->rearLeft.setGearRatio(gearRatio);
		this->rearLeft.setEncoderTicksPerRound(encoder_resolution);
		this->rearLeft.setPWMTimer(htim2, TIM_CHANNEL_3);
		this->rearLeft.setDefaultDirection(counterClockWise);
		this->rearLeft.setDirectionGPIO(motorDirection3_GPIO_Port, motorDirection3_Pin);
		this->rearLeft.setEncoderTimer(htim4);
		//Front Right Wheel
		this->rearRight.setNumber(4);
		this->rearRight.setName((char *)"frontRight");
		this->rearRight.setGearRatio(gearRatio);
		this->rearRight.setEncoderTicksPerRound(encoder_resolution);
		this->rearRight.setPWMTimer(htim2, TIM_CHANNEL_4);
		this->rearRight.setDefaultDirection(clockWise);
		this->rearRight.setDirectionGPIO(motorDirection4_GPIO_Port, motorDirection4_Pin);
		this->rearRight.setEncoderTimer(htim8);
	}

	float		getWheelRadius(void);
	float		getGearRatio(void);
	float		getLengthBetweenFrontAndRearWheels(void);
	float		getLengthBetweenFrontWheels(void);

	void 		getVelocity(float & longitudinalVelocity, float & transversalVelocity, float & angularVelocity);
	float		getLongitudinalVelocity(void);
	float		getTransversalVelocity(void);
	float		getAngularVelocity(void);

	void 		getPosition(float & longitudinalPosition, float & transversalPosition, float & angularPosition);
	float		getLongitudinalPosition(void);
	float		getTransversalPosition(void);
	float		getAngularPosition(void);

	void		updatePosition(void);

	private:

	float longitudinalPosition;
	float transversalPosition;
	float angularPosition;

};

#endif /* Base_H */

