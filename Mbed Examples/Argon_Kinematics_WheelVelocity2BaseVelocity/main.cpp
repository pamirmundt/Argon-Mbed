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
		 * Wheel Velocity to Base Velocity
		 * 	with using build in kinematics library
		 */

		float FL_velocity = 10.0f, FR_velocity = 10.0f, RL_velocity = 10.0f, RR_velocity = 10.0f;

		float longitudinalVelocity, transveralVelocity, angularVelocity;

		myBase.kinematics.wheelVelocitiesToCartesianVelocity(FL_velocity, FR_velocity, RL_velocity, RR_velocity, longitudinalVelocity, transveralVelocity, angularVelocity);

		pc.printf("Wheel Velocities: %f rad/s, %f rad/s, %f rad/s, %f rad/s\r\n", FL_velocity, FR_velocity, RL_velocity, RR_velocity);

		pc.printf("Base Velocity:    %f m/s, %f m/s, %f rad/s\r\n\r\n", longitudinalVelocity, transveralVelocity, angularVelocity);

		pc.printf("--------------------\r\n\r\n");

		wait(4);

	}
}
