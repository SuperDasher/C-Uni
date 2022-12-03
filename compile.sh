#!/bin/bash

ctrl_c_confirm() {
	echo -ne "\033[s"
	echo
	echo -ne "\e[31mAre you sure you want to exit? [Y/n] \e[0m"
	read -r answer
	if [[ "$answer" =~ ^[yY]$ ]]; then
		exit 1
	fi
	tput cuu1
	tput el
	echo -ne "\033[u"
}

trap 'tput cnorm; clear' EXIT
trap ctrl_c_confirm INT

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
		echo -e "\e[31msrc directory does not exist\e[0m"
		echo -e "\e[31mcreate src directory and put your source files in it\e[0m"
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
			echo -e "\e[31m??==> ${arg#src/} does not exist\e[0m"
		fi
	done
	local -a source_files_dirs=()
	for dir in "${dirs[@]}"; do
		mapfile -t source_files_dirs < <(find "$dir" -type f -name "*.c" -o -name "*.cpp")
		__source_files__+=("${source_files_dirs[@]}")
	done
	eval "$2"='("${__source_files__[@]}")'
}

get_parameters_from_option_index() {
	local -- __option_index__=$1
	local -a __parameters__=()
	for ((j = 0; j < ${#parameters[@]}; j++)); do
		__parameters__+=("${parameters["$__option_index__","$j"]}")
		if [ -z "${parameters["$__option_index__","$((j + 1))"]}" ]; then
			break
		fi
	done
	eval "$2"='("${__parameters__[@]}")'
}

main() {
	tput civis
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

	#check the standard options
	local -- silence_warnings=false
	local -- gcc_errors=true
	local -a c_version=()
	local -a cpp_version=()
	for i in "${!options[@]}"; do
		case "${options[i]}" in
		--silence-warnings | -S)
			silence_warnings=true
			;;
		--no-error-messages | -N)
			gcc_errors=false
			;;
		--c-version | -Vc)
			get_parameters_from_option_index "$i" c_version
			;;
		--cpp-version | -Vcpp)
			get_parameters_from_option_index "$i" cpp_version
			;;
		--help | -h | -H | "-?")
			# TODO: print help
			echo "help will be printed here, not implemented yet"
			exit 0
			;;
		esac
	done

	if ! "$silence_warnings"; then
		if [ ! -d headers/ ]; then
			echo -e "\e[31mheaders directory does not exist\e[0m"
			echo -e "\e[31mdo you want to continue?\e[0m"
			tput setaf 1
			read -r -p "(if you don't want to see this message in the future, use the option --silence-warnings) [Y/n] " answer
			tput setaf 7
			if [[ ! "$answer" =~ ^[yY]$ ]]; then
				exit 1
			fi
		fi
		if [ ! -d definitions/ ]; then
			echo -e "\e[31mdefinitions directory does not exist\e[0m"
			echo -e "\e[31mdo you want to continue?\e[0m"
			tput setaf 1
			read -r -p "(if you don't want to see this message in the future, use the option --silence-warnings) [Y/n] " answer
			tput setaf 7
			if [[ ! "$answer" =~ ^[yY]$ ]]; then
				exit 1
			fi
		fi
	fi

	#check for the validity of the c and c++ standard versions
	if [ "${#c_version[@]}" -gt 0 ]; then
		if ! is_c_valid "${c_version[*]}"; then
			echo -e "\e[31mInvalid C version\e[0m"
			exit 1
		fi
	fi
	if [ "${#cpp_version[@]}" -gt 0 ]; then
		if ! is_cpp_valid "${cpp_version[*]}"; then
			echo -e "\e[31mInvalid C++ version\e[0m"
			exit 1
		fi
	fi

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

	#check the options for file exclusion or inclusion
	local -a option_params=()
	for i in "${!options[@]}"; do
		get_parameters_from_option_index "$i" option_params
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
			local -a files_dirs_to_exclude=("${option_params[@]}")
			local -a files_to_ignore=()
			get_source_files_from_arguments files_dirs_to_exclude[@] files_to_ignore
			array_diff files[@] files_to_ignore[@] files
			array_remove_append_prepend_pattern files[@] "src/" ".c" c_files_without_extension
			array_remove_append_prepend_pattern files[@] "src/" ".cpp" cpp_files_without_extension
			;;
		--include | -i)
			local -a files_dirs_to_include=("${option_params[@]}")
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
	if [ -d definitions/ ]; then
		mapfile -t definition_c_files < <(find definitions/ -type f -name "*.c")
	fi
	local -a definition_cpp_files=()
	if [ -d definitions/ ]; then
		mapfile -t definition_cpp_files < <(find definitions/ -type f -name "*.cpp")
	fi

	#declares variables to keep track of the compiled files in real time
	local -- current_file=0

	#the array error_files contains all the files that failed to compile
	local -a error_files=()

	#compile every .c file in src as .o extension and every .cpp file as .opp extension and put them in out
	for file in "${files[@]}"; do
		#if the dir present in src doesn't exist in out, create it
		src_dir=$(dirname -- "$file")
		if [ ! -d "out/${src_dir:4}" ]; then
			mkdir -p "out/${src_dir:4}"
		fi

		#compile and place the output file in the out directory corresponding to the one in src
		local -- fail_message
		local -- success
		if [[ "$file" == *.c ]]; then
			fail_message=$(gcc -Iheaders/ ${c_version:+-std=c${c_version[*]}} -x c -Wall -Werror --pedantic -fdiagnostics-color=always -g -O0 "$file" "${definition_c_files[@]}" -o "out/${file:4:-2}.o" 2>&1)
			success=$?
		elif [[ "$file" == *.cpp ]]; then
			fail_message=$(g++ -Iheaders/ ${cpp_version:+-std=c++${cpp_version[*]}} -x c++ -Wall -Werror --pedantic -fdiagnostics-color=always -g -O0 "$file" "${definition_cpp_files[@]}" -o "out/${file:4:-4}.opp" 2>&1)
			success=$?
		fi
		((current_file++))

		#if the current file is not present in out, print an error message and add it to the error_files array
		if [ $success -eq 0 ]; then
			echo "==> Compiled ${file:4} ($current_file/${#files[@]})"
		else
			if $gcc_errors; then
				echo -e "\e[31m${fail_message:-"Interrupt"}\e[0m"
			fi
			echo -e "\e[31m!!==> File ${file:4} failed to compile ($current_file/${#files[@]})\e[0m"
			error_files+=("$file")
		fi
		find out/ -type d -empty -delete
	done

	#if error_files is not empty, list all the files that failed to compile
	if [ ${#error_files[@]} -gt 0 ]; then
		echo
		# print the error message in red
		echo -e "\e[31m==> The following files failed to compile:\e[0m"
		echo -e "\e[31m${#error_files[@]} out of ${#files[@]} files failed to compile:\e[0m"
		for i in "${!error_files[@]}"; do
			echo -e "\e[31m$((i + 1))/${#error_files[@]} ||==> ${error_files[i]:4}\e[0m"
		done
	fi

	echo
	echo "================"
	echo "=== All done ==="
	echo "================"
	echo

	read -n 1 -s -r -t 5

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
	files_dirs_to_exclude=("${files_dirs_to_exclude[@]}")
	files_dirs_to_include=("${files_dirs_to_include[@]}")
	files_to_ignore=("${files_to_ignore[@]}")
}

main "$@"
