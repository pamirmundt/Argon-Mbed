/*
 *	Argon Template
 */

#include "mbed.h"
#include "Argon.h"

Serial pc(SERIAL_TX, SERIAL_RX, 9600);

/* Argon Base */
ArgonBase myBase;

/* Wheel Angular Velocities (rad/s) */
float FL_jointAngVel = 0.0f, FR_jointAngVel = 0.0f, RL_jointAngVel, RR_jointAngVel;

/* Base Velocity */
float longitudinalVelocity = 0.0f;
float transversalVelocity = 0.0f;
float angularVelocity = 0.0f;

int main() {

	/* Set PWM for each motor */
	myBase.frontLeft.setPWM(512);
	myBase.frontRight.setPWM(512);
	myBase.rearLeft.setPWM(512);
	myBase.rearRight.setPWM(512);

	/* Geomteric Factor = (Length Between Front and RearWheels + Length Between Front Wheels)/2 */
	float geometricFactor = (myBase.getLengthBetweenFrontAndRearWheels() + myBase.getLengthBetweenFrontWheels()) / 2.0f;

	while(1){

		/* Get Wheel Velocities */
		FL_jointAngVel = myBase.frontLeft.getJointAngVel();
		FR_jointAngVel = myBase.frontRight.getJointAngVel();
		RL_jointAngVel = myBase.rearLeft.getJointAngVel();
		RR_jointAngVel = myBase.rearRight.getJointAngVel();

		/*
		 * Calculate Velocity Forward Kinematics
		 */

		/* X: Longitudinal Velocity - m/s */
		longitudinalVelocity = (FL_jointAngVel + FR_jointAngVel + RL_jointAngVel + RR_jointAngVel) * myBase.getWheelRadius() / 4.0f;

		/* Y: Transversal Velocity - m/s */
		transversalVelocity = (-FL_jointAngVel + FR_jointAngVel + RL_jointAngVel - RR_jointAngVel) * myBase.getWheelRadius() / 4.0f;

		/* t: Angular Velocity - rad/s */
		angularVelocity = (-FL_jointAngVel + FR_jointAngVel - RL_jointAngVel + RR_jointAngVel) * wheelRadius / (4.0f * geometricFactor);

		/* Print */
		pc.printf("Base Velocity: %f %f %f\r\n", longitudinalVelocity, transversalVelocity, angularVelocity);

	}
}
