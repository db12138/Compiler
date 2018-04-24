#include "symbolTable.h"
#include <stdio.h>
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
int addVar(Vtype var)
{
	vartable[varnum++]=var;
	//printf("varnum:%d\n",varnum);
	//fprintf(stderr,"why");
	return 0;
}

int displaySymbolTable()
{
	int i=0;
	printf("symbolTable:\n");
	for(;i<varnum;i++)
	{
		char BasicType[50];
		if(vartable[i].type.kind == BASIC)
		{
			if(vartable[i].type.u.basic == 1)
			{
				printf("int    ");
			}
			else
			{
				printf("float  ");
			}
		}
		else if(vartable[i].type.kind == ARRAY)
		{
			printf("ARRAY   ");
		}
		else if(vartable[i].type.kind == STRUCTURE)
		{
			printf("STRUCTURE   ");
		}
		else
		{
			Assert("should not reach",__FILE__,__LINE__);
		}
		printf("%s\n",vartable[i].name);
	}
}
