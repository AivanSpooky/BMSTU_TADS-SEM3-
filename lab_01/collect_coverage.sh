#!/bin/bash

./testing.sh

echo ""
echo "Coverage (in %):"
gcov main.c > "tmp.txt"
var=$(cat tmp.txt) 
echo "${var#*:}" | sed 's/%*$/ /g' | sed 's/ .*//'
rm -f "tmp.txt"
