#!/bin/bash

#if the directory src does not exist, exit the script
if [ ! -d src ]; then
	echo "src directory does not exist"
	exit 1
fi

#check the amount of parameters used for the c and cpp standard version
version_params=0
if [[ -n "${*: -2:1}" && "${*: -2:1}" =~ ^[0-9]+$ ]]; then
	c_version=${*: -2:1}
	cpp_version=${*: -1}
	version_params=2
elif [[ -n "${*: -1}" && "${*: -1}" =~ ^[0-9]+$ ]]; then
	c_version=${*: -1}
	version_params=1
fi

#declare an array that contains c and cpp files in src
src_files=()
for file in src/*; do
	src_files+=("$file")
done

#if no files were passed as parameters, all the files in out get deleted
#the files array contains all the files that will be compiled
if [ $version_params -eq $# ]; then
	if [ -d out ]; then
		rm -rf out/*
	else
		mkdir out
	fi
	files=("${src_files[@]}")
else
	files=("${@:1:$#-$version_params}")
	for i in "${!files[@]}"; do
		files[$i]="src/${files[$i]}"
	done
fi
current_file=0
file_tally=0
for file in "${files[@]}"; do
	((file_tally++))
done
for file in "${files[@]}"; do
	if ! echo "${src_files[@]}" | grep -q -o "$file"; then
		((current_file++))
		echo "File $(basename -- "$file") does not exist ($current_file/$file_tally)"
		continue
	fi

	#compile every .c file in src as .o extension and every .cpp file as .opp extension and put them in out
	if [[ "${file##*.}" == c ]]; then
		gcc -Iheaders/ ${c_version:+-std=c$c_version} -Wall -Werror --pedantic -fdiagnostics-color=always -g -O0 "$file" -o "out/$(basename -- "$file" .c).o"
	elif [[ "${file##*.}" == cpp ]]; then
		g++ -Iheaders/ ${cpp_version:+-std=c++$cpp_version} -Wall -Werror --pedantic -fdiagnostics-color=always -g -O0 "$file" -o "out/$(basename -- "$file" .cpp).opp"
	fi
	((current_file++))
	echo "Compiled $(basename -- "$file") ($current_file/$file_tally)"
done

printf "\nall files compiled.\n"
read -n 1 -s -r -p "Press any key to continue..."
clear
