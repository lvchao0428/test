/*************************************************************************
    > File Name: extract_4.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Tue Dec 15 11:08:48 2015
 ************************************************************************/

#include"extract_4.h"
#include"stdlib.h"
/*找到str里面的word的数量
 *in: str, word
 *ret: word出现的个数
 if ret == 0: word 没有出现过，或者str 或 word为空
 * */
int strTimes(char* str, char* word)
{
   if(!str || !word)
   {
	  return 0;
   }
   int times = 0;
   char* p = str;
   while(p && *p)
   {
	  p = strstr(p, word);
	  if(p != NULL)
	  {
		 p += strlen(word);
		 times++;
	  }
   }

   return times;
}

/*找到字符串里面标点符号的数量
 * in:line
 * ret: 标点符号数量
 * */
int find_comma_num_out(char* line)		//找到里面内容部分的标点数量
{//找到字符串里面目标符号的数量
   
   char comma[7][5] = {
	  {","},
	  {"、"},
	  {"，"},
	  {"。"},
	  {"\""},
	  {"“"},
	  {"”"},
   };
   int comma_num = 0;

   int i = 0;
   int j=0;
   while(j < 7)
   {
	  comma_num += strTimes(line, comma[j]);
	  j++;
   }

      
   return comma_num;
}

/* 找到时间信息，并且输出时间信息
 * in: str, 任意字符串
 * out: timestr
 * ret: 0 不含时间， 1 含有时间 
 * warning: timestr need to be free outside the Func
 * */
int is_time_str(const char* str, char** timestr, int* len)
{
   char* p = str;
   int ret = 0;
   char* prebeg = NULL;  //存前一个字符的指针，如果为连续数字则不是时间信息

   while(p && *p && strlen(str) >= 6)
   {
	  if(p > str)
	  {
		 prebeg = p-1;
	  }
	  if(isdigit(*p) 
			&& isdigit(*(p+1)) 
			&& isdigit(*(p+2))
			&& isdigit(*(p+3))
			&& *(p+4) == '-'
			&& isdigit(*(p+5))
			&& isdigit(*(p+6))
			&& *(p+7) == '-'
			&& isdigit(*(p+8))
			&& isdigit(*(p+9)))
	  {//****-**-**格式
		 if(prebeg && !isdigit(*prebeg))
		 {
			*timestr = (char*)malloc(sizeof(char)*(11));
			memcpy(*timestr, p, 10);
			(*timestr)[10] = '\0';
			*len = 11;
			ret = 1;
		 }
		 else
		 {
			*timestr = NULL;
			*len = 0;
			ret = 0;
		 }
		 break;
	  }
	  //****-*-*格式
	  else if(isdigit(*p) 
			&& isdigit(*(p+1)) 
			&& isdigit(*(p+2))
			&& isdigit(*(p+3))
			&& *(p+4) == '-'
			&& isdigit(*(p+5))
			&& *(p+6) == '-'
			&& isdigit(*(p+7)))
	  {
		 if(prebeg && !isdigit(*prebeg))
		 {
			*timestr = (char*)malloc(sizeof(char)*(9));
			memcpy(*timestr, p, 8);
			(*timestr)[8] = '\0';
			ret = 1;
		 }
		 else
		 {
			*timestr = NULL;
			*len = 0;
			ret = 0;
		 }
		 break;
	  }
	  //****-**-*格式
	  else if(isdigit(*p) 
			&& isdigit(*(p+1)) 
			&& isdigit(*(p+2))
			&& isdigit(*(p+3))
			&& *(p+4) == '-'
			&& isdigit(*(p+5))
			&& isdigit(*(p+6))
			&& *(p+7) == '-'
			&& isdigit(*(p+8)))
	  {
		 if(prebeg && !isdigit(*prebeg))
		 {
			*timestr = (char*)malloc(sizeof(char)*(10));
			memcpy(*timestr, p, 9);
			(*timestr)[9] = '\0';
			ret = 1;
		 }
		 else
		 {
			*timestr = NULL;
			*len = 0;
			ret = 0;
		 }
		 break;
	  }
	  //****-*-**
	  else if(isdigit(*p) 
			&& isdigit(*(p+1)) 
			&& isdigit(*(p+2))
			&& isdigit(*(p+3))
			&& *(p+4) == '-'
			&& isdigit(*(p+5))
			&& *(p+6) == '-'
			&& isdigit(*(p+7))
			&& isdigit(*(p+8)))
	  {
		 if(prebeg && !isdigit(*prebeg))
		 {

			*timestr = (char*)malloc(sizeof(char)*(10));
			memcpy(*timestr, p, 9);
			(*timestr)[9] = '\0';
			ret = 1;
		 }
		 else
		 {
			*timestr = NULL;
			*len = 0;
			ret = 0;
		 }

		 break;
	  }//**-**-**
	  else if(isdigit(*p) 
			&& isdigit(*(p+1)) 
			&& *(p+2) == '-'
			&& isdigit(*(p+3))
			&& isdigit(*(p+4))
			&& *(p+5) == '-'
			&& isdigit(*(p+6))
			&& isdigit(*(p+7)))
	  {
		 if(prebeg && !isdigit(*prebeg))
		 {
			*timestr = (char*)malloc(sizeof(char)*(9));
			memcpy(*timestr, p, 8);
			(*timestr)[8] = '\0';
			ret = 1;
		 }
		 else
		 {
			*timestr = NULL;
			*len = 0;
			ret = 0;
		 }
		 break;
	  }
	  //**-*-*
	  else if(isdigit(*p) 
			&& isdigit(*(p+1)) 
			&& *(p+2) == '-'
			&& isdigit(*(p+3))
			&& *(p+4) == '-'
			&& isdigit(*(p+5)))
	  {
		 if(prebeg && !isdigit(*prebeg))
		 {
			*timestr = (char*)malloc(sizeof(char)*(7));
			memcpy(*timestr, p, 6);
			(*timestr)[6] = '\0';
			ret = 1;
		 }
		 else
		 {
			*timestr = NULL;
			*len = 0;
			ret = 0;
		 }
		 break;
	  }
	  //**-*-**
	  else if(isdigit(*p) 
			&& isdigit(*(p+1)) 
			&& *(p+2) == '-'
			&& isdigit(*(p+3))
			&& *(p+4) == '-'
			&& isdigit(*(p+5))
			&& isdigit(*(p+6)))
	  {
		 if(prebeg && !isdigit(*prebeg))
		 {
			*timestr = (char*)malloc(sizeof(char)*(8));
			memcpy(*timestr, p, 7);
			(*timestr)[7] = '\0';
			ret = 1;
		 }
		 else
		 {
			*timestr = NULL;
			*len = 0;
			ret = 0;
		 }
		 break;
	  }
	  //**-**-*
	  else if(isdigit(*p) 
			&& isdigit(*(p+1)) 
			&& *(p+2) == '-'
			&& isdigit(*(p+3))
			&& isdigit(*(p+4))
			&& *(p+5) == '-'
			&& isdigit(*(p+6)))
	  {
		 if(prebeg && !isdigit(*prebeg))
		 {
			*timestr = (char*)malloc(sizeof(char)*(8));
			memcpy(*timestr, p, 7);
			(*timestr)[7] = '\0';
			ret = 1;
		 }
		 else
		 {
			*timestr = NULL;
			*len = 0;
			ret = 0;
		 }
		 break;
	  }

	  p++;
   }

   return ret;
}

