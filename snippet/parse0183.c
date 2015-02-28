/**
  *用可变参数来实现对nmea-0183协议的实现
  *
  */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/**
  *@param	sentence:输入参数，GPS接收的报文行
  *@param	format:输入参数，具体如下：
			t:语句类型，表示为某个类型的报文
			f:输出值类型为浮点数
			i:输出值类型为整数
			D:输出值类型为日期型	//TODO:
			c:输出值类型为字符		//TODO:
  
  *@return  0:成功  -1:失败
  */
int parse_sentence(const char *sentence, char *format, ...)
{
	int result = -1;
	const char *field = sentence;

	va_list ap;
	va_start(ap, format);

#define	next_field()	do{\
	while(*sentence)\
	{\
		if(*sentence == ',')\
		{\
			sentence++;\
			field = sentence;\
			break;\
		}else{\
			sentence++;\
		}\
	}\
}while (0)

	while( *format )
	{
		char type = *format++;
		switch(type)
		{
			case 't':
			{
				if(field[0] != '$')		//报文头固定为'$'
				{
					result = -1;
					goto parse_sentence_error;
				}
				char *buf = va_arg(ap, char *);	
				strncpy(buf, field+1, 5);
				buf[5] = '\0';
			} break;
			case 'i':
			{
				int value = strtol(field, NULL, 10);
				*va_arg(ap, int *) = value;
			}
			break;
			case 'f':
			{
				double fv = strtod(field, NULL);
				*va_arg(ap, double *) = fv;
			}
			break;
				
			default:
				result = -1;
				goto parse_sentence_error;
				
		}
		next_field();
	}
	result = 0;
parse_sentence_error:
	va_end(ap);
	return result; 
}

int main(int argc, char *argv[])
{
	int val = 0;
	double df = 0.0;
	char buf[10] = { 0 };
	parse_sentence("$GPRMC,123,4.5", "tif", buf, &val, &df);
	printf("%s, %d, %f\n", buf, val, df);
	return 0;
}
