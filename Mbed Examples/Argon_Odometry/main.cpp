/*
 *	Argon Template
 */

#include "mbed.h"
#include "Argon.h"

Serial pc(SERIAL_TX, SERIAL_RX, 9600);

/* Argon Base */
ArgonBase myBase;

/* Wheel Angular Positions (rad) */
float FL_AngPosition = 0.0f, FR_AngPosition = 0.0f, RL_AngPosition = 0.0f, RR_AngPosition = 0.0f;

/* Previous Wheel Angular Positions (rad) - Needed for the calculation of delta position */
float FL_prevAngPosition = 0.0f, FR_prevAngPosition = 0.0f, RL_prevAngPosition = 0.0f, RR_prevAngPosition = 0.0f;

/* Base Position */
float longitudinalPosition = 0.0f;	//x - meters
float transversalPosition = 0.0f;	//y - meters
float orientation = 0.0f;			//t - rad

int main() {

	/* Set PWM for each motor */
	myBase.frontLeft.setPWM(-512);
	myBase.frontRight.setPWM(512);
	myBase.rearLeft.setPWM(-512);
	myBase.rearRight.setPWM(512);

	/* Geomteric Factor = (Length Between Front and RearWheels + Length Between Front Wheels)/2 */
	float geometricFactor = (myBase.getLengthBetweenFrontAndRearWheels() + myBase.getLengthBetweenFrontWheels()) / 2.0f;

	while(1){

		/* Get Wheel Angular Positions - radian */
		FL_AngPosition = myBase.frontLeft.getJointPosition();
		FL_AngPosition = myBase.frontRight.getJointPosition();
		RL_AngPosition = myBase.rearLeft.getJointPosition();
		RR_AngPosition = myBase.rearRight.getJointPosition();

		/* Calculate Angular Position Difference */
		float FL_deltaAngPosition = FL_AngPosition - FL_prevAngPosition;
		float FR_deltaAngPosition = FR_AngPosition - FR_prevAngPosition;
		float RL_deltaAngPosition = RL_AngPosition - RL_prevAngPosition;
		float RR_deltaAngPosition = RR_AngPosition - RR_prevAngPosition;

		/* Store Previous Wheel Positions */
		FL_prevAngPosition = FL_AngPosition;
		FR_prevAngPosition = FR_AngPosition;
		RL_prevAngPosition = RL_AngPosition;
		RR_prevAngPosition = RR_AngPosition;

	    /* Calculate Delta Longitudial Position - meters */
	    float deltaLongitudinalPos = (FL_deltaAngPosition + FR_deltaAngPosition + RL_deltaAngPosition + RR_deltaAngPosition) * myBase.getWheelRadius() / 4.0f;

	    /* Calculate Delta Transversal Position in meters */
	    float deltaTransversalPos = (- FL_deltaAngPosition + FR_deltaAngPosition + RL_deltaAngPosition - RR_deltaAngPosition) * myBase.getWheelRadius() / 4.0f;

	    /* Calculate Base Orientation(t) - radians */
	    orientation += (-FL_deltaAngPosition + FR_deltaAngPosition - RL_deltaAngPosition + RR_deltaAngPosition) * myBase.getWheelRadius() / 4.0f / geometricFactor;

	    /* Calculate Base Longitudinal Position (x) - meters */
	    longitudinalPosition += deltaLongitudinalPos * cos(orientation) - deltaTransversalPos * sin(orientation);

	    /* Calculate Base Transversal Position (y) - meters */
	    transversalPosition += deltaLongitudinalPos * sin(orientation) + deltaTransversalPos * cos(orientation);

	    /* Print Base Position */
	    pc.printf("Base Position: %f %f %f\r\n\r\n", longitudinalPosition, transversalPosition, orientation);

	    wait(2); //wait 2 seconds
	}
}
