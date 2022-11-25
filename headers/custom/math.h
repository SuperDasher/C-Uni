#ifndef CUSTOM_MATH_H
#define CUSTOM_MATH_H

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
	if (b == 0)
		return a;
	return mcd(b, a % b);
}

#endif /* CUSTOM_MATH_H */
