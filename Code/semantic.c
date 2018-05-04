#include "semantic.h"
#include "debug.h"
#include <stdio.h>
extern Vtype vartable[];
extern Ftype funtalbe[];

void errorPrint(int ,int ,char *); 
FieldList addStruct(Stype);
int addVar(Vtype);
Type checkVar(char *);
int addFun(Ftype);
Ftype * checkFun(char *);
Stype * checkStruct(char *);
int checkRedefine(char *);
int checkParamList(char *,FieldList);
Type_ getStructType(char *);
Type_ getArrayType(Type_);
void displayType(Type_ );
Type checkHasField(FieldList ,char*);
int checkRedef(char *);
int checkDec(Dtype,int);
int addDec(Dtype);

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
FieldList Args(Node *root);
void FunDecStatement(Node * root);

void StructSpecifier(Node *);
FieldList DefStruct(Node *);
FieldList DefListStruct(Node *);
FieldList DecListStruct(Node *);
FieldList DecStruct(Node *);

int DefOrSt=0;
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
		if(strcmp(root->child[2]->strval,"CompSt") == 0)
		{
			//specifier Fundec compSt
			Specifier(root->child[0]);
			root->child[1]->inhtype = root->child[0]->inhtype;

			FunDec(root->child[1]);
			root->child[2]->inhtype = root->child[0]->inhtype;
			CompSt(root->child[2]);
			if(root->child[2]->hasReturn == 0)
			{
				//int linenum = root->child[2]->child[3]->linenum;
				//errorPrint(8,linenum,"u");
			}
		}
		else if(strcmp(root->child[2]->strval,"SEMI") == 0)
		{
			//Specifier FunDec SEMI
			Specifier(root->child[0]);
			root->child[1]->inhtype = root->child[0]->inhtype;
			FunDecStatement(root->child[1]);
		}
		else
		{
			Assert("should not reach",__FILE__,__LINE__);
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
		//struct definition error
		//Assert("should not happen",__FILE__,__LINE__);
	}
	else
	{
		//find tail
		FieldList pi = head;
		for(;pi->tail != NULL;pi=pi->tail)
		{}
		//link
		pi->tail = DefListStruct(root->child[1]);
	}
	return head;

}
FieldList DefStruct(Node *root)
{
	if(root == NULL)
	{
		return NULL;
	}
	//Specifier DecList SEMI
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
		head->linenum = root->child[0]->linenum;
		head->type = temp.type;
		head->tail = NULL;
		//head = NULL;
		return head;
	}
	else
	{
		//VarDec ASSIGNOP EXP
		errorPrint(151,root->child[1]->linenum,"u");
		return NULL;
		//Assert("sth need TODO",__FILE__,__LINE__);
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
		Stype *j = checkStruct(tagid);
		if(j==NULL)
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
		//struct OptTag LC DefList RC
		if(root->child[1] == NULL)
		{
			//OptTag == NULL;
			Assert("sth need TODO",__FILE__,__LINE__);
			return;
		}
		else
		{
			Stype newSt;
			Node *opt = root->child[1];
			strcpy(newSt.structname,opt->child[0]->idval);

			newSt.structtype.kind =STRUCTURE;
			newSt.structtype.u.structure = DefListStruct(root->child[3]);
			
			int judge = checkRedef(newSt.structname);
			if(judge == 1)
			{
				//Redefination
				errorPrint(16,root->child[1]->linenum,root->child[1]->child[0]->idval);
			}
			else
			{
				FieldList J = addStruct(newSt);//check field and add new struct type;
				if(J != NULL)
				{
					//field redefined ,add new struct fail; 
					errorPrint(15,J->linenum,J->name);
				}
				else
				{
					//pass
					root->inhtype = newSt.structtype;
				}
			}
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
		if(DefOrSt == 0)
		{
			if(checkVar(newParam.name) == NULL)
			{
				addVar(newParam);
			}
			else
			{
				int linenum = root->child[1]->linenum;
				errorPrint(3,linenum,newParam.name);
			}
		}
		else
		{
			//statement
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
	DefOrSt = 0;
	if(root->childnum == 4)
	{
		//ID LP VarList RP
		Ftype newfun;
		strcpy(newfun.name,root->child[0]->idval);
		newfun.paralist = VarList(root->child[2]);
		newfun.retn =root->inhtype;
		FieldList pi = newfun.paralist;
		newfun.paranum = 0;
		for(;pi!=NULL;pi=pi->tail)
		{
			newfun.paranum++;
		}
		//check consisi with statement first
		Dtype forcheck;
		strcpy(forcheck.name,newfun.name);
		forcheck.retn = newfun.retn;
		forcheck.paranum = newfun.paranum;
		forcheck.paralist = newfun.paralist;
		forcheck.linenum = root->child[0]->linenum;
		checkDec(forcheck,DefOrSt);

		//check has defined? 
		Ftype * j = checkFun(newfun.name);
		if(j == NULL)
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
		Ftype * j = checkFun(newfun.name);
		//check consisi with statement first
		Dtype forcheck;
		strcpy(forcheck.name,newfun.name);
		forcheck.retn = newfun.retn;
		forcheck.paranum = newfun.paranum;
		forcheck.paralist = newfun.paralist;
		forcheck.linenum = root->child[0]->linenum;
		checkDec(forcheck,DefOrSt);

		if(j == NULL)
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
void FunDecStatement(Node * root)
{
	if(root == NULL)
		return;
	DefOrSt = 1;
	if(root->childnum == 4)
	{
		//ID LP VarList RP
		Dtype newdec;
		strcpy(newdec.name,root->child[0]->idval);
		newdec.paralist = VarList(root->child[2]);
		newdec.retn =root->inhtype;
		FieldList pi = newdec.paralist;
		newdec.paranum = 0;
		newdec.defined = 0;
		newdec.linenum = root->child[0]->linenum;
		for(;pi!=NULL;pi=pi->tail)
		{
			newdec.paranum++;
		}
		int  j = checkDec(newdec,DefOrSt); //errorPrint(19 into the Fuc)
		if(j == 0)
		{
			addDec(newdec);
		}
		else
		{
			//Do nothing
		}
	}
	else if(root->childnum == 3)
	{
		//ID LP RP
		Dtype newdec;
		strcpy(newdec.name,root->child[0]->idval);
		newdec.retn = root->inhtype;
		newdec.paranum = 0;
		newdec.paralist = NULL;
		newdec.defined = 0;
		newdec.linenum = root->child[0]->linenum;
		int j = checkDec(newdec,DefOrSt);//errorPrint(19 into the fuc)
		if(j == 0)
		{
			addDec(newdec);
		}
		else
		{
			//Do nothing 
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
	int p1 = root->child[0]->hasReturn;
	int p2 =0;
	if(root->child[1] == NULL)
	{
		
	}
	else
	{
		root->child[1]->inhtype = root->inhtype;
		StmtList(root->child[1]);
		p2 = root->child[1]->hasReturn;
	}
	if((p1 + p2) >= 1)
	{
		root->hasReturn = 1;
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
	else if(root->childnum == 3)
	{
		//RETURN Exp SEMI
		root->hasReturn = 1;

		Exp(root->child[1]);
		Type_ T1 = root->child[1]->inhtype;
		Type_ T2 = root->inhtype;
		//displayType(T1);
		//displayType(T2);

		if(IsTypeEqual(T1,T2) == 0)
		{
			errorPrint(8,root->child[0]->linenum,"u");
		}
		//Assert("TODE",__FILE__,__LINE__);
	}
	else if(root->childnum == 7)
	{
		Exp(root->child[2]);
		root->child[4]->inhtype = root->inhtype;
		Stmt(root->child[4]);
		root->child[6]->inhtype = root->inhtype;
		Stmt(root->child[6]);
	}
	else if(root ->childnum == 5)
	{
		if(strcmp(root->child[0]->strval,"IF") == 0)
		{
			Exp(root->child[2]);
			root->child[4]->inhtype = root->inhtype;
			Stmt(root->child[4]);
		}
		else if(strcmp(root->child[0]->strval,"WHILE") == 0)
		{	
			Exp(root->child[2]);
			root->child[4]->inhtype = root->inhtype;
			Stmt(root->child[4]);
		}
		else
		{
			Assert("should not reach here",__FILE__,__LINE__);
		}
		
	}
	else
	{
		Assert("should not reach here",__FILE__,__LINE__);
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
				//Exp DOT ID
				//Assert("sth neet todo ",__FILE__,__LINE__);
				if(root->child[0]->inhtype.kind != STRUCTURE)
				{
					errorPrint(13,root->child[1]->linenum,".");
				}
				else
				{
					//here must be  Exp->ID check
					if(strcmp(root->child[0]->child[0]->strval,"ID") ==0)
					{
						char *idname = root->child[0]->child[0]->idval;
						Type J = checkVar(idname);
						if(J == NULL)
						{
							Assert("should not reach here",__FILE__,__LINE__);

						}
						else
						{
							if(J->kind != STRUCTURE)
							{
							Assert("should not reach here",__FILE__,__LINE__);
								
							}
							FieldList pi = J->u.structure;
							char *fieldname = root->child[2]->idval;
							Type j2 = checkHasField(pi,fieldname);
							if( j2 == NULL)
							{
								errorPrint(14,root->child[2]->linenum,fieldname);
							}
							else
							{
								root->inhtype = *j2; 
								//pass
							}
						}
					}
					else
					{
						Assert("should not reach here",__FILE__,__LINE__);
					}
				}
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


					/*if(T1.kind == ARRAY && T2.kind != ARRAY)
					{
						//T1 type == array T2 type == basic
						Type_ tp1 = getArrayType(T1);
						//displayType(tp1);
						int J= IsTypeEqual(tp1,T2);
						if(J == 0)
						{
							
							int linenum = root->child[1]->linenum;
							errorPrint(5,linenum,"u");
						}
						else if(T1.u.array.elem->kind == ARRAY)
						{
							//basic type equal but basic assign to array
							fprintf(stderr,"tp1");
							int linenum =root->child[1]->linenum;
							errorPrint(5,linenum,"u");
						}
						else
						{
							//pass 
							root->inhtype = tp1;
						}

					}*/
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
			Ftype * checkj = checkFun(root->child[0]->idval);
			if(checkj  == NULL )
			{
				
				Type j1 = checkVar(root->child[0]->idval);
				if(j1 == NULL)
				{
					int linenum = root->child[0]->linenum;
					//function not defined
					errorPrint(2,linenum,root->child[0]->idval);
				}
				else
				{
					//not a function
					int linenum = root->child[0]->linenum;
					errorPrint(11,linenum,root->child[0]->idval);
				}
			}
			else
			{
				int j = checkParamList(root->child[0]->idval,NULL);
				if(j == 0)
				{
					errorPrint(9,root->child[1]->linenum,root->child[0]->idval);
				}
				else
				{
					//function call Exp->inhtype should be function return type;
					root->inhtype = checkj->retn;
				}
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
		if(strcmp(root->child[0]->strval,"ID") == 0)
		{
			//Assert("sth need todo ",__FILE__,__LINE__);
			//ID LP Args RP  function call
			Ftype * checkj = checkFun(root->child[0]->idval);
			if(checkj == NULL)
			{
				Type j1 = checkVar(root->child[0]->idval);
				if(j1 == NULL)
				{
					int linenum = root->child[0]->linenum;
					//function not defined
					errorPrint(2,linenum,root->child[0]->idval);
				}
				else
				{
					//not a function
					int linenum = root->child[0]->linenum;
					errorPrint(11,linenum,root->child[0]->idval);
				}
			}
			else
			{
				//check paramlist
				FieldList parahead = Args(root->child[2]);
				int j =checkParamList(root->child[0]->idval,parahead);
				if(j == 0) //not match
				{
					errorPrint(9,root->child[2]->linenum,root->child[0]->idval);
				}
				else
				{
					root->inhtype = checkj->retn;

				}

			}
		}
		else if(strcmp(root->child[0]->strval,"Exp") == 0)
		{
			//Exp LB Exp RB
			Exp(root->child[0]);
			if(root->child[0]->inhtype.kind != ARRAY)
			{
				errorPrint(10,root->child[0]->linenum,root->child[0]->child[0]->idval);
			}
			else
			{
				//not int
				Exp(root->child[2]);
				Type_ temp = root->child[2]->inhtype;
				if(temp.kind != BASIC)
				{
					//char err[30] = root->child[2]->child[0]->
					//I can add more error information
					errorPrint(12,root->child[2]->linenum,"u");
				}
				else if(temp.u.basic != 1)
				{
						errorPrint(12,root->child[2]->linenum,"u");
				}
				else
				{
					//pass
					//next level array or basic
					Type_ temp = *root->child[0]->inhtype.u.array.elem;
					root->inhtype = temp;
					fprintf(stderr,"tp1");
					displayType(root->inhtype);
				}
				
			}
		}
		else
		{
			Assert("should not reach",__FILE__,__LINE__);
		}
	}
	else
	{
		Assert("should not reach",__FILE__,__LINE__);
	}
}
FieldList Args(Node *root)
{
	if(root == NULL)
	{
		return NULL;
	}
	if(root->childnum == 3)
	{
		FieldList parahead = (FieldList)malloc(sizeof(struct FieldList_));
		parahead->tail = NULL;
		Exp(root->child[0]);
		parahead->type = (Type)malloc(sizeof(struct Type_));
		*(parahead->type) = root->child[0]->inhtype;
		parahead->tail = Args(root->child[2]);
		return parahead;
	}
	else if(root->childnum == 1)
	{
		FieldList parahead = (FieldList)malloc(sizeof(struct FieldList_));
		parahead->tail = NULL;
		Exp(root->child[0]);
		parahead->type = (Type)malloc(sizeof(struct Type_));
		*(parahead->type) = root->child[0]->inhtype;
		return parahead;
	}
	else
	{
		Assert("should not reach",__FILE__,__LINE__);
		return NULL;
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
		//Assert("sth need todo",__FILE__,__LINE__);
		root->child[2]->inhtype = root->inhtype;
		DecList(root->child[2]);
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
			return 0;
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
	else if(root->childnum == 4)
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
			Type p = temp.type;
			while(p->u.array.elem->kind == ARRAY)
			{
				p = p->u.array.elem;
			}
			//temp.type->u.array.elem = newt;
			//p->kind = ARRAY;
			p->u.array.elem = newt;
		}
		return temp;
		//Assert("sth need todo",__FILE__,__LINE__);
	}
	else
	{
		Assert("should not reach",__FILE__,__LINE__);
		Vtype init;
		return init;
	}
}