/* 找到title节点
 * in: root
 * out: title节点
 * */
const char* find_title(GumboNode* root) 
{
   GumboVector* root_children = &root->v.element.children;
   GumboNode* head = NULL;
   if(root->type == GUMBO_NODE_ELEMENT || root->v.element.children.length >= 2)
   {

	  int i;
	  for (i = 0; i < root_children->length; ++i) {
		 GumboNode* child = root_children->data[i];
		 if (child->type == GUMBO_NODE_ELEMENT &&
			   child->v.element.tag == GUMBO_TAG_HEAD) {
			head = child;
			break;
		 }
	  }
   }

   if(head != NULL)
   {
	  GumboVector* head_children = &head->v.element.children;
	  int i;
	  for (i = 0; i < head_children->length; ++i) {
		 GumboNode* child = head_children->data[i];
		 if (child->type == GUMBO_NODE_ELEMENT &&
			   child->v.element.tag == GUMBO_TAG_TITLE) {
			if (child->v.element.children.length != 1) {
			   return "<empty title>";
			}
			GumboNode* title_text = child->v.element.children.data[0];
			if(title_text->type == GUMBO_NODE_TEXT || title_text->type == GUMBO_NODE_WHITESPACE)
			   return title_text->v.text.text;
		 }
	  }
   }


   return "<no title found>";
}

/* 找到body节点
 * in: root
 * out: bodyNode
 * */
void find_body(GumboNode* root, GumboNode** bodyNode)
{
   if(!root)
   {
	  return;
   }
   else if(*bodyNode == NULL && root->type == GUMBO_NODE_ELEMENT
		 && root->v.element.tag != GUMBO_TAG_SCRIPT)
   {
	  if(strcasecmp(gumbo_normalized_tagname(root->v.element.tag), "body") == 0)
	  {
		 *bodyNode = root;
		 return;
	  }
	  else
	  {
		 GumboVector* children = &root->v.element.children;
		 int i;
		 for(i = 0; i < children->length; ++i)
		 {
			find_body(children->data[i], bodyNode);
		 }
	  }
   }
}

