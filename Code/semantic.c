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
int checkStruct(char *);
int checkRedefine(char *);
Type_ getStructType(char *);
void displayType(Type_ );

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
int IsFieldListEqual(FieldList T1,FieldList T2);
int IsTypeEqual(Type_ T1,Type_ T2);

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
		//specifier Fundec compSt
		Specifier(root->child[0]);
		root->child[1]->inhtype = root->child[0]->inhtype;

		FunDec(root->child[1]);
		root->child[2]->inhtype = root->child[0]->inhtype;
		CompSt(root->child[2]);
		if(root->child[2]->hasReturn == 0)
		{
			int linenum = root->child[2]->child[3]->linenum;
			errorPrint(8,linenum,"u");
		}
	}
	else if(strcmp(root->child[1]->strval,"SEMI") == 0)
	{
		//specifier SEMI
		Specifier(root->child[0]);
	}
	else if(strcmp(root->child[1]->strval,"ExtDecList") == 0)
	{
		//specifier ExtdecList
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
		char *tagid = root->child[1]->child[0]->idval;
		int linenum = root->child[1]->child[0]->linenum;
		int j = checkStruct(tagid);
		if(j==0)
		{
			errorPrint(17,linenum,tagid);
		}
		else
		{
			root->inhtype = getStructType(tagid);
		}
		//Assert("sth need TODO",__FILE__,__LINE__);

	}
	else if(root->childnum ==5)
	{
		if(root->child[1] == NULL)
		{
			//OptTag == NULL;
			Assert("sth need TODO",__FILE__,__LINE__);
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
			root->inhtype = newSt.structtype;
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
		root->inhtype = root->child[0]->inhtype;
		//Assert("specifier struct",__FILE__,__LINE__);		
	}

}
FieldList ParamDec(Node *root)
{
	if(root == NULL)
	{
		return NULL;
	}
	if(root->childnum == 2)
	{
		Specifier(root->child[0]);
		
		root->child[1]->inhtype = root->child[0]->inhtype;
		Vtype newParam = VarDec(root->child[1]);
		//add to vartable;
		if(checkVar(newParam.name) == NULL)
		{
			addVar(newParam);
		}
		else
		{
			int linenum = root->child[1]->linenum;
			errorPrint(3,linenum,newParam.name);
		}
		//return param type
		FieldList retn = (FieldList)malloc(sizeof(struct FieldList_));
		retn->tail = NULL;
		retn->type = newParam.type;
		strcpy(retn->name,newParam.name);
		return retn;
	}
	else
	{
		Assert("should not reach here",__FILE__,__LINE__);
		return NULL;
	}
}
FieldList VarList(Node *root)
{
	if(root == NULL)
	{
		return NULL;
	}
	if(root->childnum == 3)
	{
		//paramDec COMMA VarList
		FieldList retn = ParamDec(root->child[0]);
		retn->tail = VarList(root->child[2]);
		return retn;
	}
	else if(root->childnum == 1)
	{
		//paramDec
		FieldList temp = ParamDec(root->child[0]);
		return temp;
	}
	else
	{
		Assert("should not reach",__FILE__,__LINE__);
		return NULL;
	}
}
void FunDec(Node *root)
{
	if(root == NULL)
		return;
	
	if(root->childnum == 4)
	{
		//ID LP VarList RP
		Ftype newfun;
		strcpy(newfun.name,root->child[0]->idval);
		newfun.paralist = VarList(root->child[2]);
		newfun.retn = root->inhtype;
		FieldList pi = newfun.paralist;
		newfun.paranum = 0;
		for(;pi!=NULL;pi=pi->tail)
		{
			newfun.paranum++;
		}
		int j = checkFun(newfun.name);
		if(j == 0)
		{
			addFun(newfun);
		}
		else
		{
			errorPrint(4,root->child[0]->linenum,newfun.name);	
		}
	}
	else if(root->childnum == 3)
	{
		//ID LP RP
		Ftype newfun;
		strcpy(newfun.name,root->child[0]->idval);
		newfun.retn = root->inhtype;
		newfun.paranum = 0;
		newfun.paralist = NULL;
		int j = checkFun(newfun.name);
		if(j == 0)
		{
			addFun(newfun);
		}
		else
		{
			errorPrint(4,root->child[0]->linenum,newfun.name);	
		}
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

	if(root->child[2] == NULL)
		return;
	else
	{
		root->child[2]->inhtype = root->inhtype;
		StmtList(root->child[2]);
		root->hasReturn = root->child[2]->hasReturn;
	}
}

void StmtList(Node *root)
{
	if(root == NULL)
	{
		Assert("sth need todo",__FILE__,__LINE__);//return nothing
		return;
	}
	root->child[0]->inhtype = root->inhtype;
	Stmt(root->child[0]);
	root->hasReturn = root->child[0]->hasReturn;
	if(root->child[1] == NULL)
		return;
	else
	{
		root->child[1]->inhtype = root->inhtype;
		StmtList(root->child[1]);
	}
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
		//RETURN Exp SEMI
		root->hasReturn = 1;

		Exp(root->child[1]);
		Type_ T1 = root->child[1]->inhtype;
		Type_ T2 = root->inhtype;
		displayType(T1);
		displayType(T2);

		if(IsTypeEqual(T1,T2) == 0)
		{
			errorPrint(8,root->child[0]->linenum,"u");
		}
		//Assert("TODE",__FILE__,__LINE__);
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
			if(strcmp(root->child[1]->strval,"DOT") ==0)
			{
				Assert("sth neet todo ",__FILE__,__LINE__);
			}
			else
			{
				if(strcmp(root->child[1]->strval,"ASSIGNOP") == 0)
				{
					//Exp = Exp
					char *p = root->child[0]->child[0]->strval;
					//fprintf(stderr,"%s\n",p);
					if(strcmp(p,"INT") == 0 || strcmp(p,"FLOAT") == 0)
					{
						errorPrint(6,root->child[0]->linenum,"u");
					}
					Exp(root->child[2]);
					
					Type_ T1 = root->child[0]->inhtype;
					Type_ T2 = root->child[2]->inhtype;
					//displayType(T1);
					//displayType(T2);
					if(IsTypeEqual(T1,T2) == 0)
					{
						int linenum = root->child[1]->linenum;
						errorPrint(5,linenum,"u");
					}
					else
					{
						root->inhtype = root->child[0]->inhtype;
					}
				}
				else
				{
					//Exp  & || <> + - */ Exp
					Exp(root->child[2]);
					
					Type_ T1 = root->child[0]->inhtype;
					Type_ T2 = root->child[2]->inhtype;
					//displayType(T1);
					//displayType(T2);
					if(T1.kind != BASIC || T2.kind != BASIC)
					{
						//array or struct operand
						int linenum = root->child[1]->linenum;
						errorPrint(7,linenum,"u");
						root->inhtype = root->child[0]->inhtype;
					}
					else if(IsTypeEqual(T1,T2) == 0)
					{
						//int float operand
						int linenum = root->child[1]->linenum;
						errorPrint(7,linenum,"u");
					}
					else
					{
						root->inhtype = root->child[0]->inhtype;
					}
					
				}
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
			//ID LP Args RP  function call
			int j = checkFun(root->child[0]->idval);
			if(j == 0)
			{
				int linenum = root->child[0]->linenum;
				errorPrint(2,linenum,root->child[0]->idval);
			}
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
		//varDec ASSIGNOP Exp;
		Vtype newVar = VarDec(root->child[0]);
		//check redefine;
		int j = checkRedefine(newVar.name);
		if(j == 1)
		{
			int linenum = root->child[0]->linenum;
			errorPrint(3,linenum,newVar.name);
		}

		Exp(root->child[2]);
		if(newVar.type == NULL)
		{
			Assert("Should not happen",__FILE__,__LINE__);
		}
		//check type 
		if(IsTypeEqual(*newVar.type, root->child[2]->inhtype) == 0)
		{
			errorPrint(5,root->child[2]->linenum,"u");
		}
		else
		{
			addVar(newVar);
		}
		//Assert("sth need todo",__FILE__,__LINE__);
	}
	else if(root -> childnum == 1)
	{
		//VarDec
		Vtype newVar = VarDec(root->child[0]);
		int j = checkRedefine(newVar.name);
		if(j == 1)
		{
			int linenum = root->child[0]->linenum;
			errorPrint(3,linenum,newVar.name);
		}
		else
		{
			addVar(newVar);
		}
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
		Vtype init;
		return init;
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













