#ifndef SWAP_H
#define SWAP_H

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

#endif /* SWAP_H */
