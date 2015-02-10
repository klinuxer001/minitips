#include <string.h>
#include <stdio.h>

int tstrtok(char *strs, const char *del)
{
	char *token = NULL;
	for(token=strtok(strs, del);
			 token!=NULL; 
			 token=strtok(NULL, del)) 
	{
		printf("%s\n", token);
	}
	return 0;
}

int main(int argc, char *argv[])
{
	tstrtok(argv[1], argv[2]);
	return 0;
}

