import serial
import wiringpi
from time import sleep

#TX BCM 14
#RX BCM 15
#Enable BCM 18

STX = '\2'
ETX = '\3'

class ArgonRS485:
	def __init__(self, device = '/dev/serial0', baud = 115200, enablePin = 18):
		self.__device = device
		self.__baud = baud
		self.__serial_id = serial.Serial(device, baud)
		self.__enablePin = enablePin
		wiringpi.wiringPiSetupGpio() #BCM Pins
		wiringpi.pinMode(self.__enablePin, 1) #OUTPUT

	def sendMsg(self, msg, length):
		pack = []
		pack.append(ord(STX))
		for i in range(0, length, +1):
			pack.extend(self.calcComplemented(msg[i]))
		pack.append(ord(ETX))
		crc8 = self.crc8(msg, length)
		pack.extend(self.calcComplemented(crc8))

		wiringpi.digitalWrite(self.__enablePin, 1)
		self.__serial_id.write(pack)
		while self.__serial_id.out_waiting:
			pass
		sleep(0.0001)
		wiringpi.digitalWrite(self.__enablePin, 0)

	def calcComplemented(self, byte):
		byte = byte % 256
		c1 = byte >> 4
		c1 = ((c1 << 4) | (c1 ^ 0x0F)) % 256
		c2 = byte & 0x0F
		c2 = ((c2 << 4) | (c2 ^ 0x0F)) % 256
		return c1, c2

	def crc8(self, msg, length):
		crc = 0
		for i in range(length-1, -1, -1):
			inbyte = msg[length - i - 1];
			for j in range(8, 0, -1):
				mix = ((crc ^ inbyte) & 0x01) % 256
				crc = (crc >> 1) % 256
				if mix:
					crc = (crc ^ 0x8C) % 256
				inbyte = (inbyte >> 1) % 256
		return (crc % 256)
# Main
argon = ArgonRS485('/dev/serial0', 1000000)

while 1:
	msg = bytearray(['h','e','l','l','o'])
	argon.sendMsg(msg, len(msg))
	sleep(0.01)