/* 输出节点的属性信息
 * in: root
 * out: NULL
 * */
void output_attr(GumboNode* root)
{
   GumboVector* attrs = &root->v.element.attributes;
   int i;
   GumboAttribute* attr = NULL;
   for(i = 0; i < attrs->length; ++i)
   {
	  attr = attrs->data[i];
	  printf("name:%s, value:%s\t", attr->name, attr->value);
   }
   printf("\n");
}

void html_get_inner_text(GumboNode* node, char** text, int maxlen)
{
   if(!node)
   {
	  return;
   }
   if(node->type == GUMBO_NODE_TEXT)
   {
	  int len = strlen(node->v.text.text);
	  if(len > 0)
	  {
		 if(*text == NULL)
		 {
			*text = (char*)malloc(sizeof(char)*(maxlen));
			bzero(*text, sizeof(char)*(maxlen));
			if(maxlen - strlen(*text) >= len)
			{
			   strncat(*text, node->v.text.text, len);
			}
		 }
	  }
   }
   else if(node->type == GUMBO_NODE_ELEMENT && 
		 node->v.element.tag != GUMBO_TAG_SCRIPT &&
		 node->v.element.tag != GUMBO_TAG_INPUT &&
		 node->v.element.tag != GUMBO_TAG_NOSCRIPT &&
		 node->v.element.tag != GUMBO_TAG_ANNOTATION_XML)
   {
	  GumboVector* children = &node->v.element.children;
	  int i;
	  for(i = 0; i < children->length; ++i)
	  {
		 html_get_inner_text(children->data[i], text, maxlen);
	  }
   }
}

/*提取纯净的文字信息
 * in: node
 * out: text
 * */
int cleantext(GumboNode* node, char** text)
{
   if(!node)
   {
	  return -1;
   }
   if(node->type == GUMBO_NODE_TEXT)
   {
	  //strncat(content, node->v.text.original_text.data, node->v.text.original_text.length);
	  //char* str = (char*)malloc(sizeof(char)*(strlen(node->v.text.text) + 1));
   
	  int len = strlen(node->v.text.text);
	  if(len <= 2)
	  {
		 return -1;
	  }
	  if(*text == NULL)
	  {
		 *text = (char*)malloc(sizeof(char)*(len + 1));
		 bzero(*text, sizeof(char)*(len + 1)); 
		 strcpy(*text, node->v.text.text);
	//	 memcpy(*text, node->v.text.text, sizeof(char)*(len))
	//	 (*text)[len] = '\0';
	  }
	  else
	  {
		 //printf("len:%d\n", len);
		 char* tempstr = NULL;
		 tempstr = (char*)malloc(sizeof(char)*(strlen(*text) + 1));
		 strcpy(tempstr, *text);
		 // memcpy(tempstr, *text, sizeof(char)*(strlen(*text)));
		// tempstr[strlen(*text)] = '\0';
		 
		 if((*text = (char*)realloc(*text, sizeof(char)*(strlen(*text) + len + 1))) == NULL)
		 {
			*text = (char*)malloc(sizeof(char)*(strlen(tempstr) + len + 1));
			strcpy(*text,  tempstr);
			//memcpy(*text, tempstr, strlen(tempstr));
			//(*text)[strlen(tempstr)] = '\0';
			strcat(*text, node->v.text.text);
			if(tempstr)
			{
			   free(tempstr);
			   tempstr = NULL;
			}
			return 1;
		 }	
		 if(tempstr)
		 {
			free(tempstr);
			tempstr = NULL;
		 }
		 strcat(*text, node->v.text.text);
//		 strncat(*text, node->v.text.text, len);
//		 (*text)[strlen(*text) + len] = '\0';
	  }

   }
   else if(node->type == GUMBO_NODE_ELEMENT &&
		 node->v.element.tag != GUMBO_TAG_SCRIPT &&
		 node->v.element.tag != GUMBO_TAG_STYLE &&
		 node->v.element.tag != GUMBO_TAG_ANNOTATION_XML)
   {
	  //char* content = (char);

	  GumboVector* children = &node->v.element.children;
	  int i;
	  for(i = 0; i < children->length; ++i)
	  {
		 cleantext(children->data[i], text);
	  }
   }

   return 1;
}

/*读文件
 * in:fp
 * out: output, length
 * */
static void read_file(FILE* fp, char** output, int* length) {
   struct stat filestats;
   int fd = fileno(fp);
   fstat(fd, &filestats);
   *length = filestats.st_size;
   *output = malloc(*length + 1);
   int start = 0;
   int bytes_read;
   while ((bytes_read = fread(*output + start, 1, *length - start, fp))) {
	  start += bytes_read;
   }
}

/*找出node节点里面的链接数量
 *in:node
 *out: num
 * */
