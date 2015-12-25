#ifndef EXTRACE_H_
#define EXTRACE_H_

#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<gumbo.h>
#include<stdlib.h>
#include<sys/stat.h>
#include"def.h"

int strTimes(char* str, char* word);
	
//找到里面内容部分的标点数量
int find_comma_num_out(char* line);	

/* 找到时间信息，并且输出时间信息
 * in: str, 任意字符串
 * out: timestr
 * ret: 0 不含时间， 1 含有时间 
 * warning: timestr need to be free outside the Func
 * */
int is_time_str(const char* str, char** timestr, int* len);

/* 找到title节点
 * in: root
 * out: title节点
 * */
const char* find_title(GumboNode* root);

/* 找到body节点
 * in: root
 * out: bodyNode
 * */
void find_body(GumboNode* root, GumboNode** bodyNode);

/* 输出节点的属性信息
 * in: root
 * out: NULL
 * */
void output_attr(GumboNode* root);

/*提取纯净的文字信息
 * in: node
 * out: text
 * */
int cleantext(GumboNode* node, char** text);

/*读文件
* in:fp
* out: output, length
* */
static void read_file(FILE* fp, char** output, int* length);

/*找出node节点里面的链接数量
 *in:node
 *out: num
 * */
void find_a_num(GumboNode* node, int* num);

//判断一个node是否是翻页node
/*in:node
 *out: text
 *
 * */
int is_page_node(GumboNode* node, char* text);

/*判断一个node是否全是链接
 * ret: aa == 0, 不全是
 * ret: aa == 1, 全是链接
 * */
void all_a(GumboNode* node, int* aa);

/*重要函数：比较两个节点并且输出第一个不同结构的节点
 *in: aNode, bNode
 *out: cNode
 * */
void compare_and_output(GumboNode* aNode, GumboNode* bNode, GumboNode** cNode);

/*重要函数：返回此节点的子节点的数量
 * in: node
 * out: ele_num, 子节点的数量 
 *
 * */
int return_elem_son_num(GumboNode* node);


/*打印节点的tag值
 *in:root
 *out:NULL
 * */
void print_Node(GumboNode* root);

/*找到时间信息，时间节点
 * in: root
 * out: time, timeNode.
 *  need to be free outside the Func.
 * */
void find_time(GumboNode* root, char** time, GumboNode** timeNode);

/*把title的内容清理干净，把后面的论坛信息去掉
 * in:rawTitle
 * out:cleanTitle
 * */
void cleantitle(const char* rawTitle, char** cleanTitle);

/*假设时间节点和内容节点属于同一父节点，此假设已失效
 *此函数暂时不再使用
 *
 * */
void find_clean_text(GumboNode* root, GumboNode* timeNode, GumboNode** contentNode);

/*从整体不同的部分，找出第一个文字块，
 * in: root, 因为提取的是内容，所以这里输入body节点
 * out: fnode, 输出到此节点，从中提取正文
 *
 * */
//base the whole diff to find the first part textnode
void find_first_node(GumboNode* root, GumboNode** fnode);

//两个以上url
int extract_4(CommonPart* cp, int* htmltotal, int* titletarget, 
	  int* timetarget, int* contenttarget, FILE* fp);
//如果为单个url
int extract_3(CommonPart* cp, int* htmltotal, int* titletarget, 
	  int* timetarget, int* contenttarget, FILE* fp);
#endif
