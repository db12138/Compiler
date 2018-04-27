#include "semantic.h"
#include "debug.h"
#include <stdio.h>
extern Vtype vartable[];
extern Ftype funtalbe[];

int addVar(Vtype);
int checkVar(char *);


void Program(Node *);
void ExtDefList(Node *);
void ExtDef(Node *);
void Specifier(Node *);
void FunDec(Node *);
void CompSt(Node *);
void DefList(Node *);
void Def(Node *);
void DecList(Node *);
void Dec(Node *);
void VarDec(Node *);
void StmtList(Node *);
void Stmt(Node *);
void Exp(Node *);

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

void ExtDef(Node *root)
{
	if(root == NULL)
		return;
	if(strcmp(root->child[1]->strval,"FunDec") == 0)
	{
		Specifier(root->child[0]);
		
		FunDec(root->child[1]);
		CompSt(root->child[2]);
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
		Assert("specifier struct",__FILE__,__LINE__);		
	}

}
void FunDec(Node *root)
{
	
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
		fprintf(stderr,"123");
		if(strcmp(root->child[0]->strval,"ID") == 0)
		{
			char *varname = root->child[0]->idval;
			if(checkVar(varname) == 0)
			{
				fprintf(stderr,"Error type 1 at Line %d :Undefined variable \"%s\"",root->child[0]->linenum,root->child[0]->idval);
			}
		}
		else if(strcmp(root->child[0]->strval,"INT") == 0)
		{
			Assert("sth need todo ",__FILE__,__LINE__);
		}
		else if(strcmp(root->child[0]->strval,"FLOAT") == 0)
		{
			Assert("sth need todo ",__FILE__,__LINE__);
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
			Assert("sth need todo ",__FILE__,__LINE__);
		}
	}
	else if(root->childnum == 2)
	{
			Assert("sth need todo ",__FILE__,__LINE__);
	}
	else if(root->childnum == 4)
	{
			Assert("sth need todo ",__FILE__,__LINE__);
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
void Dec(Node *root)
{
	if(root == NULL)
		return ;
	
	root->child[0]->inhtype = root->inhtype;

	if(root -> childnum == 3 )
	{
		Assert("sth need todo",__FILE__,__LINE__);
	}
	else if(root -> childnum == 1)
	{
		VarDec(root->child[0]);
	}
	else
	{
		Assert("should not reach",__FILE__,__LINE__);
	}
}
void VarDec(Node *root)
{
	if(root == NULL)
		return ;
	
	if(root->childnum == 1) //child is a ID
	{
		//add to symboltable;
		Vtype temp;
		temp.type = root->inhtype;
		strcpy(temp.name,root->child[0]->idval);
		addVar(temp);
	}
	else
	{
		Assert("sth need todo",__FILE__,__LINE__);
	}
}













