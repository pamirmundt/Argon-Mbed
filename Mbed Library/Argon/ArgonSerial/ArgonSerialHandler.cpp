#include "ArgonSerialHandler.h"
#include "ArgonSerialParams.h"
#include "charVar.h"
#include "int16Var.h"
#include "int32Var.h"
#include "uint8Var.h"
#include "uint16Var.h"
#include "float32Var.h"

using namespace Argon;

// DEBUG
// extern Serial pc;

void ArgonSerialHandler::init(Argon::ArgonBase * base){
    // Check if this board belogs to an arm
    if(this->_arm == NULL)
        this->_base = base;
}

void ArgonSerialHandler::init(Argon::ArgonArm * arm){
    // Check if this board belogs to a base
    if(this->_base == NULL)
        this->_arm = arm;
}

int ArgonSerialHandler::spinOnce(void){
    // Receive Message
    //  0 : No error / No message / Successful message
    // -1 : Timeout error
    // -2 : Message start frame error (should be 0xFF 0x02)
    // -3 : Message length crc error
    // -4 : Message crc error
    int retVal = _serialNode.recvMsg();
    if(retVal == 0){
        if(_serialNode.isRecvMessageAvailable()){
            uint8_t size = _serialNode.getMessageLength();
            char msg[size];
            _serialNode.getMessage(msg);
            messageParser(msg, size);
        }
    }
    
    return retVal;
}

