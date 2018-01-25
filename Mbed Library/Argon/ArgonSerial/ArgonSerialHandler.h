#ifndef ARGONSERIALHANDLER_H
#define ARGONSERIALHANDLER_H

#include "mbed.h"
#include "Argon.h"
#include "ArgonArm.h"
#include "ArgonBase.h"
#include "ArgonSerialNode.h"

/* Example:
 *
 *  #include "mbed.h"
 *  #include "Argon.h"
 *
 *  // This code is a serial listener //
 *
 *  // Create a base or an arm
 *  ArgonBase myBase;
 *  //ArgonArm myArm;
 *
 *  // Create a serial handler
 *  ArgonSerialHandler sh;
 * 
 *  int main() {
 *      // Initialize serial handler for base or arm
 *      sh.init(&myBase);
 *      //sh.init(&myArm);
 *
 *
 *      while(1) {
 *
 *          sh.spinOnce();
 *
 *      }
 *  }
 *
 */
 
using namespace Argon;

namespace Argon{
    class ArgonSerialHandler{
      public:
        ArgonSerialHandler():
            _serialNode(serialTX, serialRX, serialBaud),
            _base(NULL),
            _arm(NULL)
        {
        }
        ~ArgonSerialHandler(){}
    
        void init(Argon::ArgonBase * base);
        void init(Argon::ArgonArm * arm);
        
        int spinOnce(void);
        
      private:
        ArgonSerialNode _serialNode;
        
        Argon::ArgonBase * _base;
        Argon::ArgonArm * _arm;
        
        void messageParser(char * msg, uint8_t size);
      
    };
}

#endif
