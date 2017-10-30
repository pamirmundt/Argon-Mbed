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

		/* Get Joint Angular Velocities in rad/s */
		float FL_AngularVelocity = myBase.frontLeft.getJointAngVel();
		float FR_AngularVelocity = myBase.frontRight.getJointAngVel();
		float RL_AngularVelocity = myBase.rearLeft.getJointAngVel();
		float RR_AngularVelocity = myBase.rearRight.getJointAngVel();

		pc.printf("Angular Velocities: %f %f %f %f (rad/s)\r\n\n", FL_AngularVelocity, FR_AngularVelocity, RL_AngularVelocity, RR_AngularVelocity);
		wait_ms(500);


		/* Get Joint RPM */
		float FL_RPM = myBase.frontLeft.getJointRPM();
		float FR_RPM = myBase.frontRight.getJointRPM();
		float RL_RPM = myBase.rearLeft.getJointRPM();
		float RR_RPM = myBase.rearRight.getJointRPM();

		pc.printf("Joint Velocities:   %f %f %f %f (RPM)\r\n\n", FL_RPM, FR_RPM, RL_RPM, RR_RPM);
		wait_ms(500);
	}
}
