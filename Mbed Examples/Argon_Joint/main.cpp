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

		/* Get Encoder Counts in Ticks */
		int16_t FL_Encoder = myBase.frontLeft.getEncoderCount();
		int16_t FR_Encoder = myBase.frontRight.getEncoderCount();
		int16_t RL_Encoder = myBase.rearLeft.getEncoderCount();
		int16_t RR_Encoder = myBase.rearRight.getEncoderCount();

		pc.printf("Encoder Positions:  %d %d %d %d (Ticks)\r\n\n", FL_Encoder, FR_Encoder, RL_Encoder, RR_Encoder);
		wait_ms(500);


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


		/* Get joint positions and print */
		float FL_Position = myBase.frontLeft.getJointPosition();
		float FR_Position = myBase.frontRight.getJointPosition();
		float RL_Position = myBase.rearLeft.getJointPosition();
		float RR_Position = myBase.rearRight.getJointPosition();

		pc.printf("Joint Positions:    %f %f %f %f (Rad)\r\n\n", FL_Position, FR_Position, RL_Position, RR_Position);
		wait_ms(500);

	}
}
