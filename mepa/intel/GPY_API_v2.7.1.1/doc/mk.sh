#!/bin/sh

CONFIG=Doxyfile
OUTPUT=Doxygen

if [ "$1" = "clean" ]; then
	rm $OUTPUT -rf
	exit $?
fi

doxygen $CONFIG
cmd /k