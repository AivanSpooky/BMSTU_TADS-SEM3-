#!/bin/bash

test_ok="0"
files_count=0
count_errors=0

cd ../../
files="func_tests/data/pos_??_in.txt"
for file_in in $files; do
	if [ -f "$file_in" ]; then
		number=$(echo "$file_in" | grep -o "[0-9]*")
	else
		echo "No positive tests"
		continue
	fi
	number=$(echo "$file_in" | grep -o "[0-9]*")

	# if [[ $number == "08" ]]; then
	# 	exit
	# fi

	file_out="func_tests/data/pos_""$number""_out.txt"
	file_args="func_tests/data/pos_""$number""_args.txt"

	mode="t"

	if [ -f "$file_out" ] && [ -f "$file_args" ]; then
		if [[ $mode == "t" ]]; then
			./func_tests/scripts/pos_case.sh "$file_in" "$file_out" "$file_args" "$mode"
			error="$?"
		elif [[ $mode == "b" ]]; then
			gcc -o cnv.exe conversion.c
			file_tmp="""$file_in"".tmp" 
			./cnv.exe "t2b" "$file_in" "$file_tmp"
			./func_tests/scripts/pos_case.sh "$file_in" "$file_out" "$file_args" "$mode"
			error="$?"
		else
			echo "pos_""$number""_in"": FAIL (Wrong mode)"
			count_errors=$((count_errors + 1))
			files_count=$((files_count + 1))
			continue
		fi
	else
		echo "pos_""$number""_in"": FAIL (No Output/Args File)"
		count_errors=$((count_errors + 1))
		files_count=$((files_count + 1))
		continue
	fi
	if [ "$error" -eq "$test_ok" ]; then
		echo "pos_""$number""_in"": PASS"
	else
		echo "pos_""$number""_in"": FAIL"
		count_errors=$((count_errors + 1))
	fi
	files_count=$((files_count + 1))
done

echo
files="func_tests/data/neg_??_in.txt"
for file_in in $files; do
	if [ -f "$file_in" ]; then
		number=$(echo "$file_in" | grep -o "[0-9]*")
	else
		echo "No negative tests"
		continue
	fi

	file_args="func_tests/data/neg_""$number""_args.txt"

	mode="t"

	if [ -f "$file_args" ]; then
		if [[ $mode == "t" ]]; then
			./func_tests/scripts/neg_case.sh "$file_in" "$file_args" "$mode"
			error="$?"
		else
			gcc -o cnv.exe conversion.c
			file_tmp="""$file_in"".tmp" 
			./cnv.exe "t2b" "$file_in" "$file_tmp"
			./func_tests/scripts/neg_case.sh "$file_in" "$file_args" "$mode"
			error="$?"
		fi
	else
		echo "neg_""$number""_in"": FAIL (No Output/Args File)"
		count_errors=$((count_errors + 1))
		files_count=$((files_count + 1))
		continue
	fi

	if [ "$error" -ne "$test_ok" ]; then
		echo "neg_""$number""_in"": PASS"
	else
		echo "neg_""$number""_in"": FAIL"
		count_errors=$((count_errors + 1))
	fi
	files_count=$((files_count + 1))
done

percentage=$(echo "scale=9; ($files_count-$count_errors)/$files_count*100" | bc )
echo
echo "Tests passed (in %): "
echo "$percentage" | awk '{printf "%.0f\n",$1}'
exit "$count_errors"
