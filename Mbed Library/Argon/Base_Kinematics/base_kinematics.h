#ifndef BASE_KINEMATICS_H
#define BASE_KINEMATICS_H

class baseKinematics{
public:
	baseKinematics(){};
	float rad2Rpm(float rad);
	float rpm2Rad(float rpm);
	void cartesianVelocityToWheelVelocities(float longitudinalVelocity, float transversalVelocity, float angularVelocity, float & jointAngVel1, float & jointAngVel2, float & jointAngVel3, float & jointAngVel4);
	void wheelVelocitiesToCartesianVelocity(float jointAngVel1, float jointAngVel2, float jointAngVel3, float jointAngVel4, float & longitudinalVelocity, float & transversalVelocity, float & angularVelocity);
	void wheelPositionsToCartesianPosition(float jointAngPos1, float jointAngPos2, float jointAngPos3, float jointAngPos4, float & longitudinalPosition, float & transversalPosition, float &orientation);
	void cartesianPositionToWheelPositions(float longitudinalPosition, float transversalPosition, float orientation, float & jointPosition1, float & jointPosition2, float & jointPosition3, float & jointPosition4);
private:

	float jointLastAngPos1;
	float jointLastAngPos2;
	float jointLastAngPos3;
	float jointLastAngPos4;
};

#endif /* BASE_KINEMATICS_H */

