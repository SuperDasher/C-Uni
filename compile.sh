#!/bin/bash

is_element_in_array() {
	local -- __element__="$1"
	local -a __array__=("${!2}")
	for element in "${__array__[@]}"; do
		if [[ "$__element__" == "$element" ]]; then
			true
			return
		fi
	done
	false
}

array_unique() {
	local -a __input_array__=("${!1}")
	local -a __unique_array__=()
	for element_unique in "${__input_array__[@]}"; do
		if ! is_element_in_array "$element_unique" __unique_array__[@]; then
			__unique_array__+=("$element_unique")
		fi
	done
	eval "$2"='("${__unique_array__[@]}")'
}

array_remove_prepend_pattern() {
	local -a __array__=("${!1}")
	local -- __pattern__="$2"
	local -a __result__=()
	for element in "${__array__[@]}"; do
		if [[ "$element" == "$__pattern__"* ]]; then
			__result__+=("${element#"$__pattern__"}")
		fi
	done
	eval "$3"='("${__result__[@]}")'
}

array_remove_append_pattern() {
	local -a __array__=("${!1}")
	local -- __pattern__="$2"
	local -a __result__=()
	for element in "${__array__[@]}"; do
		if [[ "$element" == *"$__pattern__" ]]; then
			__result__+=("${element%"$__pattern__"}")
		fi
	done
	eval "$3"='("${__result__[@]}")'
}

array_remove_append_prepend_pattern() {
	local -a __input_array__=("${!1}")
	local -- __pattern1__="$2"
	local -- __pattern2__="$3"
	local -a __output__=()
	array_remove_prepend_pattern __input_array__[@] "$__pattern1__" __output__
	array_remove_append_pattern __output__[@] "$__pattern2__" __output__
	eval "$4"='("${__output__[@]}")'
}

array_prepend_pattern() {
	local -a __array__=("${!1}")
	local -- __pattern__="$2"
	local -a __result__=()
	for element in "${__array__[@]}"; do
		if [ -n "$element" ]; then
			__result__+=("$__pattern__$element")
		fi
	done
	eval "$3"='("${__result__[@]}")'
}

array_append_pattern() {
	local -a __array__=("${!1}")
	local -- __pattern__="$2"
	local -a __result__=()
	for element in "${__array__[@]}"; do
		if [ -n "$element" ]; then
			__result__+=("$element$__pattern__")
		fi
	done
	eval "$3"='("${__result__[@]}")'
}

array_append_prepend_pattern() {
	local -a __input_array__=("${!1}")
	local -- __pattern1__="$2"
	local -- __pattern2__="$3"
	local -a __output__=()
	array_prepend_pattern __input_array__[@] "$__pattern1__" __output__
	array_append_pattern __output__[@] "$__pattern2__" __output__
	eval "$4"='("${__output__[@]}")'
}

array_intersect() {
	local -a __array1__=("${!1}") __array2__=("${!2}") __intersection__=()
	for element_in1 in "${__array1__[@]}"; do
		for element_in2 in "${__array2__[@]}"; do
			if [[ "$element_in1" == "$element_in2" ]]; then
				__intersection__+=("$element_in1")
			fi
		done
	done
	array_unique __intersection__[@] __intersection__
	eval "$3"='("${__intersection__[@]}")'
}

array_diff() {
	local -a __minuend__=("${!1}") __subtrahend__=("${!2}") __difference__=()
	for minuend_element in "${__minuend__[@]}"; do
		for subtrahend_element in "${__subtrahend__[@]}"; do
			if [[ "$minuend_element" == "$subtrahend_element" ]]; then
				continue 2
			fi
		done
		__difference__+=("$minuend_element")
	done
	eval "$3"='("${__difference__[@]}")'
}

