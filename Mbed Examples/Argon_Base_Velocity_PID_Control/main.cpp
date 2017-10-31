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

/* PID Velocity Control Loop at 100Hz (0.01sec) */
Ticker velocityPID;

float dt = 0.01f;

/* Reference RPM */
float joint1_refRPM = 0.0f, joint2_refRPM = 0.0f, joint3_refRPM = 0.0f, joint4_refRPM = 0.0f;

/* PID Control Constants */
float Kp = 128.0f; 	//Proportional Constant
float Ki = 128.0f; 	//Integral Constant
float Kd = 0.0f; 	//Derivative Constant

/* PID stored values */
float joint1_integral = 0.0f, joint2_integral = 0.0f, joint3_integral = 0.0f, joint4_integral = 0.0f; //Integral sums
float joint1_prevRpmError = 0.0f, joint2_prevRpmError = 0.0f, joint3_prevRpmError = 0.0f, joint4_prevRpmError = 0.0f; 	//Previous RPM Errors


/* MAIN ******/
int main() {

	/* Set reference Base Velocity */
	float reference_x = 0.05f; 	// m/s

	float reference_y = 0.0f;	// m/s

	float reference_t = 0.0f;	// rad/s

	/* Start Control Loop */
	velocityPID.attach(&calcVelocityPID, dt);

	/* Set Base Velocity */
	/* cartesianVelocityToWheelVelocities function returns angular velocity (rad/s) */
	float refAngVel1 = 0.0f, refAngVel2 = 0.0f, refAngVel3 = 0.0f, refAngVel4 = 0.0f;

	myBase.kinematics.cartesianVelocityToWheelVelocities(reference_x, reference_y, reference_t, refAngVel1, refAngVel2, refAngVel3, refAngVel4);

	/* Convert angular velocity to RPM */
	joint1_refRPM = myBase.kinematics.rad2Rpm(refAngVel1);

	joint2_refRPM = myBase.kinematics.rad2Rpm(refAngVel2);

	joint3_refRPM = myBase.kinematics.rad2Rpm(refAngVel3);

	joint4_refRPM = myBase.kinematics.rad2Rpm(refAngVel4);



	while(1){

		/* Serial Print Joint RPMs */
		pc.printf("J-1: %f RPM, J-2: %f RPM, J-3: %f RPM, J-4: %f RPM\r\n\r\n", myBase.frontLeft.getJointRPM(), myBase.frontRight.getJointRPM(), myBase.rearLeft.getJointRPM(), myBase.rearRight.getJointRPM() );

		/* Wait 250ms */
		wait_ms(250);
	}
}
/*************/


/* Control Loop */
void calcVelocityPID(){

	/** Front Left Wheel PID **********************************************/
	/* Get Joint 1 RPM */
	float joint1_RPM = myBase.frontLeft.getJointRPM();

	/* Calculate Joint 1 RPM Error */
	float joint1_rpmError = joint1_refRPM - joint1_RPM;

	/* Joint 1 Integral */
	joint1_integral = joint1_integral + joint1_rpmError * dt;

	/* Joint 1 Derivative */
	float joint1_derivative = (joint1_rpmError - joint1_prevRpmError) / dt;

	/* Joint 1 PID Output as PWM */
	float joint1_output = Kp * joint1_rpmError + Ki * joint1_integral + Kd * joint1_derivative;

	/* Store Joint 1 rpmError */
	joint1_prevRpmError = joint1_rpmError;

	/* Set Joint 1 PWM */
	myBase.frontLeft.setPWM( int16_t(joint1_output) );
	/**********************************************************************/

	/** Front Right Wheel PID *********************************************/
	/* Get Joint 2 RPM */
	float joint2_RPM = myBase.frontRight.getJointRPM();

	/* Calculate Joint 2 RPM Error */
	float joint2_rpmError = joint2_refRPM - joint2_RPM;

	/* Joint 2 Integral */
	joint2_integral = joint2_integral + joint2_rpmError * dt;

	/* Joint 2 Derivative */
	float joint2_derivative = (joint2_rpmError - joint2_prevRpmError) / dt;

	/* Joint 2 PID Output as PWM */
	float joint2_output = Kp * joint2_rpmError + Ki * joint2_integral + Kd * joint2_derivative;

	/* Store Joint 2 rpmError */
	joint2_prevRpmError = joint2_rpmError;

	/* Set Joint 2 PWM */
	myBase.frontRight.setPWM( int16_t(joint2_output) );
	/**********************************************************************/

	/** Rear Left Wheel PID ***********************************************/
	/* Get Joint 3 RPM */
	float joint3_RPM = myBase.rearLeft.getJointRPM();

	/* Calculate Joint 3 RPM Error */
	float joint3_rpmError = joint3_refRPM - joint3_RPM;

	/* Joint 3 Integral */
	joint3_integral = joint3_integral + joint3_rpmError * dt;

	/* Joint 3 Derivative */
	float joint3_derivative = (joint3_rpmError - joint3_prevRpmError) / dt;

	/* Joint 3 PID Output as PWM */
	float joint3_output = Kp * joint3_rpmError + Ki * joint3_integral + Kd * joint3_derivative;

	/* Store Joint 3 rpmError */
	joint3_prevRpmError = joint3_rpmError;

	/* Set Joint 3 PWM */
	myBase.rearLeft.setPWM( int16_t(joint3_output) );
	/**********************************************************************/

	/** Rear Right Wheel PID **********************************************/
	/* Get Joint 4 RPM */
	float joint4_RPM = myBase.rearRight.getJointRPM();

	/* Calculate Joint 4 RPM Error */
	float joint4_rpmError = joint4_refRPM - joint4_RPM;

	/* Joint 4 Integral */
	joint4_integral = joint4_integral + joint4_rpmError * dt;

	/* Joint 4 Derivative */
	float joint4_derivative = (joint4_rpmError - joint4_prevRpmError) / dt;

	/* Joint 4 PID Output as PWM */
	float joint4_output = Kp * joint4_rpmError + Ki * joint4_integral + Kd * joint4_derivative;

	/* Store Joint 4 rpmError */
	joint4_prevRpmError = joint4_rpmError;

	/* Set Joint 4 PWM */
	myBase.rearRight.setPWM( int16_t(joint4_output) );
	/**********************************************************************/

}
