#!/bin/bash

# Compiles binary

COMPILER=g++
SRC_FILES="src/*.cpp"
BIN_PATH="shado"
INC_PATH="include/"
LIB=""
FLAGS="-I$INC_PATH -Ideps/ -std=c++11 -o$BIN_PATH"

echo "Compiling shado to $BIN_PATH..."
COMPILE_LINE="$COMPILER $FLAGS $SRC_FILES"
echo -e "\t$COMPILE_LINE"
$($COMPILE_LINE)

if $($COMPILE_LINE); then
    echo "Success"
else
    echo "Failed"
fi
