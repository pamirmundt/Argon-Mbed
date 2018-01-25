#ifndef ARGONARM_H
#define ARGONARM_H

#include "ArgonJoint.h"
#include "ArgonArmParams.h"

namespace Argon{

    class ArgonArm{
    public:
        ArgonJoint & joint1;
        ArgonJoint & joint2;
        ArgonJoint & joint3;
        ArgonJoint & joint4;
        ArgonJoint & joint5;
        ArgonJoint & joint6;
        
        // Constructor
        ArgonArm(uint8_t DoF = 4):joint1(ArgonJoint::joint1_Instance()),
                            joint2(ArgonJoint::joint2_Instance()),
                            joint3(ArgonJoint::joint3_Instance()),
                            joint4(ArgonJoint::joint4_Instance()),
                            joint5(ArgonJoint::joint5_Instance()),
                            joint6(ArgonJoint::joint6_Instance()),
                            _DoF(DoF)
        {
            //Arm Init
            armInit();
            
            //Joint 1
            joint1._setAvailable(true); //bool
            joint1._setGearRatio(ArgonArmParams::gearRatio); //float
            joint1._setEncoderTicksPerRound(ArgonArmParams::encoderResolution); //uint16_t
            joint1._setEncodingMode(ArgonArmParams::encodingMode); //uint8_t
            //Joint 2
            joint2._setAvailable(true); //bool
            joint2._setGearRatio(ArgonArmParams::gearRatio); //float
            joint2._setEncoderTicksPerRound(ArgonArmParams::encoderResolution); //uint16_t
            joint2._setEncodingMode(ArgonArmParams::encodingMode); //uint8_t
            //Joint 3
            joint3._setAvailable(true); //bool
            joint3._setGearRatio(ArgonArmParams::gearRatio); //float
            joint3._setEncoderTicksPerRound(ArgonArmParams::encoderResolution); //uint16_t
            joint3._setEncodingMode(ArgonArmParams::encodingMode); //uint8_t
            //Joint 4
            joint4._setAvailable(true); //bool
            joint4._setGearRatio(ArgonArmParams::gearRatio); //float
            joint4._setEncoderTicksPerRound(ArgonArmParams::encoderResolution); //uint16_t
            joint4._setEncodingMode(ArgonArmParams::encodingMode); //uint8_t
            //Joint 5
            if((_DoF == 5) || (_DoF == 6)){
                joint5._setAvailable(true); //bool
                joint5._setGearRatio(ArgonArmParams::gearRatio); //float
                joint5._setEncoderTicksPerRound(ArgonArmParams::encoderResolution); //uint16_t
                joint5._setEncodingMode(ArgonArmParams::encodingMode); //uint8_t
            }
            //Joint 6
            if(_DoF == 6){
                joint6._setAvailable(true); //bool
                joint6._setGearRatio(ArgonArmParams::gearRatio); //float
                joint6._setEncoderTicksPerRound(ArgonArmParams::encoderResolution); //uint16_t
                joint6._setEncodingMode(ArgonArmParams::encodingMode); //uint8_t
            }

        }
        
        // Destructor
        ~ArgonArm(){}
        
        /* Sets */
        //Config

        /* Gets */
        //Config
        uint8_t         getDoF(void);
        
        //----------------------------------------------------------------------
        // Joint Extension
        //----------------------------------------------------------------------
        // Sets
        void        setPWM(uint8_t jointNum, int16_t PWM);
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
        float       getMotorRPM(uint8_t jointNum);
        float       getJointRPM(uint8_t jointNum);
        float       getMotorAngVel(uint8_t jointNum);
        float       getJointAngVel(uint8_t jointNum);
        
    private:
        void            armInit(void);
        ArgonJoint*     getJoint(uint8_t jointNumber);
        
        uint8_t _DoF;
    

    };
    
}


#endif