void find_a_num(GumboNode* node, int* num)
{
   if(!node)
   {
	  return;

   }
   else if(node->type == GUMBO_NODE_ELEMENT)
   {
	  if(node->v.element.tag == GUMBO_TAG_A)
	  {
		 *num++;
	  }
	  GumboVector* children = &node->v.element.children;
	  int i;
	  for(i = 0 ; i < children->length; ++i)
	  {
		 find_a_num(children->data[i], num);
	  }
   }
}

//判断一个node是否是翻页node
/*in:node
 *out: text
 *
 * */
int is_page_node(GumboNode* node, char* text)
{
   if(!text || !node)
   {
	  return 0;
   }
   if(strlen(text) > 100)
   {
	  return 0;
   }

   
   if(strcasestr(text, "下一页") || 
		 strcasestr(text, "下页") ||
		 strcasestr(text, "上页") ||
		 strcasestr(text, "上一页"))
   {
	  return 1;
   }

   int numnum = 0;
   int i = 0;
   /*
	  while(text[i] != '\0')
	  {
	  if(isdigit(text[i]))
	  {
	  numnum++;
	  }
	  i++;
	  }
	  */
   //图片块，跳出

   int imgNum = 0;
   if(strstr(text, "积分") || strstr(text, "等级") ||\
		 strstr(text, "在线时长"))
   {
	  return 1;
   }
   int anum = 0;
   find_a_num(node, &anum);
   //printf("anum:%d\n", anum);
   int len = strlen(text);
   //printf("len:%d,anum:%d\n", len, anum);
   if((double)len / anum < 50)
   {
	  return 1;
   }
   int aa;
   all_a(node, &aa);
   if(aa == 1)
   {
	  return 1;
   }
   else
   {
	  return 0;
   }
   //   printf("")
   /*
	  if((double)len / numnum < 2)
	  {
	  return 1;
	  }
	  */
}

/*判断一个node是否全是链接
 * ret: aa == 0, 不全是
 * ret: aa == 1, 全是链接
 * */
void all_a(GumboNode* node, int* aa)
{
   if(!node)
   {
	  return;
   }
   else if(node->type == GUMBO_NODE_ELEMENT)
   {
	  GumboVector* children = &node->v.element.children;
	  int i;
	  for(i = 0; i < children->length; ++i)
	  {
		 all_a(children->data[i], aa);
	  }

   }
   else if(node->type == GUMBO_NODE_TEXT)
   {
	  if(node->parent->v.element.tag == GUMBO_TAG_A)
	  {
		 *aa = 1;
	  }
	  else
	  {
		 *aa = 0;
	  }
   }
}

/*重要函数：比较两个节点并且输出第一个不同结构的节点
 *in: aNode, bNode
 *out: cNode
 * */
