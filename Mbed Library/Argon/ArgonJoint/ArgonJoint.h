#ifndef ARGONJOINT_H
#define ARGONJOINT_H

#include "mbed.h"
#include "hal_inits_params.h"
#include "ArgonJointParams.h"

enum jointDirections{
    counterClockWise,
    clockwise,
};

namespace argon{
    
    TIM_HandleTypeDef * _getRpmCalcTimer(void);

    class ArgonJoint{
    public:
        // Constructor
        ArgonJoint(uint8_t number,
                    TIM_HandleTypeDef * pwmTimer,
                    uint32_t pwmTimerChannel,
                    uint16_t pwmResolution,
                    TIM_HandleTypeDef * icTimer,
                    uint32_t icTimerChannelA,
                    uint32_t icTimerChannelB,
                    GPIO_TypeDef * directionPort,
                    uint16_t directionPin):
            
            _available(false),
            _number(number),
            _pwmTimer(pwmTimer),
            _pwmTimerChannel(pwmTimerChannel),
            _pwmResolution(pwmResolution),
            _icTimer(icTimer),
            _icTimerChannelA(icTimerChannelA),
            _icTimerChannelB(icTimerChannelB),
            _directionPort(directionPort),
            _directionPin(directionPin),
            _gearRatio(0.0f),
            _encoderTicksPerRound(0),
            _encodingType(0),
            _PWM(0),
            _power(0.0f),
            _encoderCount(0),
            _prevEncoderCount(0),
            _encoderIndex(0),
            _direction(0),
            _motorRPM(0.0f),
            _jointRPM(0.0f),
            _motorPosition(0.0f),
            _jointPosition(0.0f)
        {

        };
        
        // Destructor
        ~ArgonJoint(){}
        
        /* Joint 1 
                Argon Base: Front Left
                Argon Arm: Joint 1
        */
        static ArgonJoint& joint1_Instance(){
            static ArgonJoint joint1(ArgonJointParams::joint1_number,
                                    ArgonJointParams::joint1_PWM_timer,
                                    ArgonJointParams::joint1_PWM_channel,
                                    HalInitParams::timer8_period + 1,
                                    ArgonJointParams::joint1_ic_timer,
                                    ArgonJointParams::joint1_ic_timer_CH_A,
                                    ArgonJointParams::joint1_ic_timer_CH_B,
                                    ArgonJointParams::joint1_direction_port,
                                    ArgonJointParams::joint1_direction_pin);
            return joint1;
        }
        
        /* Joint 2
            Argon Base: Front Right
            Argon Arm: Joint 2
        */
        static ArgonJoint& joint2_Instance(){
            static ArgonJoint joint2(ArgonJointParams::joint2_number,
                                    ArgonJointParams::joint2_PWM_timer,
                                    ArgonJointParams::joint2_PWM_channel,
                                    HalInitParams::timer8_period + 1,
                                    ArgonJointParams::joint2_ic_timer,
                                    ArgonJointParams::joint2_ic_timer_CH_A,
                                    ArgonJointParams::joint2_ic_timer_CH_B,
                                    ArgonJointParams::joint2_direction_port,
                                    ArgonJointParams::joint2_direction_pin);
            return joint2;
        }
        
        /* Joint 3
            Argon Base: Rear Left
            Argon Arm: Joint 3
        */
        static ArgonJoint& joint3_Instance(){
            static ArgonJoint joint3(ArgonJointParams::joint3_number,
                                    ArgonJointParams::joint3_PWM_timer,
                                    ArgonJointParams::joint3_PWM_channel,
                                    HalInitParams::timer8_period + 1,
                                    ArgonJointParams::joint3_ic_timer,
                                    ArgonJointParams::joint3_ic_timer_CH_A,
                                    ArgonJointParams::joint3_ic_timer_CH_B,
                                    ArgonJointParams::joint3_direction_port,
                                    ArgonJointParams::joint3_direction_pin);
            return joint3;
        }
        
        /* Joint 4
            Argon Base: Rear Right
            Argon Arm: Joint 4
        */
        static ArgonJoint& joint4_Instance(){
            static ArgonJoint joint4(ArgonJointParams::joint4_number,
                                    ArgonJointParams::joint4_PWM_timer,
                                    ArgonJointParams::joint4_PWM_channel,
                                    HalInitParams::timer8_period + 1,
                                    ArgonJointParams::joint4_ic_timer,
                                    ArgonJointParams::joint4_ic_timer_CH_A,
                                    ArgonJointParams::joint4_ic_timer_CH_B,
                                    ArgonJointParams::joint4_direction_port,
                                    ArgonJointParams::joint4_direction_pin);
            return joint4;
        }
        
