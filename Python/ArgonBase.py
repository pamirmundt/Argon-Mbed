import struct
import wiringpi

""" Check
"""
CHECK_SPI = 0x21

""" Gets
"""
#Joint / Motor
GET_WHEEL_RADIUS							= 0x22
GET_GEAR_RATIO								= 0x23
GET_ENCODER_TICKS_PER_ROUND					= 0x24
GET_QUAD_ENCODER_TICKS_PER_ROUND			= 0x25
GET_MAXIMUM_RPM								= 0x26
GET_MAXIMUM_ANGULAR_VELOCITY				= 0x27
GET_DIRECTION								= 0x28
GET_PWM										= 0x29
GET_POWER									= 0x2A
GET_ENCODER_COUNT							= 0x2B
GET_JOINT_RPM								= 0x2C
GET_MOTOR_RPM								= 0x2D
GET_JOINT_ANG_VEL							= 0x2E
GET_MOTOR_ANG_VEL							= 0x2F
GET_JOINT_POSITION							= 0x30
GET_MOTOR_POSITION							= 0x31

#Base
GET_LENGTH_BETWEEN_FRONT_AND_REAR_WHEELS	= 0x40
GET_LENGTH_BETWEEN_LEFT_AND_RIGHT_WHEELS	= 0x41
#GET_BASE_VELOCITY							= 0x42
GET_LONGITUDINAL_VELOCITY					= 0x43
GET_TRANSVERSAL_VELOCITY					= 0x44
GET_ANGULAR_VELOCITY						= 0x45
#GET_POSITION								= 0x46
GET_LONGITUDINAL_POSITION					= 0x47
GET_TRANSVERSAL_POSITION					= 0x48
GET_ANGULAR_POSITION						= 0x49
#updatePosition								= 0x4A

""" Sets
"""
#SET_NAME 									= 0x60
#SET_NUMBER 								= 0x61
SET_WHEEL_RADIUS 							= 0x62
SET_GEAR_RATIO 								= 0x63
SET_ENCODER_TICKS_PER_ROUND 				= 0x64
SET_QUAD_ENCODER_TICKS_PER_ROUND 			= 0x65
SET_MAXIMUM_RPM 							= 0x66
SET_MAXIMUM_ANGULAR_VELOCITY 				= 0x67
SET_PWM 									= 0x68
SET_DIRECTION 								= 0x69
SET_POWER 									= 0x6A

