#ifndef READHTML_H_
#define READHTML_H_

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<malloc.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<errno.h>
#include<curl/curl.h>
#include"def.h"

int read_urls_to_UrlBuf(UrlBuf** urls, char* urlfilename);

void read_url_with_siss(UrlBuf** urls, char* urlsissfilename);

char* get_siss(char* url);


#endif
