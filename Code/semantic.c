#include "semantic.h"
#include "debug.h"
#include <stdio.h>
extern Vtype vartable[];
extern Ftype funtalbe[];

void errorPrint(int ,int ,char *); 
int addStruct(Stype);
int addVar(Vtype);
Type checkVar(char *);
int addFun(Ftype);
int checkFun(char *);

void Program(Node *);
void ExtDefList(Node *);
void ExtDef(Node *);
void ExtDecList(Node *);
void Specifier(Node *);
void FunDec(Node *);
void CompSt(Node *);
void DefList(Node *);
void Def(Node *);
void DecList(Node *);
void Dec(Node *);
Vtype VarDec(Node *);
void StmtList(Node *);
void Stmt(Node *);
void Exp(Node *);

void StructSpecifier(Node *);
FieldList DefStruct(Node *);
FieldList DefListStruct(Node *);
FieldList DecListStruct(Node *);
FieldList DecStruct(Node *);

void Program(Node *root)
{
	if(root == NULL)
		return;

	ExtDefList(root->child[0]);
}

void ExtDefList(Node *root)
{
	if(root == NULL)
		return;
	
	ExtDef(root->child[0]);

	ExtDefList(root->child[1]);
}

void ExtDecList(Node *root)
{
	if(root == NULL)
		return;
	
	if(root->childnum == 1)
	{
		root->child[0]->inhtype = root->inhtype;
		Vtype newVar = VarDec(root->child[0]);
		addVar(newVar);
	}
	else
	{
		Assert("std need TODO",__FILE__,__LINE__);
	}
}
void ExtDef(Node *root)
{
	if(root == NULL)
		return;
	if(strcmp(root->child[1]->strval,"FunDec") == 0)
	{
		Specifier(root->child[0]);
		root->child[1]->inhtype = root->child[0]->inhtype;

		FunDec(root->child[1]);
		CompSt(root->child[2]);
	}
	else if(strcmp(root->child[1]->strval,"SEMI") == 0)
	{
		Specifier(root->child[0]);
	}
	else if(strcmp(root->child[1]->strval,"ExtDecList") == 0)
	{
		Specifier(root->child[0]);
		root->child[1]->inhtype = root->child[0]->inhtype;
		ExtDecList(root->child[1]);
	}
	else
	{
		Assert("Should not reach",__FILE__,__LINE__);
	}
}
FieldList DefListStruct(Node *root)
{
	if(root == NULL)
	{
		return NULL;
	}
	FieldList head = DefStruct(root->child[0]);
	if(head == NULL)
	{
		Assert("should not happen",__FILE__,__LINE__);
	}
	else
	{
		head->tail = DefListStruct(root->child[1]);
	}
	return head;

}
FieldList DefStruct(Node *root)
{
	if(root == NULL)
	{
		return NULL;
	}
	Specifier(root->child[0]);
	root->child[1]->inhtype = root->child[0]->inhtype;
	
	FieldList head = DecListStruct(root->child[1]);
	return head;

}
FieldList DecListStruct(Node *root)
{
	if(root == NULL)
	{
		return NULL;
	}
	FieldList head = NULL;
	if(root->childnum == 1)
	{
		//Dec
		root->child[0]->inhtype = root->inhtype;
		head = DecStruct(root->child[0]);
	}
	else if(root->childnum == 3)
	{
		//Dec comma DecList
		
		root->child[0]->inhtype = root->inhtype;
		root->child[2]->inhtype = root->inhtype;

		head = DecStruct(root->child[0]);
		head->tail = DecListStruct(root->child[2]);
		//Assert("sth need TODO",__FILE__,__LINE__);
	}
	return head;
}
FieldList DecStruct(Node *root)
{
	if(root == NULL)
		return NULL;
	
	if(root->childnum == 1)
	{
		//VarDec
		root->child[0]->inhtype = root->inhtype;
		Vtype temp = VarDec(root->child[0]);

		FieldList head = (FieldList)malloc(sizeof(struct FieldList_));
		strcpy(head->name,temp.name);
		head->type = temp.type;
		head->tail = NULL;
	}
	else
	{
		//VarDec ASSIGNOP EXP
		Assert("sth need TODO",__FILE__,__LINE__);
	}
}
void StructSpecifier(Node *root)
{
	if(root == NULL)
		return;
	//fprintf(stderr,"childnum: %d",root->childnum);
	if(root->childnum == 2)
	{
		//struct tag
		Assert("sth need TODO",__FILE__,__LINE__);

	}
	else if(root->childnum ==5)
	{
		if(root->child[1] == NULL)
		{
			//OptTag == NULL;
			return;
		}
		else
		{
			//fprintf(stderr,"test1");
			Stype newSt;
			Node *opt = root->child[1];
			strcpy(newSt.structname,opt->child[0]->idval);

			newSt.structtype.kind =STRUCTURE;
			newSt.structtype.u.structure = DefListStruct(root->child[3]);
			addStruct(newSt);//add new struct type;
		}
	}
	

}
void Specifier(Node *root)
{
	if(root == NULL)
		return;
	if(strcmp(root->child[0]->strval,"TYPE")== 0)
	{
		root->inhtype.kind = BASIC; 
		if(strcmp(root->child[0]->idval,"int") == 0)
		{	
			root->inhtype.u.basic = 1;//1 represent int 2 represent float;
		}
		else
		{
			root->inhtype.u.basic=2;//1 represent int 2 represent float;
		}
	}
	else
	{
		StructSpecifier(root->child[0]);
		//Assert("specifier struct",__FILE__,__LINE__);		
	}

}
void FunDec(Node *root)
{
	if(root == NULL)
		return;
	
	if(root->childnum == 4)
	{
		
	}
	else if(root->childnum == 3)
	{
		//ID LP RP
		Ftype newfun;
		strcpy(newfun.name,root->child[0]->idval);
		newfun.retn = root->inhtype;
		newfun.paranum = 0;
		addFun(newfun);
	}
	else
	{
		Assert("Should not reach",__FILE__,__LINE__);
	}
}
void CompSt(Node *root)
{
	if(root == NULL)
		return;
	
	DefList(root->child[1]);
	StmtList(root->child[2]);
}