void compare_and_output(GumboNode* aNode, GumboNode* bNode, GumboNode** cNode)
{//compare a & b, and output the different part in aNode
   if(aNode  == NULL || bNode == NULL)
   {
	  return;
   }
   else if(*cNode == NULL && aNode->type == GUMBO_NODE_ELEMENT &&
		 
		 bNode->type == GUMBO_NODE_ELEMENT && 
		 aNode->v.element.tag != GUMBO_TAG_SCRIPT &&
		 bNode->v.element.tag != GUMBO_TAG_SCRIPT &&
		 aNode->v.element.tag != GUMBO_TAG_ANNOTATION_XML &&
		 aNode->v.element.tag != GUMBO_TAG_ANNOTATION_XML )
   {
	  GumboVector* aChildren = &aNode->v.element.children;
	  GumboVector* bChildren = &bNode->v.element.children;
	  //printf("anode:%s, ac num:%d, bc num:%d\n", gumbo_normalized_tagname(aNode->v.element.tag)
	  //			,aChildren->length, bChildren->length);
	  //	  print_Node(aNode);
	  //	  print_Node(bNode);
//	  printf("anode:%s, bnode:%s\n", gumbo_normalized_tagname(aNode->v.element.tag),
//			gumbo_normalized_tagname(bNode->v.element.tag));
	  int ason = return_elem_son_num(aNode);
	  int bson = return_elem_son_num(bNode);
//	  printf("ason:%d, bson:%d\n",  ason, bson);
	  if(ason == bson)
	  {

		 if((ason == 0 && bson == 0))
		 {
			if(strcasecmp(gumbo_normalized_tagname(aNode->v.element.tag),
					 gumbo_normalized_tagname(bNode->v.element.tag)) == 0)
			{
			   //即使两个节点同一类型，但是里面内容不一样也是可以认定为内容区域的
			   char* tempcontent1 = NULL;
			   char* tempcontent2 = NULL;
			   cleantext(aNode, &tempcontent1);
			   cleantext(bNode, &tempcontent2);
			   //html_get_inner_text(aNode, &tempcontent1, 5000);
			   //html_get_inner_text(bNode, &tempcontent2, 5000);
			   if(tempcontent1 == NULL || tempcontent2 == NULL)
			   {
				  if(tempcontent1)
				  {
					 free(tempcontent1);
				  }
				  if(tempcontent2)
				  {
					 free(tempcontent2);
				  }
				  return;
			   }
			   if(find_comma_num_out(tempcontent1) == 0 || find_comma_num_out(tempcontent2) == 0)
			   {
				  if(tempcontent1)
				  {
					 free(tempcontent1);
					 tempcontent1 = NULL;
				  }

				  if(tempcontent2)
				  {
					 free(tempcontent2);
					 tempcontent2 = NULL;
				  }
				  return;
			   }
			   if(is_page_node(aNode, tempcontent1))
			   {
				  if(tempcontent1)
				  {
					 free(tempcontent1);
					 tempcontent1 = NULL;
				  }

				  if(tempcontent2)
				  {
					 free(tempcontent2);
					 tempcontent2 = NULL;
				  }
				 // printf("is page\n");
				  return;
			   }
			   int len1 = strlen(tempcontent1);
			   int len2 = strlen(tempcontent2);
			   //printf("len1:%d, len2:%d\n", len1, len2);
			   if(tempcontent1)
			   {
				  free(tempcontent1);
				  tempcontent1 = NULL;
			   }

			   if(tempcontent2)
			   {
				  free(tempcontent2);
				  tempcontent2 = NULL;
			   }
			   int aa;
			   all_a(aNode, &aa);
			   if(aa == 1)
			   {
				  return;
			   }
			   if((double)len1/len2 > 1.2 || (double)len1/len2 < 0.8)
			   {
				  *cNode = aNode->parent;
				  return;
			   }
			   return;
			}
			else
			{
			   //printf("sec1\n");
			   char* tempstr = NULL;
			   cleantext(aNode, &tempstr);
			   //html_get_inner_text(aNode, &tempstr, 5000);

			   if( tempstr && is_page_node(aNode, tempstr))
			   {
				  if(tempstr)
				  {
					 free(tempstr);
					 tempstr = NULL;
				  }
				  return;
			   }

			   if(tempstr)
			   {
				  free(tempstr);
				  tempstr = NULL;
			   }
			   *cNode = aNode->parent;
			   return;
			}
		 }
		 else 
		 {
			int i;
			//printf("children:\n");
			for(i = 0; i < aChildren->length && i < bChildren->length; ++i)
			{
//			   GumboNode* bChild = bChildren->data[i];
			   //printf("place value:%p\n", bChild);
//			   int addr = bChild;
//			   if(bChild == 0xb || bChild == 0x30)
			   //{
			   //  return;
			   // }
			   
			  // printf("bNodep:%p, strlen:%d\n", bNode, strlen(bNode));
			   compare_and_output(aChildren->data[i], bChildren->data[i], cNode);
			}
		 }
	  }
	  else
	  {
		 //把选中页码的情况排除

		 //printf("set2\n");
		 char* tempstr = NULL;
		 cleantext(aNode, &tempstr);
		 //html_get_inner_text(aNode, &tempstr, 5000);
		 if(tempstr && is_page_node(aNode, tempstr)) 
		 {
			if(tempstr)
			{
			   free(tempstr);
			   tempstr = NULL;
			}
			return;
		 }
		 else
		 {
			if(tempstr)
			{
			   free(tempstr);
			   tempstr = NULL;
			}
			//printf("aNode:\n");
		//	print_Node(aNode);

			//printf("*(*****************************************)\n");
			//printf("bNode:\n");
			//print_Node(bNode);
			*cNode = aNode;
			return;
		 }

	  }

   }
}

/*重要函数：返回此节点的子节点的数量
 * in: node
 * out: ele_num, 子节点的数量 
 *
 * */
int return_elem_son_num(GumboNode* node)
{
   GumboVector* children = &node->v.element.children;

   int ele_num = 0;
   int i;

   for(i = 0; i < children->length; ++i)
   {
	  GumboNode* temp = children->data[i];
	  if(temp->type == GUMBO_NODE_ELEMENT &&
			//		 temp->v.element.tag != GUMBO_TAG_A)
		 strcasecmp(gumbo_normalized_tagname(temp->v.element.tag), "a") != 0 &&
			temp->v.element.tag != GUMBO_TAG_ANNOTATION_XML &&
			temp->v.element.tag != GUMBO_TAG_SCRIPT)
			{
			   ele_num++;
			}
   }

   return ele_num;
}

/*打印节点的tag值
 *in:root
 *out:NULL
 * */
