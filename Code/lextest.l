%{
#include <stdio.h>
#include "common.h"
#include "syntax.tab.h"

Node * NewNode(char *);
Node * NewNodeId(char *,char *);
Node * NewNodeInt(int);
Node * NewNodeFloat(float);

int yycolumn = 1;
extern BOOL hasError;
extern int errorCount;

int s2i(char * str) {
  int i;
  long res;
  switch(str[0]) {
    case '0':
    	// hexadecimal
	if (str[1] == 'x' || str[1] == 'X') {
	  i = 2;
	  while(str[i] != '\0') {
	    if(str[i] < '0' || (str[i] < 'A' && str[i] > '9')|| (str[i] > 'F' && str[i] < 'a') || str[i] > 'f') {
	      hasError = TRUE;
	      printf("Error type A at Line %d: '%s' is not a valid hexadecimal.\n", yylineno, str);
	      return -1;
            }
	    i++;
	    //	printf("%c", str[i++]);
	    //printf("\n");
	  }
	    if(!hasError)
	      res = strtol(str + 2, NULL, 16);
	}
	// octal
	else if (str[1] != '\0') {
	  i = 1;
	  while(str[i] != '\0') {
	    if(str[i] < '0' || str[i] > '7') {
	      hasError = TRUE;
	      printf("Error type A at Line %d: '%s' is not a valid octal.\n", yylineno, str);
	      return -1;
	    }
	    i++;
	  }
	  if(!hasError)
	    res = strtol(str + 1, NULL, 8);
	}
	else
	  res = 0;
	break;
	
	default:
	  i = 0;
	  while(str[i] != '\0') {
	    if(str[i] < '0' || str[i] > '9') {
	      hasError = TRUE;
	      printf("Error type A at Line %d: '%s' is not a valid decimal or identifier.\n", yylineno, str);
	      return -1;
	    }
	    i++;
	  }
	  if(!hasError)
	    res = strtol(str, NULL, 10);
	  break;
	}

  return (int)res;
}

//maintain location
YYLTYPE yylloc;

#define YY_USER_ACTION yylloc.first_line = yylineno; \
	yylloc.last_line = yylineno; \
	yylloc.first_column = yycolumn; \
	yylloc.last_column = yycolumn + yyleng - 1; \
	yycolumn += yyleng;
%}

delim 		[ \t]
letter		[A-Za-z]
digit		[1-9]
relop		">"|"<"|">="|"<="|"=="|"!="
int     	(0|[1-9]({digit}|{letter})*|0({digit}|{letter})+|0[Xx]({digit}|{letter})+)
id 		[_a-zA-Z][_a-zA-Z0-9]*
float 		([0-9]*\.[0-9]+|[0-9]+\.[0-9]*)([Ee][+-]?[0-9]+)?


%%

{delim}+ 			{/*empty*/}
{int}	 			{int temp = s2i(yytext); 
				 if(hasError && temp == -1) {
				  yylval.type_node = NewNodeId("ID", yytext); return ID;
				 } else {
				  yylval.type_node = NewNodeInt(temp);  return INT;
				 }
				}
\n|\r\n 			{yylineno++; yycolumn = 1;}
"+" 				{yylval.type_node=NewNode("PLUS");return PLUS;}
"-" 				{yylval.type_node=NewNode("MINUS");return MINUS;}
"*" 				{yylval.type_node=NewNode("STAR");return STAR;}
"/" 				{yylval.type_node=NewNode("DIV");return DIV;}
";" 				{yylval.type_node=NewNode("SEMI");return SEMI;}
"," 				{yylval.type_node=NewNode("COMMA");return COMMA;}
"=" 				{yylval.type_node=NewNode("ASSIGNOP");return ASSIGNOP;}
{relop} 			{yylval.type_node=NewNode("RELOP");return RELOP;}
"&&" 				{yylval.type_node=NewNode("AND");return AND;}
"||" 				{yylval.type_node=NewNode("OR");return OR;}
"." 				{yylval.type_node=NewNode("DOT");return DOT;}
"!" 				{yylval.type_node=NewNode("NOT");return NOT;}
"int" 				{yylval.type_node=NewNodeId("TYPE",yytext);return TYPE;}
"float" 			{yylval.type_node=NewNodeId("TYPE",yytext);return TYPE;}
"(" 				{yylval.type_node=NewNode("LP");return LP;} 
")" 				{yylval.type_node=NewNode("RP");return RP;}
"[" 				{yylval.type_node=NewNode("LB");return LB;}
"]" 				{yylval.type_node=NewNode("RB");return RB;}
"{" 				{yylval.type_node=NewNode("LC");return LC;}
"}" 				{yylval.type_node=NewNode("RC");return RC;}
"struct" 			{yylval.type_node=NewNode("STRUCT");return STRUCT;}
"return" 			{yylval.type_node=NewNode("RETURN");return RETURN;}
"if" 				{yylval.type_node=NewNode("IF");return IF;}
"else" 				{yylval.type_node=NewNode("ELSE");return ELSE;}
"while" 			{yylval.type_node=NewNode("WHILE");return WHILE;} 
{id}+ 				{ yylval.type_node=NewNodeId("ID",yytext);return ID; }
{float}+ 			{yylval.type_node=NewNodeFloat(atof(yytext)); return FLOAT; } 
. 				{hasError = TRUE; printf("Error type A at Line %d: Mysterious character '%s'\n",yylineno,yytext);}
%%
