#ifndef ARGONSERIALPARAMS_H
#define ARGONSERIALPARAMS_H

class ArgonSerialParams{
    public:
        enum Constans{
            
            //------------------------------------------------------------------
            // Configurations
            //------------------------------------------------------------------
            BASE_CONFIGURATION              = 0x01,
            ARM_CONFIGURATION               = 0x02,
            RESERVED_CONFIGURATION          = 0x03,
            
            // 0x1* is for future configurations
            
            //------------------------------------------------------------------
            // Joint Command ID
            //------------------------------------------------------------------
            // Sets
            SET_PWM                         = 0x20,
            SET_POWER                       = 0x21,
            
            // 0x3* is for future sets
        
            // Gets
            GET_AVAILABLE                   = 0x40,
            GET_NUMBER                      = 0x41,
            GET_GEAR_RATIO                  = 0x42,
            GET_ENCODER_TICKS_PER_ROUND     = 0x43,
            GET_ENCODING_MODE               = 0x44,
            GET_PWM                         = 0x45,
            GET_PWM_RESOLUTION              = 0x46,
            GET_POWER                       = 0x47,
            GET_DIRECTION                   = 0x48,
            GET_ENCODER_COUNT               = 0x49,
            GET_JOINT_POSITION              = 0x4a,
            GET_MOTOR_POSITION              = 0x4b,
            GET_JOINT_RPM                   = 0x4c,
            GET_MOTOR_RPM                   = 0x4d,
            GET_JOINT_ANG_VEL               = 0x4e,
            GET_MOTOR_ANG_VEL               = 0x4f,
            
            // 0x5* is for future gets
            
            //------------------------------------------------------------------
            // Base Command ID
            //------------------------------------------------------------------
            
            // Sets
            // 0x6* - 0x7* is for future sets
            
            // Gets
            GET_WHEEL_RADIUS                            = 0x80,
            GET_LENGTH_BETWEEN_FRONT_AND_REAR_WHEELS    = 0x81,
            GET_LENGTH_BETWEEN_FRONT_WHEELS             = 0x82,
            GET_GEOM_FACTOR                             = 0x83,
            
            GET_VELOCITY                                = 0x84,
            GET_LONGITUDINAL_VELOCITY                   = 0x85,
            GET_TRANSVERSAL_VELOCITY                    = 0x86,
            GET_ANGULAR_VELOCITY                        = 0x87,
            GET_POSITION                                = 0x88,
            GET_LONGITUDINAL_POSITION                   = 0x89,
            GET_TRANSVERSAL_POSITION                    = 0x8a,
            GET_ANGULAR_POSITION                        = 0x8b
            
            // 0x9* is for future gets
            
            //------------------------------------------------------------------
            // Arm Command ID
            //------------------------------------------------------------------
            
            // Sets - 0xA*-0xB*
            
            // Gets - 0xC*-0xD*
        };
};

#endif