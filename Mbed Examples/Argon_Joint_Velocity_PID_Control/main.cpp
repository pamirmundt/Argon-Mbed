/*
 *	Argon Template
 */

#include "mbed.h"
#include "Argon.h"

/*Prototype*/
void calcVelocityPID(void);

/* Argon Base */
ArgonBase myBase;

/* Serial */
Serial pc(SERIAL_TX, SERIAL_RX);

/* Control Loop at 100Hz (0.01sec) */
Ticker velocityPID;
float dt = 0.01f;


/* Reference RPM for Front Left Wheel */
float joint1_refRPM = 0.0f;
/* PID Control Constants */
float Kp = 140.0f; 	//Proportional Constant
float Ki = 128.0f; 	//Integral Constant
float Kd = 0.0f; 	//Derivative Constant
/* PID stored values */
float integral = 0.0f; 		//Integral sum
float prevRpmError = 0.0f; 	//Previours RPM Error



int main() {

	/* Set reference RPM */
	joint1_refRPM = 20.0f;

	/* Start Control Loop */
	velocityPID.attach(&calcVelocityPID, dt);


	while(1){

		/* Serial Print */
		pc.printf("Reference RPM: %f, RPM: %f, Error: %f\r\n\r\n", joint1_refRPM, myBase.frontLeft.getJointRPM(), joint1_refRPM - myBase.frontLeft.getJointRPM() );

	}
}

/* Control Loop */
void calcVelocityPID(){

	float joint1_RPM = myBase.frontLeft.getJointRPM();

	/* Calculate Error */
	float rpmError = joint1_refRPM - joint1_RPM;

	/* Integral */
	integral = integral + rpmError * dt;

	/* Derivative */
	float derivative = (rpmError - prevRpmError)/dt;

	/* PID Output as PWM */
	float output = Kp * rpmError + Ki * integral + Kd * derivative;

	/* Store rpmError */
	prevRpmError = rpmError;

	/* Set Motor PWM */
	myBase.frontLeft.setPWM( int16_t(output) );

}
