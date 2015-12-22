/*************************************************************************
    > File Name: readhtml.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Fri Dec 18 09:33:39 2015
 ************************************************************************/

#include<stdio.h>
#include"readhtml.h"

void print_url(UrlBuf* ub)
{
   UrlBuf* p = ub;
   while(p)
   {
	  printf("url:%s\n", p->url);
	  p = p->next;
   }
}

void push_compart(char* siss, CommonPart** cp, UrlBuf* ub)
{
   if(!siss)
   {
	  return NULL;
   }

   //first find the compart siss
   CommonPart* head = *cp;
   CommonPart* p = head;
   if(*cp == NULL)
   {
	  (*cp) = (CommonPart*)malloc(sizeof(CommonPart));
	  bzero((*cp), sizeof((CommonPart)));
	  (*cp)->next = NULL;

	  (*cp)->siss = (char*)malloc(sizeof(char)*(strlen(siss) + 1));
	  memcpy((*cp)->siss, siss, sizeof(char)*(strlen(siss)));
	  *((*cp)->siss + strlen(siss)) = '\0';

	  push_url(&((*cp)->ubList), ub->file, ub->url, ub->htmls);

   }
   else
   {

	  while(p->next)
	  {
		 if(memcmp(p->siss, siss, strlen(siss)) == 0)
		 {
			break;
		 }
		 p = p->next;
	  }
	  
	  if(p->next == NULL)
	  {//无此siss
		 CommonPart* q = (CommonPart*)malloc(sizeof(CommonPart));
		 bzero(q, sizeof(*q));
		 q->next = NULL;
	
		 p->next = q;
		 
		 q->siss = (char*)malloc(sizeof(char)*(strlen(siss) + 1));
		 memcpy(q->siss, siss, sizeof(char)*(strlen(siss)));
		 *(q->siss + strlen(siss)) = '\0';	 
		 
		 
		 push_url(&(q->ubList), ub->file, ub->url, ub->htmls);
	  }
	  else
	  {
		 
	  }
   }

}

void push_url(UrlBuf** ub, char* filename, char* url, char* htmls)
{
   UrlBuf* head = *ub;
   UrlBuf* p = head;

   if(*ub == NULL)
   {
	  *ub = (UrlBuf*)malloc(sizeof(UrlBuf));
	  (*ub)->next = NULL;

	  (*ub)->filename = (char*)malloc(sizeof(char)*(strlen(filename) + 1));
	  memcpy((*ub)->filename, filename, sizeof(char)*(strlen(filename)));
	  *((*ub)->filename + strlen(filename)) = '\0';

	  (*ub)->url = (char*)malloc(sizeof(char)*(strlen(url) + 1));
	  memcpy((*ub)->url, url, sizeof(char)*(strlen(url)));
	  *((*ub)->url + strlen(url)) = '\0';

	  (*ub)->htmls = (char*)malloc(sizeof(char)*(strlen(htmls) + 1));
	  memcpy((*ub)->htmls, htmls, sizeof(char)*(strlen(htmls)));
	  *((*ub)->htmls + strlen(htmls)) = '\0';
   }
   else
   {
	  while(p->next)
	  {
		 p = p->next;
	  }
	  UrlBuf* q = (UrlBuf*)malloc(sizeof(UrlBuf));
	  q->next = NULL;


	  q->filename = (char*)malloc(sizeof(char)*(strlen(filename) + 1));
	  memcpy(q->filename, filename, sizeof(char)*(strlen(filename)));
	  *(q->filename + strlen(filename)) = '\0';

	  q->url = (char*)malloc(sizeof(char)*(strlen(url) + 1));
	  memcpy(q->url, url, sizeof(char)*(strlen(url)));
	  *(q->url + strlen(url)) = '\0';

	  q->htmls = (char*)malloc(sizeof(char)*(strlen(htmls) + 1));
	  memcpy(q->htmls, htmls, sizeof(char)*(strlen(htmls)));
	  *(q->htmls + strlen(htmls)) = '\0';
	  p->next = q;
	  *ub = head;
   }
}

/*
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
 */

char* get_siss(char* url)
{
   if(!url)
   {
	  return NULL;
   }

   char* beg = strstr(url, "http://");
   if(!beg)
   {
	  return NULL;
   }

   beg += 7;
   char* end = strchr(beg, '/');

   char* siss = NULL;
   int len = end - beg;
   siss = (char*)malloc(sizeof(char)*(len + 1));
   memcpy(siss, beg, len);
   siss[len] = '\0';

   return siss;
}
