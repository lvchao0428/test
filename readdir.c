/*************************************************************************
    > File Name: readdir.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Mon Dec 21 11:44:08 2015
 ************************************************************************/

#include"readdir.h"
#include"readhtml.h"

/*读取文件
 * in: filename
 * out: dest
 * warning: dest need to be freed outside the Func
 * */
int file_read_full(char** dest, const char* filename)
{
   FILE* fp;
   struct stat file_stats;
   int nItems, nBytesRead;

   *dest = NULL;
   if((fp = fopen(filename, "r")) == NULL)
   {
	  fprintf(stderr, "failed to open %s - %s\n", filename, strerror(errno));
	  return(-1);
   }
   fstat(fileno(fp), &file_stats);

   if((*dest = (char*)malloc(file_stats.st_size + 1)) == NULL)
   {
	  fclose(fp);
	  fprintf(stderr, "failed to allocate memory for reading file %s\n", filename);

	  return -2;
   }	

   nBytesRead = 0;
   while((nItems = fread(*dest + nBytesRead, 1, BUFSIZ, fp)) > 0)
   {
	  nBytesRead += nItems;
   }
   fclose(fp);
   *(*dest + nBytesRead) = '\0';

   return nBytesRead;
}

 /* 读取网页url
  *
  *
  * */
char* get_url(char* htmls)
{
   if(!htmls)
   {//htmls为空，则不可能找到url
	  return NULL;
   }
   char* beg = strstr(htmls, "UINFO: ");
   if(!beg)
   {//没有uinfo标记则文件非法
	  printf("no unifo\n");
	  return NULL;
   }

   char* end = strchr(htmls, '\t');
   int len = end - (beg + 7); 
   char* url = NULL;
   url = (char*)malloc(sizeof(char)*(len + 1));
   memcpy(url, beg + 7, sizeof(char)*(len));
   url[len] = '\0';
   
   return url;
}

/* 列出列表文件, 读取文件名，读取url，html源码
 *
 * */
int read_url(const char* path, UrlBuf** ub)
{
   struct dirent * entry;
   DIR* dp;
   dp = opendir(path);
   if(dp == NULL)
   {
	  perror("opendir");
	  return -1;
   }
   *ub = NULL;
   FILE* fp;
   FILE* fpillegal;
   fpillegal= fopen("illegalhtml", "w");
   if(!fpillegal)
   {
	  printf("open illegal file error\n");
	  return -1;
   }
   fp = fopen("filelist", "w");
   if(!fp)
   {
	  printf("open write file %s failed\n", "filelist");
	  return -1;
   }
   int lineno = 0;
   while((entry = readdir(dp)))
   {
	  /*read the htmls*/				  
	  
	  //fprintf(fp, "%s\n", entry->d_name);
	  if(strstr(entry->d_name, ".") || strstr(entry->d_name, ".."))
	  {
		 continue;
	  }
	  char* htmls = NULL;
	  char tempfullfile[50];
	  bzero(tempfullfile, sizeof(tempfullfile));
	  sprintf(tempfullfile, "./out/%s", entry->d_name);
	  file_read_full(&htmls, tempfullfile);
	  char* url = NULL;
	  //如果网页不完整不分析
	  if(!strstr(htmls, "</html>"))
	  {
		 char* tempurl = get_url(htmls);

		 fprintf(fpillegal, "filename:%s, url:%s\n", entry->d_name, tempurl);
		 if(htmls)
		 {
			free(htmls);
			htmls = NULL;
		 }

		 if(url)
		 {
			free(url);
			url = NULL;
		 }

		 free(tempurl);
		 continue;
	  }
	  if((url = get_url(htmls)) != NULL)
	  {
		 lineno++;
		 if(strstr(url, "www.xici.net"))
		 {
			fprintf(fpillegal, "filename:%s, url:%s\n", entry->d_name, url);
			if(htmls)
			{
			   free(htmls);
			   htmls = NULL;
			}

			if(url)
			{
			   free(url);
			   url = NULL;
			}

			continue;
		 }
		 printf("lineno:%d, url:%s\n", lineno,url);
		 int file_size = strlen(htmls);

		 char* siss  = get_siss(url);
		 push_url(ub, entry->d_name, url, htmls, siss, file_size);
		 free(siss);

	  }

	  free(htmls);
	  free(url);
   }

   fclose(fpillegal);
   closedir(dp);

   return 0;
}


/*把所有的urlbuf 填入 commonpart里面*/
int fill_compart(UrlBuf* ub, CommonPart** cp)
{
   UrlBuf* ubp = ub;

   while(ubp)
   {
	  push_compart(cp, ubp);

	  ubp = ubp->next;
   }

}

int fill_max_url(CommonPart* cp)
{
   CommonPart* pcp = cp;

   while(pcp)
   {
	  int urlNum = 0;
	  UrlBuf* ubp = pcp->ubList;
	  int maxsize = 0;
	  while(ubp)
	  {
		 urlNum++;
		 if(maxsize < ubp->file_size)
		 {
			maxsize = ubp->file_size;
			pcp->maxBuf = ubp;
		 }

		 ubp = ubp->next;
	  }

	  pcp->urlNum = urlNum;
	  pcp = pcp->next;
   }
}

int deal_url_com(CommonPart** cp)
{
   UrlBuf* ub = NULL;
   read_url("./out", &ub);

   //   CommonPart* cp = NULL;
   fill_compart(ub, cp);

   free_url(ub);
   fill_max_url(*cp);


   return 1;
}

void test_com()
{

   CommonPart* cp = NULL;
   deal_url_com(&cp);
   CommonPart* p = cp;
   print_CommonPart(cp);

   while(p)
   {
	  printf("maxbuf:size:%d,urlNum:%d, url:%s\n", p->maxBuf->file_size, p->urlNum, p->maxBuf->url);

	  p = p->next;
   }


   FILE* fp;
   fp = fopen("sixLog", "w");
   if(!fp)
   {
	  printf("cannot open sixLog\n");
	  exit(-1);
   }
   //test all
   p = cp;
   int htmltotal = 0, titletarget = 0, timetarget = 0, contenttarget = 0; 
   while(p)
   {
	  CommonPart* q;
	  printf("url:%s\n", p->maxBuf->url);
	  if(p->urlNum == 1)
	  {
		 extract_3(p, &htmltotal, &titletarget, &timetarget, &contenttarget, fp);
	  }
	  else if(p->urlNum > 1)
	  {
		 extract_4(p, &htmltotal, &titletarget, &timetarget, &contenttarget, fp);
	  }
	  q = p;
	  p = p->next;
	  free_compart(q);
   }
   //  fclose(fp);
   printf("htmltotal:%d, titletarget:%d, timetarget:%d, contenttarget:%d\n", 
		 htmltotal, titletarget, timetarget, contenttarget);

   /*
	  FILE* fp = NULL;
	  fp = fopen("urlfilelist", "w");
	  if(!fp)
	  {
	  printf("cannot open urlfilelist file\n");
	  exit(0);
	  }
	  p = cp;
	  while(p)
	  {
	  UrlBuf* pub = p->ubList;
	  while(pub)
	  {
	  fprintf(fp, "filename:%s, url:%s\n", pub->filename, pub->url); 

	  pub = pub->next;
	  }

	  p = p->next;
	  }


	  fclose(fp);
	  */
}

