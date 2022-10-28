#!/bin/bash

#if the directory src does not exist, exit the script
if [ ! -d src ]; then
	echo "src directory does not exist"
	exit 1
fi

#remove every file in out if the directory exists, otherwise create an empty out directory
if [ -d out ]; then
	rm -rf out/*
else
	mkdir out
fi

#set the c/c++ include path to the directory headers/ if it's not already set
if [ -z "$C_INCLUDE_PATH" ]; then
	export C_INCLUDE_PATH="headers/"
else
	export C_INCLUDE_PATH=$C_INCLUDE_PATH:"headers/"
fi
if [ -z "$CPLUS_INCLUDE_PATH" ]; then
	export CPLUS_INCLUDE_PATH="headers/"
else
	export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:"headers/"
fi

#compile every .c file in src as .o extension and every .cpp file as .opp extension and put them in out
for file in src/*; do
	if [[ "${file##*.}" == c ]]; then
		gcc -Wall -Werror --pedantic -fdiagnostics-color=always -g -O0 "$file" -o "out/$(basename -- "$file" .c).o"
	elif [[ "${file##*.}" == cpp ]]; then
		g++ -std=c++2a -Wall -Werror --pedantic -fdiagnostics-color=always -g -O0 "$file" -o "out/$(basename -- "$file" .cpp).opp"
	fi
done
