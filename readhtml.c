/*************************************************************************
    > File Name: readhtml.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Fri Dec 18 09:33:39 2015
 ************************************************************************/

#include<stdio.h>
#include"readhtml.h"

void push_url(UrlBuf** ub, UrlBuf* src)
{
   UrlBuf* head = *ub;

   if
}

int read_urls_to_UrlBuf(UrlBuf** ub, char* urlfilename)
{
   FILE* fp;
   char* line = NULL;
   size_t len = 0;
   ssize_t read;
   UrlBuf* p, * temp;
   //p = temp = *ub;
   fp = fopen(urlfilename, "r");
   if(!fp)
   {
	  printf("cannot open the file %s\n", urlfilename);
	  return -1;
   }
   int lineno = 1;
   while((read = getline(&line, &len, fp)) != -1)
   {
	  char tempno[20];
	  bzero(tempno, sizeof(tempno));
	  //读取lineno
	  int j = 0;
	  while(line[j] != '~')
	  {
		 tempno[j] = line[j];
		 j++;
	  }
	  tempno[j] = '\0';
	  j++;		//skip '~'
	  int intNo = atoi(tempno);
	  if(*ub == NULL)
	  {
		 *ub = (UrlBuf*)malloc(sizeof(UrlBuf));
		 memset(*ub, 0, sizeof(UrlBuf));
		 
		 (*ub)->lineno = intNo;
		 (*ub)->str = (char*)malloc(sizeof(char)*(strlen(line) + 1));
		 //strcpy((*ub)->str, line);
		 memcpy((*ub)->str, line + j, sizeof(char)*(strlen(line) + 1));
		 p = temp = *ub;
	  }
	  else
	  {
		 UrlBuf* q = (UrlBuf*)malloc(sizeof(UrlBuf));
		 memset(q, 0, sizeof(*q));
		 q->str = (char*)malloc(sizeof(char)*(strlen(line) + 1));
		 q->lineno = intNo;
		 memcpy(q->str, line+j, sizeof(char)*(strlen(line) + 1));
		 p->next = q;
		 p = p->next;
	  }
	  
	  lineno++;
   }
   *ub = temp; 
   free(line);
   fclose(fp); 

   return 1;

}

void read_url_with_siss(UrlBuf** urls, char* urlsissfilename)
{
   FILE* fp;
   char* line = NULL;
   size_t len = 0;
   ssize_t read;

   fopen(fp, urlsissfilename);
   if(!fp)
   {
	  printf("open siss file failed.\n");
	  exit(1);
   }

   while((read = getline(&line, &len, fp)) != -1)
   {
	  
   }
}
