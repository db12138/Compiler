#include <stdio.h>
#include "lex.yy.c"
#include "interCode.h"

extern FILE *yyin;
extern Node *Root;
BOOL hasError = FALSE;
extern BOOL IRError;
int errorCount = 0;

void DisplayTree(Node *head,int n);
int yyparse(void);
void Program(Node *);
void displaySymbolTable();
void initTable();
void checkAllStatement();
int main(int argc,char **argv)
{
	Root = NULL;
	initTable();
	FILE * out = NULL;
	if(argc > 2) {
		if(!(yyin=fopen(argv[1],"r"))) {
			perror(argv[1]);
			return 1;
		}
		if(!(out = fopen(argv[2], "w"))) {
			perror(argv[2]);
			return 1;
		}
	}else {
		if(argc == 1) {
		 	fprintf(stderr, "Error: Please enter an input source and an output file name!\n\n");
                } else if (argc == 2) {
                        fprintf(stderr, "Error: Please enter an output file name!\n\n");
                }
                return 1;	
	}
	yylineno = 1;
	yyrestart(yyin);
	yyparse();
	if(!hasError)
	{
//	  DisplayTree(Root,0);
//	  displaySymbolTable();
	  checkAllStatement();
	  translate_Program(Root);
	  if(IRError == FALSE)
		  printIR(out);
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
