#pragma once
#include <stddef.h>
#include <stdlib.h>
typedef struct Node
{
	int type; //0 terminal 1 noterminal 2 int 3 float 4 Id
	int linenum;
	int intval;
	float floatval;
	char idval[50];
	char strval[50];
	int childnum;
	struct Node * child[100];
}Node;

typedef int BOOL;
#define TRUE 1
#define FALSE 0

/*typedef struct YYLTYPE
{
	int first_line;
	int last_line;
	int first_column;
	int last_column;
}YYLTYPE;*/
