/* Includes ------------------------------------------------------------------*/
#include "mbed.h"
#include "ArgonBase.h"
#include "params.h"
#include "base_kinematics.h"

/* Defines -------------------------------------------------------------------*/
#ifndef M_PI
#define M_PI        3.14159265358979323846f
#endif

#ifndef RPM2RAD
#define RPM2RAD     ((2.0f * M_PI) / 60.0f)
#endif

#ifndef RAD2RPM
#define RAD2RPM     (60.0f / (2.0f * M_PI))
#endif

/* Functions -----------------------------------------------------------------*/
/**
 * Radian to RPM
 * @param Radians
 * @return RPM
 */
float baseKinematics::rad2Rpm(float rad){
	return rad * RAD2RPM;
}

/**
 * RPM to Radian
 * @param RPM
 * @return Radians
 */
float baseKinematics::rpm2Rad(float rpm){
	return rpm * RPM2RAD;
}

/**
 * Calculates from the Cartesian velocity the individual wheel velocities
 * @param longitudinalVelocity - forward or backward velocity (m/s)
 * @param transversalVelocity - sideways velocity (m/s)
 * @param angularVelocity- rotational velocity around the center (rad/s)
 * @param jointRPM1 - joint 1 velocity to return (rad/s)
 * @param jointRPM2 - joint 2 velocity to return (rad/s)
 * @param jointRPM3 - joint 3 velocity to return (rad/s)
 * @param jointRPM4 - joint 4 velocity to return (rad/s)
 */
void baseKinematics::cartesianVelocityToWheelVelocities(float longitudinalVelocity, float transversalVelocity, float angularVelocity, float & jointAngVel1, float & jointAngVel2, float & jointAngVel3, float & jointAngVel4){
  jointAngVel1 = (longitudinalVelocity - transversalVelocity - geomFactor*angularVelocity) / wheelRadius;
  jointAngVel2 = (longitudinalVelocity + transversalVelocity + geomFactor*angularVelocity) / wheelRadius;
  jointAngVel3 = (longitudinalVelocity + transversalVelocity - geomFactor*angularVelocity) / wheelRadius;
  jointAngVel4 = (longitudinalVelocity - transversalVelocity + geomFactor*angularVelocity) / wheelRadius;
}

/**
 * Calculates from the wheel velocities the cartesian velocity
 * @param jointRPM1 - joint 1 velocity to return (rad/s)
 * @param jointRPM2 - joint 2 velocity to return (rad/s)
 * @param jointRPM3 - joint 3 velocity to return (rad/s)
 * @param jointRPM4 - joint 4 velocity to return (rad/s)
 * @param longitudinalVelocity - forward or backward velocity to return (m/s)
 * @param transversalVelocity - sideways velocity to return (m/s)
 * @param angularVelocity - rotational velocity around the center to return (rad/s)
 */
void baseKinematics::wheelVelocitiesToCartesianVelocity(float jointAngVel1, float jointAngVel2, float jointAngVel3, float jointAngVel4, float & longitudinalVelocity, float & transversalVelocity, float & angularVelocity){
  longitudinalVelocity = (jointAngVel1 + jointAngVel2 + jointAngVel3 + jointAngVel4) * wheelRadius / 4.0f;
  transversalVelocity = (-jointAngVel1 + jointAngVel2 + jointAngVel3 - jointAngVel4) * wheelRadius / 4.0f;
  angularVelocity = (-jointAngVel1 + jointAngVel2 - jointAngVel3 + jointAngVel4) * wheelRadius / (4.0f * geomFactor);
}

/**
 * Calculates from the cartesian position the wheel positions
 * @param jointAngPos1
 * @param jointAngPos2
 * @param jointAngPos3
 * @param jointAngPos4
 * @param longitudinalPosition
 * @param transversalPosition
 * @param orientation
 */
void baseKinematics::wheelPositionsToCartesianPosition(float jointAngPos1, float jointAngPos2, float jointAngPos3, float jointAngPos4, float & longitudinalPosition, float & transversalPosition, float & orientation){
    //Calculate Delta Encoder Position    
	float deltaAngPosJoint1 = jointAngPos1 - jointLastAngPos1;
	float deltaAngPosJoint2 = jointAngPos2 - jointLastAngPos2;
	float deltaAngPosJoint3 = jointAngPos3 - jointLastAngPos3;
	float deltaAngPosJoint4 = jointAngPos4 - jointLastAngPos4;

    //Store Encoder Count for next iteration
	jointLastAngPos1 = jointAngPos1;
	jointLastAngPos2 = jointAngPos2;
	jointLastAngPos3 = jointAngPos3;
	jointLastAngPos4 = jointAngPos4;

    //Calculate Delta Longitudial Position in meters
    float deltaLongitudinalPos = (float(deltaAngPosJoint1 + deltaAngPosJoint2 + deltaAngPosJoint3 + deltaAngPosJoint4) * wheelRadius) / 4.0f;
    //Calculate Delta Transversal Position in meters
    float deltaTransversalPos = (float(-deltaAngPosJoint1 + deltaAngPosJoint2 + deltaAngPosJoint3 - deltaAngPosJoint4) * wheelRadius) / 4.0f;

    //Calculate Base Position (x, y, theta)
    //Radians
    orientation += (float(-deltaAngPosJoint1 + deltaAngPosJoint2 - deltaAngPosJoint3 + deltaAngPosJoint4) * wheelRadius) / 4.0f / geomFactor;

    //Meters
    longitudinalPosition += deltaLongitudinalPos * cos(orientation) - deltaTransversalPos * sin(orientation);

    //Meters
    transversalPosition += deltaLongitudinalPos * sin(orientation) + deltaTransversalPos * cos(orientation);
}

