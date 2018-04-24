#include "semantic.h"

extern Vtable vartable[10000];
extern Ftable funtalbe[1000]

void Assert(char *);

void Program(Node *);
void ExtDefList(Node *);
void ExtDef(Node *);
void Specifier(Node *);
void FunDec(Node *);
void CompSt(Node *);
void DefList(Node *);
void Def(Node *);

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
	if(strcmp(root->child[0]->strval,"TYPE"))
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
		Assert("specifier struct");		
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
	cld1 = root->child[0];
	cld2 = root->child[1];

	cld2->inhtype = cld1->inhtype;
	DecList(root->child[1]);
}
void DecList(Node *root)
{
	if(root == NULL)
		return;
	

}














