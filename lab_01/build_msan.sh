#!/bin/bash

clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer -g ./*.c -o app.exe
