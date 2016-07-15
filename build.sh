#!/bin/sh

err_chk="-D ERROR_CHECK"
dbug_log="-D DEBUG_LOG"

for arg in "$@"
do
	case "$arg" in 
		"-ne")
			err_chk=""
			echo "Error checking disabled for this build."
			;;
		"-nd")
			dbug_log=""
			echo "Debug logs disabled for this build."
			;;
	esac
done

compiler="gcc -g $err_chk $dbug_log  -O3"
includes="-I src/include"
libraries="`pkg-config --libs --cflags libusb-1.0`"
sources="src/*.c test.c"
output="-o bin/test"
eval "$compiler $includes $sources $libraries $output"
