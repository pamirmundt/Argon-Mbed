/*
 *	Argon Template
 */

#include "mbed.h"
#include "Argon.h"

Serial pc(SERIAL_TX, SERIAL_RX, 9600);

/* Argon Base */
ArgonBase myBase;

/* Wheel Angular Velocities (rad/s) */
float FL_jointAngVel = 0.0f, FR_jointAngVel = 0.0f, RL_jointAngVel = 0.0f, RR_jointAngVel = 0.0f;

/* Calculated wheel Angular Velocities from inverse kinematics (rad/s) */
float cFL_jointAngVel = 0.0f, cFR_jointAngVel = 0.0f, cRL_jointAngVel = 0.0f, cRR_jointAngVel = 0.0f;

/* Base Velocity */
float longitudinalVelocity = 0.0f;
float transversalVelocity = 0.0f;
float angularVelocity = 0.0f;

int main() {

	/* Set PWM for each motor */
	myBase.frontLeft.setPWM(-512);
	myBase.frontRight.setPWM(512);
	myBase.rearLeft.setPWM(-512);
	myBase.rearRight.setPWM(512);

	/* Geomteric Factor = (Length Between Front and RearWheels + Length Between Front Wheels)/2 */
	float geometricFactor = (myBase.getLengthBetweenFrontAndRearWheels() + myBase.getLengthBetweenFrontWheels()) / 2.0f;

	while(1){

		/* Get Wheel Velocities */
		FL_jointAngVel = myBase.frontLeft.getJointAngVel();
		FR_jointAngVel = myBase.frontRight.getJointAngVel();
		RL_jointAngVel = myBase.rearLeft.getJointAngVel();
		RR_jointAngVel = myBase.rearRight.getJointAngVel();

		/* Calculate Base Velocity - Forward Kinematics *******************************************/

		/* X: Longitudinal Velocity - m/s */
		longitudinalVelocity = (FL_jointAngVel + FR_jointAngVel + RL_jointAngVel + RR_jointAngVel) * myBase.getWheelRadius() / 4.0f;

		/* Y: Transversal Velocity - m/s */
		transversalVelocity = (-FL_jointAngVel + FR_jointAngVel + RL_jointAngVel - RR_jointAngVel) * myBase.getWheelRadius() / 4.0f;

		/* t: Angular Velocity - rad/s */
		angularVelocity = (-FL_jointAngVel + FR_jointAngVel - RL_jointAngVel + RR_jointAngVel) * wheelRadius / (4.0f * geometricFactor);

		/* Print Base Velocity */
		pc.printf("(K) Base Velocity:   %f (m/s), %f (m/s), %f (rad/s)\r\n", longitudinalVelocity, transversalVelocity, angularVelocity);

		/******************************************************************************************/

		/* Calculate Wheel Velocities - Inverse Kinematics ****************************************/

		/* (1) Front Wheel Angular Velocity */
		cFL_jointAngVel = (longitudinalVelocity - transversalVelocity - geometricFactor * angularVelocity) / myBase.getWheelRadius();

		/* (2) Front Wheel Angular Velocity */
		cFR_jointAngVel = (longitudinalVelocity + transversalVelocity + geometricFactor * angularVelocity) / myBase.getWheelRadius();

		/* (3) Front Wheel Angular Velocity */
		cRL_jointAngVel = (longitudinalVelocity + transversalVelocity - geometricFactor * angularVelocity) / myBase.getWheelRadius();

		/* (4) Front Wheel Angular Velocity */
		cRR_jointAngVel = (longitudinalVelocity - transversalVelocity + geometricFactor * angularVelocity) / myBase.getWheelRadius();

		/* Print Wheel Velocities */
		pc.printf("(IK) Wheel Velocity: %f(rad/s) %f (rad/s) %f (rad/s) %f (rad/s)\r\n\r\n", cFL_jointAngVel, cFR_jointAngVel, cRL_jointAngVel, cRR_jointAngVel);

		/******************************************************************************************/

		pc.printf("------------------------------------\r\n\r\n");
		wait(1); //Wait 1 sec
	}
}
