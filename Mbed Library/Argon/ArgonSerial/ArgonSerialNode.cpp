#include "mbed.h"

#include "ArgonSerialNode.h"

using namespace Argon;

//extern Serial pc;

//const uint8_t STX = '\2';
//const uint8_t ETX = '\3';

#define MODE_FIRST_FF       0
#define MODE_MSG_START      1
#define MODE_SIZE           2
#define MODE_SIZE_CRC       3
#define MODE_MESSAGE        4
#define MODE_MSG_CRC        5

// calculate 8-bit CRC
uint8_t ArgonSerialNode::crc8(const uint8_t *addr, uint8_t len)
{
    uint8_t crc = 0;
    while (len--)
    {
        uint8_t inbyte = *addr++;
        for (uint8_t i = 8; i; i--)
        {
            uint8_t mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if (mix)
                crc ^= 0x8C;
            inbyte >>= 1;
        }  // end of for
    }  // end of while
    return crc;
}  // end of crc8

int ArgonSerialNode::read(void){
    if (_serial.readable())
        return _serial.getc();
    return -1;
}

int ArgonSerialNode::write(char * msg, uint8_t msg_size){
    if (_serial.writeable()){
        if(_serial.write(msg, msg_size) == msg_size)
            return 0;
    }
    return -1;    
}

int ArgonSerialNode::recvMsg(void){
    // 0xFF | STX | MSG_LENGTH | MSG_LENGTH_CRC | MSG | MSG_CRC8
    // MSG = MSG_ID + Module (Base/Arm) + Joint + MSG
    
    Timer t;
    t.start();
    uint32_t c_time = t.read_ms();
    /* Timeout */

    while(true){
        int data = read();
        
        if(data < 0)
            break;
        
        /* Start of frame (0xFF)*/
        if(_mode == MODE_FIRST_FF){
            _recvMsgAvailable = false;
            if(data == 0xff){
                _mode = MODE_MSG_START;
            }
            else if(t.read_ms() > 1000){
                //TIMEOUT HERE
                return -1;
            }
        }
        
        /* Start of frame (0x02) */
        else if(_mode == MODE_MSG_START){
            if(data == 0x02){
                _mode = MODE_SIZE;
            }
            else{
                _mode = MODE_FIRST_FF;
                return -2;
            }
        }
        
        /* Message size (Joint + MSG_ID + MSG) */
        else if(_mode == MODE_SIZE){
            _msgSize = data;
            _mode = MODE_SIZE_CRC;
        }
        
        /* Message length CRC */
        else if(_mode == MODE_SIZE_CRC){
            if(crc8(&_msgSize, 1) == data){
                _mode = MODE_MESSAGE;
                _index = 0;
            }
            else{
            /* Abondon frame if msg_length_crc is wrong */
                _mode = MODE_FIRST_FF;
                return -3;
            }
        }
        
        /* Message data being received */
        else if(_mode == MODE_MESSAGE){
            message_in[_index++] = data;
            /* Message is completed */
            if(_index == _msgSize){
                _mode = MODE_MSG_CRC;
            }
        }
        
        /* Message CRC8 calculation */
        else if(_mode == MODE_MSG_CRC){
            _mode = MODE_FIRST_FF;
            
            if(crc8(message_in, _msgSize) ==  data){
                _recvMsgAvailable = true;
            }
            else{
                return -4;
            }
        }
    }
    return 0;
}

int ArgonSerialNode::sendMsg(char * msg, uint8_t msg_size){
    // 0xFF | STX | MSG_LENGTH | MSG_LENGTH_CRC | MSG | MSG_CRC8
    // MSG = MSG_ID + Joint + MSG
    char pack[msg_size + 5];
    
    pack[0] = 0xff;                     // 0xFF
    pack[1] = 0x02;                     // STX
    pack[2] = msg_size;                 // MSG LENGTH
    pack[3] = crc8(&msg_size, 1);       // CRC OF MESSAGE LENGTH
    for(int i = 0; i < msg_size; i++)   // MESSAGE
        pack[i+4] = msg[i];
    pack[msg_size + 4] = crc8((uint8_t *)msg, msg_size);    // CRC OF MESSAGE
    
    return write(pack, msg_size + 5);
}

void ArgonSerialNode::getMessage(char * msg){
    for(int i = 0; i < _index; i++){
        msg[i] = message_in[i];
    }
    _recvMsgAvailable = false;
}

bool ArgonSerialNode::isRecvMessageAvailable(void){
    return _recvMsgAvailable;
}

/*
bool ArgonSerialNode::isSendMessageAvailable(void){
    return _sendMsgAvailable;
}
*/

uint8_t ArgonSerialNode::getMessageLength(void){
    if (_recvMsgAvailable)
        return _index;
    else
        return 0;
}
