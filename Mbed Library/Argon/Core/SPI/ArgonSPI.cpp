#include "ArgonSPI.h"
#include "stm32f4xx_hal.h"
#include <string.h>

extern SPI_HandleTypeDef hspi3;

#define TxRxTimeout									10

#define CHECK_SPI 									0xAA

//Wheel
#define GET_WHEEL_NUMBER							0x21
#define GET_WHEEL_RADIUS							0x22
#define GET_GEAR_RATIO								0x23
#define GET_ENCODER_TICKS_PER_ROUND					0x24
#define GET_QUAD_ENCODER_TICKS_PER_ROUND			0x25
#define GET_MAXIMUM_RPM								0x26
#define GET_MAXIMUM_ANGULAR_VELOCITY				0x27
#define GET_DIRECTION								0x28
#define GET_PWM										0x29
#define GET_POWER									0x2A
#define GET_ENCODER_COUNT							0x2B
#define GET_JOINT_RPM								0x2C
#define GET_MOTOR_RPM								0x2D
#define GET_JOINT_ANG_VEL							0x2E
#define GET_MOTOR_ANG_VEL							0x2F
#define GET_JOINT_POSITION							0x30
#define GET_MOTOR_POSITION							0x31

#define GET_LENGTH_BETWEEN_FRONT_AND_REAR_WHEELS	0x40
#define GET_LENGTH_BETWEEN_LEFT_AND_RIGHT_WHEELS	0x41

//#define GET_BASE_VELOCITY							0x42
#define GET_LONGITUDINAL_VELOCITY					0x43
#define GET_TRANSVERSAL_VELOCITY					0x44
#define GET_ANGULAR_VELOCITY						0x45

//#define GET_POSITION								0x46
#define GET_LONGITUDINAL_POSITION					0x47
#define GET_TRANSVERSAL_POSITION					0x48
#define GET_ANGULAR_POSITION						0x49
//#define updatePosition							0x4A


int ArgonSPIHander(ArgonBase &myBase){

	uint8_t CMD[2] = {0, 0};
	uint8_t dummyByte[2] = {CHECK_SPI, CHECK_SPI};
	HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)dummyByte, (uint8_t*)CMD, 2, 1);

	//Parse CMD
	switch (CMD[0]) {
		case CHECK_SPI:
			checkSPI();
			break;
		case GET_WHEEL_NUMBER:
			getWheelNumber(CMD[1], myBase);
			break;
		case GET_WHEEL_RADIUS:
			getWheelRadius(CMD[1], myBase);
			break;
		case GET_GEAR_RATIO:
			getGearRatio(CMD[1], myBase);
			break;
		case GET_ENCODER_TICKS_PER_ROUND:
			getEncoderTicksPerRound(CMD[1], myBase);
			break;
		case GET_QUAD_ENCODER_TICKS_PER_ROUND:
			getQuadEncoderTicksPerRound(CMD[1], myBase);
			break;
		case GET_MAXIMUM_RPM:
			getMaximumRPM(CMD[1], myBase);
			break;
		case GET_MAXIMUM_ANGULAR_VELOCITY:
			getMaximumAngularVelocity(CMD[1], myBase);
			break;
		case GET_DIRECTION:
			getDirection(CMD[1], myBase);
			break;
		case GET_PWM:
			getPWM(CMD[1], myBase);
			break;
		case GET_POWER:
			getPower(CMD[1], myBase);
			break;
		case GET_ENCODER_COUNT:
			getEncoderCount(CMD[1], myBase);
			break;
		case GET_JOINT_RPM:
			getJointRPM(CMD[1], myBase);
			break;
		case GET_MOTOR_RPM:
			getMotorRPM(CMD[1], myBase);
			break;
		case GET_JOINT_ANG_VEL:
			getJointAngVel(CMD[1], myBase);
			break;
		case GET_MOTOR_ANG_VEL:
			getMotorAngVel(CMD[1], myBase);
			break;
		case GET_JOINT_POSITION:
			getJointPosition(CMD[1], myBase);
			break;
		case GET_MOTOR_POSITION:
			getMotorPosition(CMD[1], myBase);
			break;

		case GET_LENGTH_BETWEEN_FRONT_AND_REAR_WHEELS:
			getLengthBetweenFrontAndRearWheels(myBase);
			break;
		case GET_LENGTH_BETWEEN_LEFT_AND_RIGHT_WHEELS:
			getLengthBetweenFrontWheels(myBase);
			break;

		//case GET_BASE_VELOCITY:
		//	getVelocity();
		//	break;
		case GET_LONGITUDINAL_VELOCITY:
			getLongitudinalVelocity(myBase);
			break;
		case GET_TRANSVERSAL_VELOCITY:
			getTransversalVelocity(myBase);
			break;
		case GET_ANGULAR_VELOCITY:
			getAngularVelocity(myBase);
			break;

		//case GET_POSITION:
		//	getPosition();
		//	break;
		case GET_LONGITUDINAL_POSITION:
			getLongitudinalPosition(myBase);
			break;
		case GET_TRANSVERSAL_POSITION:
			getTransversalPosition(myBase);
			break;
		case GET_ANGULAR_POSITION:
			getAngularPosition(myBase);
			break;

		default:
			break;
	}

	return 0;
}

