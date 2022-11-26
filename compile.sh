#!/bin/bash

#if the directory src does not exist, exit the script
if [ ! -d src ]; then
	echo "src directory does not exist"
	exit 1
fi

#declare an array that contains c and cpp files in definitions
definition_c_files=()
mapfile -t definition_c_files < <(find definitions/ -name "*.c")
definition_cpp_files=()
mapfile -t definition_cpp_files < <(find definitions/ -name "*.cpp")

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
mapfile -t src_files < <(find src/ -name "*.c" -o -name "*.cpp")

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

#delete the old executable
for i in "${files[@]}"; do
	if [ -f "out/${i:4:-2}.o" ]; then
		rm "out/${i:4:-2}.o"
	fi
done
find out/ -type d -empty -delete

#declares variables to keep track of the compiled files in real time
current_file=0
file_tally=0
for file in "${files[@]}"; do
	((file_tally++))
done

#compile every .c file in src as .o extension and every .cpp file as .opp extension and put them in out
for file in "${files[@]}"; do
	#if the file doesn't exist in src then print an error message and keep going
	if ! echo "${src_files[@]}" | grep -q -o "$file"; then
		((current_file++))
		echo -e "==> File $(basename -- "$file") does not exist ($current_file/$file_tally)"
		continue
	fi

	#if the dir present in src doesn't exist in out, create it
	src_dir=$(dirname -- "$file")
	if [ ! -d "out/${src_dir:4}" ]; then
		mkdir -p "out/${src_dir:4}"
	fi

	#compile and place the output file in the out directory corresponding to the one in src
	if [[ "$file" == *.c ]]; then
		gcc -Iheaders/ ${c_version:+-std=c$c_version} -Wall -Werror --pedantic -fdiagnostics-color=always -g -O0 "$file" "${definition_c_files[@]}" -o "out/${file:4:-2}.o"
	elif [[ "$file" == *.cpp ]]; then
		g++ -Iheaders/ ${cpp_version:+-std=c++$cpp_version} -Wall -Werror --pedantic -fdiagnostics-color=always -g -O0 "$file" "${definition_cpp_files[@]}" -o "out/${file:4:-4}.opp"
	fi
	((current_file++))

	#if the current file is not present in out, print an error message
	#the array error_files contains all the files that failed to compile
	if [ ! -f "out/${file:4:-2}.o" ] && [ ! -f "out/${file:4:-4}.opp" ]; then
		echo -e "!!==> File $(basename -- "$file") failed to compile ($current_file/$file_tally)"
		error_files+=("$file")
	else
		echo "==> Compiled $(basename -- "$file") ($current_file/$file_tally)"
	fi
done

echo ""
echo "=========================="
echo "=== Operation complete ==="
echo "=========================="
echo ""

#if error_files is not empty, list all the files that failed to compile
if [ ${#error_files[@]} -gt 0 ]; then
	echo "The following files failed to compile:"
	for file in "${error_files[@]}"; do
		echo -e "${file:4}"
	done
fi
echo ""

read -n 1 -s -r -p "Press any key to continue..."
clear
