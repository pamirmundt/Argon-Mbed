/*
 *	Argon PWM
 */

#include "mbed.h"
#include "Argon.h"

ArgonBase myBase;

Serial pc(SERIAL_TX, SERIAL_RX, 9600);

int main() {

	myBase.frontLeft.setPWM(512);

	myBase.frontRight.setPWM(512);

	myBase.rearLeft.setPWM(512);

	myBase.rearRight.setPWM(512);

	while(1){

		pc.printf("PWM: %d %d %d %d\r\n", myBase.frontLeft.getPWM(), myBase.frontRight.getPWM(), myBase.rearLeft.getPWM(), myBase.rearRight.getPWM());

		wait_ms(500);

		pc.printf("Direction: %d %d %d %d\r\n", myBase.frontLeft.getDirection(), myBase.frontRight.getDirection(), myBase.rearLeft.getDirection(), myBase.rearRight.getDirection());

		wait_ms(500);

	}
}
