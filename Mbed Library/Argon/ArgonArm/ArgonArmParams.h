#ifndef ARGONARMPARAMS_H
#define ARGONARMPARAMS_H

namespace ArgonArmParams
{
    //Dimensions

    //Motor Config
    const uint16_t encoderResolution                = 3;    //3 CPR
    const uint8_t encodingMode                      = 4;    //Quadrature (x4)
    const float gearRatio = ((35.0f*37.0f*35.0f*38.0f)/(12.0f*11.0f*13.0f*10.0f)); // ~=100.37
}

#endif