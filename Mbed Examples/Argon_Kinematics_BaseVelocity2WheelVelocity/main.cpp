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
		 * Base Velocity to Wheel Velocities
		 * 	with using build in kinematics library
		 */

		float longitudinalVelocity = 0.3f, transveralVelocity = 0.0f, angularVelocity = 0.0f;

		float FL_velocity, FR_velocity, RL_velocity, RR_velocity;

		myBase.kinematics.cartesianVelocityToWheelVelocities(longitudinalVelocity, transveralVelocity, angularVelocity, FL_velocity, FR_velocity, RL_velocity, RR_velocity);

		pc.printf("Base Velocity:    %f m/s, %f m/s, %f rad/s\r\n\r\n", longitudinalVelocity, transveralVelocity, angularVelocity);

		pc.printf("Wheel Velocities: %f rad/s, %f rad/s, %f rad/s, %f rad/s\r\n", FL_velocity, FR_velocity, RL_velocity, RR_velocity);

		pc.printf("--------------------\r\n\r\n");

		wait(4);

	}
}
