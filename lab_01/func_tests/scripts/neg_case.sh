#!/bin/bash

if [ $# -ne 3 ]; then
	exit 1
fi

ok="0"
fail="1"

bin_file=$1
args_test=$2

mode=$3

tmp_out="tmp_out.txt"
command="./app.exe "

# if [ $# -eq 3 ]; then
# 	command="$command $(cat "$args_test")"
# fi

if [[ $mode != "b" ]]; then
    $command < "$bin_file" > "$tmp_out"
    error="$?"
    if [[ $error -ne 0 ]]; then
        exit "$fail"
    fi
else
    $command < "$bin_file"
    error="$?"
    if [[ $error -ne 0 ]]; then
        exit "$fail"
    fi
fi

exit "$ok"
