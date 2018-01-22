#ifndef ARGONBASEPARAMS_H
#define ARGONBASEPARAMS_H

namespace ArgonBaseParams
{
    //Dimensions
    const float wheelRadius                         = 0.03f;    //Meters
    const float lengthBetweenFrontAndRearWheels     = 0.130f;   //Meters
    const float lengthBetweenFrontWheels            = 0.160f;   //Meters
    const float geomFactor = (lengthBetweenFrontAndRearWheels / 2.0f + lengthBetweenFrontWheels / 2.0f);

    //Motor Config
    const uint16_t encoderResolution                = 3;    //3 CPR
    const uint8_t encodingMode                      = 4;    //Quadrature (x4)
    const float gearRatio = ((35.0f*37.0f*35.0f*38.0f)/(12.0f*11.0f*13.0f*10.0f)); // ~=100.37
}

#endif