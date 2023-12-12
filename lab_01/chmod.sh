#!/bin/bash

files="./*.sh"
for file_in in $files; do
	chmod +x "$file_in"
done
cd ./func_tests/scripts || exit 1
files="./*.sh"
for file_in in $files; do
	chmod +x "$file_in"
done
cd ../../
