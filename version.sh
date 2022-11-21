#!/bin/bash

#check the arguments
if [ -n "$1" ]; then
	if [[ ! "$1" =~ ^[0-9]+$ ]]; then
		echo "Invalid argument"
		exit 1
	fi
	c_version="$(gcc -std="c$1" -dM -E - </dev/null | grep __STDC_VERSION__ | awk '{print $3}')"
else
	c_version="$(gcc -dM -E - </dev/null | grep __STDC_VERSION__ | awk '{print $3}')"
fi
if [ -n "$2" ]; then
	if [[ ! "$2" =~ ^[0-9]+$ ]]; then
		echo "Invalid argument"
		exit 1
	fi
	cpp_version="$(g++ -std="c++$2" -dM -E -x c++ /dev/null | grep -F __cplusplus | awk '{print $3}')"
else
	cpp_version="$(g++ -dM -E -x c++ /dev/null | grep -F __cplusplus | awk '{print $3}')"
fi

#check the C standard version used

case $c_version in
199409L)
	echo "C version: C90"
	;;
199901L)
	echo "C version: C99"
	;;
201112L)
	echo "C version: C11"
	;;
201710L)
	echo "C version: C17"
	;;
*)
	if [ -z "$c_version" ]; then
		echo "C version not found"
	else
		echo "C version: pre-standard C [$c_version]"
	fi
	;;
esac

#check the C++ standard version used
case $cpp_version in
199711L)
	echo "C++ version: C++98"
	;;
201103L)
	echo "C++ version: C++11"
	;;
201402L)
	echo "C++ version: C++14"
	;;
201703L)
	echo "C++ version: C++17"
	;;
202002L)
	echo "C++ version: C++20"
	;;
*)
	if [[ $cpp_version > 202002L ]]; then
		echo "C++ version: C++23 beta [$cpp_version]"
	elif [[ $cpp_version > 201703L ]]; then
		echo "C++ version: C++20 beta [$cpp_version]"
	elif [[ $cpp_version > 201402L ]]; then
		echo "C++ version: C++17 beta [$cpp_version]"
	elif [[ $cpp_version > 201103L ]]; then
		echo "C++ version: C++14 beta [$cpp_version]"
	elif [[ $cpp_version > 199711L ]]; then
		echo "C++ version: C++11 beta [$cpp_version]"
	else
		if [ -z "$cpp_version" ]; then
			echo "C++ version not found"
		else
			echo "C++ version: pre-standard C++ [$cpp_version]"
		fi
	fi
	;;
esac

read -p "Press any key to continue..."
clear
