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
 * Calculates from the Cartesian velocity the individual wheel velocities
 * @param longitudinalVelocity - forward or backward velocity (m/s)
 * @param transversalVelocity - sideways velocity (m/s)
 * @param angularVelocity- rotational velocity around the center (rad/s)
 * @param jointRPM1 - joint 1 velocity to return (RPM)
 * @param jointRPM2 - joint 2 velocity to return (RPM)
 * @param jointRPM3 - joint 3 velocity to return (RPM)
 * @param jointRPM4 - joint 4 velocity to return (RPM)
 */
void baseKinematics::cartesianVelocityToWheelVelocities(float longitudinalVelocity, float transversalVelocity, float angularVelocity, float & jointRPM1, float & jointRPM2, float & jointRPM3, float & jointRPM4){
  float jointAngVel1 = (longitudinalVelocity - transversalVelocity - geomFactor*angularVelocity) / wheelRadius;
  float jointAngVel2 = (longitudinalVelocity + transversalVelocity + geomFactor*angularVelocity) / wheelRadius;
  float jointAngVel3 = (longitudinalVelocity + transversalVelocity - geomFactor*angularVelocity) / wheelRadius;
  float jointAngVel4 = (longitudinalVelocity - transversalVelocity + geomFactor*angularVelocity) / wheelRadius;

  //Angular velocity to RPM
  jointRPM1 = jointAngVel1 * RAD2RPM;
  jointRPM2 = jointAngVel2 * RAD2RPM;
  jointRPM3 = jointAngVel3 * RAD2RPM;
  jointRPM4 = jointAngVel4 * RAD2RPM;
}

/**
 * Calculates from the wheel velocities the cartesian velocity
 * @param jointRPM1 - joint 1 velocity to return (RPM)
 * @param jointRPM2 - joint 2 velocity to return (RPM)
 * @param jointRPM3 - joint 3 velocity to return (RPM)
 * @param jointRPM4 - joint 4 velocity to return (RPM)
 * @param longitudinalVelocity - forward or backward velocity to return (m/s)
 * @param transversalVelocity - sideways velocity to return (m/s)
 * @param angularVelocity - rotational velocity around the center to return (rad/s)
 */
void baseKinematics::wheelVelocitiesToCartesianVelocity(float jointRPM1, float jointRPM2, float jointRPM3, float jointRPM4, float & longitudinalVelocity, float & transversalVelocity, float & angularVelocity){
  //RPM to rad/s
  float jointAngVel1 = jointRPM1 * RPM2RAD;
  float jointAngVel2 = jointRPM2 * RPM2RAD;
  float jointAngVel3 = jointRPM3 * RPM2RAD;
  float jointAngVel4 = jointRPM4 * RPM2RAD;

  longitudinalVelocity = (jointAngVel1 + jointAngVel2 + jointAngVel3 + jointAngVel4) * wheelRadius / 4.0f;
  transversalVelocity = (-jointAngVel1 + jointAngVel2 + jointAngVel3 - jointAngVel4) * wheelRadius / 4.0f;
  angularVelocity = (-jointAngVel1 + jointAngVel2 - jointAngVel3 + jointAngVel4) * wheelRadius / (4.0f * geomFactor);
}

/**
 * Calculates from the cartesian position the wheel positions
 * @param encPos1 - Joint 1 Velocity
 * @param encPos2 - Joint 2 Velocity
 * @param encPos3 - Joint 3 Velocity
 * @param encPos4 - Joint 4 Velocity
 */
