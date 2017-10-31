#ifndef BASE_KINEMATICS_H
#define BASE_KINEMATICS_H

class baseKinematics{
public:
	baseKinematics():jointLastAngPos1(0),jointLastAngPos2(0),jointLastAngPos3(0),jointLastAngPos4(0){};
	float rad2Rpm(float rad);
	float rpm2Rad(float rpm);
	void cartesianVelocityToWheelVelocities(float longitudinalVelocity, float transversalVelocity, float angularVelocity, float & jointAngVel1, float & jointAngVel2, float & jointAngVel3, float & jointAngVel4);
	void wheelVelocitiesToCartesianVelocity(float jointAngVel1, float jointAngVel2, float jointAngVel3, float jointAngVel4, float & longitudinalVelocity, float & transversalVelocity, float & angularVelocity);
	void wheelPositionsToCartesianPosition(float jointAngPos1, float jointAngPos2, float jointAngPos3, float jointAngPos4, float & longitudinalPosition, float & transversalPosition, float &orientation);
	void cartesianPositionToWheelPositions(float longitudinalPosition, float transversalPosition, float orientation, float & jointPosition1, float & jointPosition2, float & jointPosition3, float & jointPosition4);
	void calcJacobian(float baseLongitudinal_J, float baseTransversal_J, float baseAngular_J, float & joint1_J, float & joint2_J, float & joint3_J, float & joint4_J);
	void calcJacobianInverse(float joint1_J, float joint2_J, float joint3_J, float joint4_J, float & baseLongitudinal_J, float & baseTransversal_J, float & baseAngular_J);

private:
	float jointLastAngPos1;
	float jointLastAngPos2;
	float jointLastAngPos3;
	float jointLastAngPos4;
};

#endif /* BASE_KINEMATICS_H */

