#include "symbolTable.h"
#include <stdio.h>
#include <string.h>
#include "debug.h"
Vtype vartable[1000];
int varnum;
Ftype funtable[500];
int funnum;
Stype structtable[100];
int structnum;

void displayType(Type_ var);
void initTable()
{
	varnum = 0;
	funnum = 0;
	structnum = 0;
}
Type_ getStructType(char *name)
{
	int i=0;
	for(;i<structnum;i++)
	{
		if(strcmp(structtable[i].structname,name) == 0)
			return structtable[i].structtype;
	}
	Assert("should not reach",__FILE__,__LINE__);
	Type_ init;
	return init;
}
int checkStruct(char *name)
{
	int i=0;
	for(;i<structnum;i++)
	{
		if(strcmp(structtable[i].structname,name) == 0)
		{
			return 1;
		}
	}
	return 0;
}
int addStruct(Stype s)
{
	structtable[structnum++] = s;
	return 0;
}
int addFun(Ftype fun)
{
	funtable[funnum++] = fun;
	return 0;
}

int checkRedefine(char *name)
{
	int i=0;
	for(;i<varnum;i++)
	{
		if(strcmp(vartable[i].name,name) == 0)
		{
			return 1;
		}
	}
	i=0;
	for(;i<structnum;i++)
	{
		if(strcmp(structtable[i].structname,name) == 0)
		{
			return 1;
		}
	}
	i=0;
	for(;i<funnum;i++)
	{
		if(strcmp(funtable[i].name,name) == 0)
		{
			return 1;
		}
	}
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
	//fprintf(stderr,"varnum:%d\n",varnum);
	//ffprintf(stderr,stderr,"why");
	return 0;
}
Type checkVar(char *varname)
{
	int i=0;
	for(;i<varnum;i++)
	{
		if(strcmp(vartable[i].name,varname) == 0)
		{
			return vartable[i].type; //var in the table
		}
	}
	return NULL; //not in
}

void displayFieldList(FieldList f)
{
	if(f == NULL)
		return;
	displayType(*(f->type));
	fprintf(stderr,"%s    ",f->name);
	displayFieldList(f->tail);
}
void displayType(Type_ var)
{
	char BasicType[50];
	if(var.kind == BASIC)
	{
		if(var.u.basic == 1)
		{
			fprintf(stderr,"int  ");
		}
		else
		{
			fprintf(stderr,"float  ");
		}
	}
	else if(var.kind == ARRAY)
	{
		fprintf(stderr,"[%d]",var.u.array.size);
		displayType(*var.u.array.elem);
	}
	else if(var.kind == STRUCTURE)
	{
		fprintf(stderr,"{\n");
		displayFieldList(var.u.structure);
		fprintf(stderr,"};\n");
	}
	else
	{
		Assert("should not reach",__FILE__,__LINE__);
	}
	
}
void displayStructTable()
{
	int i=0;
	for(;i<structnum;i++)
	{
		fprintf(stderr,"STRUCT %s",structtable[i].structname);
		displayType(structtable[i].structtype);
	}
}
int displaySymbolTable()
{
	int i=0;
	fprintf(stderr,"symbolTable:\n");
	fprintf(stderr,"  vartable:\n");
	for(;i<varnum;i++)
	{
		displayType(*vartable[i].type);
		fprintf(stderr,"%s\n",vartable[i].name);
	}
	fprintf(stderr,"  funtable:\n");
	for(i=0;i<funnum;i++)
	{
		displayType(funtable[i].retn);
		fprintf(stderr,"name:%s  ",funtable[i].name);
		fprintf(stderr,"paralistnum:%d  ",funtable[i].paranum);
		displayFieldList(funtable[i].paralist);
		fprintf(stderr,"\n");
	}
	displayStructTable();
	return 0;
}

