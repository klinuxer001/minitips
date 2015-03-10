/**
  *@file epoll.c
  *@brief	socket通信之epoll模型示例
  *
  */
#include "common.h"
static int global = 1;	

static int init_tcp_socket(int port, const char *ipaddr)
{
	int sockid = -1,on = 1;
	struct sockaddr_in address;

	sockid = socket(AF_INET, SOCK_STREAM, 0);
	if(sockid < 0)
	{
		return FAILURE;
	}
	setsockopt( sockid, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );   
	memset(&address, 0, sizeof(struct sockaddr_in));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ipaddr);
	address.sin_port = htons(port);
	if(bind(sockid,(struct sockaddr *)&address,sizeof(struct sockaddr))<0)
	{
		return FAILURE;
	}
	if (listen(sockid, 10)<0)
	{
		return FAILURE;
	}
	return sockid;
}
int sockfd, epfd;

int epoll_add_fd(int fd, int flag)
{
	struct epoll_event ev;
	ev.events = flag;
	ev.data.fd = fd;
	epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
	return SUCCESS;	
}

void setnonblocking(int fd)
{
	int opt = fcntl(fd, F_GETFL);
	opt |= O_NONBLOCK;
	fcntl(fd, F_SETFL, opt);
}

void handler(int sig)
{
	printf("Catch a signal:%d\n", sig);
	global = 0;	
}

void dump_buf(char *buf, int len)
{
	register int i = 0;
	for(; i<len; i++)
	{
		if((i!=0) && (i%10 == 0))
		{
			printf("%2x\n", buf[i]);
		}
		printf("%2x ", buf[i]);
	}
}

/**
  *
  *
  */
void install_signal(int sig, void *func)
{
	struct sigaction act;
	memset(&act, 0, sizeof(struct sigaction));
	act.sa_handler = func;
	sigaction(sig, &act, NULL);
}

int main(int argc, char *argv[])
{
	struct epoll_event events;
	struct sockaddr_in local;
	socklen_t  addrlen = 0;
	int nfds, i, confd;

	if(argc < 3)
	{
		printf("Usage:%s port ipaddr\n", argv[0]);
		return -1;
	}

	install_signal(SIGINT, handler);
	install_signal(SIGHUP, handler);
	epfd = epoll_create(1);
	sockfd = init_tcp_socket(atoi(argv[1]), argv[2]);

	epoll_add_fd(sockfd, EPOLLIN);
	while( global ){
		nfds = epoll_wait(epfd, &events, 100, -1);
		for( i=0; i<nfds; i++)
		{
			if(events.events & EPOLLERR)
				continue;
			if(events.data.fd == sockfd)
			{
				memset(&local, 0, sizeof(struct sockaddr_in));
				confd = accept(sockfd, (struct sockaddr *)&local, &addrlen);
				setnonblocking(confd);
				epoll_add_fd(confd, EPOLLIN | EPOLLET);
				printf("Accept from %s\n",inet_ntoa(local.sin_addr));
			}
			if(events.data.fd == confd)
			{
				char buf[512] = { 0 };
				recv(confd, buf, sizeof(buf), 0);
				dump_buf(buf, strlen(buf));
			}
		}
	}
	return 0;
}

