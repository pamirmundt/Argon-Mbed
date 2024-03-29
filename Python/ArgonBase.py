import struct
from ArgonSerialParams import *
from ArgonSerialNode import ArgonSerialNode

#Module Number			
MODULE_NUMBER			= BASE

'''
	STRUCT TYPES
'''
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

'''
	BASE CLASS
'''
class ArgonBase:
	def __init__(self, device = BASE_SERIAL_DEVICE, baud = BASE_SERIAL_BAUD, timeout = BASE_SERIAL_TIMEOUT):
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

	'''
		JOINT METHODS
	'''
	def setPwm(self, jointNumber, PWM):
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

	def getPwm(self, jointNumber):
		return self.sendRecv(GET_PWM, jointNumber, _short, 2)

	def getPwmResolution(self, jointNumber):
		return self.sendRecv(GET_PWM_RESOLUTION, jointNumber, _unsigned_short, 2)

	def getPower(self, jointNumber):
		return self.sendRecv(GET_POWER, jointNumber, _float, 4)

	def getDirection(self, jointNumber):
		return self.sendRecv(GET_DIRECTION, jointNumber, _signed_char, 1)

	def getEncoderCount(self, jointNumber):
		return self.sendRecv(GET_ENCODER_COUNT, jointNumber, _int, 4)

	def getJointPosition(self, jointNumber):
		return self.sendRecv(GET_JOINT_POSITION, jointNumber, _float, 4)

	def getMotorPosition(self, jointNumber):
		return self.sendRecv(GET_MOTOR_POSITION, jointNumber, _float, 4)

	def getJointRPM(self, jointNumber):
		return self.sendRecv(GET_JOINT_RPM, jointNumber, _float, 4)

	def getMotorRPM(self, jointNumber):
		return self.sendRecv(GET_MOTOR_RPM, jointNumber, _float, 4)

	def getJointAngVel(self, jointNumber):
		return self.sendRecv(GET_JOINT_ANG_VEL, jointNumber, _float, 4)

	def getMotorAngVel(self, jointNumber):
		return self.sendRecv(GET_MOTOR_ANG_VEL, jointNumber, _float, 4)

	'''
		BASE METHODS
	'''
	def getWheelRadius(self):
		return self.sendRecv(GET_WHEEL_RADIUS, 0, _float, 4)

	def getLengthBetweenFrontAndRearWheels(self):
		return self.sendRecv(GET_LENGTH_BETWEEN_FRONT_AND_REAR_WHEELS, 0, _float, 4)

	def getLengthBetweenFrontWheels(self):
		return self.sendRecv(GET_LENGTH_BETWEEN_FRONT_WHEELS, 0, _float, 4)

	def getGeomFactor(self):
		return self.sendRecv(GET_GEOM_FACTOR, 0, _float, 4)

	#def getVelocity(float & longitudinalVelocity, float & transversalVelocity, float & angularVelocity):
	#	return

	def getLongitudinalVelocity(self):
		return self.sendRecv(GET_LONGITUDINAL_VELOCITY, 0, _float, 4)

	def getTransversalVelocity(self):
		return self.sendRecv(GET_TRANSVERSAL_VELOCITY, 0, _float, 4)

	def getAngularVelocity(self):
		return self.sendRecv(GET_ANGULAR_VELOCITY, 0, _float, 4)

	#def getPosition(float & longitudinalPosition, float & transversalPosition, float & angularPosition);
	#	return

	def getLongitudinalPosition(self):
		return self.sendRecv(GET_LONGITUDINAL_POSITION, 0, _float, 4)

	def getTransversalPosition(self):
		return self.sendRecv(GET_TRANSVERSAL_POSITION, 0, _float, 4)

	def getAngularPosition(self):
		return self.sendRecv(GET_ANGULAR_POSITION, 0, _float, 4)