int checkSPI(void){
	uint8_t RX[1] = {0};
	uint8_t TX[1] = {CHECK_SPI};
	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, 1, TxRxTimeout);
}

int getWheelNumber(int CMD, ArgonBase &myBase){
	uint8_t RX[1] = {0};
	uint8_t TX[1] = {0};
	switch (CMD) {
		case 1:{
			TX[0] = myBase.frontLeft.getNumber();
			break;}
		case 2:{
			TX[0] = myBase.frontRight.getNumber();
			break;}
		case 3:{
			TX[0] = myBase.rearLeft.getNumber();
			break;}
		case 4:{
			TX[0] = myBase.rearRight.getNumber();
			break;}
		default:{
			memset(TX, 0, sizeof(TX));
			break;}
	}

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, 1, TxRxTimeout);
}

int getWheelRadius(int CMD, ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	switch (CMD) {
		case 1:{
			float radius = myBase.frontLeft.getWheelRadius();
			memcpy(TX, &radius, sizeof(float));
			break;}
		case 2:{
			float radius = myBase.frontRight.getWheelRadius();
			memcpy(TX, &radius, sizeof(float));
			break;}
		case 3:{
			float radius = myBase.rearLeft.getWheelRadius();
			memcpy(TX, &radius, sizeof(float));
			break;}
		case 4:{
			float radius = myBase.rearRight.getWheelRadius();
			memcpy(TX, &radius, sizeof(float));
			break;}
		default:{
			memset(TX, 0, sizeof(TX));
			break;}
	}

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

int getGearRatio(int CMD, ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	switch (CMD) {
		case 1:{
			float gear = myBase.frontLeft.getGearRatio();
			memcpy(TX, &gear, sizeof(float));
			break;}
		case 2:{
			float gear = myBase.frontRight.getGearRatio();
			memcpy(TX, &gear, sizeof(float));
			break;}
		case 3:{
			float gear = myBase.rearLeft.getGearRatio();
			memcpy(TX, &gear, sizeof(float));
			break;}
		case 4:{
			float gear = myBase.rearRight.getGearRatio();
			memcpy(TX, &gear, sizeof(float));
			break;}
		default:{
			memset(TX, 0, sizeof(TX));
			break;}
	}

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

int getEncoderTicksPerRound(int CMD, ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	switch (CMD) {
		case 1:{
			float ticks = myBase.frontLeft.getEncoderTicksPerRound();
			memcpy(TX, &ticks, sizeof(float));
			break;}
		case 2:{
			float ticks = myBase.frontRight.getEncoderTicksPerRound();
			memcpy(TX, &ticks, sizeof(float));
			break;}
		case 3:{
			float ticks = myBase.rearLeft.getEncoderTicksPerRound();
			memcpy(TX, &ticks, sizeof(float));
			break;}
		case 4:{
			float ticks = myBase.rearRight.getEncoderTicksPerRound();
			memcpy(TX, &ticks, sizeof(float));
			break;}
		default:{
			memset(TX, 0, sizeof(TX));
			break;}
	}

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

int getQuadEncoderTicksPerRound(int CMD, ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	switch (CMD) {
		case 1:{
			float quadTicks = myBase.frontLeft.getQuadEncoderTicksPerRound();
			memcpy(TX, &quadTicks, sizeof(float));
			break;}
		case 2:{
			float quadTicks = myBase.frontRight.getQuadEncoderTicksPerRound();
			memcpy(TX, &quadTicks, sizeof(float));
			break;}
		case 3:{
			float quadTicks = myBase.rearLeft.getQuadEncoderTicksPerRound();
			memcpy(TX, &quadTicks, sizeof(float));
			break;}
		case 4:{
			float quadTicks = myBase.rearRight.getQuadEncoderTicksPerRound();
			memcpy(TX, &quadTicks, sizeof(float));
			break;}
		default:{
			memset(TX, 0, sizeof(TX));
			break;}
	}

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

int getMaximumRPM(int CMD, ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	switch (CMD) {
		case 1:{
			float maxRPM = myBase.frontLeft.getMaximumRPM();
			memcpy(TX, &maxRPM, sizeof(float));
			break;}
		case 2:{
			float maxRPM = myBase.frontRight.getMaximumRPM();
			memcpy(TX, &maxRPM, sizeof(float));
			break;}
		case 3:{
			float maxRPM = myBase.rearLeft.getMaximumRPM();
			memcpy(TX, &maxRPM, sizeof(float));
			break;}
		case 4:{
			float maxRPM = myBase.rearRight.getMaximumRPM();
			memcpy(TX, &maxRPM, sizeof(float));
			break;}
		default:{
			memset(TX, 0, sizeof(TX));
			break;}
	}

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

int getMaximumAngularVelocity(int CMD, ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	switch (CMD) {
		case 1:{
			float maxAngVel = myBase.frontLeft.getMaximumAngularVelocity();
			memcpy(TX, &maxAngVel, sizeof(float));
			break;}
		case 2:{
			float maxAngVel = myBase.frontRight.getMaximumAngularVelocity();
			memcpy(TX, &maxAngVel, sizeof(float));
			break;}
		case 3:{
			float maxAngVel = myBase.rearLeft.getMaximumAngularVelocity();
			memcpy(TX, &maxAngVel, sizeof(float));
			break;}
		case 4:{
			float maxAngVel = myBase.rearRight.getMaximumAngularVelocity();
			memcpy(TX, &maxAngVel, sizeof(float));
			break;}
		default:{
			memset(TX, 0, sizeof(TX));
			break;}
	}

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

int getDirection(int CMD, ArgonBase &myBase){
	uint8_t RX[sizeof(uint8_t)] = {0};	//uint8_t
	uint8_t TX[sizeof(uint8_t)] = {0};	//uint8_t

	switch (CMD) {
		case 1:{
			uint8_t dir = myBase.frontLeft.getDirection();
			memcpy(TX, &dir, sizeof(uint8_t));
			break;}
		case 2:{
			uint8_t dir = myBase.frontRight.getDirection();
			memcpy(TX, &dir, sizeof(uint8_t));
			break;}
		case 3:{
			uint8_t dir = myBase.rearLeft.getDirection();
			memcpy(TX, &dir, sizeof(uint8_t));
			break;}
		case 4:{
			uint8_t dir = myBase.rearRight.getDirection();
			memcpy(TX, &dir, sizeof(uint8_t));
			break;}
		default:{
			memset(TX, 0, sizeof(TX));
			break;}
	}

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(uint8_t), TxRxTimeout);
}

int getPWM(int CMD, ArgonBase &myBase){
	uint8_t RX[sizeof(int16_t)] = {0};	//uint8_t
	uint8_t TX[sizeof(int16_t)] = {0};	//uint8_t

	switch (CMD) {
		case 1:{
			int16_t pwm = myBase.frontLeft.getPWM();
			memcpy(TX, &pwm, sizeof(int16_t));
			break;}
		case 2:{
			int16_t pwm = myBase.frontRight.getPWM();
			memcpy(TX, &pwm, sizeof(int16_t));
			break;}
		case 3:{
			int16_t pwm = myBase.rearLeft.getPWM();
			memcpy(TX, &pwm, sizeof(int16_t));
			break;}
		case 4:{
			int16_t pwm = myBase.rearRight.getPWM();
			memcpy(TX, &pwm, sizeof(int16_t));
			break;}
		default:{
			memset(TX, 0, sizeof(TX));
			break;}
	}

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(int16_t), TxRxTimeout);
}

int getPower(int CMD, ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	switch (CMD) {
		case 1:{
			float power = myBase.frontLeft.getPower();
			memcpy(TX, &power, sizeof(float));
			break;}
		case 2:{
			float power = myBase.frontRight.getPower();
			memcpy(TX, &power, sizeof(float));
			break;}
		case 3:{
			float power = myBase.rearLeft.getPower();
			memcpy(TX, &power, sizeof(float));
			break;}
		case 4:{
			float power = myBase.rearRight.getPower();
			memcpy(TX, &power, sizeof(float));
			break;}
		default:{
			memset(TX, 0, sizeof(TX));
			break;}
	}

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

int getEncoderCount(int CMD, ArgonBase &myBase){
	uint8_t RX[sizeof(int16_t)] = {0};	//uint8_t
	uint8_t TX[sizeof(int16_t)] = {0};	//uint8_t

	switch (CMD) {
		case 1:{
			int16_t encCount = myBase.frontLeft.getEncoderCount();
			memcpy(TX, &encCount, sizeof(int16_t));
			break;}
		case 2:{
			int16_t encCount = myBase.frontRight.getEncoderCount();
			memcpy(TX, &encCount, sizeof(int16_t));
			break;}
		case 3:{
			int16_t encCount = myBase.rearLeft.getEncoderCount();
			memcpy(TX, &encCount, sizeof(int16_t));
			break;}
		case 4:{
			int16_t encCount = myBase.rearRight.getEncoderCount();
			memcpy(TX, &encCount, sizeof(int16_t));
			break;}
		default:{
			memset(TX, 0, sizeof(TX));
			break;}
	}

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(int16_t), TxRxTimeout);
}

int getJointRPM(int CMD, ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	switch (CMD) {
		case 1:{
			float rpm = myBase.frontLeft.getJointRPM();
			memcpy(TX, &rpm, sizeof(float));
			break;}
		case 2:{
			float rpm = myBase.frontRight.getJointRPM();
			memcpy(TX, &rpm, sizeof(float));
			break;}
		case 3:{
			float rpm = myBase.rearLeft.getJointRPM();
			memcpy(TX, &rpm, sizeof(float));
			break;}
		case 4:{
			float rpm = myBase.rearRight.getJointRPM();
			memcpy(TX, &rpm, sizeof(float));
			break;}
		default:{
			memset(TX, 0, sizeof(TX));
			break;}
	}

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

int getMotorRPM(int CMD, ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	switch (CMD) {
		case 1:{
			float rpm = myBase.frontLeft.getMotorRPM();
			memcpy(TX, &rpm, sizeof(float));
			break;}
		case 2:{
			float rpm = myBase.frontRight.getMotorRPM();
			memcpy(TX, &rpm, sizeof(float));
			break;}
		case 3:{
			float rpm = myBase.rearLeft.getMotorRPM();
			memcpy(TX, &rpm, sizeof(float));
			break;}
		case 4:{
			float rpm = myBase.rearRight.getMotorRPM();
			memcpy(TX, &rpm, sizeof(float));
			break;}
		default:{
			memset(TX, 0, sizeof(TX));
			break;}
	}

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

int getJointAngVel(int CMD, ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	switch (CMD) {
		case 1:{
			float angVel = myBase.frontLeft.getJointAngVel();
			memcpy(TX, &angVel, sizeof(float));
			break;}
		case 2:{
			float angVel = myBase.frontRight.getJointAngVel();
			memcpy(TX, &angVel, sizeof(float));
			break;}
		case 3:{
			float angVel = myBase.rearLeft.getJointAngVel();
			memcpy(TX, &angVel, sizeof(float));
			break;}
		case 4:{
			float angVel = myBase.rearRight.getJointAngVel();
			memcpy(TX, &angVel, sizeof(float));
			break;}
		default:{
			memset(TX, 0, sizeof(TX));
			break;}
	}

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

int getMotorAngVel(int CMD, ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	switch (CMD) {
		case 1:{
			float angVel = myBase.frontLeft.getMotorAngVel();
			memcpy(TX, &angVel, sizeof(float));
			break;}
		case 2:{
			float angVel = myBase.frontRight.getMotorAngVel();
			memcpy(TX, &angVel, sizeof(float));
			break;}
		case 3:{
			float angVel = myBase.rearLeft.getMotorAngVel();
			memcpy(TX, &angVel, sizeof(float));
			break;}
		case 4:{
			float angVel = myBase.rearRight.getMotorAngVel();
			memcpy(TX, &angVel, sizeof(float));
			break;}
		default:{
			memset(TX, 0, sizeof(TX));
			break;}
	}

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

int getJointPosition(int CMD, ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	switch (CMD) {
		case 1:{
			float pos = myBase.frontLeft.getJointPosition();
			memcpy(TX, &pos, sizeof(float));
			break;}
		case 2:{
			float pos = myBase.frontRight.getJointPosition();
			memcpy(TX, &pos, sizeof(float));
			break;}
		case 3:{
			float pos = myBase.rearLeft.getJointPosition();
			memcpy(TX, &pos, sizeof(float));
			break;}
		case 4:{
			float pos = myBase.rearRight.getJointPosition();
			memcpy(TX, &pos, sizeof(float));
			break;}
		default:{
			memset(TX, 0, sizeof(TX));
			break;}
	}

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

int getMotorPosition(int CMD, ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	switch (CMD) {
		case 1:{
			float pos = myBase.frontLeft.getMotorPosition();
			memcpy(TX, &pos, sizeof(float));
			break;}
		case 2:{
			float pos = myBase.frontRight.getMotorPosition();
			memcpy(TX, &pos, sizeof(float));
			break;}
		case 3:{
			float pos = myBase.rearLeft.getMotorPosition();
			memcpy(TX, &pos, sizeof(float));
			break;}
		case 4:{
			float pos = myBase.rearRight.getMotorPosition();
			memcpy(TX, &pos, sizeof(float));
			break;}
		default:{
			memset(TX, 0, sizeof(TX));
			break;}
	}

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

//Base

int getLengthBetweenFrontAndRearWheels(ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	float length = myBase.getLengthBetweenFrontAndRearWheels();
	memcpy(TX, &length, sizeof(float));

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

int getLengthBetweenFrontWheels(ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	float length = myBase.getLengthBetweenFrontWheels();
	memcpy(TX, &length, sizeof(float));

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

/*
int getVelocity(ArgonBase &myBase){
	uint8_t RX[3 * sizeof(float)] = {0};	//float float float
	uint8_t TX[3 * sizeof(float)] = {0};	//float float float

	float longVel = 0, transVel = 0, angVel = 0;

	myBase.getVelocity(longVel, transVel, angVel);

	memcpy(TX, &length, sizeof(float));

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}
*/

int getLongitudinalVelocity(ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	float vel = myBase.getLongitudinalVelocity();
	memcpy(TX, &vel, sizeof(float));

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

int getTransversalVelocity(ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	float vel = myBase.getTransversalVelocity();
	memcpy(TX, &vel, sizeof(float));

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

int getAngularVelocity(ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	float vel = myBase.getAngularVelocity();
	memcpy(TX, &vel, sizeof(float));

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

int getLongitudinalPosition(ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	float pos = myBase.getLongitudinalPosition();
	memcpy(TX, &pos, sizeof(float));

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

int getTransversalPosition(ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	float pos = myBase.getTransversalPosition();
	memcpy(TX, &pos, sizeof(float));

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}

int getAngularPosition(ArgonBase &myBase){
	uint8_t RX[sizeof(float)] = {0};	//float
	uint8_t TX[sizeof(float)] = {0};	//float

	float pos = myBase.getAngularPosition();
	memcpy(TX, &pos, sizeof(float));

	return HAL_SPI_TransmitReceive(&hspi3, (uint8_t*)TX, (uint8_t*)RX, sizeof(float), TxRxTimeout);
}
