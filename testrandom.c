#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	for(int i = 0; i < 100; i++)
	{
		int num = rand()%10;
		if(num == 0) printf("%d", num);
	}
	return 0;
}
