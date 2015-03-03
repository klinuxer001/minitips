#include "mlog.h"


int main(int argc, char *argv[])
{
	mlog.setLogFile("log.txt");	
	mlog.writeLog(MLOG_DEBUG, "debug, %d", __LINE__);
	mlog.writeLog(MLOG_WARN, "warn, %d", __LINE__);
	mlog.writeLog(MLOG_ERROR, "error, %d", __LINE__);
	return 0;
}
