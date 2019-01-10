#include <stdio.h>

#include <mee/itim.h>

__attribute__ ((noinline))
MEE_PLACE_IN_ITIM
int run_in_itim(int x)
{
	return x * x;
}

int main(void)
{
	int x = 2;
	int y = run_in_itim(x);

	if(y != 4) {
		puts("ITIM test failed\n");
		return 1;
	}

	puts("ITIM test passed\n");

	return 0;
}
