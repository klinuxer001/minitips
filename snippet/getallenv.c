#include <stdio.h>

/**
  *if *args++!= 0x0 instead of *++args != 0x0, program will core dump, because :
  *  printf require *args is a NOT-NULL variable.
  */
void dump_env_0(char const *args[])
{
	while( *++args != 0x0 )	//NOT *args++ != 0x0 
	{
		printf("%s\n", *args);
	}
}

/**
   recommand this method, dump_env_0 method 
   will less 1 line than dump_env_1 method
**/
void dump_env_1(char const *args[])		
{
	while( *args != 0x0 )
	{
		printf("%s\n", *args);
		args++;
	}
}

int main(int argc, char *argv[], char const *argp[])
{
//	dump_env_0(argp);
	dump_env_1(argp);

	return 0;
}
