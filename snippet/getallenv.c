#include <stdio.h>

/**
  *@notice: if '*argp != 0x0' instead of '*argp++ != 0x0', will occure core dump
  */

int main(int argc, char *argv[], char *argp[])
{
	while( *argp != 0x0 )   //NOT  *argp++ != 0x0
	{
		printf("%s\n", *argp);
		argp++;
	}
	return 0;
}