void StmtList(Node *root)
{
	if(root == NULL)
		return;
	Stmt(root->child[0]);
	StmtList(root->child[1]);
}
void Stmt(Node *root)
{	
	if(root == NULL)
		return;
	
	if(root->childnum == 1)
	{
		//ComSt
		Assert("TODO",__FILE__,__LINE__);
	}
	else if(root->childnum == 2)
	{
		Exp(root->child[0]);
	}
	else
	{
		Assert("TODE",__FILE__,__LINE__);
	}
}
void Exp(Node *root)
{
	if(root == NULL)
		return;
	if(root->childnum == 1)
	{
		if(strcmp(root->child[0]->strval,"ID") == 0)
		{
			char *varname = root->child[0]->idval;
			Type vartype = checkVar(varname);
			if(vartype == NULL)
			{
				//fprintf(stderr,"Error type 1 at Line %d :Undefined variable \"%s\"\n",root->child[0]->linenum,root->child[0]->idval);
				errorPrint(1,root->linenum,root->child[0]->idval);
			}
			else
			{
				root->inhtype = *vartype;
			}
		}
		else if(strcmp(root->child[0]->strval,"INT") == 0)
		{
			root->inhtype.kind = BASIC;
			root->inhtype.u.basic = 1;
			//Assert("sth need todo ",__FILE__,__LINE__);
		}
		else if(strcmp(root->child[0]->strval,"FLOAT") == 0)
		{
			root->inhtype.kind=BASIC;
			root->inhtype.u.basic = 2;
			//Assert("sth need todo ",__FILE__,__LINE__);
		}
		else
		{
			Assert("should not reach",__FILE__,__LINE__);
		}
	}
	else if(root->childnum == 3)
	{
		if(strcmp(root->child[0]->strval,"Exp") ==0 )
		{
			Exp(root->child[0]);
			if(strcmp(root->child[1]->strval,"DOT")==0)
			{
				Exp(root->child[2]);
			}
		}
		else if(strcmp(root->child[0]->strval,"LP") == 0)
		{
			Exp(root->child[1]);
		}
		else if(strcmp(root->child[0]->strval,"ID") == 0)
		{
			//Exp -> ID LP RP
			if(checkFun(root->child[0]->idval) == 0 )
			{
				errorPrint(2,root->child[0]->linenum,root->child[0]->idval);
			}
			//Assert("sth need todo ",__FILE__,__LINE__);
		}
	}
	else if(root->childnum == 2)
	{
			Assert("sth need todo ",__FILE__,__LINE__);
	}
	else if(root->childnum == 4)
	{
			//Assert("sth need todo ",__FILE__,__LINE__);
	}
	else
	{
		Assert("should not reach",__FILE__,__LINE__);
	}
}
void DefList(Node *root)
{
	if(root == NULL)
		return;
	
	Def(root->child[0]);

	DefList(root->child[1]);

}
void Def(Node *root)
{
	if(root == NULL)
		return;
	Specifier(root->child[0]);
	Node *cld1 = root->child[0];
	Node *cld2 = root->child[1];

	cld2->inhtype = cld1->inhtype;
	DecList(root->child[1]);
}
void DecList(Node *root)
{
	if(root == NULL)
		return;
	root->child[0]->inhtype = root->inhtype;
	Dec(root->child[0]);
	if(root->childnum==3)
	{
		Assert("sth need todo",__FILE__,__LINE__);
		//DecList(root->child[2]);
	}
}
int IsFieldListEqual(FieldList T1,FieldList T2)
{
	if(T1 == NULL && T2 == NULL)
		return 1;
	else if(T1 ==NULL && T2 != NULL)
		return 0;
	else if(T1 != NULL && T2 == NULL)
		return 0;

	if(strcmp(T1->name,T2->name) != 0)
	{
		fprintf(stderr,"fieldlist name not equal");
		return 0;
	}
	else
	{
		if(IsTypeEqual(*T1->type,*T2->type) == 0)
		{
			return 0;
		}
		else
		{
			if(IsFieldListEqual(T1->tail,T2->tail) == 1)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
}
int IsTypeEqual(Type_ T1,Type_ T2)
{
	if(T1.kind != T2.kind)
		return 0;
	else
	{
		if(T1.kind == BASIC)
		{
			if(T1.u.basic == T2.u.basic)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if(T1.kind == ARRAY)
		{
			if(T1.u.array.size != T2.u.array.size)
			{
				return 0;
			}
			else
			{
				if(IsTypeEqual(*(T1.u.array.elem), *(T2.u.array.elem)) == 1)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
		else if(T1.kind == STRUCTURE)
		{
			if(IsFieldListEqual(T1.u.structure,T2.u.structure))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			Assert("should not reach",__FILE__,__LINE__);
		}
	}
}
void Dec(Node *root)
{
	if(root == NULL)
		return ;
	
	root->child[0]->inhtype = root->inhtype;

	if(root -> childnum == 3 )
	{
		Vtype newVar = VarDec(root->child[0]);

		Exp(root->child[2]);
		if(newVar.type == NULL)
		{
			Assert("Should not happen",__FILE__,__LINE__);
		}
		if(IsTypeEqual(*newVar.type, root->child[2]->inhtype) == 0)
		{
			errorPrint(5,root->child[2]->linenum,"u");
		}
		//Assert("sth need todo",__FILE__,__LINE__);
	}
	else if(root -> childnum == 1)
	{
		Vtype newVar = VarDec(root->child[0]);
		addVar(newVar);
	}
	else
	{
		Assert("should not reach",__FILE__,__LINE__);
	}
}
Vtype VarDec(Node *root)
{
	if(root == NULL)
	{
		Assert("should not reach",__FILE__,__LINE__);
		return ;
	}
	if(root->childnum == 1) //child is a ID
	{
		//add to symboltable;
		Vtype temp;
		strcpy(temp.name,root->child[0]->idval);
		temp.type = (Type)malloc(sizeof(struct Type_));
		*temp.type = root->inhtype;
		return temp;
	}
	else
	{
		//VarDec LB INT RB
		root->child[0]->inhtype = root->inhtype;
		Vtype temp = VarDec(root->child[0]);

		Type newt = (Type)malloc(sizeof(struct Type_));
		newt->kind = ARRAY;
		newt->u.array.elem =(Type)malloc(sizeof(struct Type_));
		*(newt->u.array.elem) = root->inhtype;
		newt->u.array.size = root->child[2]->intval;

		if(temp.type->kind != ARRAY)
		{
			temp.type=newt;
		}
		else
		{
			temp.type->u.array.elem = newt;
		}
		return temp;
		//Assert("sth need todo",__FILE__,__LINE__);
	}
}













