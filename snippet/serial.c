/**
  *@file	serial.c
  *@brief	
  *
  *@author	klinuxer001
  *@date 
  */
#include "common.h"
#include "debug.h"

#define	COM_FILE	"/dev/ttyS1"
#define BAUDRATE	B19200
int sfd;

#undef	MODNAME
#define	MODNAME	"serial"

/**
 * 设置串口配置选项, 8N1，BAUDRATE
 * @param newtio: 串口参数结构指针
 **/
void set_termios(struct termios *newtio)
{
	memset(newtio,0, sizeof(struct termios)); 

	newtio->c_cflag = BAUDRATE | CS8 | CREAD | CLOCAL;
	newtio->c_iflag = IGNPAR | ICRNL;
	newtio->c_oflag = 0;
	newtio->c_lflag = 0; 

	newtio->c_cflag &= ~PARENB; 
	newtio->c_iflag &= ~INPCK; 

	newtio->c_cflag &= ~CSTOPB;
	cfsetispeed(newtio, BAUDRATE);	//设置终端输入波特率
	cfsetospeed(newtio, BAUDRATE);	//设置终端输出波特率
}

/**
  *从串口读取数据
  *@param	buf:输出参数
  *@param	len:输入参数
  *@return	>=0  成功   -1:失败
  */
int read_com(char *buf, int len)
{
	int ret = read(sfd, (char *)buf, len);
	if (ret == -1)
	{
		fprintf(stderr, "read com error, errno:%s\n", strerror(errno));
	}
	return ret;
}

/**
  *往串口发送数据
  *@param	buf:输入参数
  *@param	len:输入参数
  *@return	>=0  成功   -1:失败
  */
int write_com(char *buf, int len)
{
	int ret = write(sfd, (char *)buf, len);
	if (ret == -1)
	{
		fprintf(stderr, "write com error, errno:%s\n", strerror(errno));
	}
	return ret; 
}

/**
  *初始化串口
  */
int open_comdev(void)
{
	struct termios newtio;
	if ((sfd = open(COM_FILE, O_RDWR | O_NOCTTY)) < 0)
	{
		printf("%s\n", strerror(errno));
		return FAILURE;
	}
	set_termios(&newtio);
	tcflush(sfd, TCIFLUSH);
	tcsetattr(sfd, TCSANOW, &newtio);
	return SUCCESS;
}

/**
  *关闭串口
  */
int close_comdev(void)
{
	if(sfd > 0){
		close(sfd);
		sfd = 0;
	}
	return SUCCESS;
}

/**
  *从串口接收一个数据包
  *@param	buf:输出参数，接收的数据
  *@param	len:输入参数
  *@param	outlen:输出参数,接收到的字串长度
  *@return	SUCCESS
  *			FAILURE
  */
int recv_one_pack_from_serial(char *buf, int len, int *outlen)
{
	char rcvch;
	int bstart = 0, ret = -1;
	register int i = 0;
	while(1)
	{
		ret = read_com(&rcvch, 1);
		if (ret == -1) 
		{
			return FAILURE;
		}
		else if(ret == 0)
		{
			continue;
		}
		if (rcvch== '$')
		{
			bzero (buf, len);
			bstart = 1;
		}
		if (bstart == 1)
		{ 
			if (i > len - 1)		
			{
				bstart = 0;
				bzero (buf, len);
				i = 0;
				continue;
			}
			buf[i] = rcvch;
			if ((rcvch== '\r') || (rcvch== '\n') || (rcvch== '*'))
			{
				*outlen = i;
				return SUCCESS;
			}else{
				i++;	
			}
		}
	}
	return FAILURE;
}