void ArgonSerialHandler::messageParser(char * MSG, uint8_t size){
    
    if(this->_arm == NULL && this->_base == NULL)
        // Arm or base not initialized
        return;        
    
    // Received Msg -> MSG_ID | Module Number | Joint Number
    char msg_id = MSG[0];
    char module_num = MSG[1];
    char joint_num = MSG[2];
    
    if(module_Num > RESERVED_CONFIGURATION)
        // Wrong configuration number
        return;
    
    switch (msg_id){
        //----------------------------------------------------------------------
        // Joint Sets
        //----------------------------------------------------------------------
        case ArgonSerialParams::SET_PWM:{
            argonSerial::int16Var pwm;
            pwm.deserialize((unsigned char*)MSG + 3);
            
            if(module_num == ArgonSerialParams::BASE_CONFIGURATION && this->_base != NULL)
                this->_base->setPwm(joint_num, pwm.data);
            //else if(module_num == ArgonSerialParams::ARM_CONFIGURATION && this->_arm != NULL)
                //this->_arm->setPwm(joint_num, pwm.data);
                
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            // Send the msg back for ack
            char msg[3] = {msg_id, module_num, joint_num};
            _serialNode.sendMsg(msg, size);
            
            break;
        }
        case ArgonSerialParams::SET_POWER:{
            argonSerial::float32Var power;
            power.deserialize((unsigned char*)MSG + 3);
            
            if(module_num == ArgonSerialParams::BASE_CONFIGURATION && this->_base != NULL)
                this->_base->setPower(joint_num, power.data);
            //else if(module_num == ArgonSerialParams::ARM_CONFIGURATION && this->_arm != NULL)
                //this->_arm->setPower(joint_num, power.data);
                
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            // Send the msg back for ack
            char msg[3] = {msg_id, module_num, joint_num};
            _serialNode.sendMsg(msg, size);
            
            break;
        }
        
        //----------------------------------------------------------------------
        // Joint Gets
        //----------------------------------------------------------------------
        case ArgonSerialParams::GET_AVAILABLE:{
            
            char available = 0;
            
            if(module_num == ArgonSerialParams::BASE_CONFIGURATION && this->_base != NULL)
                available = this->_base->getAvailable(joint_num);
            //else if(module_num == ArgonSerialParams::ARM_CONFIGURATION && this->_arm != NULL)
                //available = this->_arm->getAvailable(joint_num);
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[4] = {msg_id, module_num, joint_num};
            msg[3] = available;
            _serialNode.sendMsg(msg, sizeof(msg));

            break;
        }
        
        case ArgonSerialParams::GET_NUMBER:{
            
            char number = 0;
            
            if(module_num == ArgonSerialParams::BASE_CONFIGURATION && this->_base != NULL)
                number = this->_base->getNumber(joint_num);
            //else if(module_num == ArgonSerialParams::ARM_CONFIGURATION && this->_arm != NULL)
                //number = this->_arm->getNumber(joint_num);
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[4] = {msg_id, module_num, joint_num};
            msg[3] = number;
            _serialNode.sendMsg(msg, sizeof(msg));

            break;
        }
        
        case ArgonSerialParams::GET_GEAR_RATIO:{

            argonSerial::float32Var gearRatio;
            
            if(module_num == ArgonSerialParams::BASE_CONFIGURATION && this->_base != NULL)
                gearRatio.data = this->_base->getGearRatio(joint_num);
            //else if(module_num == ArgonSerialParams::ARM_CONFIGURATION && this->_arm != NULL)
                //gearRatio.data = this->_arm->getGearRatio(joint_num);
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(float)] = {msg_id, module_num, joint_num};
            gearRatio.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            break;
        }
        
        case ArgonSerialParams::GET_ENCODER_TICKS_PER_ROUND:{

            argonSerial::uint16Var encoderTicksPerRound;
            
            if(module_num == ArgonSerialParams::BASE_CONFIGURATION && this->_base != NULL)
                encoderTicksPerRound.data = this->_base->getEncoderTicksPerRound(joint_num);
            //else if(module_num == ArgonSerialParams::ARM_CONFIGURATION && this->_arm != NULL)
                //encoderTicksPerRound.data = this->_arm->getEncoderTicksPerRound(joint_num);
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(uint16_t)] = {msg_id, module_num, joint_num};
            encoderTicksPerRound.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            break;
        }
        
        case ArgonSerialParams::GET_ENCODING_MODE:{

            uint8_t encodingMode = 0;
            
            if(module_num == ArgonSerialParams::BASE_CONFIGURATION && this->_base != NULL)
                encodingMode = this->_base->getEncodingMode(joint_num);
            //else if(module_num == ArgonSerialParams::ARM_CONFIGURATION && this->_arm != NULL)
                //encodingMode = this->_arm->getEncodingMode(joint_num);
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(uint8_t)] = {msg_id, module_num, joint_num};
            msg[3] = encodingMode;
            _serialNode.sendMsg(msg, sizeof(msg));

            break;
        }
        
        case ArgonSerialParams::GET_PWM:{

            argonSerial::int16Var pwm;
            
            if(module_num == ArgonSerialParams::BASE_CONFIGURATION && this->_base != NULL)
                pwm.data = this->_base->getPwm(joint_num);
            //else if(module_num == ArgonSerialParams::ARM_CONFIGURATION && this->_arm != NULL)
                //pwm.data = this->_arm->getPwm(joint_num);
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(int16_t)] = {msg_id, module_num, joint_num};
            pwm.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            break;
        }
        
        case ArgonSerialParams::GET_PWM_RESOLUTION:{

            argonSerial::uint16Var pwmRes;
            
            if(module_num == ArgonSerialParams::BASE_CONFIGURATION && this->_base != NULL)
                pwmRes.data = this->_base->getPwmResolution(joint_num);
            //else if(module_num == ArgonSerialParams::ARM_CONFIGURATION && this->_arm != NULL)
                //pwmRes.data = this->_arm->getPwmResolution(joint_num);
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(uint16_t)] = {msg_id, module_num, joint_num};
            pwmRes.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));

            break;
        }
        
        case ArgonSerialParams::GET_POWER:{

            argonSerial::float32Var power;
            
            if(module_num == ArgonSerialParams::BASE_CONFIGURATION && this->_base != NULL)
                power.data = this->_base->getPower(joint_num);
            //else if(module_num == ArgonSerialParams::ARM_CONFIGURATION && this->_arm != NULL)
                //power.data = this->_arm->getPower(joint_num);
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(float)] = {msg_id, module_num, joint_num};
            power.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            break;
        }
        
        case ArgonSerialParams::GET_DIRECTION:{

            char direction = 0;
            
            if(module_num == ArgonSerialParams::BASE_CONFIGURATION && this->_base != NULL)
                direction = this->_base->getDirection(joint_num);
            //else if(module_num == ArgonSerialParams::ARM_CONFIGURATION && this->_arm != NULL)
                //direction = this->_arm->getDirection(joint_num);
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(char)] = {msg_id, module_num, joint_num};
            msg[3] = direction;
            _serialNode.sendMsg(msg, sizeof(msg));

            break;
        }
        
        case ArgonSerialParams::GET_ENCODER_COUNT:{

            argonSerial::int32Var encCount;
            
            if(module_num == ArgonSerialParams::BASE_CONFIGURATION && this->_base != NULL)
                encCount.data = this->_base->getEncoderCount(joint_num);
            //else if(module_num == ArgonSerialParams::ARM_CONFIGURATION && this->_arm != NULL)
                //encCount.data = this->_arm->getEncoderCount(joint_num);
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(int32_t)] = {msg_id, module_num, joint_num};
            encCount.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));

            break;
        }
        
        case ArgonSerialParams::GET_JOINT_POSITION:{

            argonSerial::float32Var jointPos;
            
            if(module_num == ArgonSerialParams::BASE_CONFIGURATION && this->_base != NULL)
                jointPos.data = this->_base->getJointPosition(joint_num);
            //else if(module_num == ArgonSerialParams::ARM_CONFIGURATION && this->_arm != NULL)
                //jointPos.data = this->_arm->getJointPosition(joint_num);
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(float)] = {msg_id, module_num, joint_num};
            jointPos.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            break;
        }
        
        case ArgonSerialParams::GET_MOTOR_POSITION:{

            argonSerial::float32Var motorPos;
            
            if(module_num == ArgonSerialParams::BASE_CONFIGURATION && this->_base != NULL)
                motorPos.data = this->_base->getMotorPosition(joint_num);
            //else if(module_num == ArgonSerialParams::ARM_CONFIGURATION && this->_arm != NULL)
                //motorPos.data = this->_arm->getMotorPosition(joint_num);
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(float)] = {msg_id, module_num, joint_num};
            motorPos.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            break;
        }
        
        case ArgonSerialParams::GET_JOINT_RPM:{

            argonSerial::float32Var jointRPM;
            
            if(module_num == ArgonSerialParams::BASE_CONFIGURATION && this->_base != NULL)
                jointRPM.data = this->_base->getJointRPM(joint_num);
            //else if(module_num == ArgonSerialParams::ARM_CONFIGURATION && this->_arm != NULL)
                //jointRPM.data = this->_arm->getJointRPM(joint_num);
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(float)] = {msg_id, module_num, joint_num};
            jointRPM.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            break;
        }
        
        case ArgonSerialParams::GET_MOTOR_RPM:{

            argonSerial::float32Var motorRPM;
            
            if(module_num == ArgonSerialParams::BASE_CONFIGURATION && this->_base != NULL)
                motorRPM.data = this->_base->getMotorRPM(joint_num);
            //else if(module_num == ArgonSerialParams::ARM_CONFIGURATION && this->_arm != NULL)
                //motorRPM.data = this->_arm->getMotorRPM(joint_num);
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(float)] = {msg_id, module_num, joint_num};
            motorRPM.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            break;
        }
        
        case ArgonSerialParams::GET_JOINT_ANG_VEL:{

            argonSerial::float32Var jointAngVel;
            
            if(module_num == ArgonSerialParams::BASE_CONFIGURATION && this->_base != NULL)
                jointAngVel.data = this->_base->getJointAngVel(joint_num);
            //else if(module_num == ArgonSerialParams::ARM_CONFIGURATION && this->_arm != NULL)
                //jointAngVel.data = this->_arm->getJointAngVel(joint_num);
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(float)] = {msg_id, module_num, joint_num};
            jointAngVel.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            break;
        }
        
        case ArgonSerialParams::GET_MOTOR_ANG_VEL:{

            argonSerial::float32Var motorAngVel;
            
            if(module_num == ArgonSerialParams::BASE_CONFIGURATION && this->_base != NULL)
                motorAngVel.data = this->_base->getMotorAngVel(joint_num);
            //else if(module_num == ArgonSerialParams::ARM_CONFIGURATION && this->_arm != NULL)
                //motorAngVel.data = this->_arm->getMotorAngVel(joint_num);
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(float)] = {msg_id, module_num, joint_num};
            motorAngVel.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            break;
        }
    }
}
