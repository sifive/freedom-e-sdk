#include <stdio.h>

#include <mee/itim.h>

MEE_PLACE_IN_ITIM
int run_in_itim(int x)
{
	return x * x;
}

int main(void)
{
	int x = 2;
	int y = run_in_itim(x);

	printf("Value returned from itim: %d\n", y);

	return y;
}
