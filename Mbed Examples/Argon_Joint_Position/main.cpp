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

		/* Get Encoder Counts in Ticks (tick) */
		int16_t FL_Encoder = myBase.frontLeft.getEncoderCount();
		int16_t FR_Encoder = myBase.frontRight.getEncoderCount();
		int16_t RL_Encoder = myBase.rearLeft.getEncoderCount();
		int16_t RR_Encoder = myBase.rearRight.getEncoderCount();

		pc.printf("Encoder Positions:  %d %d %d %d (Ticks)\r\n\n", FL_Encoder, FR_Encoder, RL_Encoder, RR_Encoder);
		wait_ms(500);

		/* Get joint positions and print (Radians) */
		float FL_Position = myBase.frontLeft.getJointPosition();
		float FR_Position = myBase.frontRight.getJointPosition();
		float RL_Position = myBase.rearLeft.getJointPosition();
		float RR_Position = myBase.rearRight.getJointPosition();

		pc.printf("Joint Positions:    %f %f %f %f (Rad)\r\n\n", FL_Position, FR_Position, RL_Position, RR_Position);
		wait_ms(500);

	}
}
