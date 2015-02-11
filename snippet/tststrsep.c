#include <string.h>
#include <stdio.h>

int tstrsep(char *strs, const char *del)
{
	char *token = NULL;
	while(token=strsep(&strs, del))
	{
		if(token!=NULL)
			printf("%s\n", token);
	}
	return 0;
}

int main(int argc, char *argv[])
{
	tstrsep(argv[1], argv[2]);
	return 0;
}

