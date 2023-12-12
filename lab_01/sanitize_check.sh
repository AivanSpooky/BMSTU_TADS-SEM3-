#!/bin/bash

echo "build_asan:"
./build_asan.sh
./testing.sh
./clean.sh

echo ""
echo "build_msan:"
./build_msan.sh
./testing.sh
./clean.sh

echo ""
echo "build_ubsan:"
./build_ubsan.sh
./testing.sh
./clean.sh