void print_Node(GumboNode* root)
{
   if(!root)
   {
	  return;
   }
   else if(root->type == GUMBO_NODE_ELEMENT)
   {

	  GumboVector* children = &root->v.element.children;
	  GumboNode* temp;

	  int i;
	  for(i = 0; i < children->length; ++i)
	  {
		 temp = children->data[i];
		 if(temp->type == GUMBO_NODE_ELEMENT &&
			   //		 temp->v.element.tag != GUMBO_TAG_A)
			strcasecmp(gumbo_normalized_tagname(temp->v.element.tag), "a") != 0 &&
			   temp->v.element.tag != GUMBO_TAG_SCRIPT)
			   {
				  printf("node:%s\n", gumbo_normalized_tagname(temp->v.element.tag));
				  output_attr(temp);
			   }
	  }
   }
}

/*找到时间信息，时间节点
 * in: root
 * out: time, timeNode.
 *  need to be free outside the Func.
 * */
void find_time(GumboNode* root, char** time, GumboNode** timeNode)
{
   if(!root)
   {
	  return;
   }
   else if(*time == NULL && root->type == GUMBO_NODE_ELEMENT)
   {
	  GumboVector* attrs = &root->v.element.attributes;
	  int i;
	  GumboAttribute* attr = NULL;
	  char* begtime = NULL;
	  //char* endtime = NULL;
	  int timeLen = 0;
	  //find time if timestr in the attr value;
	  for(i = 0; i < attrs->length; ++i)
	  {
		 //begtime = NULL;
		 timeLen = 0; 
		 attr = attrs->data[i];
		 if(root->v.element.tag != GUMBO_TAG_A && is_time_str(attr->value, time, &timeLen))
		 {
			*timeNode = root;
			return;
		 }
	  }
	  GumboVector* children = &root->v.element.children;
	  GumboNode* child = NULL;
	  for(i = 0; i < children->length; ++i)
	  {
		 child = children->data[i];
		 find_time(child, time, timeNode);
	  }
   }
   //find time if the timestr is in the text
   else if(*time == NULL && root->type == GUMBO_NODE_TEXT)
   {
	  int timeLen = 0; 
	  if(is_time_str(root->v.text.text, time, &timeLen))
	  {
		 //find the latest notext node
		 *timeNode = root->parent;
		 return;
	  }
   }
}


/*把title的内容清理干净，把后面的论坛信息去掉
 * in:rawTitle
 * out:cleanTitle
 * */
void cleantitle(const char* rawTitle, char** cleanTitle)
{
   int i = 0, j = 0;

   *cleanTitle = (char*)malloc(sizeof(char)*(strlen(rawTitle) + 1));
   while(rawTitle[i] != '\0' && rawTitle[i] != '_' && rawTitle[i] != '-')
   {
	  (*cleanTitle)[j++] = rawTitle[i++];
   }
   (*cleanTitle)[j] = '\0';
}

/*假设时间节点和内容节点属于同一父节点，此假设已失效
 *此函数暂时不再使用
 *
 * */
void find_clean_text(GumboNode* root, GumboNode* timeNode, GumboNode** contentNode)
{//root为最大的块范围，以内都是正文或者堆楼
   //timeNode 为时间节点的所在node， 
   //contentNode 为传出的contentNode变量
   if(!root)
   {
	  return;
   }
   else if(*contentNode == NULL)
   {
	  GumboNode* p = timeNode;
	  while(p->parent && p != root)
	  { 
		 char* temptext = NULL;
		 cleantext(p, &temptext);
		 //html_get_inner_text(p, &temptext, 5000);
		 int commaNum = find_comma_num_out(temptext);
		 
		 
		 if(commaNum > 3)
		 {
			*contentNode = p;			
			return;
		 }
		 p = p->parent;
		 free(temptext);
	  }
   }
}

/*从整体不同的部分，找出第一个文字块，
 * in: root, 因为提取的是内容，所以这里输入body节点
 * out: fnode, 输出到此节点，从中提取正文
 *
 * */
