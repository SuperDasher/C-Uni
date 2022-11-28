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
	# if the c or cpp versions are not valid, exit the script, checking if it gives problems with a test file
	touch test.c
	touch test.cpp
	if [[ ! "$(gcc -std="c$c_version" -dM -E - </dev/null test.c 2>/dev/null | grep __STDC_VERSION__ | awk '{print $3}')" != "" ]]; then
		echo -e "Invalid C version"
		rm test.c
		rm test.cpp
		exit 1
	fi
	if [[ ! "$(g++ -std="c++$cpp_version" -dM -E -x c++ /dev/null test.cpp 2>/dev/null | grep -F __cplusplus | awk '{print $3}')" != "" ]]; then
		echo -e "Invalid C++ version"
		rm test.c
		rm test.cpp
		exit 1
	fi
elif [[ -n "${*: -1}" && "${*: -1}" =~ ^[0-9]+$ ]]; then
	c_version=${*: -1}
	version_params=1
	# if the c version is not valid, exit the script, checking if it gives problems with a test file
	touch test.c
	if [[ ! "$(gcc -std="c$c_version" -dM -E - </dev/null test.c 2>/dev/null | grep __STDC_VERSION__ | awk '{print $3}')" != "" ]]; then
		echo -e "Invalid C version"
		rm test.c
		exit 1
	fi
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
	#declare a dirs array that will be filled with all the args that end with a /
	dirs=()
	for arg in "${@:1:$#-$version_params}"; do
		if [[ $arg =~ /$ ]]; then
			if [ -d "src/$arg" ]; then
				dirs+=("$arg")
			else
				echo -e "??==> Directory $arg does not exist"
			fi
		else
			files+=("$arg")
		fi
	done
	for i in "${!files[@]}"; do
		files[$i]="src/${files[$i]}"
	done
	for dir in "${dirs[@]}"; do
		mapfile -t dir_files < <(find "src/$dir" -name "*.c" -o -name "*.cpp")
		files+=("${dir_files[@]}")
	done

	#remove any duplicates from the files array
	for i in "${!files[@]}"; do
		for j in "${!files[@]}"; do
			if [ "$i" -ne "$j" ]; then
				if [ "${files[$i]}" = "${files[$j]}" ]; then
					unset 'files[$j]'
				fi
			fi
		done
	done

	#declare an array that contains o and opp files in out
	out_files=()
	mapfile -t out_files < <(find out/ -name "*.o" -o -name "*.opp")

	#delete the out files that do not correspond to the files in src
	for out_file in "${out_files[@]}"; do
		out_file=${out_file#out/}
		for src_file in "${src_files[@]}"; do
			src_file=${src_file#src/}
			if [ "${out_file%.*}" = "${src_file%.*}" ]; then
				continue 2
			fi
		done
		rm "out/$out_file"
	done

	#remove any file in out that doesn't have the o or opp extension
	files_in_out=()
	mapfile -t files_in_out < <(find out/ -type f)
	for out_file in "${files_in_out[@]}"; do
		if [[ "$out_file" != *.o ]] && [[ "$out_file" != *.opp ]]; then
			rm -f "$out_file"
		fi
	done
fi

#delete the old executable
for file in "${files[@]}"; do
	if [[ "$file" == *.c ]]; then
		if [ -f "out/${file:4:-2}.o" ]; then
			rm "out/${file:4:-2}.o"
		fi
	elif [[ "$file" == *.cpp ]]; then
		if [ -f "out/${file:4:-4}.opp" ]; then
			rm "out/${file:4:-4}.opp"
		fi
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
	found=false
	for src_file in "${src_files[@]}"; do
		if [ "$src_file" = "$file" ]; then
			found=true
			break
		fi
	done
	if ! "$found"; then
		((current_file++))
		echo -e "??==> File ${file:4} does not exist ($current_file/$file_tally)"
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
		echo -e "!!==> File ${file:4} failed to compile ($current_file/$file_tally)"
		error_files+=("$file")
	else
		echo "==> Compiled ${file:4} ($current_file/$file_tally)"
	fi
done

echo
echo "=========================="
echo "=== Operation complete ==="
echo "=========================="
echo

#if error_files is not empty, list all the files that failed to compile
if [ ${#error_files[@]} -gt 0 ]; then
	echo "The following files failed to compile:"
	for i in "${!error_files[@]}"; do
		echo -e "$i || ${error_files[i]:4}"
	done
	echo
fi

read -n 1 -s -r -p "Press any key to continue..."
clear
