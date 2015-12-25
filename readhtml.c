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

void free_url(UrlBuf* ub)
{
   UrlBuf* p = ub;
   while(p)
   {
	  UrlBuf* q = p;
	  if(q->filename)
	  {
		 free(q->filename);
		 q->filename = NULL;
	  }

	  if(q->url)
	  {
		 free(q->url);
		 q->url = NULL;
	  }

	  if(q->htmls)
	  {
		 free(q->htmls);
		 q->htmls = NULL;
	  }

	  if(q->siss)
	  {
		 free(q->siss);
		 q->siss = NULL;
	  }

	  p = p->next;
	  if(q)
	  {
		 free(q);
		 q = NULL;
	  }
   }
}

void free_compart(CommonPart* cp)
{
   if(cp->siss)
   {
	  free(cp->siss);
	  cp->siss = NULL;
   }

   if(cp->ubList)
   {
	  free_url(cp->ubList);
   }
}

void push_compart(CommonPart** cp, UrlBuf* ub)
{

   //first find the compart siss
   CommonPart* head = *cp;
   CommonPart* p = head;
   if(*cp == NULL)
   {
	  (*cp) = (CommonPart*)malloc(sizeof(CommonPart));
	  bzero((*cp), sizeof(CommonPart));
	  (*cp)->next = NULL;

	  (*cp)->siss = (char*)malloc(sizeof(char)*(strlen(ub->siss) + 1));
	  strcpy((*cp)->siss, ub->siss);
	  //memcpy((*cp)->siss, ub->siss, sizeof(char)*(strlen(ub->siss)));
	  //*((*cp)->siss + strlen(ub->siss)) = '\0';

	  push_url(&((*cp)->ubList), ub->filename, ub->url, ub->htmls, ub->siss, ub->file_size);

   }
   else
   {

	  while(p->next)
	  {
		 if(memcmp(p->siss, ub->siss, strlen(ub->siss)) == 0)
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
		 
		 q->siss = (char*)malloc(sizeof(char)*(strlen(ub->siss) + 1));
		 strcpy(q->siss, ub->siss);
	//	 memcpy(q->siss, ub->siss, sizeof(char)*(strlen(ub->siss)));
	//	 *(q->siss + strlen(ub->siss)) = '\0';	 
		 

		 
		 push_url(&(q->ubList), ub->filename, ub->url, ub->htmls, ub->siss, ub->file_size);
	  }
	  else
	  {//存在siss
		 push_url(&(p->ubList), ub->filename, ub->url, ub->htmls, ub->siss, ub->file_size);		  
	  }

	  *cp = head;
   }

}

void print_CommonPart(CommonPart* cp)
{
   CommonPart* p = cp;
   while(p)
   {
	  UrlBuf* pub = p->ubList;
	  while(pub)
	  {
		 printf("filename:%s, url:%s\n", pub->filename, pub->url);

		 pub = pub->next;
	  }

	  p = p->next;
   }
}

void push_url(UrlBuf** ub, char* filename, char* url, char* htmls, char* siss, int file_size)
{
   UrlBuf* head = *ub;
   UrlBuf* p = head;

   if(*ub == NULL)
   {
	  *ub = (UrlBuf*)malloc(sizeof(UrlBuf));
	  (*ub)->next = NULL;

	  (*ub)->filename = (char*)malloc(sizeof(char)*(strlen(filename) + 1));
	  strcpy((*ub)->filename, filename);
//	  memcpy((*ub)->filename, filename, sizeof(char)*(strlen(filename)));
//	  *((*ub)->filename + strlen(filename)) = '\0';

	  (*ub)->url = (char*)malloc(sizeof(char)*(strlen(url) + 1));
	  strcpy((*ub)->url, url);
//	  memcpy((*ub)->url, url, sizeof(char)*(strlen(url)));
//	  *((*ub)->url + strlen(url)) = '\0';

	  (*ub)->htmls = (char*)malloc(sizeof(char)*(strlen(htmls) + 1));
	  strcpy((*ub)->htmls, htmls);
//	  memcpy((*ub)->htmls, htmls, sizeof(char)*(strlen(htmls)));
//	  *((*ub)->htmls + strlen(htmls)) = '\0';

	  (*ub)->siss = (char*)malloc(sizeof(char)*(strlen(siss) + 1));
	  strcpy((*ub)->siss, siss);
//	  memcpy((*ub)->siss, siss, sizeof(char)*(strlen(siss)));
//	  *((*ub)->siss + strlen(siss)) = '\0';

	  (*ub)->file_size = file_size;
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
	  strcpy(q->filename, filename); 
//	  memcpy(q->filename, filename, sizeof(char)*(strlen(filename)));
//	  *(q->filename + strlen(filename)) = '\0';

	  q->url = (char*)malloc(sizeof(char)*(strlen(url) + 1));
	  strcpy(q->url, url);
//	  memcpy(q->url, url, sizeof(char)*(strlen(url)));
//	  *(q->url + strlen(url)) = '\0';

	  q->htmls = (char*)malloc(sizeof(char)*(strlen(htmls) + 1));
	  strcpy(q->htmls, htmls);
//	  memcpy(q->htmls, htmls, sizeof(char)*(strlen(htmls)));
//	  *(q->htmls + strlen(htmls)) = '\0';

	  q->siss = (char*)malloc(sizeof(char)*(strlen(siss) + 1));
	  strcpy(q->siss, siss);
//	  memcpy(q->siss, siss, sizeof(char)*(strlen(siss)));
//	  *(q->siss + strlen(siss)) = '\0';

	  q->file_size = file_size;

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

/*need free siss outside the func*/
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
