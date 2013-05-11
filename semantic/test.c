/**
 * @file   test.c
 * @author pein <pein0119@gmail.com>
 * @date   Sun May  5 14:54:43 2013
 * 
 * @brief  测试程序
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
int* f(int x = 3)
{
	x = 5;
	return &x;
}
int main(int argc, char *argv[])
{
	int w;
	int* y = f(w);
	printf("%d\n",*y);
    return 0;
}
