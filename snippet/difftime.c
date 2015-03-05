/**
  *@file	difftime.c
  *
  */
#include "common.h"
/**
 *@brief	计算两个时间点的间隔，返回值单位为ms
 *@notice	1s = 1000ms = 1000000us, in struct timeval, the unit of tv_sec is sec, tv_sec is us.
 */
unsigned long int get_diff_time(struct timeval start, struct timeval end)
{
	return (end.tv_sec < start.tv_sec)? 0:
          ((end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec)/1000;	
}


int main(int argc, char *argv[])
{
	struct timeval start, end;

	gettimeofday(&start, NULL);
	printf("TIMESTAMP:%ld, %ld\n", start.tv_sec, start.tv_usec);
	usleep(atoi(argv[1]));
	gettimeofday(&end, NULL);
	printf("TIMESTAMP:%ld, %ld\n", end.tv_sec, end.tv_usec);
	
	fprintf(stdout, "Time interval: %lu.\n", get_diff_time(start, end));
	return 0;
}

