#ifndef ARGONSERIALNODE_H
#define ARGONSERIALNODE_H

#include "mbed.h"
#include "BufferedSerial.h"

namespace Argon{
    
    class ArgonSerialNode{
      public:
        ArgonSerialNode(PinName tx, PinName rx, long baud = 9600)
                    :_serial(tx, rx, 1024),
                    _baud(baud),
                    _recvMsgAvailable(false),
                    //_sendMsgAvailable(false),
                    _mode(0),
                    _msgSize(0),
                    _index(0)
        {
            _serial.baud(baud);
            
            for(unsigned int i=0; i<INPUT_SIZE; i++)
                message_in[i] = 0;
            //for(unsigned int i=0; i<OUTPUT_SIZE; i++)
            //    message_out[i] = 0;
        }
        
        ~ArgonSerialNode(){}
    
        static uint8_t crc8(const uint8_t *addr, uint8_t len);
        
        int read(void);
        int write(char * msg, uint8_t msg_size);
        int recvMsg(void);
        int sendMsg(char * msg, uint8_t msg_size);
        
        bool isRecvMessageAvailable(void);
        //bool isSendMessageAvailable(void);
        uint8_t getMessageLength(void);
        void getMessage(char * msg);
        
      private:
        BufferedSerial _serial;
        long _baud;
        
        bool _recvMsgAvailable;
        //bool _sendMsgAvailable;
        
        uint8_t _mode;
        uint8_t _msgSize;
        uint8_t _index;
        
        static const int INPUT_SIZE = 256;
        //static const int OUTPUT_SIZE = 256;
        uint8_t message_in[INPUT_SIZE];
        //char message_out[OUTPUT_SIZE];
    };
    
}

#endif