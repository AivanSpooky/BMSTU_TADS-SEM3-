#!/bin/bash

scripts="./*.sh"

for file in $scripts ; do
	shellcheck "$file"
done

scripts="./func_tests/scripts/*.sh"

for file in $scripts ; do
	shellcheck "$file"
done