/*
 *	Argon Serial Display
 */

#include "mbed.h"
#include "Argon.h"

Serial pc(SERIAL_TX, SERIAL_RX, 9600);

ArgonBase myBase;

int main() {

	int duration = 1;

	pc.printf("Hello World !\r\n");

	while(1){

		wait(1);

		pc.printf("This program runs since %d seconds.\r\n", duration++);

	}
}
