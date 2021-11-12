#!/bin/bash

g++ main.cpp *.h

if [ $# -eq 1 ]; then
	./a.out > test$1.ppm
else
	./a.out > test.ppm
fi
