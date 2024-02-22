#!/usr/bin/bash

make clean
rm -r cmake_install.cmake
rm -r CMakeCache.txt
rm -r Makefile
rm -r CMakeFiles
mv ./tests/Makefile ./