array_diff_symmetric() {
	local -a __array1__=("${!1}") __array2__=("${!2}") __difference1__=()
	array_diff __array1__ __array2__ __difference1__
	local -a __difference2__=()
	array_diff __array2__ __array1__ __difference2__
	__difference1__+=("${__difference2__[@]}")
	eval "$3"='("${__difference1__[@]}")'
}

# main procedure
check_source_directory() {
	if [ ! -d src ]; then
		echo -e "src directory does not exist"
		echo -e "create src directory and put your source files in it"
		exit 1
	fi
}

get_options() {
	local -a __options__=()
	local -a __arguments__=("${!1}")
	local -- option_index=-1
	local -- parameter_index=-1
	for arg in "${__arguments__[@]}"; do
		if [[ "$arg" == -* ]]; then
			option_index=$((option_index + 1))
			parameter_index=-1
			__options__+=("$arg")
		elif [ "$option_index" -gt -1 ]; then
			parameter_index=$((parameter_index + 1))
			eval "$3"["$option_index","$parameter_index"]="$arg"
		fi
	done
	eval "$2"='("${__options__[@]}")'
}

is_c_valid() {
	[ -n "$(gcc -std="c$1" -dM -E - </dev/null 2>/dev/null | grep __STDC_VERSION__ | awk '{print $3}')" ]
}

is_cpp_valid() {
	[ -n "$(g++ -std="c++$1" -dM -E -x c++ /dev/null 2>/dev/null | grep -F __cplusplus | awk '{print $3}')" ]
}

get_source_files_from_arguments() {
	local -a dirs=()
	local -a __arguments__=("${!1}")
	local -a __source_files__=()
	array_prepend_pattern __arguments__[@] "src/" __arguments__
	for arg in "${__arguments__[@]}"; do
		if [ -d "$arg" ]; then
			dirs+=("$arg")
		elif [ -f "$arg" ]; then
			__source_files__+=("$arg")
		else
			echo -e "??==> ${arg#src/} does not exist"
		fi
	done
	local -a source_files_dirs=()
	for dir in "${dirs[@]}"; do
		mapfile -t source_files_dirs < <(find "$dir" -type f -name "*.c" -o -name "*.cpp")
		__source_files__+=("${source_files_dirs[@]}")
	done
	eval "$2"='("${__source_files__[@]}")'
}

