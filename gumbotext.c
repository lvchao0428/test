/*************************************************************************
    > File Name: gumbotext.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Tue Dec 15 11:08:48 2015
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<gumbo.h>
#include<stdlib.h>
#include<sys/stat.h>


int strTimes(char* str, char* word)
{
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
   //LablePosPair* wordPair = (LablePosPair*)malloc(sizeof(LablePosPair));
   //wordPair->next = NULL;
   //out_content_scope(line, wordPair);
   //LablePosPair* p = wordPair->next;

   int i = 0;
   int j=0;
   while(j < 7)
   {
	  comma_num += strTimes(line, comma[j]);
	  j++;
   }

      
   return comma_num;
}

int is_time_str(char* str, char** beg, char** end)
{
   char* p = str;
   int ret = 0;
   char* prebeg = NULL;
   while(p && *p && strlen(str) >= 6)
   {
	  //****-**-**格式
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
	  {//
			
		 *beg = p;
		 *end = (p+9);
		 
		 if(prebeg && !isdigit(*prebeg))
			ret = 1;
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
		 *beg = p;
		 *end = (p+7);

		 if(prebeg && !isdigit(*prebeg))
			ret = 1;
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
		 *beg = p;
		 *end = (p+8);

		 if(prebeg && !isdigit(*prebeg))
			ret = 1;
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
		 *beg = p;
		 *end = (p+8);

		 if(prebeg && !isdigit(*prebeg))
			ret = 1;
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
		 *beg = p;
		 *end = (p+7);

		 if(prebeg && !isdigit(*prebeg))
			ret = 1;
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
		 *beg = p;
		 *end = (p+5);

		 if(prebeg && !isdigit(*prebeg))
			ret = 1;
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
		 *beg = p;
		 end = (p+6);

		 if(prebeg && !isdigit(*prebeg))
			ret = 1;
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
		 *beg = p;
		 *end = (p+6);

		 if(prebeg && !isdigit(*prebeg))
			ret = 1;
		 break;
	  }

	  p++;
   }

   return ret;
}

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
	  if(*text == NULL)
	  {
		 *text = (char*)malloc(sizeof(char)*(len + 1));
		 bzero(*text, sizeof(char)*(strlen(*text) + 1)); 
		 strcpy(*text, node->v.text.text);
	  }
	  else
	  {
		 *text = (char*)realloc(*text, sizeof(char)*(strlen(*text) + len+1));
		 strcat(*text, node->v.text.text);
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

void print_Node(GumboNode* root);

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

void all_a(GumboNode* node, int* aa);
//判断一个node是否是翻页node
int is_page_node(GumboNode* node, char* text)
{
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
   int anum = 0;
   find_a_num(node, &anum);
   printf("anum:%d\n", anum);
   int len = strlen(text);
   printf("len:%d,anum:%d\n", len, anum);
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

int return_elem_son_num(GumboNode* node);
void compare_and_output(GumboNode* aNode, GumboNode* bNode, GumboNode** cNode)
{//compare a & b, and output the different part in aNode
   if(aNode  == NULL || bNode == NULL)
   {
	  return;
   }
   else if(aNode->type == GUMBO_NODE_ELEMENT &&
		 bNode->type == GUMBO_NODE_ELEMENT && 
		 aNode->v.element.tag != GUMBO_TAG_SCRIPT &&
		 bNode->v.element.tag != GUMBO_TAG_SCRIPT &&
		 *cNode == NULL)
   {
	  GumboVector* aChildren = &aNode->v.element.children;
	  GumboVector* bChildren = &bNode->v.element.children;

	  //printf("anode:%s, ac num:%d, bc num:%d\n", gumbo_normalized_tagname(aNode->v.element.tag)
	  //			,aChildren->length, bChildren->length);
	  //	  print_Node(aNode);
	  //	  print_Node(bNode);
	  printf("anode:%s, bnode:%s\n", gumbo_normalized_tagname(aNode->v.element.tag),
			gumbo_normalized_tagname(bNode->v.element.tag));
	  int ason = return_elem_son_num(aNode);
	  int bson = return_elem_son_num(bNode);
	  printf("ason:%d, bson:%d\n",  ason, bson);
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
			   if(tempcontent1 == NULL || tempcontent2 == NULL)
			   {
				  return;
			   }
			   if(find_comma_num_out(tempcontent1) == 0 || find_comma_num_out(tempcontent2) == 0)
			   {
				  return;
			   }
			   if(is_page_node(aNode, tempcontent1))
			   {

				  printf("is page\n");
				  return;
			   }
			   int len1 = strlen(tempcontent1);
			   int len2 = strlen(tempcontent2);
			   printf("len1:%d, len2:%d\n", len1, len2);
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
			   printf("sec1\n");
			   char* tempstr = NULL;
			   cleantext(aNode, &tempstr);

			   if(is_page_node(aNode, tempstr))
			   {
				  free(tempstr);
				  return;
			   }
			   free(tempstr);
			   *cNode = aNode->parent;
			   return;
			}
		 }
		 else 
		 {
			int i;
			//printf("children:\n");
			for(i = 0; i < aChildren->length; ++i)
			{
			   compare_and_output(aChildren->data[i], bChildren->data[i], cNode);
			}
		 }
	  }
	  else
	  {
		 //把选中页码的情况排除

		 printf("set2\n");
		 char* tempstr = NULL;
		 cleantext(aNode, &tempstr);
		 if(is_page_node(aNode, tempstr)) 
		 {
			return;
		 }
		 else
		 {
			print_Node(aNode);
			printf("*(*****************************************)\n");
			print_Node(bNode);
			*cNode = aNode;
			return;
		 }

	  }

   }
}

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
	  char* endtime = NULL;
	  //find time if timestr in the attr value;
	  for(i = 0; i < attrs->length; ++i)
	  {
		 begtime = NULL;
		 endtime = NULL;
		 attr = attrs->data[i];
		 if(root->v.element.tag != GUMBO_TAG_A &&  is_time_str(attr->value, &begtime, &endtime))
		 {
			*time = (char*)malloc(sizeof(char)*(endtime - begtime + 1));
			strncpy(*time, begtime, endtime-begtime + 1);
			(*time)[endtime - begtime + 1] = '\0';
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
   else if(root->type == GUMBO_NODE_TEXT && *time == NULL)
   {
	  char* begtime = NULL;
	  char* endtime = NULL;
	  if(is_time_str(root->v.text.text, &begtime, &endtime))
	  {
		 *time = (char*)malloc(sizeof(char)*(endtime - begtime + 1));
		 strncpy(*time, begtime, endtime - begtime + 1);
		 (*time)[endtime - begtime + 1] = '\0';
		 //find the latest notext node
		 *timeNode = root->parent;
		 return;
	  }
   }
}

void deleteNode(GumboNode* root, char* tagname)
{
   if(!root)
   {
	  return;
   }
   else if(root->type == GUMBO_NODE_ELEMENT)
   {
	  if(strcasecmp(gumbo_normalized_tagname(root->v.element.tag), tagname) == 0)
	  {
		 root = NULL;
		 return;
	  }
	  else
	  {
		 deleteNode(root, tagname);
	  }
   }
}

void cleantitle(const char* rawTitle, char** cleanTitle)
{
   int i = 0, j = 0;

   *cleanTitle = (char*)malloc(sizeof(char)*(strlen(rawTitle) + 1));
   while(rawTitle[i] != '\0' && rawTitle[i] != '_')
   {
	  (*cleanTitle)[j++] = rawTitle[i++];
   }
   (*cleanTitle)[j] = '\0';
}

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

//base the whole diff to find the first part textnode
void find_first_node(GumboNode* root, GumboNode** fnode)
{
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
		 GumboNode* p = root;
		 while(p && p->parent && p->v.element.tag != GUMBO_TAG_DIV)
		 {
			p = p->parent;
		 }
		 *fnode = p;
		 return;
	  }
	  else
	  {
		 return;
	  }
   }
}

int main(int argc, char* argv[])
{
   if(argc != 3)
   {
	  printf("need file name\n");
	  exit(1);
   }

   FILE* fp = fopen(argv[1], "r");
   FILE* fp1 = fopen(argv[2], "r");
   if(!fp || !fp1)
   {
	  printf("read file error\n");
	  exit(1);
   }


   char* input = NULL;
   int length;
   read_file(fp, &input, &length);
   GumboOutput* output = gumbo_parse(input);

   char* input1 = NULL;
   int length1;
   read_file(fp1, &input1, &length1);
   GumboOutput* output1 = gumbo_parse(input1);
   //************************************************************
   //extract content title and time with two html file with same struct
   //************************************************************
   //print_Node(output->root);
   GumboNode* cNode = NULL;
   //   deleteNode(output->root, "h1");
   // find title
   const char* title = find_title(output->root);
   //find title, then use title in BODY to find the first dom content
   GumboNode* mainNode = NULL;
   char* cleanTitle = NULL;
   cleantitle(title, &cleanTitle);
   GumboNode* bodyNode1 = NULL;
   GumboNode* bodyNode2 = NULL;
   find_body(output->root, &bodyNode1);
   find_body(output1->root, &bodyNode2);
   compare_and_output(bodyNode1, bodyNode2, &cNode);
   //base the cNode to find the first time
   //extract time in attr
   char* time = NULL;
   GumboNode* timeNode = NULL;
   find_time(cNode, &time, &timeNode);
   //printf("compare answer:\n");
   // print_Node(cNode);

   //find clean fisrt part text
   GumboNode* contentNode = NULL;

   //   find_clean_text(cNode, timeNode, &contentNode);
   find_first_node(cNode, &contentNode);
   char* content = NULL;
   cleantext(contentNode, &content);
   printf("**************************************\n");
   print_Node(contentNode);
   
   printf("title:%s\n", cleanTitle);
   printf("time:%s\n", time);
   //printf("contentlable:%s\n", gumbo_normalized_tagname(contentNode->v.element.tag));
   printf("contetn:%s\n", content);
   return 0;
}
