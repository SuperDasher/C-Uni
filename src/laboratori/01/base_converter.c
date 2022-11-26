#include <stdio.h>
#include <inttypes.h>

void convert(uint16_t, uint8_t);

int main()
{
	uint16_t number;

	printf("inserisci un numero\n");
	scanf("%" SCNu16, &number);

	convert(number, 2);
	convert(number, 8);

	return 0;
}

void convert(uint16_t number, uint8_t base)
{
	if (base > 10)
	{
		printf("non posso convertire in base %d\n", base);
		return;
	}
	uint16_t n = number;
	uint64_t result = 0;
	uint64_t power = 1;
	while (n > 0)
	{
		result += power * (n % base);
		n /= base;
		power *= 10;
	}
	printf("%" PRIu16 " in base %" PRIu8 " e' %" PRIu64 "\n", number, base, result);
}
