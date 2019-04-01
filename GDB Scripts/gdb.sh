#!/bin/bash

#bash [ObjectFileName] [var1] [var2] ...

DISPLAY_WARNINGS=0
GDB_PY_SCRIPT_NAME="gdbPyScript.py"

#Get File Name
file=$1

#Subtract file name from arguments
((argsNum = $# - 1))

#Add all argument together with double quote and commas
for i in "${@:2}"
do
	args+="\"$i\""
	((argsNum--))
	if [ $argsNum != 0 ]
	then
		args+=","
	fi
done

if [ $DISPLAY_WARNINGS == 1 ]
then
	eval "gdb -q --batch -ex 'py file = \"$file\"' -ex 'py argsList = []' -ex 'py argsList.extend([$args])' -x $GDB_PY_SCRIPT_NAME"
else
	eval "gdb -q --batch -ex 'py file = \"$file\"' -ex 'py argsList = []' -ex 'py argsList.extend([$args])' -x $GDB_PY_SCRIPT_NAME 2> /dev/null"
fi
