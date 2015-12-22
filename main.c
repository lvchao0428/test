/*************************************************************************
    > File Name: main.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Tue Dec  1 09:34:42 2015
 ************************************************************************/

#include<stdio.h>
#include<string.h>


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
