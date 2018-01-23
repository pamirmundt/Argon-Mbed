#ifndef ARGONSERIALHANDLER_H
#define ARGONSERIALHANDLER_H

#include "ArgonSerialNode.h"
#include "mbed.h"

/* Example:
 *
 *  #include "mbed.h"
 *  #include "ArgonSerialHandler.h"
 * 
 *  Argon::ArgonSerialHandler sh;
 * 
 *  int main() {
 *
 *      while(1) {
 *          int a = sh.spinOnce();
 *          if (a < 0)
 *              pc.printf("%d\r\n", a);
 *      }
 *  }
 *
 */

namespace Argon{
    class ArgonSerialHandler{
      public:
        ArgonSerialHandler():
            _serialNode(PA_9, PA_10, 9600)
            //_serialNode(PC_10, PC_11, 9600)
        {
        }
        ~ArgonSerialHandler(){}
    
        int spinOnce(void);
        
      private:
        ArgonSerialNode _serialNode;
        
        void messageParser(char * msg, uint8_t size);
      
    };
}

#endif