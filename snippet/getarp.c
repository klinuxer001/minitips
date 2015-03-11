#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct _arpinfo {
	char ipstr[16];
	char mac[18];
}arpi;

int getarp(const char *cmd, arpi *arp, int len)
{
	int i = 0;
	char buf[128];
	FILE *fp = popen(cmd, "r");
	assert(fp!=NULL);

	while(NULL != fgets(buf, sizeof(buf), fp))
	{
		if(memcmp(buf, "IP", 2) == 0)
			continue;
		sscanf(buf, "%15[0-9.] %*s %*s %17[A-Fa-f0-9:] %*s %*s", arp[i].ipstr, arp[i].mac);
		printf("ip=%s, mac=%s\n", arp[i].ipstr, arp[i].mac);
		if(++i ==len)
			break;
	}
	pclose(fp);
}

int main(int argc, char *argv[])
{
	arpi arp[atoi(argv[1])]; 
	getarp("cat /proc/net/arp", arp, sizeof(arp)/sizeof(arpi));
	return 0;
}
