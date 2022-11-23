#include <custom/datastruct.h>

#define N 10

bool is_odd(int);

int main()
{
	int input_matrix[N][N];
	randfill_m(input_matrix, N, N, 1, 30);
	int output_matrix[N][N];
	filter_m(is_odd, output_matrix, input_matrix, N, N);
	printf("matrice input:\n");
	print_m(input_matrix, N, N);
	printf("matrice output:\n");
	print_m(output_matrix, N, N);

	return 0;
}

bool is_odd(int n)
{
	return n % 2 == 1;
}
