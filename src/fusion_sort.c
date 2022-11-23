#include <custom/datastruct.h>
#include <custom/intsort.h>

#define N1 5
#define N2 7

void merge(int *, int *, int *, int, int);

int main()
{
	int array1[N1];
	int array2[N2];
	scan_a(array1, N1, "inserisci i valori del primo array (%d elementi)");
	scan_a(array2, N2, "inserisci i valori del secondo array (%d elementi)");
	bubble_sort(array1, N1);
	bubble_sort(array2, N2);

	int array3[N1 + N2];
	merge(array3, array1, array2, N1, N2);
	printf("array1:\n");
	print_a(array1, N1);
	printf("array2:\n");
	print_a(array2, N2);

	printf("array unito e ordinato:\n");
	print_a(array3, N1 + N2);
}

void merge(int *merged_array, int *array1, int *array2, int len1, int len2)
{
	int index1 = 0, index2 = 0;
	for (int i = 0; i < len1 + len2; i++)
	{
		if (array1[index1] < array2[index2])
		{
			merged_array[i] = array1[index1++];
			if (index1 == len1)
			{
				for (int j = index2; j < len2; j++)
					merged_array[len1 + j] = array2[index2++];
				break;
			}
		}
		else
		{
			merged_array[i] = array2[index2++];
			if (index2 == len2)
			{
				for (int j = index1; j < len1; j++)
					merged_array[len2 + j] = array1[index1++];
				break;
			}
		}
	}
}
