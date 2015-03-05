/**
  *@file	selectsockrtx.c
  *@brief	socket通讯之select模型
  *@notice 	参考点为_sock结构的封装
  *@date	2015-
  *@author	klinuxer001
  */
#include "common.h"

typedef	struct _sock 
{
	int sock;
	struct sockaddr_in addr;
#define	BACKLOG	10
	uint32_t (*getipaddr)(struct sockaddr_in addr);
	int (*listen)(int sock, int backlog);
	int (*bind)(int sock, struct sockaddr_in *addr);
	int (*accept)(int sock, struct sockaddr *addr, int *len);
	int (*send)(int sock, char *buf, int len);
	int (*recv)(int sock, char *buf, int len);
	int (*setopt)(int sock, int cmd, void *flag);
	int (*block)(int sock, int flag);
	int (*close)(int sock);
}sock_namespace;

typedef struct _peer
{
	int sock;
	struct sockaddr_in addr;
}peerinfo;

uint32_t sgetipaddr(struct sockaddr_in addr)
{
	return addr.sin_addr.s_addr;
}

int slisten(int sock, int backlog)
{
	int num = backlog > 128 ? BACKLOG:backlog;
	return listen(sock, num);
}

int saccept(int sock, struct sockaddr *addr, int *len)
{
	*len = sizeof(struct sockaddr);
	int ret = accept(sock, addr, len);
	return ret;
}

int sbind(int sock, struct sockaddr_in *addr)
{
	int ret = bind(sock, (struct sockaddr *)addr, sizeof(struct sockaddr));
	assert(ret == 0);
	return ret;
}

/**
  *@param	sock:输入参数
  *@param	buf:输入参数
  *@param	len:输入参数
  *@return	0 OR -1
  */
int ssend(int sock, char *buf, int len)
{
	return 0;
}

/**
  *@param	sock:输入参数
  *@param	buf:输入参数
  *@param	len:输入参数
  *@return	0 OR -1
  */
int srecv(int sock, char *buf, int len)
{
	return 0;
}

/**
  *@param	sock:输入参数，要操作的sock
  *@param	cmd:操作命令,支持以下命令：
            SO_REUSEADDR:地址重用
			SO_BROADCAST:设置广播开关
  *@param	flag:输入参数
  *@return	0:成功，-1：失败
  */
int ssetopt(int sock, int cmd, void* flag)
{
	int ival = 0;
	switch(cmd)
	{
		case SO_REUSEADDR:
			ival = *(int *)flag;
			setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &ival, sizeof(int));
			break;
		case SO_BROADCAST:
			ival = *(int *)flag;
			setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &ival, sizeof(int));
			break;
		default:
			printf("Dont support this command:%d\n", cmd);
			return -1;
	}
	return 0;	
}

static int create_tcp_sock(void)
{
	return socket(AF_INET, SOCK_STREAM, 0);	
}

static int create_udp_sock(void)
{
	return socket(AF_INET, SOCK_DGRAM, 0);
}

void set_local_sockaddr(struct sockaddr_in *addr, unsigned short port, const char *ipaddr)
{
	addr->sin_family = AF_INET;
	addr->sin_port = htons(port);
	addr->sin_addr.s_addr = inet_addr(ipaddr);	//防止返回为-1=255.255.255.255的情况，推荐使用inet_aton()
}

void set_globe_val(sock_namespace *sname, struct sockaddr_in addr)
{
	sname->sock 		= create_tcp_sock();
	sname->addr 		= addr;
	sname->bind 		= sbind;
	sname->listen 		= slisten;
	sname->accept		= saccept;
	sname->send 		= ssend;
	sname->recv 		= srecv;
	sname->setopt 		= ssetopt;
	sname->getipaddr 	= sgetipaddr;
	sname->close		= close;
}

sock_namespace gsock_tcp ;
static unsigned int gsock_ctl = 1;

/**
  *@param	sig:输入参数
  */
void handler(int sig)
{
	printf("Catch sig:%d\n", sig);
	gsock_ctl = 0;
}

/**
  *安装信号
  *@param	sig:输入参数，需处理的信号
  *@param	fun:输入参数，信号处理函数入口
  *
  */
void init_signal(int sig, void (*fun)(int)) 
{
	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));
	act.sa_handler = fun;
	sigaction(sig, &act, NULL);
}

/**
  *@param	port:输入参数，端口
  *@param	ipaddr:输入参数，ip地址
  */
int init_tcplink(unsigned short port, const char *ipaddr)
{
	struct sockaddr_in in;
	set_local_sockaddr(&in, port, ipaddr);
	set_globe_val(&gsock_tcp, in);
	
	gsock_tcp.bind(gsock_tcp.sock, &(gsock_tcp.addr));	
	gsock_tcp.listen(gsock_tcp.sock, BACKLOG);

	return 0;
}

int do_subtask(peerinfo peer)
{
	return 0;
}

void set_itime_tv(struct timeval *tv, int sec, int usec)
{
	tv->tv_sec = sec;
	tv->tv_usec = usec;
}

int main_loop(void)
{
	fd_set rdset;
	peerinfo peer;
	int ret = -1, nsd = -1, len = sizeof(struct sockaddr);
	
	struct timeval tv ;

	while (gsock_ctl != 0)
	{
		FD_ZERO(&rdset);
		FD_SET(gsock_tcp.sock, &rdset);
		set_itime_tv(&tv, 2, 0);
		if((ret = select(gsock_tcp.sock+1, &rdset, NULL, NULL, &tv)) <=0)
		{
			printf("select return =%d\n", ret);
			continue;
		}
		if(FD_ISSET(gsock_tcp.sock, &rdset))
		{
			if((nsd = gsock_tcp.accept(gsock_tcp.sock, (struct sockaddr *)&(peer.addr), &len)) > 0) 
			{
				printf("Established by %x\n", peer.addr.sin_addr.s_addr);
				peer.sock = nsd;
				do_subtask(peer);
				close(nsd);
			}
		}
	}
	return 0;
}

/**
  *
  */
int main(int argc, char *argv[])
{
	int opt = 1;
	if(argc < 3)
	{
		printf("Usage: %s  port  ipaddr\n", argv[0]);
		return -1;
	}
	init_tcplink(atoi(argv[1]), argv[2]);
	init_signal(SIGINT, handler);
	gsock_tcp.setopt(gsock_tcp.sock, SO_REUSEADDR, &opt);
	fcntl(gsock_tcp.sock, F_SETFL, fcntl(gsock_tcp.sock, F_GETFL) | O_NONBLOCK);
	main_loop();
	gsock_tcp.close(gsock_tcp.sock);

	return 0;
}
