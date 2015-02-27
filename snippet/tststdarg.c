#include <stdio.h>
#include <stdarg.h>

/**
 *@notice: va_start(va_list ap, last):last指可变参数前的那个参数
 *
 *add_0不足：传入的参数中最后一个参数作为边界值，不计入运算
 *add_1不足：传入的可变参数前的参数作为可变参数的个数值，仍然需多传一个参数
 */
int add_0(int argc, ...)
{
	va_list ap;
	va_start(ap, argc);
	int i, sum = 0;
	for(i=argc; i!=0; i=va_arg(ap, int))
		sum += i;
	va_end(ap);
	printf("%d\n", sum);
	return sum;	
}

int add_1(char *string, int argc, ...)
{
	va_list ap;
	va_start(ap, argc);
	int i, sum=0;
	for(i=0; i<argc; i++)
	{
		sum += va_arg(ap, int);
	}
	printf("%s:%d\n", string, sum);
	va_end(ap);
	return sum;
}

int main(int argc, char *argv[])
{
	int sum_0 = add_0(1,2,3,4,5,0);
	int sum_1 = add_1("the sum is", 5, 1,2,3,4,5);
	return 0;
}

