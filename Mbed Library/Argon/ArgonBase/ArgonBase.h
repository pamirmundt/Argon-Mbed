#ifndef ARGONBASE_H
#define ARGONBASE_H

#include "ArgonJoint.h"
#include "ArgonBaseParams.h"

namespace Argon{

    class ArgonBase{
    public:
        ArgonJoint & joint1;
        ArgonJoint & joint2;
        ArgonJoint & joint3;
        ArgonJoint & joint4;
        
        // Constructor
        ArgonBase():joint1(ArgonJoint::joint1_Instance()),
                    joint2(ArgonJoint::joint2_Instance()),
                    joint3(ArgonJoint::joint3_Instance()),
                    joint4(ArgonJoint::joint4_Instance()),
                    _wheelRadius(ArgonBaseParams::wheelRadius),
                    _lengthBetweenFrontAndRearWheels(ArgonBaseParams::lengthBetweenFrontAndRearWheels),
                    _lengthBetweenFrontWheels(ArgonBaseParams::lengthBetweenFrontWheels),
                    _geomFactor(ArgonBaseParams::geomFactor)
        {
            //Base Init
            baseInit();
            
            //Joint 1 - Front Left Wheel
            joint1._setAvailable(true); //bool
            joint1._setGearRatio(ArgonBaseParams::gearRatio); //float
            joint1._setEncoderTicksPerRound(ArgonBaseParams::encoderResolution); //uint16_t
            joint1._setEncodingMode(ArgonBaseParams::encodingMode); //uint8_t
            //Joint 2 - Front Left Wheel
            joint2._setAvailable(true); //bool
            joint2._setGearRatio(ArgonBaseParams::gearRatio); //float
            joint2._setEncoderTicksPerRound(ArgonBaseParams::encoderResolution); //uint16_t
            joint2._setEncodingMode(ArgonBaseParams::encodingMode); //uint8_t
            //Joint 3 - Front Left Wheel
            joint3._setAvailable(true); //bool
            joint3._setGearRatio(ArgonBaseParams::gearRatio); //float
            joint3._setEncoderTicksPerRound(ArgonBaseParams::encoderResolution); //uint16_t
            joint3._setEncodingMode(ArgonBaseParams::encodingMode); //uint8_t
            //Joint 4 - Front Left Wheel
            joint4._setAvailable(true); //bool
            joint4._setGearRatio(ArgonBaseParams::gearRatio); //float
            joint4._setEncoderTicksPerRound(ArgonBaseParams::encoderResolution); //uint16_t
            joint4._setEncodingMode(ArgonBaseParams::encodingMode); //uint8_t
        }
        
        // Destructor
        ~ArgonBase(){}
        
        /* Sets */
        //Config
        //void _setWheelRadius(void);
        //void _setLengthBetweenFrontAndRearWheels(void);
        //void _setLengthBetweenFrontWheels(void);

        /* Gets */
        //Config
        float       getWheelRadius(void);
        float       getLengthBetweenFrontAndRearWheels(void);
        float       getLengthBetweenFrontWheels(void);
        float       getGeomFactor(void);
        //Velocity
        void        getVelocity(float & longitudinalVelocity, float & transversalVelocity, float & angularVelocity);
        float       getLongitudinalVelocity(void);
        float       getTransversalVelocity(void);
        float       getAngularVelocity(void);
        //Position
        void        getPosition(float & longitudinalPosition, float & transversalPosition, float & angularPosition);
        float       getLongitudinalPosition(void);
        float       getTransversalPosition(void);
        float       getAngularPosition(void);
        
        //----------------------------------------------------------------------
        // Joint Extension
        //----------------------------------------------------------------------
        // Sets
        void        setPwm(uint8_t jointNum, int16_t PWM);
        void        setPower(uint8_t jointNumber, float power);
        
        //Gets
        bool        getAvailable(uint8_t jointNum);
        uint8_t     getNumber(uint8_t jointNum);
        float       getGearRatio(uint8_t jointNum);    
        uint16_t    getEncoderTicksPerRound(uint8_t jointNum);
        uint8_t     getEncodingMode(uint8_t jointNum);
        int16_t     getPwm(uint8_t jointNum);
        uint16_t    getPwmResolution(uint8_t jointNum);
        float       getPower(uint8_t jointNum);
        int8_t      getDirection(uint8_t jointNum);       
        int32_t     getEncoderCount(uint8_t jointNum);
        float       getJointPosition(uint8_t jointNum);
        float       getMotorPosition(uint8_t jointNum);
        float       getJointRPM(uint8_t jointNum);
        float       getMotorRPM(uint8_t jointNum);
        float       getJointAngVel(uint8_t jointNum);
        float       getMotorAngVel(uint8_t jointNum);
        
    private:
        void        baseInit(void);
        
        ArgonJoint* getJoint(uint8_t jointNum);
    
        float       _wheelRadius;
        float       _lengthBetweenFrontAndRearWheels;
        float       _lengthBetweenFrontWheels;
        float       _geomFactor;
    };
    
}


#endif