class ArgonBase:
	def __init__(self, channel, speed = 1000000, mode = 0):
		self.__channel = channel
		self.__speed = speed
		self.__mode = mode
		wiringpi.wiringPiSetup()
		wiringpi.wiringPiSPISetupMode(channel, speed, mode)

	def SPISendReceive(self, format, *args):
		cmdStruct = struct.pack(format, *args)
		wiringpi.wiringPiSPIDataRW(self.__channel, cmdStruct)
		return struct.unpack(format, cmdStruct)

	def checkSPI(self):
		if(self.SPISendReceive('BB', CHECK_SPI, 0) == (0xAA, 0xAA)):
			return 0
		return -1

	""" Gets
	"""
	def getWheelRadius(self, wheelNumber):
		if( self.SPISendReceive('BB', GET_WHEEL_RADIUS, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', wheelNumber)[0]
		else:
			return -1

	def getGearRatio(self, wheelNumber):
		if( self.SPISendReceive('BB', GET_GEAR_RATIO, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', wheelNumber)[0]
		else:
			return -1

	def getEncoderTicksPerRound(self, wheelNumber):
		if(self.SPISendReceive('BB', GET_ENCODER_TICKS_PER_ROUND, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', wheelNumber)[0]
		else:
			return -1

	def getQuadEncoderTicksPerRound(self, wheelNumber):
		if(self.SPISendReceive('BB', GET_QUAD_ENCODER_TICKS_PER_ROUND, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', wheelNumber)[0]
		else:
			return -1

	def getMaximumRPM(self, wheelNumber):
		if(self.SPISendReceive('BB', GET_MAXIMUM_RPM, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', wheelNumber)[0]
		else:
			return -1

	def getMaximumAngularVelocity(self, wheelNumber):
		if(self.SPISendReceive('BB', GET_MAXIMUM_ANGULAR_VELOCITY, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', wheelNumber)[0]
		else:
			return -1

	def getDirection(self, wheelNumber):
		if(self.SPISendReceive('BB', GET_DIRECTION, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('B', wheelNumber)[0]
		else:
			return -1

	def getPWM(self, wheelNumber):
		if(self.SPISendReceive('BB', GET_PWM, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('h', wheelNumber)[0]
		else:
			return -1

	def getPower(self, wheelNumber):
		if(self.SPISendReceive('BB', GET_POWER, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', wheelNumber)[0]
		else:
			return -1

	def getEncoderCount(self, wheelNumber):
		if(self.SPISendReceive('BB', GET_ENCODER_COUNT, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('h', wheelNumber)[0]
		else:
			return -1

	def getJointRPM(self, wheelNumber):
		if(self.SPISendReceive('BB', GET_JOINT_RPM, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', wheelNumber)[0]
		else:
			return -1

	def getMotorRPM(self, wheelNumber):
		if(self.SPISendReceive('BB', GET_MOTOR_RPM, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', wheelNumber)[0]
		else:
			return -1

	def getJointAngVel(self, wheelNumber):
		if(self.SPISendReceive('BB', GET_JOINT_ANG_VEL, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', wheelNumber)[0]
		else:
			return -1

	def getJointPosition(self, wheelNumber):
		if(self.SPISendReceive('BB', GET_JOINT_POS, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', wheelNumber)[0]
		else:
			return -1

	def getMotorPosition(self, wheelNumber):
		if(self.SPISendReceive('BB', GET_MOTOR_POSITION, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', wheelNumber)[0]
		else:
			return -1

	#Base
	def getLengthBetweenFrontAndRearWheels(self):
		if(self.SPISendReceive('BB', GET_LENGTH_BETWEEN_FRONT_AND_REAR_WHEELS, 0) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', 0)[0]
		else:
			return -1

	def getLengthBetweenFrontWheels(self):
		if(self.SPISendReceive('BB', GET_LENGTH_BETWEEN_LEFT_AND_RIGHT_WHEELS, 0) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', 0)[0]
		else:
			return -1

	def getLongitudinalVelocity(self):
		if(self.SPISendReceive('BB', GET_LONGITUDINAL_VELOCITY, 0) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', 0)[0]
		else:
			return -1

	def getTransversalVelocity(self):
		if(self.SPISendReceive('BB', GET_TRANSVERSAL_VELOCITY, 0) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', 0)[0]
		else:
			return -1

	def getAngularVelocity(self):
		if(self.SPISendReceive('BB', GET_ANGULAR_VELOCITY, 0) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', 0)[0]
		else:
			return -1

	def getLongitudinalPosition(self):
		if(self.SPISendReceive('BB', GET_LONGITUDINAL_POSITION, 0) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', 0)[0]
		else:
			return -1

	def getTransversalPosition(self):
		if(self.SPISendReceive('BB', GET_TRANSVERSAL_POSITION, 0) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', 0)[0]
		else:
			return -1

	def getAngularPosition(self):
		if(self.SPISendReceive('BB', GET_ANGULAR_POSITION, 0) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', 0)[0]
		else:
			return -1

	""" Sets
	"""
	def setWheelRadius(self, radius, wheelNumber):
		if(self.SPISendReceive('BB', SET_WHEEL_RADIUS, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', radius)[0]
		else:
			return -1

	def setGearRatio(self, gearRatio, wheelNumber):
		if(self.SPISendReceive('BB', SET_GEAR_RATIO, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', gearRatio)[0]
		else:
			return -1

	def setEncoderTicksPerRound(self, ticksPerRound, wheelNumber):
		if(self.SPISendReceive('BB', SET_ENCODER_TICKS_PER_ROUND, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', ticksPerRound)[0]
		else:
			return -1

	def setQuadEncoderTicksPerRound(self, quadTicksPerPeriod, wheelNumber):
		if(self.SPISendReceive('BB', SET_QUAD_ENCODER_TICKS_PER_ROUND, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', quadTicksPerPeriod)[0]
		else:
			return -1

	def setMaximumRPM(self, maxRPM, wheelNumber):
		if(self.SPISendReceive('BB', SET_MAXIMUM_RPM, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', maxRPM)[0]
		else:
			return -1

	def setMaximumAngularVelocity(self, maxAngVel, wheelNumber):
		if(self.SPISendReceive('BB', SET_MAXIMUM_ANGULAR_VELOCITY, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', maxAngVel)[0]
		else:
			return -1

	def setPWM(self, pwm, wheelNumber):
		if(self.SPISendReceive('BB', SET_PWM, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('h', pwm)[0]
		else:
			return -1

	#def setDirection(self, direction, wheelNumber):
	#	if(self.SPISendReceive('BB', SET_PWM, wheelNumber) == (0xAA, 0xAA)):
	#		return self.SPISendReceive('B', direction)[0]
	#	else:
	#		return -1

	def setPower(self, power, wheelNumber = 0):
		if(self.SPISendReceive('BB', SET_POWER, wheelNumber) == (0xAA, 0xAA)):
			return self.SPISendReceive('f', power)[0]
		else:
			return -1
