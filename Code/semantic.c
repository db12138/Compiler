#include "semantic.h"
#include "debug.h"
#include <stdio.h>
extern Vtype vartable[];
extern Ftype funtalbe[];

int addVar(Vtype);



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
{}
void CompSt(Node *root)
{
	if(root == NULL)
		return;
	
	DefList(root->child[1]);

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













