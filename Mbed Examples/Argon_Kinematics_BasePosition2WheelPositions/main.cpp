/*
 *	Argon Template
 */

#include "mbed.h"
#include "Argon.h"

Serial pc(SERIAL_TX, SERIAL_RX, 9600);

ArgonBase myBase;

int main() {

	/*  SETUP */

	while(1){

		/*
		 * Base position to wheel positions
		 * 	with using build in kinematics library
		 */

		float longitudinalPosition = 0.3f, transveralPosition = 0.0f, angularPosition = 0.0f;

		float FL_position, FR_position, RL_position, RR_position;

		myBase.kinematics.cartesianPositionToWheelPositions(longitudinalPosition, transveralPosition, angularPosition, FL_position, FR_position, RL_position, RR_position);

		pc.printf("Base Position:   %f m, %f m, %f rad\r\n\r\n", longitudinalPosition, transveralPosition, angularPosition);

		pc.printf("Wheel Positions: %f rad, %f rad, %f rad, %f rad\r\n", FL_position, FR_position, RL_position, RR_position);

		pc.printf("--------------------\r\n\r\n");

		wait(4);

	}
}
