#include <stdio.h>
#include "lex.yy.c"
#include "common.h"
extern FILE *yyin;
extern Node *Root;
BOOL hasError = FALSE;
int errorCount = 0;

void DisplayTree(Node *head,int n);
int yyparse(void);
void Program(Node *);
void displaySymbolTable();
void initTable();
int main(int argc,char **argv)
{
	Root = NULL;
	initTable();

	if(argc > 1)
	{
		if(!(yyin=fopen(argv[1],"r")))
		{
			perror(argv[1]);
			return 1;
		}
	}
	yylineno = 1;
	yyrestart(yyin);
	yyparse();
	if(!hasError)
	{
	  DisplayTree(Root,0);

	  Program(Root);
	  displaySymbolTable();
	}
	
	return 0;
}

void yyerror(char *msg)
{
	hasError = TRUE;
	//fprintf(stderr,"error: ....%s\n",msg);
	if(strcmp(msg, "syntax error"))
	  printf("Error type B at Line %d :%s\n",yylineno,msg);
	  else
	  {
	  //	fprintf(stderr,"Error type B fault!\n");
	  }
}
