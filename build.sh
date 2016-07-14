#!/bin/sh
compiler="gcc -g -D ERROR_LOG -D WARN_LOG"
includes="-I src/include"
libraries="`pkg-config --libs --cflags libusb-1.0`"
sources="src/*.c test.c"
output="-o bin/test"
eval "$compiler $includes $sources $libraries $output"
