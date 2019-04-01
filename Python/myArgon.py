import Argon

from time import sleep


myBase = Argon.ArgonBase()
#myArm = ArgonArm()

while(1):
	print myBase.getPower(1)
	print myBase.setPower(1, 50)
	
	#print myArm.getPower(1)
	#print myArm.setPower(1, -200)
		

	sleep(0.5)