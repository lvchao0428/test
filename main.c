/*************************************************************************
    > File Name: main.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Tue Dec  1 09:34:42 2015
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include"def.h"
#include"extract_4.h"
#include"readdir.h"
#include"readhtml.h"

void test_single(char* file1, char* file2)
{

   char* htmls1 = NULL;
   char* htmls2 = NULL;

   int len = file_read_full(&htmls1, file1);
   int len1 = file_read_full(&htmls2, file2);
   if(len == 0 || len1 == 0)
   {
	  return;
   }


   char* title = NULL;
   char* content = NULL;
   char* time = NULL;
   

   int ret = deal_htmls_4(htmls1, htmls2, &title, &content, &time);
   printf("ret:%d\n", ret);

   printf("title:%s, time:%s, content:%s\n", title, time, content);
   
}

int main(int argc, char* argv[])
{
   test_com();
   //test_single(argv[1], argv[2]); 


   
}
