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

		/* Get Base Position
		 *  Longitudinal position (m)
		 *  Transversal position (m)
		 *  Angular position (rad)
		 */
		float longPos = myBase.getLongitudinalPosition();

		float transPos = myBase.getTransversalPosition();

		float angPos = myBase.getAngularPosition();

		pc.printf("Base Position: %f m, %f m, %f rad\r\n\n", longPos, transPos, angPos);

		myBase.updatePosition();

		wait_ms(500);
	}
}
