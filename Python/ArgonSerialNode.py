import serial
import struct

MODE_FIRST_FF		= 0
MODE_MSG_START		= 1
MODE_SIZE			= 2
MODE_SIZE_CRC		= 3
MODE_MESSAGE		= 4
MODE_MSG_CRC		= 5

class ArgonSerialNode:
	def __init__(self, device = '/dev/serial0', baud = 9600, timeout = 0.1):
		self.__device = device
		self.__baud = baud
		self.__serial_id = serial.Serial(device, baud)
		self.__serial_id.timeout = timeout
		self.__mode = 0
		self.__msg_size = 0
		self.__index = 0
		self.__message_in = []

	def crc8(self, msg, length):
		crc = 0
		for i in range(length-1, -1, -1):
			inbyte = ord(msg[length - i - 1])
			for j in range(8, 0, -1):
				mix = ((crc ^ inbyte) & 0x01) % 256
				crc = (crc >> 1) % 256
				if mix:
					crc = (crc ^ 0x8C) % 256
				inbyte = (inbyte >> 1) % 256
		return (crc % 256)

	def sendMsg(self, msg):
		pack = []
		#Sync 0xFF
		pack.extend('\xff')
		#Start STX
		pack.extend('\x02')

		#Size of actual message
		pack.extend(chr(len(msg)))
		#Crc of size of actual message
		size_crc = self.crc8(chr(len(msg)),1)
		pack.extend(chr(size_crc))

		#Actual message
		pack.extend(msg)
		#Crc of actual message
		msg_crc = self.crc8(msg, len(msg))
		pack.extend(chr(msg_crc))

		# Needs out_waiting somewhere?
		if(self.__serial_id.write(pack) == len(pack)):
			if __debug__:
				print "Sent data:", msg
			return True
		if __debug__:
			print "Send data error"
		return False

	def recvMsg(self):
		#print self.__serial_id.in_waiting
		while(1):
			data = self.__serial_id.read(1)

			#Timeout
			if len(data) == 0:
				return -1

			#Start of frame (0xFF)
			if(self.__mode == MODE_FIRST_FF):
				self.__message_in[:] = []
				self.__index = 0
				if(data == '\xFF'):
					self.__mode = MODE_MSG_START

			#Start of frame (0x02)
			elif(self.__mode == MODE_MSG_START):
				if(data == '\x02'):
					self.__mode = MODE_SIZE
				else:
					self.__mode = MODE_FIRST_FF
					return -2

			#Message Size
			elif(self.__mode == MODE_SIZE):
				self.__msg_size = data
				self.__mode = MODE_SIZE_CRC

			#Message Size CRC
			elif(self.__mode == MODE_SIZE_CRC):
				if(self.crc8([self.__msg_size], 1) == ord(data)):
					self.__mode	= MODE_MESSAGE
				else:
					self.__mode = MODE_FIRST_FF
					return -3

			#Message data being received
			elif(self.__mode == MODE_MESSAGE):
				self.__message_in.extend(data)
				self.__index +=1

				if(self.__index == ord(self.__msg_size)):
					self.__mode = MODE_MSG_CRC

			#Message CRC8 calculation
			elif(self.__mode == MODE_MSG_CRC):
				self.__mode = MODE_FIRST_FF
				if(self.crc8(self.__message_in, ord(self.__msg_size)) == ord(data)):
					if __debug__:
						print "Received:", self.__message_in
					return True
				else:
					return -4

	def readMsg(self):
		msg = self.__message_in
		self.__message_in = []
		return msg
