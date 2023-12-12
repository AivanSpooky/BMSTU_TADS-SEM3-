#!/bin/bash

ok="0"
fail="1"

if [ $# -ne 4 ]; then
	exit "$fail"
fi

bin_file=$1

out_test=$2
args_test=$3

mode=$4

tmp_out="tmp_out.txt"
command="./app.exe "

# if [ $# -eq 4 ]; then
# 	#command="$command $(cat "$args_test")"
# fi

if [[ $mode == "t" ]]; then
    $command < "$bin_file" > "$tmp_out"
    error="$?"
    if [[ $error -ne 0 ]]; then
        exit "$fail"
    fi
    ./func_tests/scripts/comparator.sh "$tmp_out" "$out_test"
    return_code="$?"
elif [[ $mode == "b" ]]; then
    $command < "$bin_file"
    error="$?"
    if [[ $error -ne 0 ]]; then
        exit "$fail"
    fi
    text_out="bin_out.txt"
    ./cnv.exe "b2t" """$bin_file"".tmp" "$text_out"
    ./func_tests/scripts/comparator.sh "$text_out" "$out_test"
    return_code="$?"
else
    exit "$fail"
fi


if [[ return_code -eq 0 ]]; then
    exit "$ok"
else
    exit "$fail"
fi
