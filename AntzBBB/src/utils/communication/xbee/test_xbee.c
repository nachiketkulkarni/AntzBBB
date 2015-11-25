#include "xbee.h"

int
main()
{
	double x = 2;
	double y = 4;
	double res;

	res = raiseto(x, y);
	printf("x raise to y = %ld\n", (long)res);

	return 0;
}
