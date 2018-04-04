#include <stdio.h>
#include "lex.yy.c"
#include "common.h"
extern FILE *yyin;
extern Node *root;
BOOL hasError = FALSE;
int errorCount = 0;
void DisplayTree(Node *head,int n);
int main(int argc,char **argv)
{
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
	  DisplayTree(root,0);
	return 0;
}

void yyerror(char *msg)
{
	hasError = TRUE;
	//fprintf(stderr,"error: ....%s\n",msg);
	if(strcmp(msg, "syntax error"))
	  printf("Error type B at Line %d :%s\n",yylineno,msg);
}
