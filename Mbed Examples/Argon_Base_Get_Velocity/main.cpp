/*
 *	Argon Template
 */

#include "mbed.h"
#include "Argon.h"

ArgonBase myBase;

Serial pc(SERIAL_TX, SERIAL_RX, 9600);

int main() {

	myBase.frontLeft.setPWM(512);

	myBase.frontRight.setPWM(512);

	myBase.rearLeft.setPWM(512);

	myBase.rearRight.setPWM(512);

	while(1){

		/* Get Base Velocity (return)
		 *  Longitudinal Velocity (m/s)
		 *  Transversal Velocity (m/s)
		 *  Angular Velocity (rad/s)
		 */
		float longVel = myBase.getLongitudinalVelocity();

		float transVel = myBase.getTransversalVelocity();

		float angVel = myBase.getAngularVelocity();

		pc.printf("Base Velocity: %f m/s, %f m/s, %f rad/s\r\n\n", longVel, transVel, angVel);

		wait_ms(500);

	}
}