//base the whole diff to find the first part textnode
void find_first_node(GumboNode* root, GumboNode** fnode)
{

   //需要增加删除边栏节点，方案是取关键字，和转义字符消除
   if(!root)
   {
	  return;
   }
   else if(*fnode == NULL && root->type == GUMBO_NODE_ELEMENT &&
		 root->v.element.tag != GUMBO_TAG_ANNOTATION_XML &&
		 root->v.element.tag != GUMBO_TAG_SCRIPT &&
		 root->v.element.tag != GUMBO_TAG_NOSCRIPT &&
		 root->v.element.tag != GUMBO_TAG_INPUT)
   {
	  GumboVector* children = &root->v.element.children;
	  int i;
	  for(i = 0; i < children->length; ++i)
	  {
		 GumboNode* child = children->data[i];
		 find_first_node(child, fnode);
	  }
   }
   else if(root->type == GUMBO_NODE_TEXT && *fnode == NULL)
   {
	  if(find_comma_num_out(root->v.text.text) > 3)
	  {
		 //find the lastest div
		 //if above div is table,chose the table
		 //
		 GumboNode* p = root;
		 GumboNode* iftablep = root;

		 while(iftablep)
		 {
			if(iftablep->v.element.tag == GUMBO_TAG_TABLE)
			{
			   break;
			}
			else
			{
			   iftablep = iftablep->parent;
			}
		 }
		 //else
		 if(!iftablep)
		 {
			while(p && p->parent && p->v.element.tag != GUMBO_TAG_DIV)
			{
			   p = p->parent;
			}
			*fnode = p;
		 }
		 else
		 {
			*fnode = iftablep;
		 }

		 return;
	  }
	  else
	  {
		 return;
	  }
   }
}

/*side 为辅助网页， dest为目标解析的网页，其他三项为输出*/
int deal_htmls_4(char* dest, char* side, char** title, char** content, char** time)
{
   if(!(dest && side))
   {
	  return 0;
   }
   GumboOutput* output = gumbo_parse(dest);
   GumboOutput* output1 = gumbo_parse(side);


   if(!dest || !side)
   {
	  return 0;
   }

   //title
   char* temptitle = find_title(output->root);
   *title = (char*)malloc(sizeof(char)*(strlen(temptitle) + 1));
   strcpy(*title, temptitle);
   //memcpy(*title, temptitle, strlen(temptitle));
   //(*title)[strlen(temptitle)] = '\0'; 
   GumboNode* bodyNode1 = NULL;
   GumboNode* bodyNode2 = NULL;
   find_body(output->root, &bodyNode1);
   find_body(output1->root, &bodyNode2);

   GumboNode* cNode = NULL;
   compare_and_output(bodyNode1, bodyNode2, &cNode);
   if(!cNode)
   {
	  gumbo_destroy_output(&kGumboDefaultOptions, output);
	  gumbo_destroy_output(&kGumboDefaultOptions, output1);
	  return 0;
   }
   //time
   GumboNode* timeNode = NULL;
   find_time(bodyNode1, time, &timeNode);

   GumboNode* contentNode = NULL;
   find_first_node(cNode, &contentNode);


   //printf("beg clean\n");
   *content = NULL;
   //printf("file1:%s, file2:%s\n", file1, file2);
   cleantext(contentNode, content);
   //html_get_inner_text(contentNode, content, 5000);
   //printf("content:%s\n", *content);
   gumbo_destroy_output(&kGumboDefaultOptions, output);
   gumbo_destroy_output(&kGumboDefaultOptions, output1);

   return 1;
}


void read_spc_html2(GumboNode* root, GumboNode** contentNode )
{
   if(!root)
   {
	  return;
   }
   else if((*contentNode == NULL) && root->type == GUMBO_NODE_ELEMENT  
		 && root->type != GUMBO_TAG_SCRIPT &&
		 root->type != GUMBO_TAG_STYLE)
   {
	  GumboVector* children = &root->v.element.children;
	  int i;
	  for(i = 0; i < children->length; ++i)
	  {
		 read_spc_html2(children->data[i], contentNode);
	  }
   }
   else if(root->type == GUMBO_NODE_TEXT &&
		 root->parent->v.element.tag != GUMBO_TAG_SCRIPT &&
		 root->parent->v.element.tag != GUMBO_TAG_STYLE &&
		 (*contentNode == NULL) &&
		 root->parent->v.element.tag != GUMBO_TAG_ANNOTATION_XML)// &&
	  //strcasecmp(gumbo_normalized_tagname(root->parent->v.element.tag), "textarea") != 0)
   {
	  //ver1 1只检测标点,并直接找到最近div
	  if(find_comma_num_out(root->v.text.text) > 5)
	  {
		 //如果text的标点符号超过阈值，则向上遍历到div或者table节点
		 GumboNode* tempcontentNode = NULL;
		 tempcontentNode = root->parent;

		 /*
			while(tempcontentNode)
			{
		 //	printf("tagnum:%d\n", tempcontentNode->v.element.tag);
		 //	printf("tag last:%d\n", GUMBO_TAG_LAST);
		 if(strcasecmp(gumbo_normalized_tagname(tempcontentNode->v.element.tag), "div") == 0 ||
		 strcasecmp(gumbo_normalized_tagname(tempcontentNode->v.element.tag), "table") == 0)
		 {
		  *contentNode = tempcontentNode;
		  break;
		  }

		  tempcontentNode = tempcontentNode->parent;
		  }
		  */
		 if(tempcontentNode->v.element.children.length > 3)
		 {
			while(tempcontentNode)
			{
			   if(strcasecmp(gumbo_normalized_tagname(tempcontentNode->v.element.tag), "div") == 0 ||
					 strcasecmp(gumbo_normalized_tagname(tempcontentNode->v.element.tag), "table") == 0)
			   {
				  *contentNode = tempcontentNode;
				  break;
			   }
			   tempcontentNode = tempcontentNode->parent;
			}
		 }
	  }
   }
}

