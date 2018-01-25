#ifndef ARGONSERIALPARAMS_H
#define ARGONSERIALPARAMS_H

class ArgonSerialParams{
    public:
        enum Constans{
            //------------------------------------------------------------------
            // Joint Command ID
            //------------------------------------------------------------------
            // Configurations
            BASE_CONFIGURATION              = 0x01,
            ARM_CONFIGURATION               = 0x02,
            RESERVED_CONFIGURATION          = 0x03,
            
            // Sets
            SET_PWM                         = 0x10,
            SET_POWER                       = 0x11,
        
            // Gets
            GET_AVAILABLE                   = 0x20,
            GET_NUMBER                      = 0x21,
            GET_GEAR_RATIO                  = 0x22,
            GET_ENCODER_TICKS_PER_ROUND     = 0x23,
            GET_ENCODING_MODE               = 0x24,
            GET_PWM                         = 0x25,
            GET_PWM_RESOLUTION              = 0x26,
            GET_POWER                       = 0x27,
            GET_DIRECTION                   = 0x28,
            GET_ENCODER_COUNT               = 0x29,
            GET_JOINT_POSITION              = 0x2a,
            GET_MOTOR_POSITION              = 0x2b,
            GET_JOINT_RPM                   = 0x2c,
            GET_MOTOR_RPM                   = 0x2d,
            GET_JOINT_ANG_VEL               = 0x2e,
            GET_MOTOR_ANG_VEL               = 0x2f
        };
};

#endif