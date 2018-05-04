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
Dtype dectable[600];
int decnum;

void displayType(Type_ var);
int IsTypeEqual(Type_,Type_);
Type checkVar(char *varname);
void errorPrint(int ,int ,char *);
int checkDecParamList(FieldList p1,FieldList p2);
int checkDec(Dtype new,int DOS);

void initTable()
{
	varnum = 0;
	funnum = 0;
	structnum = 0;
	decnum = 0;
}
void displayDtable()
{
	int i=0;
	printf(" Dtable:\n");
	for(;i<decnum;i++)
	{
		printf("name:%s\n",dectable[i].name);
	}
}
int checkDecParamList(FieldList p1,FieldList p2)
{
	for(;(p1!=NULL) && (p2!=NULL);p1=p1->tail,p2=p2->tail)
	{
		//only check type
		if(IsTypeEqual(*(p1->type),*(p2->type)) == 0)
		{
			return 0;
		}
	}
	if(p1 == NULL && p2 == NULL)
		return 1;
	else
		return 0;
}
int checkDec(Dtype new,int DOS)
{
	int i=0;
	for(;i<decnum;i++)
	{
		if(strcmp(dectable[i].name,new.name) == 0)
		{
			if(new.paranum != dectable[i].paranum)
			{
				//check paramlist number
				//fprintf(stderr,"er: %d %d\n",new.paranum,dectable[i].paranum);
				errorPrint(191,new.linenum,new.name);
				return 1;
			}
			else if(IsTypeEqual(new.retn,dectable[i].retn) == 0)
			{
				//return type not equa;;
				errorPrint(19,new.linenum,new.name);
				return 1;
			}
			else if(checkDecParamList(new.paralist,dectable[i].paralist) ==0)
			{
				errorPrint(192,new.linenum,new.name);
				return 1;
			}
			else
			{
				if(DOS == 0)
				{
					dectable[i].defined = 1;
				}
				return 1; //has defined but dont have conflit;
			}
		}
	}
	return 0;
}
int addDec(Dtype new)
{
	dectable[decnum++] = new;
	return 0;
}
void checkAllStatement()
{
	int i=0;
	for(;i<decnum;i++)
	{
		if(dectable[i].defined == 0)
		{
			errorPrint(18,dectable[i].linenum,dectable[i].name);
		}
	}
}
Type checkHasField(FieldList pi,char *name)
{
	for(;pi!=NULL;pi=pi->tail)
	{
		if(strcmp(pi->name,name) == 0)
		{
			return pi->type;
		}
	}
	return NULL;
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
Type_ getArrayType(Type_ A)
{
	//A is a array type
	/*while(1)
	{
		if(A.kind == BASIC)
		{
			return A;
		}
		else
		{
			A = *(A.u.array.elem);
		}
	}*/
	if(A.kind == BASIC)
	{
		return A;
	}
	else
	{
		return getArrayType(*(A.u.array.elem));
	}
}
Stype* checkStruct(char *name)
{
	int i=0;
	for(;i<structnum;i++)
	{
		if(strcmp(structtable[i].structname,name) == 0)
		{
			return &structtable[i];
		}
	}
	return NULL;
}
int checkRedef(char *name)
{
	//check Redefination
	Stype *j1 = checkStruct(name);
	if(j1 != NULL)
	{
		//redefnation
		return 1;
	}
	Type j2 = checkVar(name);
	if(j2 != NULL)
	{
		//Redefination
		return 1;
	}
	return 0;
}
FieldList addStruct(Stype s)
{
	//check redefined field
	FieldList pi = s.structtype.u.structure;

	for(;pi!=NULL;pi=pi->tail)
	{
		char *f1 = pi->name;
		FieldList cur = pi->tail;
		for(;cur != NULL;cur = cur->tail)
		{
			char *f2 = cur->name;
			if(strcmp(f1,f2) == 0)
			{
				return cur;
			}
		}
	}
	structtable[structnum++] = s;
	return NULL;
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


Ftype * checkFun(char *funname)
{
	int i=0;
	for(;i<funnum;i++)
	{
		if(strcmp(funtable[i].name,funname) == 0)
		{
			return &funtable[i];
		}
	}
	return NULL;
}

int checkParamList(char *funname,FieldList paraList)
{
	int i=0;
	for(;i<funnum;i++)
	{
		if(strcmp(funtable[i].name,funname) == 0)
		{
			FieldList p1 = funtable[i].paralist;
			FieldList p2 = paraList;
			for(;p1!=NULL && p2 !=NULL ;p1=p1->tail,p2=p2->tail)
			{
				int j =IsTypeEqual(*(p1->type),*(p2->type));
				if(j == 0)
				{
					// not equal;
					return 0;
				}
			}
			if((p1 == NULL && p2!= NULL) || (p1!=NULL && p2==NULL))
				return 0;
			else
			{
				return 1;
			}
		}
	}
	return 0; //not found
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
	displayDtable();
	return 0;
}