int deal_htmls_3(char* dest, char** title, char** content, char** time)
{
   GumboOutput* output = gumbo_parse(dest);


   char* temptitle = find_title(output->root);
   *title = (char*)malloc(sizeof(char)*(strlen(temptitle) + 1));
   memcpy(*title, temptitle, strlen(temptitle));
   (*title)[strlen(temptitle)] = '\0';

   GumboNode* contentNode = NULL;
   GumboNode* bodyNode;
   find_body(output->root, &bodyNode);
   read_spc_html2(bodyNode, &contentNode);

   GumboNode* timeNode = NULL;
   find_time(bodyNode, time, &timeNode);
   cleantext(contentNode, content);
   //html_get_inner_text(contentNode, content, 5000);
   gumbo_destroy_output(&kGumboDefaultOptions, output);
   return 1;
}

/*需要输入的commonpart需要有两个以上的网页*/
int extract_4(CommonPart* cp, int* htmltotal, int* titletarget, 
	  int* timetarget, int* contenttarget, FILE* fp)
{
   UrlBuf* p = cp->ubList;
   
   UrlBuf* sucp = NULL;
   while(p)
   {
	  sucp = cp->maxBuf;
	  if(p == cp->maxBuf)
	  {
		 p = p->next;
		 continue;
	  }
	  p->title = NULL;
	  p->content = NULL;
	  p->time = NULL;
	  int deal_ret = deal_htmls_4(p->htmls, cp->maxBuf->htmls, &p->title, &p->content, &p->time);
	  //printf("title:%s, time:%s, content:%s\n", p->title, p->time, p->content);
	  //
	  if(p->content)
	  {
		 sucp = p;
	  }
	  else
	  {
		 UrlBuf* tempp = cp->ubList;

		 while(tempp)
		 {
			p->title = NULL;
			p->content = NULL;
			p->time = NULL;	 
			if(tempp == p)
			{
			   tempp = tempp->next;
			   continue;
			}

			deal_ret = deal_htmls_4(p->htmls, tempp->htmls, &p->title, &p->content, &p->time);
			if(p->content)
			{
			   break;
			}

			tempp = tempp->next;
		 }

	  }
	  char tempcontent[300];
	  bzero(tempcontent, sizeof(tempcontent));
	  if(p->content)
	  {
		 strncpy(tempcontent, p->content, 299);
		 tempcontent[299] = '\0';
	  }
	  (*htmltotal)++;
	  if(deal_ret)
	  {
		 fprintf(fp, "filename:%s, url:%s, title:%s, time:%s, content:%s\n", 
			   p->filename, p->url, p->title, p->time, p->content);
		 printf("htmltalnum:%d, titletarget:%d, timetarget:%d, contenttarget:%d, \
			   filename:%s, url:%s, title:%s, time:%s, content:%s\n", \
			   *htmltotal, *titletarget, *timetarget, *contenttarget, 
			   p->filename, p->url, p->title, p->time, p->content);
		 
		 if(p->title)
		 {
			(*titletarget)++;
		 }

		 if(p->time)
		 {
			(*timetarget)++;
		 }

		 if(strlen(tempcontent) > 0)
			(*contenttarget)++;
	  }

	  p = p->next;
   }


   return 1;
}

int extract_3(CommonPart* cp, int* htmltotal, int* titletarget, 
	  int* timetarget, int* contenttarget, FILE* fp)
{
   UrlBuf* p = cp->ubList;

   (*htmltotal)++;
   p->title = NULL;
   p->content = NULL;
   p->time = NULL;
   deal_htmls_3(p->htmls, &p->title, &p->content, &p->time);
   if(p->content)
   {
	  (*contenttarget)++;
   }
   if(p->title)
   {
	  (*titletarget)++;
   }
   if(p->time)
   {
	  (*timetarget)++;
   }

   char tempcontent[300];
   bzero(tempcontent, sizeof(tempcontent));
   if(p->content)
   {
	  strncpy(tempcontent, p->content, 299);
	  tempcontent[299] = '\0';
   }

 
   fprintf(fp, "filename:%s, url:%s, title:%s, time:%s, content:%s\n\n\n", 
		 p->filename, p->url, p->title, p->time, p->content);
   printf("filename:%s, url:%s, title:%s, time:%s, content:%s\n\n\n", 
		 p->filename, p->url, p->title, p->time, p->content);

   return 1;
}




