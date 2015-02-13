#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "debug.h"

#define MODNAME "GENFILE"

int main(int argc, char *argv[])
{
	int i;
	char buf[128] = { 0 };
	init_syslog();
	FILE *fp = fopen(argv[1], "a");
	assert(fp!=NULL);
	for(i=0; i<atoi(argv[2]); i++)
	{
		memset(buf, '\n', sizeof(buf));
		memset(buf, i+'0', sizeof(buf)-1);
		fwrite(buf, 1, sizeof(buf), fp);
		_dump_info(MODNAME, INFO,"%s", buf);
	}	
	fclose(fp);
	fini_syslog();
	return 0;
}
