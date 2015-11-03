#include <stdio.h>



int main(int argc, char *argv[])
{

	if(argc > 1)
	{
		printf("Hello World (I mean %s)\n",argv[1]);
	}
	else
	{
		printf("Hello World (no name)\n");
	}
}
