#!/bin/bash

COMMAND="\
g++ --std=c++17  ./src/main.cpp  -o main \
-I/home/miguel/cpp_snake_tutorial/include/ \
$(pkg-config opencv4 --libs --cflags) "

echo "${COMMAND}"
$(${COMMAND})