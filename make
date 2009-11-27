#!/bin/bash

name=lua_udf
deploy=/Files/fbtest-udf-directory

[ "$1" = "without-ibutil" ] || opt="-DUSE_IB_UTIL_MALLOC"

# make library
gcc -O -fpic -g -c -Wall $name.c md5.c $opt
gcc -shared -W1,-soname,$name.so -o lib$name.so $name.o md5.o -llua -lib_util

# make test program
gcc -o test_$name test_$name.c -l$name -llua -ldl -lib_util

# copy lib files to test server
cp "lib$name.so" "$deploy/"
cp "$name.lua" "$deploy/"

