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

c_version=${1:+-std=c$1}
cpp_version=${2:+-std=c++$2}

#compile every .c file in src as .o extension and every .cpp file as .opp extension and put them in out
for file in src/*; do
	if [[ "${file##*.}" == c ]]; then
		gcc -Iheaders/ $c_version -Wall -Werror --pedantic -fdiagnostics-color=always -g -O0 "$file" -o "out/$(basename -- "$file" .c).o"
	elif [[ "${file##*.}" == cpp ]]; then
		g++ -Iheaders/ $cpp_version -Wall -Werror --pedantic -fdiagnostics-color=always -g -O0 "$file" -o "out/$(basename -- "$file" .cpp).opp"
	fi
done

printf "\nall files compiled.\n"
read -n 1 -s -r -p "Press any key to continue..."
clear
