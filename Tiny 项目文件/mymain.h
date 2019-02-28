#ifndef MYMAIN_H
#define MYMAIN_H


//如果出现 像parse() 等函数没有定义，那么，就将代码改成下面那样
/*
   extern "C" {
    #include "globals.h"
    #include "util.h"
    #include "parse.h"
    #include "scan.h"
   }
*/  //代码改成这样，下面的就可以注释掉

#include "globals.h"
#include "util.h"
#include "parse.h"
#include "scan.h"


int lineno = 0;
FILE * source;
FILE * listing;


/* allocate and set tracing flags */
int EchoSource = FALSE;
int TraceScan = TRUE;
int TraceParse = TRUE;

int Error = FALSE;

void syntree()
{
   TreeNode * syntaxTree;
   char pgm[]="SAMPLE.txt";
   source = fopen(pgm,"rt");
 //  listing = fopen("tiny compilation.txt","wt+");  // 编译时生成的中间文件
 //  fprintf(listing,"TINY COMPILATION: %s\n",pgm);
   syntaxTree = parse();
 //  fclose(listing);
   char ch[]="syntax tree.txt";  //语法树输出文件
   listing  = fopen(ch,"wt+");
   if (TraceParse) {
      fprintf(listing,"Syntax tree:\n");
      printTree(syntaxTree);
      fclose(listing);
      }
    fclose(source);
}





#endif // MYMAIN_H

