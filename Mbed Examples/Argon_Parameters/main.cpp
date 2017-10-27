/*
 *	Argon Joint
 */

#include "mbed.h"
#include "Argon.h"

ArgonBase myBase;

Serial pc(SERIAL_TX, SERIAL_RX, 9600);

/*

Front Left			Front Right

   	  	   - L1 -
		\\\---+---///
      	  	  |
      	  	  |			|
      	  	  +			L2
      	  	  |			|
      	  	  |
		///---+---\\\

Rear Left			Rear Right

*/

int main() {



	/* Get wheel radius in meters */
	float WR = myBase.getWheelRadius();

	/* Get the length between front wheels (centers of the wheels)*/
	float L1 = myBase.getLengthBetweenFrontWheels();

	/* Get the length between front and rear wheels (centers of the wheels)*/
	float L2 = myBase.getLengthBetweenFrontAndRearWheels();

	/* Encoder Ticks per motor round (Encoder Resolution) */
	uint16_t encRes = myBase.frontLeft.getEncoderTicksPerRound();

	/* Get Gear Ratio */
	float gear = myBase.frontLeft.getGearRatio();

	while(1){

		pc.printf("Wheel Radius: %f (m)\r\n", WR);

		pc.printf("Length Between Front Wheels: %f (m)\r\n", L1);

		pc.printf("Length Between Front and RearWheels: %f (m)\r\n", L2);

		pc.printf("Encoder Ticks per Motor Revolution: %d (ticks)\r\n", encRes);

		pc.printf("Encoder Ticks per Wheel Revolution: %f (ticks)\r\n", float(encRes * gear * 4.0f) );	//Quadrature Encoder (x4)

		pc.printf("Motor Gear Ratio: %f (1:ratio)\r\n\r\n", gear);

		pc.printf("--------------------\r\n\r\n", L2);

		wait(4);
	}
}