void baseKinematics::wheelPositionsToCartesianPosition(int16_t encPos1, int16_t encPos2, int16_t encPos3,int16_t encPos4, float & longitudinalPosition, float & transversalPosition, float & orientation){
    //Calculate Delta Encoder Position    
    int16_t deltaPosJoint1 = encPos1 - motorLastEncPos1;;
    int16_t deltaPosJoint2 = encPos2 - motorLastEncPos2;
    int16_t deltaPosJoint3 = encPos3 - motorLastEncPos3;
    int16_t deltaPosJoint4 = encPos4 - motorLastEncPos4;

    //Store Encoder Count for next iteration
    motorLastEncPos1 = encPos1;
    motorLastEncPos2 = encPos2;
    motorLastEncPos3 = encPos3;
    motorLastEncPos4 = encPos4;

    //Calculate Delta Longitudial Position in meters
    float deltaLongitudinalPos = (float(deltaPosJoint1 + deltaPosJoint2 + deltaPosJoint3 + deltaPosJoint4) * 2.0f * M_PI * wheelRadius) / 4.0f / encoder_resolution / gearRatio / encoder_mode;
    //Calculate Delta Transversal Position in meters
    float deltaTransversalPos = (float(-deltaPosJoint1 + deltaPosJoint2 + deltaPosJoint3 - deltaPosJoint4) * 2.0f * M_PI * wheelRadius) / 4.0f / encoder_resolution / gearRatio / encoder_mode;

    //Calculate Base Position (x, y, theta)
    //Radians
    orientation += (float(-deltaPosJoint1 + deltaPosJoint2 - deltaPosJoint3 + deltaPosJoint4) * 2.0f * M_PI * wheelRadius) / 4.0f / geomFactor / encoder_resolution / gearRatio / encoder_mode;

    //Meters
    longitudinalPosition += deltaLongitudinalPos * cos(orientation) - deltaTransversalPos * sin(orientation);

    //Meters
    transversalPosition += deltaLongitudinalPos * sin(orientation) + deltaTransversalPos * cos(orientation);
}

void baseKinematics::cartesianPositionToWheelPositions(float longitudinalPosition, float transversalPosition, float orientation, float & jointPosition1, float & jointPosition2, float & jointPosition3, float & jointPosition4){
	float Rad_FromX = longitudinalPosition / wheelRadius;
	float Rad_FromY = transversalPosition / wheelRadius;

	float Rad_FromTheta = geomFactor / wheelRadius;

	jointPosition1 = -Rad_FromX + Rad_FromY + Rad_FromTheta;
	jointPosition2 = Rad_FromX + Rad_FromY + Rad_FromTheta;
	jointPosition3 = -Rad_FromX - Rad_FromY + Rad_FromTheta;
	jointPosition4 = Rad_FromX - Rad_FromY + Rad_FromTheta;
}

//calculate wheel torques
//Calculates wheel torques from base force with Jacobian Transpose
//@param base longitudinal force
//@param base transversal force
//@param base orientation force
//@param returns wheel torques
/*
void calcJacobianT(float baseLongitudinalForce, float baseTransversalForce, float baseOrientationForce, float angularVelocity, float wheel1_refRPM, float wheel2_refRPM, float wheel3_refRPM, float wheel4_refRPM){    
    wheel1Torque = baseLongitudinalForce*(cos(orientation)-sin(orientation))/sqrtf(2.0f) + baseTransversalForce*(sin(orientation)+cos(orientation))/sqrtf(2.0f) + baseOrientationForce*geomFactor*sqrtf(2.0f);
    wheel2Torque = baseLongitudinalForce*(cos(orientation)+sin(orientation))/sqrtf(2.0f) + baseTransversalForce*(sin(orientation)-cos(orientation))/sqrtf(2.0f) - baseOrientationForce*geomFactor*sqrtf(2.0f);
    wheel3Torque = baseLongitudinalForce*(cos(orientation)+sin(orientation))/sqrtf(2.0f) + baseTransversalForce*(sin(orientation)-cos(orientation))/sqrtf(2.0f) + baseOrientationForce*geomFactor*sqrtf(2.0f);
    wheel4Torque = baseLongitudinalForce*(cos(orientation)-sin(orientation))/sqrtf(2.0f) + baseTransversalForce*(sin(orientation)+cos(orientation))/sqrtf(2.0f) - baseOrientationForce*geomFactor*sqrtf(2.0f);

    wheel1_refRPM = wheel1Torque;
    wheel2_refRPM = wheel2Torque;
    wheel3_refRPM = wheel3Torque;
    wheel4_refRPM = wheel4Torque;
}
*/
