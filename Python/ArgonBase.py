from ArgonSerialNode import ArgonSerialNode
from time import sleep
import struct

#Base
MODULE_NUMBER			= 1
#Arm
#MODULE_NUMBER			= 2

#Struct Types
_char 					= 'c'
_signed_char 			= 'b'
_unsigned_char			= 'B'
_bool					= '?'
_short					= 'h'
_unsigned_short			= 'H'
_int					= 'i'
_unsigned_int			= 'I'
_long					= 'l'
_unsigned_long			= 'L'
_long_long				= 'q'
_unsigned_long_long		= 'Q'
_float					= 'f'
_double					= 'd'

#Commands
#Sets
SET_PWM							= 0x10
SET_POWER						= 0x11

#Gets
GET_AVAILABLE					= 0x20 
GET_NUMBER						= 0x21
GET_GEAR_RATIO					= 0x22
GET_ENCODER_TICKS_PER_ROUND		= 0x23
GET_ENCODING_MODE				= 0x24
GET_PWM							= 0x25

'''
GET_POWER						= 0x26
GET_DIRECTION					= 0x27

GET_ENCODER_COUNT				= 0x28
GET_JOINT_POSITION				= 0x29
GET_MOTOR_POSITION				= 0x30
GET_MOTOR_RPM					= 0x3a
GET_JOINT_RPM					= 0x3b
GET_MOTOR_ANG_VEL				= 0x3c
GET_JOINT_ANG_VEL				= 0x3d
'''


class ArgonBase:
	def __init__(self, device = '/dev/serial0', baud = 9600, timeout = 0.1):
		self.__sn = ArgonSerialNode(device, baud, timeout)

	def sendRecv(self, CMD, jointNumber, msgType, msgSize):
		pack = []
		pack.extend( struct.pack('B', CMD) )
		pack.extend( struct.pack('B', MODULE_NUMBER) )
		pack.extend( struct.pack('B', jointNumber) )
		#msg.extend( struct.pack(msgType, msgSize) )

		if(self.__sn.sendMsg(pack)):
			if(self.__sn.recvMsg()):
				retMsg = self.__sn.readMsg()
				if( retMsg[0:3] == pack[0:3]):
					return struct.unpack(msgType, ''.join(retMsg[3:3+msgSize]))[0]
					#Received MSG -> MSG_ID | Joint Number | Message(uint8_t)

	def sendOnly(self, CMD, jointNumber, msg, msgType):
		pack = []
		pack.extend( struct.pack('B', CMD) )
		pack.extend( struct.pack('B', MODULE_NUMBER) )
		pack.extend( struct.pack('B', jointNumber) )
		pack.extend( struct.pack(msgType, msg) )

		if(self.__sn.sendMsg(pack)):
			if(self.__sn.recvMsg()):
				retMsg = self.__sn.readMsg()
				if( retMsg[0:3] == pack[0:3]):
					return True
		return False

	def setPWM(self, jointNumber, PWM):
		return self.sendOnly(SET_PWM, jointNumber, PWM, _short)

	def setPower(self, jointNumber, power):
		return self.sendOnly(SET_POWER, jointNumber, power, _float)

	def getAvailable(self, jointNumber):
		return self.sendRecv(GET_AVAILABLE, jointNumber, _unsigned_char, 1)

	def getNumber(self, jointNumber):
		return self.sendRecv(GET_NUMBER, jointNumber, _unsigned_char, 1)

	def getGearRatio(self, jointNumber):
		return self.sendRecv(GET_GEAR_RATIO, jointNumber, _float, 4)

	def getEncoderTicksPerRound(self, jointNumber):
		return self.sendRecv(GET_ENCODER_TICKS_PER_ROUND, jointNumber, _unsigned_short, 2)

	def getEncodingMode(self, jointNumber):
		return self.sendRecv(GET_ENCODING_MODE, jointNumber, _unsigned_char, 1)

	def getPWM(self, jointNumber):
		return self.sendRecv(GET_PWM, jointNumber, _short, 2)

myBase = ArgonBase()

while(1):
	print myBase.getPWM(2)
	sleep(0.5)
