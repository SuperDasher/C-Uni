#include <iostream>

int main()
{
	if (__cplusplus > 202002L)
	{
		std::cout << "C++23 beta [" << __cplusplus << "L]\n";
		return 0;
	}
	switch (__cplusplus)
	{
	case 202002L:
		std::cout << "C++20" << std::endl;
		break;
	case 201703L:
		std::cout << "C++17" << std::endl;
		break;
	case 201402L:
		std::cout << "C++14" << std::endl;
		break;
	case 201103L:
		std::cout << "C++11" << std::endl;
		break;
	case 199711L:
		std::cout << "C++98" << std::endl;
		break;
	default:
		std::cout << "C++ version not recognized" << std::endl;
		break;
	}
}
