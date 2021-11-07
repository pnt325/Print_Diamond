#include <stdint.h>
#include <conio.h>
#include <stdio.h>

#include "diamond.h"

int main(void)
{
	// test diamond 
	printf("Test diamond\r\n");

	diamond_t* diamond = diamond_create(11, '*');
	if (diamond)
	{
		diamond->print(diamond->context);

		diamond_delete(diamond);
	}
	return 0;
}

