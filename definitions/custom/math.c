#include <custom/math.h>

#include <math.h>

int power(int base, int exponent)
{
	int result = 1;
	for (int i = 0; i < exponent; i++)
	{
		result *= base;
	}
	return result;
}

int mcd(int a, int b)
{
	a = abs(a);
	b = abs(b);
	if (b == 0)
		return a;
	return mcd(b, a % b);
}

int mcm(int a, int b)
{
	a = abs(a);
	b = abs(b);
	return a * b / mcd(a, b);
}