/**
 *
 * @param longitudinalPosition
 * @param transversalPosition
 * @param orientation
 * @param jointPosition1
 * @param jointPosition2
 * @param jointPosition3
 * @param jointPosition4
 */
void baseKinematics::cartesianPositionToWheelPositions(float longitudinalPosition, float transversalPosition, float orientation, float & jointPosition1, float & jointPosition2, float & jointPosition3, float & jointPosition4){
	float Rad_FromX = longitudinalPosition / wheelRadius;
	float Rad_FromY = transversalPosition / wheelRadius;

	float Rad_FromTheta = ( orientation * geomFactor) / wheelRadius;

	jointPosition1 = Rad_FromX - Rad_FromY - Rad_FromTheta;
	jointPosition2 = Rad_FromX + Rad_FromY + Rad_FromTheta;
	jointPosition3 = Rad_FromX + Rad_FromY - Rad_FromTheta;
	jointPosition4 = Rad_FromX - Rad_FromY + Rad_FromTheta;
}

//calculate wheel torques
//Calculates wheel torques from base force with Jacobian Transpose
//@param base longitudinal force
//@param base transversal force
//@param base orientation force
//@param returns wheel torques
/*
void calcJacobianTranspose(float baseLongitudinalForce, float baseTransversalForce, float baseOrientationForce, float angularVelocity, float wheel1_refRPM, float wheel2_refRPM, float wheel3_refRPM, float wheel4_refRPM){
    wheel1Torque = baseLongitudinalForce * (cos(orientation) - sin(orientation)) / sqrtf(2.0f) + baseTransversalForce * (sin(orientation) + cos(orientation)) / sqrtf(2.0f) + baseOrientationForce * geomFactor * sqrtf(2.0f);
    wheel2Torque = baseLongitudinalForce * (cos(orientation) + sin(orientation)) / sqrtf(2.0f) + baseTransversalForce * (sin(orientation) - cos(orientation)) / sqrtf(2.0f) - baseOrientationForce * geomFactor * sqrtf(2.0f);
    wheel3Torque = baseLongitudinalForce * (cos(orientation) + sin(orientation)) / sqrtf(2.0f) + baseTransversalForce * (sin(orientation) - cos(orientation)) / sqrtf(2.0f) + baseOrientationForce * geomFactor * sqrtf(2.0f);
    wheel4Torque = baseLongitudinalForce * (cos(orientation) - sin(orientation)) / sqrtf(2.0f) + baseTransversalForce * (sin(orientation) + cos(orientation)) / sqrtf(2.0f) - baseOrientationForce * geomFactor * sqrtf(2.0f);

    wheel1_refRPM = wheel1Torque;
    wheel2_refRPM = wheel2Torque;
    wheel3_refRPM = wheel3Torque;
    wheel4_refRPM = wheel4Torque;
}
*/

/**
 * Local (joint space)
 * @param baseLongitudinal_J
 * @param baseTransversal_J
 * @param baseOrientation_J
 * @param joint1_J
 * @param joint2_J
 * @param joint3_J
 * @param joint4_J
 */
void baseKinematics::calcJacobian(float baseLongitudinal_J, float baseTransversal_J, float baseAngular_J, float & joint1_J, float & joint2_J, float & joint3_J, float & joint4_J){
	joint1_J = (baseLongitudinal_J - baseTransversal_J - baseAngular_J * geomFactor) / wheelRadius;
	joint2_J = (baseLongitudinal_J + baseTransversal_J + baseAngular_J * geomFactor) / wheelRadius;
	joint3_J = (baseLongitudinal_J + baseTransversal_J - baseAngular_J * geomFactor) / wheelRadius;
	joint4_J = (baseLongitudinal_J - baseTransversal_J + baseAngular_J * geomFactor) / wheelRadius;
}

/**
 * Local (task space)
 * @param joint1_J
 * @param joint2_J
 * @param joint3_J
 * @param joint4_J
 * @param baseLongitudinal_J
 * @param baseTransversal_J
 * @param baseAngular_J
 */
void baseKinematics::calcJacobianInverse(float joint1_J, float joint2_J, float joint3_J, float joint4_J, float & baseLongitudinal_J, float & baseTransversal_J, float & baseAngular_J){
	baseLongitudinal_J = (joint1_J + joint2_J + joint3_J + joint4_J) * wheelRadius / 4.0f;
	baseTransversal_J = (- joint1_J + joint2_J + joint3_J - joint4_J) * wheelRadius / 4.0f ;
	baseAngular_J = (- joint1_J + joint2_J - joint3_J + joint4_J) * wheelRadius / (4.0f * geomFactor);
}
