#include <stdio.h>
#include "mlog.h"

void func3(void)
{
	mlog.writeStackTrace();
}

void func2(void)
{
	func3();
}

void func1(void)
{
	func2();
}

void func(void)
{
	func1();
}

int main(int argc, char *argv[])
{
	mlog.setLogFile("log.txt");	
	mlog.writeLog(MLOG_DEBUG, "debug, %d", __LINE__);
	mlog.writeLog(MLOG_WARN, "warn, %d", __LINE__);
	mlog.writeLog(MLOG_ERROR, "error, %d", __LINE__);
	func();
	return 0;
}
