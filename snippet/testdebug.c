#include "debug.h"

#define	MODNAME "TEST:"

int main()
{
	int a=5, b=4;
	if(init_syslog()<0)
	{
		printf("Error!\n");
		return -1;
	}
	_dump_info(MODNAME, INFO, "hello");
	_dump_info(MODNAME, ERROR, "a=%d, b=%d", a,b);
	fini_syslog();
	return 0;
}
