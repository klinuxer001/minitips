/**
 *@file debug.h
 *@brief 
 *
 *@date	
 *@author	klinuxer001
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef DEBUG_H_
#define DEBUG_H_

#ifdef	LOGDEBUG
#define	LOGFILE	"rtx.log"
#define	FATAL	"FATAL"
#define	ERROR	"ERROR"
#define	INFO	"INFO"
/**
  *level为：FATAL:致命错误，此级别时系统不能正常工作
  *			ERROR:错误，出现时系统能工作，但不一定正确
  *			INFO:信息，调试时可用此日志级别
  */
FILE *logf; 
int init_syslog(void)
{
	logf = fopen(LOGFILE, "a");				
	if(logf == NULL)							
	{
		fprintf(stdout, "Open logfile failed\n");
		return -1;
	}
	return 1;
}

#define _dump_info(module, level,format, args...)  do			\
		{	fprintf(logf, module level " (%s-%d):" format "\n",\
				__FILE__, __LINE__,##args);						\
			fflush(logf);										\
		}while(0)


#define	CLOSE_LOGFILE()									\
{														\
	fclose(logf);										\
	logf=NULL;											\
}

int	fini_syslog(void)
{
	CLOSE_LOGFILE();
	return 1;
}
#else
#define	init_syslog(void)
#define fini_syslog(void)
#define _dump_info(module, level,format, args...) 
#endif
#endif //END DEBUG_H_

