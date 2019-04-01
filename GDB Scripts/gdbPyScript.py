import gdb
import time
import os

#o = gdb.execute('file Capture.axf')
#arg0 - file
#args[] - variables

#Check file exist
if not (os.path.isfile(file)):
	print(file + ' File does not exist!')
	sys.exit(0)
#Check arguments axist
if not (argsList):
	print('Missing argument!')
	sys.exit(0)

#Provide obejct file to gdb
gdb.execute('file '+ file)

#Pass all arguments to 'gdb display'
i=0
while i<len(argsList):
	gdb.execute('display '+ argsList[i])
	i+=1

while True:
	gdb.execute('display')
	time.sleep(1)

gdb.execute('quit')
