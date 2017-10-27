#ifndef BASE_KINEMATICS_H
#define BASE_KINEMATICS_H

class baseKinematics{
public:
	baseKinematics(){};
	void cartesianVelocityToWheelVelocities(float longitudinalVelocity, float transversalVelocity, float angularVelocity, float & jointRPM1, float & jointRPM2, float & jointRPM3, float & jointRPM4);
	void wheelVelocitiesToCartesianVelocity(float jointRPM1, float jointRPM2, float jointRPM3, float jointRPM4, float & longitudinalVelocity, float & transversalVelocity, float & angularVelocity);
	void wheelPositionsToCartesianPosition(int16_t encPos1, int16_t encPos2, int16_t encPos3, int16_t encPos4, float & lastLongPos, float & lastTransPos, float &lastAngPos);
	void cartesianPositionToWheelPositions(float longitudinalPosition, float transversalPosition, float orientation, float & jointPosition1, float & jointPosition2, float & jointPosition3, float & jointPosition4);
private:

	float motorLastEncPos1;
	float motorLastEncPos2;
	float motorLastEncPos3;
	float motorLastEncPos4;
};

#endif /* BASE_KINEMATICS_H */

