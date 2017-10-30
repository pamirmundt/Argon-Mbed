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
		 * Wheel positions to base position
		 * 	with using build in kinematics library
		 */

		float FL_position = 10.0f, FR_position = 10.0f, RL_position = 10.0f, RR_position = 10.0f; //rad

		float longitudinalPosition, transveralPosition, angularPosition; //Meters, meters, rad/s

		myBase.kinematics.wheelPositionsToCartesianPosition(FL_position, FR_position, RL_position, RR_position, longitudinalPosition, transveralPosition, angularPosition);

		pc.printf("Wheel Positions: %f rad, %f rad, %f rad, %f rad\r\n", FL_position, FR_position, RL_position, RR_position);

		pc.printf("Base Position:   %f m, %f m, %f rad\r\n\r\n", longitudinalPosition, transveralPosition, angularPosition);

		pc.printf("--------------------\r\n\r\n");

		wait(4);

	}
}
