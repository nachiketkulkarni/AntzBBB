#include "ant1.h"

int
main()
{
	int x = 100;
	int y = 2;

	int res;

	res = add(x, y);
	printf("Addition of x = %d and y = %d is %d\n", x, y, res);
	
	res = subtract(x, y);
	printf("Subtraction of x = %d and y = %d is %d\n", x, y, res);
	
	res = multiplication(x, y);
	printf("Multiiplication of x = %d and y = %d is %d\n", x, y, res);
	
	res = division(x, y);
	printf("Division of x = %d and y = %d is %d\n", x, y, res);
	
	res = (double) raiseto((double)x, (double)y);
	printf("Division of x = %d and y = %d is %d\n", x, y, res);

	return 0;
}
