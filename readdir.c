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
	  
	  if((url = get_url(htmls)) != NULL)
	  {
		 lineno++;
	//	 printf("lineno:%d, url:%s\n", lineno,url);
		 push_url(ub, entry->d_name, url, htmls);
		 char* siss  = get_siss(url);
		 printf("siss:%s\n", siss);

		 
	  }
	  free(htmls);
	  free(url);
   }

   closedir(dp);

   return 0;
}

int main(int argc, char* argv[])
{
   UrlBuf* ub;
   read_url("./out", &ub);

   /*
	  while(++counter <= argc)
	  {
	  printf("\nListing %s...\n", argv[counter-1]);
	  listdir(argv[counter - 1]);
	  }
	  */
   print_url(ub);

   return 0;
}
