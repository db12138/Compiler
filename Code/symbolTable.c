#include "symbolTable.h"
#include <stdio.h>
#include <string.h>
#include "debug.h"
Vtype vartable[1000];
int varnum;
Ftype funtable[500];
int funnum;

void initTable()
{
	varnum = 0;
	funnum = 0;
}
int addFun(Ftype fun)
{
	funtable[funnum++] = fun;
	return 0;
}
int checkFun(char *funname)
{
	int i=0;
	for(;i<funnum;i++)
	{
		if(strcmp(funtable[i].name,funname) == 0)
		{
			return 1;
		}
	}
	return 0;
}
int addVar(Vtype var)
{
	vartable[varnum++]=var;
	//printf("varnum:%d\n",varnum);
	//fprintf(stderr,"why");
	return 0;
}
int checkVar(char *varname)
{
	int i=0;
	for(;i<varnum;i++)
	{
		if(strcmp(vartable[i].name,varname) == 0)
		{
			return 1; //var in the table
		}
	}
	return 0; //not in
}

void displayType(Type_ var)
{
	char BasicType[50];
	if(var.kind == BASIC)
	{
		if(var.u.basic == 1)
		{
			printf("int    ");
		}
		else
		{
			printf("float  ");
		}
	}
	else if(var.kind == ARRAY)
	{
		printf("ARRAY   ");
	}
	else if(var.kind == STRUCTURE)
	{
		printf("STRUCTURE   ");
	}
	else
	{
		Assert("should not reach",__FILE__,__LINE__);
	}
	
}
int displaySymbolTable()
{
	int i=0;
	printf("symbolTable:\n");
	printf("  vartable:\n");
	for(;i<varnum;i++)
	{
		displayType(vartable[i].type);
		printf("%s\n",vartable[i].name);
	}
	printf("  funtable:\n");
	for(i=0;i<funnum;i++)
	{
		displayType(funtable[i].retn);
		printf("paralistnum:%d  ",funtable[i].paranum);
		printf("name:%s\n",funtable[i].name);
	}
}

