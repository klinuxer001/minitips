//$--GGA,hhmmss.ss,ddmm.mm,a,dddmm.x,xx,x.M,xxxx,x

#include <stdio.h>
#include <string.h>

int count_delim(char *buf, int len)
{
	int cnt = 0;
	while(len--)
	{
		if(*buf++ == ',')
			cnt++;
	}
	return cnt;
}

int getvalue(char *buf, int pos, char *out)
{
	int cnt = 0;
	char *token = NULL;
	while(token=strsep(&buf, ","))
	{
		cnt+=1;
		if(cnt == pos+1)
		{
			strcpy(out, token);
			return 1;
		}
	}
	return 0;
}

int main(void)
{
	char val[10] = { 0 };
	char buf[]= "GGA,111111.11,2222.22,33333,44444.4,55,6.6,7777,8,,";
	int c = count_delim(buf, strlen(buf));
	getvalue(buf, 9, val);
	printf("all items:%d, item=%s\n", c, val);
	return 0;
}
