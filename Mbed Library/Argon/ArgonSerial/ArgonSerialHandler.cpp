#include "ArgonSerialHandler.h"
#include "ArgonSerialParams.h"
#include "charVar.h"
#include "int16Var.h"
#include "int32Var.h"
#include "uint8Var.h"
#include "uint16Var.h"
#include "float32Var.h"

using namespace Argon;

extern Serial pc;

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
    // Received Msg -> MSG_ID | Module Number | Joint Number
    char msg_id = MSG[0];
    char module_num = MSG[1];
    char joint_num = MSG[2];
    
    // MSG_ID CHECK
    // MODULE CHECK
    // JOINT CHECK
    
    switch (msg_id){
        //----------------------------------------------------------------------
        // Joint Sets
        //----------------------------------------------------------------------
        case ArgonSerialParams::SET_PWM:{
            argonSerial::int16Var PWM;
            PWM.deserialize((unsigned char*)MSG + 3);
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            // Send the msg back for ack
            char msg[3] = {msg_id, module_num, joint_num};
            _serialNode.sendMsg(msg, size);
            
            pc.printf("SET PWM: %d %d \r\n", joint_num, PWM.data);
            break;
        }
        case ArgonSerialParams::SET_POWER:{
            argonSerial::float32Var power;
            power.deserialize((unsigned char*)MSG + 3);
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            // Send the msg back for ack
            char msg[3] = {msg_id, module_num, joint_num};
            _serialNode.sendMsg(msg, size);
            
            pc.printf("SET POWER %d %f\r\n", joint_num, power.data);
            break;
        }
        
        //----------------------------------------------------------------------
        // Joint Gets
        //----------------------------------------------------------------------
        case ArgonSerialParams::GET_AVAILABLE:{
            
            char available = 1;
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[4] = {msg_id, module_num, joint_num};
            msg[3] = available;
            _serialNode.sendMsg(msg, sizeof(msg));
            
            pc.printf("GET AVAILABLE %d %d %d\r\n", module_num, joint_num, available);
            break;
        }
        
        case ArgonSerialParams::GET_NUMBER:{
            
            char number = 3;
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[4] = {msg_id, module_num, joint_num};
            msg[3] = number;
            _serialNode.sendMsg(msg, sizeof(msg));
            
            pc.printf("GET NUMBER %d %d %d\r\n", module_num, joint_num, number);
            break;
        }
        
        case ArgonSerialParams::GET_GEAR_RATIO:{

            argonSerial::float32Var gearRatio;
            
            gearRatio.data = 1.8f;
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(float)] = {msg_id, module_num, joint_num};
            gearRatio.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            pc.printf("GET GEAR RATIO %d %d %f\r\n", module_num, joint_num, gearRatio.data);
            break;
        }
        
        case ArgonSerialParams::GET_ENCODER_TICKS_PER_ROUND:{

            argonSerial::uint16Var encoderTicksPerRound;
            
            encoderTicksPerRound.data = 12;
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(uint16_t)] = {msg_id, module_num, joint_num};
            encoderTicksPerRound.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            pc.printf("GET ENCODER TICKS PER ROUND %d %d %d\r\n", module_num, joint_num, encoderTicksPerRound.data);
            break;
        }
        
        case ArgonSerialParams::GET_ENCODING_MODE:{

            uint8_t encodingMode = 4;
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(uint8_t)] = {msg_id, module_num, joint_num};
            msg[3] = encodingMode;
            _serialNode.sendMsg(msg, sizeof(msg));
            
            pc.printf("GET ENCODING MODE %d %d %d\r\n", module_num, joint_num, encodingMode);
            break;
        }
        
        case ArgonSerialParams::GET_PWM:{

            argonSerial::int16Var pwm;
            
            pwm.data = 1024;
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(int16_t)] = {msg_id, module_num, joint_num};
            pwm.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            pc.printf("GET PWM %d %d %d\r\n", module_num, joint_num, pwm.data);
            break;
        }
        
        case ArgonSerialParams::GET_PWM_RESOLUTION:{

            argonSerial::uint16Var pwmRes;
            
            pwmRes.data = 4096;
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(uint16_t)] = {msg_id, module_num, joint_num};
            pwmRes.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            pc.printf("GET PWM RES %d %d %d\r\n", module_num, joint_num, pwmRes.data);
            break;
        }
        
        case ArgonSerialParams::GET_POWER:{

            argonSerial::float32Var power;
            
            power.data = 45.5f;
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(float)] = {msg_id, module_num, joint_num};
            power.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            pc.printf("GET POWER %d %d %d\r\n", module_num, joint_num, power.data);
            break;
        }
        
        case ArgonSerialParams::GET_DIRECTION:{

            char direction = 3;
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(char)] = {msg_id, module_num, joint_num};
            msg[3] = direction;
            _serialNode.sendMsg(msg, sizeof(msg));
            
            pc.printf("GET DIRECTION %d %d %d\r\n", module_num, joint_num, direction);
            break;
        }
        
        case ArgonSerialParams::GET_ENCODER_COUNT:{

            argonSerial::int32Var encCount;
            
            encCount.data = 223123;
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(int32_t)] = {msg_id, module_num, joint_num};
            encCount.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            pc.printf("GET ENCODER COUNT %d %d %d\r\n", module_num, joint_num, encCount.data);
            break;
        }
        
        case ArgonSerialParams::GET_JOINT_POSITION:{

            argonSerial::float32Var jointPos;
            
            jointPos.data = 12354.123f;
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(float)] = {msg_id, module_num, joint_num};
            jointPos.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            pc.printf("GET JOINT POSITION %d %d %f\r\n", module_num, joint_num, jointPos.data);
            break;
        }
        
        case ArgonSerialParams::GET_MOTOR_POSITION:{

            argonSerial::float32Var motorPos;
            
            motorPos.data = 22.123f;
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(float)] = {msg_id, module_num, joint_num};
            motorPos.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            pc.printf("GET MOTOR POSITION %d %d %f\r\n", module_num, joint_num, motorPos.data);
            break;
        }
        
        case ArgonSerialParams::GET_JOINT_RPM:{

            argonSerial::float32Var jointRPM;
            
            jointRPM.data = 1.1f;
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(float)] = {msg_id, module_num, joint_num};
            jointRPM.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            pc.printf("GET JOINT RPM %d %d %f\r\n", module_num, joint_num, jointRPM.data);
            break;
        }
        
        case ArgonSerialParams::GET_MOTOR_RPM:{

            argonSerial::float32Var motorRPM;
            
            motorRPM.data = 3.1f;
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(float)] = {msg_id, module_num, joint_num};
            motorRPM.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            pc.printf("GET MOTOR RPM %d %d %f\r\n", module_num, joint_num, motorRPM.data);
            break;
        }
        
        case ArgonSerialParams::GET_JOINT_ANG_VEL:{

            argonSerial::float32Var jointAngVel;
            
            jointAngVel.data = 3.1f;
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(float)] = {msg_id, module_num, joint_num};
            jointAngVel.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            pc.printf("GET JOINT ANG VEL %d %d %f\r\n", module_num, joint_num, jointAngVel.data);
            break;
        }
        
        case ArgonSerialParams::GET_MOTOR_ANG_VEL:{

            argonSerial::float32Var motorAngVel;
            
            motorAngVel.data = 3.1f;
            
            // Sent Msg -> MSG_ID | Module Number | Joint Number | MSG
            char msg[3 + sizeof(float)] = {msg_id, module_num, joint_num};
            motorAngVel.serialize((unsigned char*)msg + 3);
            _serialNode.sendMsg(msg, sizeof(msg));
            
            pc.printf("GET MOTOR ANG VEL %d %d %f\r\n", module_num, joint_num, motorAngVel.data);
            break;
        }
    }
}
