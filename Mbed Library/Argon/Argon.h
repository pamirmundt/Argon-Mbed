#ifndef ARGON_H
#define ARGON_H

/*******************************************************************************
 * Serial (UART)
 */
#define serialTX        PA_9   
#define serialRX        PA_10
#define serialBaud      9600

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "ArgonArm.h"
#include "ArgonBase.h"
#include "ArgonSerialHandler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
using namespace Argon;

/*******************************************************************************
 *  Timer Functions and Pin Configurations
 *******************************************************************************
 *
 *  Serial - UART
 *      Serial TX - (PA_7) 
 *      Serial RX - (PA_10)
 *
 *
 *  Timer 2 (90Mhz) - Quadrature Encoder Reading for Joint 1 and 2
 *      Input Capture - Motor 1 Encoder A - (PA_0)
 *      Input Capture - Motor 1 Encoder B - (PA_1)
 *      Input Capture - Motor 2 Encoder A - (PB_10)
 *      Input Capture - Motor 2 Encoder B - (PB_2)
 *
 *  Timer 3 (90Mhz) - Quadrature Encoder Reading for Joint 3 and 4
 *      Input Capture - Motor 3 Encoder A - (PA_6)
 *      Input Capture - Motor 3 Encoder B - (PA_7)
 *      Input Capture - Motor 4 Encoder A - (PB_0)
 *      Input Capture - Motor 4 Encoder B - (PB_1)
 *
 *  Timer 4 (90Mhz) - Quadrature Encoder Reading for Joint 5 and 6
 *      Input Capture - Motor 5 Encoder A - (PB_6)
 *      Input Capture - Motor 5 Encoder B - (PB_7)
 *      Input Capture - Motor 6 Encoder A - (PB_8)
 *      Input Capture - Motor 6 Encoder B - (PB_9)
 *
 *  Timer 8 (180Mhz) - PWM Generation for Joint 1, 2, 3, and 4
 *      PWM Generation - Motor 1 PWM - (PC_6)
 *      PWM Generation - Motor 2 PWM - (PC_7)
 *      PWM Generation - Motor 3 PWM - (PC_8)
 *      PWM Generation - Motor 4 PWM - (PC_9)
 *
 *  Timer 12 (90Mhz) - PWM Generation for Joint 5 and 6
 *      PWM Generation - Motor 5 PWM - (PB_14)
 *      PWM Generation - Motor 6 PWM - (PB_15)
 *
 *  ADC1 Channel - Motor Current Reading for all Joints
 *      Analog Read(IN10) - Motor 1 Current - (PC_0)
 *      Analog Read(IN11) - Motor 2 Current - (PC_1)
 *      Analog Read(IN12) - Motor 3 Current - (PC_2)
 *      Analog Read(IN13) - Motor 4 Current - (PC_3)
 *      Analog Read(IN14) - Motor 5 Current - (PC_4)
 *      Analog Read(IN15) - Motor 6 Current - (PC_5)
 *
 *  Direction GPIO - Motor Direction Control
 *      GPIO Write - Motor 1 Direction - (PB_5)
 *      GPIO Write - Motor 2 Direction - (PD_2)
 *      GPIO Write - Motor 3 Direction - (PA_12)
 *      GPIO Write - Motor 4 Direction - (PA_11)
 *      GPIO Write - Motor 5 Direction - (PB_12)
 *      GPIO Write - Motor 6 Direction - (PB_13)
 *
 *  Direction GPIO - Arm Limit Switch
 *      GPIO Read - Motor 1 Limit - (PC_12)
 *      GPIO Read - Motor 2 Limit - (PC_11)
 *      GPIO Read - Motor 3 Limit - (PC_10)
 *      GPIO Read - Motor 4 Limit - (PA_15)
 *      GPIO Read - Motor 5 Limit - (PA_8)
 *      GPIO Read - Motor 6 Limit - (PB_4)
 *
 */

#endif /* ARGON_H */