main() {
	local -a args=("$@")

	#if the directory src does not exist, exit the script
	check_source_directory

	#check for the options
	local -a options=()
	local -A parameters
	get_options args[@] options parameters

	local -a base_args
	array_diff args[@] options[@] base_args
	base_args=("${base_args[@]:0:${#base_args[@]}-${#parameters[@]}}")

	#check the amount of parameters used for the c and cpp standard version
	local -- c_version
	local -- cpp_version
	local -- version_params=0
	if [[ -n "${base_args[*]: -2:1}" && "${base_args[*]: -2:1}" =~ ^[0-9]+$ ]]; then
		c_version=${base_args[*]: -2:1}
		cpp_version=${base_args[*]: -1:1}
		version_params=2
		# if the c or cpp versions are not valid, exit the script
		if ! is_c_valid "$c_version"; then
			echo -e "Invalid C version"
			exit 1
		fi
		if ! is_cpp_valid "$cpp_version"; then
			echo -e "Invalid C++ version"
			exit 1
		fi
	elif [[ -n "${base_args[*]: -1}" && "${base_args[*]: -1}" =~ ^[0-9]+$ ]]; then
		c_version=${base_args[*]: -1:1}
		version_params=1
		# if the c version is not valid, exit the script
		if ! is_c_valid "$c_version"; then
			echo -e "Invalid C version"
			exit 1
		fi
	fi
	base_args=("${base_args[@]:0:$((${#base_args[@]} - version_params))}")

	#declare an array that contains c and cpp files in src
	local -a src_files=()
	mapfile -t src_files < <(find src/ -type f -name "*.c" -o -name "*.cpp")

	#the files array contains all the files that will be compiled
	local -a files=()
	if [ ${#base_args[@]} -eq 0 ]; then
		files=("${src_files[@]}")
	else
		get_source_files_from_arguments base_args[@] files
		array_unique files[@] files
	fi

	#declare an array that contains o and opp files in out
	local -a out_files=()
	if [ -d out/ ]; then
		mapfile -t out_files < <(find out/ -type f -name "*.o" -o -name "*.opp")
	fi
	local -a files_in_out=()
	if [ -d out/ ]; then
		mapfile -t files_in_out < <(find out/ -type f)
	fi

	#delete the files in out without .o or .opp extension
	local -a wrong_files=()
	array_diff files_in_out[@] out_files[@] wrong_files
	for file in "${wrong_files[@]}"; do
		rm -f "$file"
	done

	#delete the out files that do not correspond to the files in src
	local -a c_src_files_without_extension=()
	array_remove_append_prepend_pattern src_files[@] "src/" ".c" c_src_files_without_extension
	local -a c_out_files_without_extension=()
	array_remove_append_prepend_pattern out_files[@] "out/" ".o" c_out_files_without_extension
	local -a cpp_src_files_without_extension=()
	array_remove_append_prepend_pattern src_files[@] "src/" ".cpp" cpp_src_files_without_extension
	local -a cpp_out_files_without_extension=()
	array_remove_append_prepend_pattern out_files[@] "out/" ".opp" cpp_out_files_without_extension
	local -a c_files_to_delete=()
	array_diff c_out_files_without_extension[@] c_src_files_without_extension[@] c_files_to_delete
	array_prepend_pattern c_files_to_delete[@] "out/" c_files_to_delete
	local -a cpp_files_to_delete=()
	array_diff cpp_out_files_without_extension[@] cpp_src_files_without_extension[@] cpp_files_to_delete
	array_prepend_pattern cpp_files_to_delete[@] "out/" cpp_files_to_delete
	local -a files_to_delete=("${c_files_to_delete[@]}" "${cpp_files_to_delete[@]}")
	for file in "${files_to_delete[@]}"; do
		rm -f "$file"
	done

	#declare arrays for the basenames of the files to compile
	local -a c_files_without_extension=()
	array_remove_append_prepend_pattern files[@] "src/" ".c" c_files_without_extension
	local -a cpp_files_without_extension=()
	array_remove_append_prepend_pattern files[@] "src/" ".cpp" cpp_files_without_extension

	#check the parameters
	for i in "${!options[@]}"; do
		case "${options[i]}" in
		--only-new | -n)
			local -a c_files_to_ignore=()
			array_intersect c_files_without_extension[@] c_out_files_without_extension[@] c_files_to_ignore
			array_append_prepend_pattern c_files_to_ignore[@] "src/" ".c" c_files_to_ignore
			local -a cpp_files_to_ignore=()
			array_intersect cpp_files_without_extension[@] cpp_out_files_without_extension[@] cpp_files_to_ignore
			array_append_prepend_pattern cpp_files_to_ignore[@] "src/" ".cpp" cpp_files_to_ignore
			local -a files_to_ignore=("${c_files_to_ignore[@]}" "${cpp_files_to_ignore[@]}")
			array_diff files[@] files_to_ignore[@] files
			array_remove_append_prepend_pattern files[@] "src/" ".c" c_files_without_extension
			array_remove_append_prepend_pattern files[@] "src/" ".cpp" cpp_files_without_extension
			;;
		--only-old | -o)
			local -a c_files_to_ignore=()
			array_diff c_files_without_extension[@] c_out_files_without_extension[@] c_files_to_ignore
			array_append_prepend_pattern c_files_to_ignore[@] "src/" ".c" c_files_to_ignore
			local -a cpp_files_to_ignore=()
			array_diff cpp_files_without_extension[@] cpp_out_files_without_extension[@] cpp_files_to_ignore
			array_append_prepend_pattern cpp_files_to_ignore[@] "src/" ".cpp" cpp_files_to_ignore
			local -a files_to_ignore=("${c_files_to_ignore[@]}" "${cpp_files_to_ignore[@]}")
			array_diff files[@] files_to_ignore[@] files
			array_remove_append_prepend_pattern files[@] "src/" ".c" c_files_without_extension
			array_remove_append_prepend_pattern files[@] "src/" ".cpp" cpp_files_without_extension
			;;
		--exclude | -e)
			local -a files_dirs_to_exclude=()
			for ((j = 0; j < ${#parameters[@]}; j++)); do
				files_dirs_to_exclude+=("${parameters["$i","$j"]}")
				if [ -z "${parameters["$i","$((j + 1))"]}" ]; then
					break
				fi
			done
			local -a files_to_ignore=()
			get_source_files_from_arguments files_dirs_to_exclude[@] files_to_ignore
			array_diff files[@] files_to_ignore[@] files
			array_remove_append_prepend_pattern files[@] "src/" ".c" c_files_without_extension
			array_remove_append_prepend_pattern files[@] "src/" ".cpp" cpp_files_without_extension
			;;
		--include | -i)
			local -a files_dirs_to_include=()
			for ((j = 0; j < ${#parameters[@]}; j++)); do
				files_dirs_to_include+=("${parameters["$i","$j"]}")
				if [ -z "${parameters["$i","$((j + 1))"]}" ]; then
					break
				fi
			done
			local -a files_to_add=()
			get_source_files_from_arguments files_dirs_to_include[@] files_to_add
			files=("${files[@]}" "${files_to_add[@]}")
			array_unique files[@] files
			array_remove_append_prepend_pattern files[@] "src/" ".c" c_files_without_extension
			array_remove_append_prepend_pattern files[@] "src/" ".cpp" cpp_files_without_extension
			;;
		esac
	done

	#delete the old executables
	local -a old_o_files_without_extension=()
	array_intersect c_files_without_extension[@] c_out_files_without_extension[@] old_o_files_without_extension
	local -a old_opp_files_without_extension=()
	array_intersect cpp_files_without_extension[@] cpp_out_files_without_extension[@] old_opp_files_without_extension
	for file in "${old_o_files_without_extension[@]}"; do
		rm -f "out/$file.o"
	done
	for file in "${old_opp_files_without_extension[@]}"; do
		rm -f "out/$file.opp"
	done
	if [ -d out/ ]; then
		find out/ -type d -empty -delete
	fi

	#declare an array that contains c and cpp files in definitions
	local -a definition_c_files=()
	mapfile -t definition_c_files < <(find definitions/ -type f -name "*.c")
	local -a definition_cpp_files=()
	mapfile -t definition_cpp_files < <(find definitions/ -type f -name "*.cpp")

	#declares variables to keep track of the compiled files in real time
	local -- current_file=0
	local -- file_tally=0
	for file in "${files[@]}"; do
		((file_tally++))
	done

	#compile every .c file in src as .o extension and every .cpp file as .opp extension and put them in out
	for file in "${files[@]}"; do
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
			echo -e "${i+1} || ${error_files[i]:4}"
		done
		echo
	fi

	read -n 1 -s -r -p "Press any key to continue..."
	clear

	#these next instructions are merely to silence the shellcheck warnings
	args=("${args[@]}")
	out_files=("${out_files[@]}")
	files_in_out=("${files_in_out[@]}")
	c_src_files_without_extension=("${c_src_files_without_extension[@]}")
	c_out_files_without_extension=("${c_out_files_without_extension[@]}")
	cpp_src_files_without_extension=("${cpp_src_files_without_extension[@]}")
	cpp_out_files_without_extension=("${cpp_out_files_without_extension[@]}")
	c_files_without_extension=("${c_files_without_extension[@]}")
	cpp_files_without_extension=("${cpp_files_without_extension[@]}")
	files_to_ignore=("${files_to_ignore[@]}")
}

main "$@"
