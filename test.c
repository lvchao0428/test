/*************************************************************************
    > File Name: test.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Tue Dec 22 15:03:32 2015
 ************************************************************************/

#include<stdio.h>
#include<string.h>

int main(int argc, char* argv[])
{
   char* p = strstr(argv[1], argv[2]);
   if(p)
   {
	  printf("%c\n", *p);
   }

   return 0;
}

