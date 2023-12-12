#!/bin/bash

files="./func_tests/data/*.tmp ./func_tests/scripts/*.txt ./func_tests/scripts/*.exe *.exe *.o *.out *.gcno *.gcda *.gcov *.txt"
for file in $files; do
	rm -f "$file" 
done