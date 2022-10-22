#include <stdio.h>

int main()
{
	switch (__STDC_VERSION__)
	{
	case 201710L:
		printf("C17\n");
		break;
	case 201112L:
		printf("C11\n");
		break;
	case 199901L:
		printf("C99\n");
		break;
	case 199409L:
		printf("C90\n");
		break;
	default:
		printf("C version not recognized\n");
		break;
	}
}