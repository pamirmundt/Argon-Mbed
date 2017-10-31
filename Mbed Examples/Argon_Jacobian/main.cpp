/*
 *	Argon Jacobian
 */

#include "mbed.h"
#include "Argon.h"

ArgonBase myBase;

/*

J: Jacobian
r: wheel radius
Lx: length between left and right wheels
Ly: length between front and rear wheels

			| 1   -1   -(Lx + Ly)/2 |
J = 1/r  *	| 1    1    (Lx + Ly)/2 |
			| 1    1   -(Lx + Ly)/2 |
			| 1   -1    (Lx + Ly)/2 |

*/

float joint1_J = 0.0f, joint2_J = 0.0f, joint3_J = 0.0f, joint4_J = 0.0f;

float baseLongitudinal_J = 0.0f, baseTransversal_J = 0.0f, baseAngular_J = 0.0f;

int main() {

	float Lx = myBase.getLengthBetweenFrontWheels();
	float Ly = myBase.getLengthBetweenFrontAndRearWheels();
	float wheel_radius = myBase.getWheelRadius();

	while(1){

		joint1_J = (baseLongitudinal_J - baseTransversal_J - baseAngular_J * ((Lx + Ly) / 2.0f) ) / wheel_radius;

		joint2_J = (baseLongitudinal_J + baseTransversal_J + baseAngular_J * ((Lx + Ly) / 2.0f) ) / wheel_radius;

		joint3_J = (baseLongitudinal_J + baseTransversal_J - baseAngular_J * ((Lx + Ly) / 2.0f) ) / wheel_radius;

		joint4_J = (baseLongitudinal_J - baseTransversal_J + baseAngular_J * ((Lx + Ly) / 2.0f) ) / wheel_radius;

	}
}
