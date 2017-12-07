#ifndef ARGONSPI_H
#define ARGONSPI_H

#include "ArgonBase.h"

int ArgonSPIHander(ArgonBase &myBase);

int checkSPI(void);

int getWheelNumber(int CMD, ArgonBase &myBase);
int getWheelRadius(int CMD, ArgonBase &myBase);
int getGearRatio(int CMD, ArgonBase &myBase);
int getEncoderTicksPerRound(int CMD, ArgonBase &myBase);
int getQuadEncoderTicksPerRound(int CMD, ArgonBase &myBase);
int getMaximumRPM(int CMD, ArgonBase &myBase);
int getMaximumAngularVelocity(int CMD, ArgonBase &myBase);
int getDirection(int CMD, ArgonBase &myBase);
int getPWM(int CMD, ArgonBase &myBase);
int getPower(int CMD, ArgonBase &myBase);
int getEncoderCount(int CMD, ArgonBase &myBase);
int getJointRPM(int CMD, ArgonBase &myBase);
int getMotorRPM(int CMD, ArgonBase &myBase);
int getJointAngVel(int CMD, ArgonBase &myBase);
int getMotorAngVel(int CMD, ArgonBase &myBase);
int getJointPosition(int CMD, ArgonBase &myBase);
int getMotorPosition(int CMD, ArgonBase &myBase);

int getLengthBetweenFrontAndRearWheels(ArgonBase &myBase);
int getLengthBetweenFrontWheels(ArgonBase &myBase);

//int getVelocity(ArgonBase &myBase);
int getLongitudinalVelocity(ArgonBase &myBase);
int getTransversalVelocity(ArgonBase &myBase);
int getAngularVelocity(ArgonBase &myBase);

int getLongitudinalPosition(ArgonBase &myBase);
int getTransversalPosition(ArgonBase &myBase);
int getAngularPosition(ArgonBase &myBase);

#endif /* MOTOR_H */