        /* Joint 5
            Argon Base: No usage
            Argon Arm: Joint 5
        */
        static ArgonJoint& joint5_Instance(){
            static ArgonJoint joint5(ArgonJointParams::joint5_number,
                                    ArgonJointParams::joint5_PWM_timer,
                                    ArgonJointParams::joint5_PWM_channel,
                                    HalInitParams::timer12_period + 1,
                                    ArgonJointParams::joint5_ic_timer,
                                    ArgonJointParams::joint5_ic_timer_CH_A,
                                    ArgonJointParams::joint5_ic_timer_CH_B,
                                    ArgonJointParams::joint5_direction_port,
                                    ArgonJointParams::joint5_direction_pin);
            return joint5;
        }
        
        /* Joint 6
            Argon Base: No usage
            Argon Arm: Joint 6
        */
        static ArgonJoint& joint6_Instance(){
            static ArgonJoint joint6(ArgonJointParams::joint6_number,
                                    ArgonJointParams::joint6_PWM_timer,
                                    ArgonJointParams::joint6_PWM_channel,
                                    HalInitParams::timer12_period + 1,
                                    ArgonJointParams::joint6_ic_timer,
                                    ArgonJointParams::joint6_ic_timer_CH_A,
                                    ArgonJointParams::joint6_ic_timer_CH_B,
                                    ArgonJointParams::joint6_direction_port,
                                    ArgonJointParams::joint6_direction_pin);
            return joint6;
        }
        
        /* Sets */
        //Config
        void        _setAvailable(bool jointAvailable);
        void        _setGearRatio(float gearRatio);
        void        _setEncoderTicksPerRound(uint16_t encoderTicksPerRound);
        void        _setEncodingMode(uint8_t encodingType);
        void        _setEncoderIndex(uint8_t encoderIndex);
        void        _setEncoderCount(int32_t encoderCount);
        void        _setPrevEncoderCount(int32_t encoderCount);
        // RPM
        void        _setMotorRPM(float motorRPM);
        void        _setJointRPM(float jointRPM);
        // Position
        void        _setMotorPosition(float motorPosition);
        
        // Function
        void        setPWM(int16_t PWM);
        void        setPower(float power);

        /* Gets */
        //Config
        bool        getAvailable(void);
        uint8_t     getNumber(void);
        
        TIM_HandleTypeDef * _getPwmTimer(void){return _pwmTimer;};
        uint32_t    _getPwmTimerChannel(void){return _pwmTimerChannel;};
        
        TIM_HandleTypeDef * _getICTimer(void){return _icTimer;};
        uint32_t    _getICTimerChannelA(void){return _icTimerChannelA;};
        uint32_t    _getICTimerChannelB(void){return _icTimerChannelB;};
        
        
        
        uint8_t     _getEncoderIndex(void);
        
        float       getGearRatio(void);
        uint16_t    getEncoderTicksPerRound(void);
        uint8_t     getEncodingMode(void);
        //Function
        int16_t     getPwm(void);
        uint16_t    getPwmResolution(void);
        float       getPower(void);
        int8_t      getDirection(void);
        //Position              
        int32_t     getEncoderCount(void);
        int32_t     _getPrevEncoderCount(void);
        float       getJointPosition(void);
        float       getMotorPosition(void);
        //RPM
        float       getMotorRPM(void);
        float       getJointRPM(void);
        //AngVelocity
        float       getMotorAngVel(void);
        float       getJointAngVel(void);
        

    private:
        //Constants
        bool                _available;
        uint8_t             _number;   //Fixed
        //Pwm
        TIM_HandleTypeDef * _pwmTimer;
        uint32_t            _pwmTimerChannel;
        uint16_t            _pwmResolution;
        //Input capture
        TIM_HandleTypeDef * _icTimer;
        uint32_t            _icTimerChannelA;
        uint32_t            _icTimerChannelB;
        //Direction
        GPIO_TypeDef *      _directionPort;
        uint16_t            _directionPin;
        //Motor Params
        float               _gearRatio;
        uint16_t            _encoderTicksPerRound;
        uint8_t             _encodingType;  //x1, x2, x4

        //Variables
        int16_t             _PWM;
        float               _power;
        int32_t             _encoderCount;
        int32_t             _prevEncoderCount;
        uint8_t             _encoderIndex;
        uint8_t             _direction;
        float               _motorRPM;
        float               _jointRPM;
        float               _motorPosition;
        float               _jointPosition;
        
    };
}

#endif /* MOTOR_H */
