#!/bin/sh

err_chk="-D ERROR_CHECK"
dbug_log="-D DEBUG_LOG"

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 FILENAME" >&2
  exit 1
fi

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
includes="-I ../src/include"
libraries="`pkg-config --libs --cflags libusb-1.0`"
sources="../src/*.c $1.c"
output="-o bin/$1"
eval "$compiler $includes $sources $libraries $output"
