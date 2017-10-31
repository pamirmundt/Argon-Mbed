/*
 *	Argon Jacobian
 */

#include "mbed.h"
#include "Argon.h"

ArgonBase myBase;

/*

J+: Jacobian Inverse
r: wheel radius
Lx: length between left and right wheels
Ly: length between front and rear wheels

			| 1            1            1            1         |
J+ = r/4  *	|-1            1            1           -1         |
			|-2/(Lx+Ly)    2/(Lx+Ly)   -2/(Lx+Ly)    2/(Lx+Ly) |

*/

float joint1_J = 0.0f, joint2_J = 0.0f, joint3_J = 0.0f, joint4_J = 0.0f;

float baseLongitudinal_J = 0.0f, baseTransversal_J = 0.0f, baseAngular_J = 0.0f;

int main() {

	float Lx = myBase.getLengthBetweenFrontWheels();
	float Ly = myBase.getLengthBetweenFrontAndRearWheels();
	float wheel_radius = myBase.getWheelRadius();

	while(1){

		baseLongitudinal_J = (joint1_J + joint2_J + joint3_J + joint4_J) * wheel_radius / 4.0f;

		baseTransversal_J = (- joint1_J + joint2_J + joint3_J - joint4_J) * wheel_radius / 4.0f ;

		baseAngular_J = (- joint1_J + joint2_J - joint3_J + joint4_J) * wheel_radius / (4.0f * (Lx + Ly) / 2.0f );

	}
}
