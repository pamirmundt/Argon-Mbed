/*
 *	Argon Joint
 */

#include "mbed.h"
#include "Argon.h"

ArgonBase myBase;

Serial pc(SERIAL_TX, SERIAL_RX, 9600);

int main() {

	/*
	 * FL - Front Left
	 * FR - Front Right
	 * RL - Rear Left
	 * RR - Rear Right
	 */

	while(1){

		/* Get Motor Angular Velocity in rad/s */
		float FL_AngularVelocity = myBase.frontLeft.getMotorAngVel();
		float FR_AngularVelocity = myBase.frontRight.getMotorAngVel();
		float RL_AngularVelocity = myBase.rearLeft.getMotorAngVel();
		float RR_AngularVelocity = myBase.rearRight.getMotorAngVel();

		pc.printf("Angular Velocities: %f %f %f %f (rad/s)\r\n\n", FL_AngularVelocity, FR_AngularVelocity, RL_AngularVelocity, RR_AngularVelocity);
		wait_ms(500);


		/* Get Joint RPM */
		float FL_RPM = myBase.frontLeft.getMotorRPM();
		float FR_RPM = myBase.frontRight.getMotorRPM();
		float RL_RPM = myBase.rearLeft.getMotorRPM();
		float RR_RPM = myBase.rearRight.getMotorRPM();

		pc.printf("Motor Velocities:   %f %f %f %f (RPM)\r\n\n", FL_RPM, FR_RPM, RL_RPM, RR_RPM);
		wait_ms(500);


		/* Get joint positions and print */
		float FL_Position = myBase.frontLeft.getMotorPosition();
		float FR_Position = myBase.frontRight.getMotorPosition();
		float RL_Position = myBase.rearLeft.getMotorPosition();
		float RR_Position = myBase.rearRight.getMotorPosition();

		pc.printf("Motor Positions:    %f %f %f %f (Rad)\r\n\n", FL_Position, FR_Position, RL_Position, RR_Position);
		wait_ms(500);

	}
}
