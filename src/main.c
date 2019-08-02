#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main()
{
	srand(time(NULL));
	int die = 6;
	int roll = rand() % die + 1;
	int result = 1 * (roll) + 6;

	printf("1D%d+6=%d\n", die, result);

	return 0;
}
