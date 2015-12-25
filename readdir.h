#ifndef READDIR_H_
#define READDIR_H_

#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
#include<malloc.h>
#include<errno.h>
#include<string.h>
#include"def.h"
#include"extract_4.h"
/*读取文件
 * in: filename
 * out: dest
 * warning: dest need to be freed outside the Func
 * */
int file_read_full(char** dest, const char* filename);

char* get_url(char* htmls);

int deal_url_com(CommonPart** cp);
//int read_url(const char* path, UrlBuf** ub);

void test_com();

#endif
