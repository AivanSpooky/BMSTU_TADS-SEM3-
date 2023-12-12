#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -c -O0 -g --coverage ./*.c
gcc -o app.exe ./*.o --coverage -lm