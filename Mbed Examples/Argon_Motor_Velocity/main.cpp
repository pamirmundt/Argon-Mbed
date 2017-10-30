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

		/* Get Motor Angular Velocities in rad/s */
		float FL_AngularVelocity = myBase.frontLeft.getMotorAngVel();
		float FR_AngularVelocity = myBase.frontRight.getMotorAngVel();
		float RL_AngularVelocity = myBase.rearLeft.getMotorAngVel();
		float RR_AngularVelocity = myBase.rearRight.getMotorAngVel();

		pc.printf("Angular Velocities: %f %f %f %f (rad/s)\r\n\n", FL_AngularVelocity, FR_AngularVelocity, RL_AngularVelocity, RR_AngularVelocity);
		wait_ms(500);


		/* Get Motor RPM */
		float FL_RPM = myBase.frontLeft.getMotorRPM();
		float FR_RPM = myBase.frontRight.getMotorRPM();
		float RL_RPM = myBase.rearLeft.getMotorRPM();
		float RR_RPM = myBase.rearRight.getMotorRPM();

		pc.printf("Motor Velocities:   %f %f %f %f (RPM)\r\n\n", FL_RPM, FR_RPM, RL_RPM, RR_RPM);
		wait_ms(500);

	}
}
