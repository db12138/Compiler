#include "interCode.h"
#include "common.h"
#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


extern Node *Root;
IRCode * IRListHead = NULL;	
IRCode * IRListTail = NULL;
int labelsCount = 1;
int tempVarCount = 1;
int definedVarCount = 1;
BOOL IRError = FALSE;


IRCode * createIRCodeNode(IRKind kind) {
	IRCode * IR = (IRCode *)malloc(sizeof(IRCode));
        assert(IR != NULL);

        IR->kind = kind;
        IR->relop = NULL;
        IR->pre = NULL;
        IR->next = NULL;
        IR->opt1 = NULL;
        IR->opt2 = NULL;
        IR->result = NULL;

        return IR;
}

Operand * createOperand(OperandKind kind, char * symbolName) {
	Operand * operand = (Operand *)malloc(sizeof(Operand));
	assert(operand != NULL);
	memset(operand->symbolName, 0, BUFFERSIZE);
	operand->kind = kind;
	// funciton var tempvar ref int label
	switch(kind) {
		case OP_TEMP:
			sprintf(operand->symbolName, "t%d", tempVarCount++);
			break;
		case OP_VARIABLE:
		case OP_FUNCTION:
		case OP_REF:
			sprintf(operand->symbolName, "%s", symbolName);
			break;
		case OP_CONSTANT:
			sprintf(operand->symbolName, "%s", symbolName);
			break;
		case OP_LABEL:
			operand->u.var_no = labelsCount++;
			sprintf(operand->symbolName, "label%d", operand->u.var_no);
			break;
	}
	return operand;
}

Operand * dereference(Operand * operand) {
	if(operand == NULL) { return operand; }
	
	else if(operand->kind == OP_REF) {
		Operand * newOperand = createOperand(OP_TEMP, "");
		IRCode * ircode = createIRCodeNode(IR_DEREF_R);
		linkIRCode(ircode, newOperand, operand, NULL, NULL);
		return newOperand;
	}
	
	else { return operand; }
}

void linkIRCode(IRCode * IR, Operand * result, Operand * opt1, Operand * opt2, char * relop) {
	IR->result = result;
	IR->opt1 = opt1;
	IR->opt2 = opt2;
	IR->relop = relop;
	IRListTail->next = IR;
	IR->pre = IRListTail;
	IRListTail = IR;
}

void initAll() {
	if(IRListHead == NULL) {
		IRListHead = createIRCodeNode(IR_NOP);
		IRListTail = IRListHead;
	}
}

// Program : ExdefList
void translate_Program() {
	assert(Root != NULL);
	initAll();
	Node * exdeflist = Root->child[0];
	translate_ExtDefList(exdeflist);
}

// ExtDefList : ExtDef ExtDefList 
//    | epsilon
void translate_ExtDefList(Node * node) {
	if(node == NULL) { return; }

	translate_ExtDef(node->child[0]);
	translate_ExtDefList(node->child[1]);
}

// ExtDef : Specifier ExtDecList SEMI
//     | Specifier SEMI
//     | Specifier FunDec CompSt
void translate_ExtDef(Node * node) {
	assert(node != NULL);
	if(strcmp("SEMI", node->child[1]->strval)==0) {
			translate_Specifier(node->child[0]);
	}
	else if(strcmp("ExtDecList", node->child[1]->strval)==0) {
		translate_Specifier(node->child[0]);
		translate_ExtDecList(node->child[1]);
	}
	else if(strcmp("FunDec", node->child[1]->strval) == 0) {
		translate_Specifier(node->child[0]);
		translate_FunDec(node->child[1]);
		translate_CompSt(node->child[2]);
	}
}

// ExtDecList : VarDec
//     | VarDec COMMA ExtDecList
void translate_ExtDecList(Node * node) {
	if(node != NULL) {
		IRError = TRUE;
		fprintf(stderr, "Hypothesis 4: there is no global variables.\n");
	}
}


//////////////////////////////////////////////////////////
// TODO: STRUCT

// Specifier : TYPE
//    | StructSpecifier
void translate_Specifier(Node * node) {
	assert(node != NULL);
	if(strcmp(node->child[0]->strval,"TYPE") == 0)
	{
		//Do nothing
	}
	else //StructSpecifier
	{
		translate_StructSpecifier(node->child[0]);
		node->inhtype = node->child[0]->inhtype;
	}

	/*switch(node->type) {
		case 2: // int
			break;
		case 3: // float
			IRError = TRUE;
			fprintf(stderr, "Hypothesis 1: there is no float defination.\n");
			break;
		case 0: //TODO: struct??? 
			break;
	}*/	
}

// StructSpecifier : STRUCT OptTag LC DefList RC
//    | STRUCT Tag
FieldList DefListStruct(Node *);
int getStructSize(Type_);
Stype* checkStruct(char *);
FieldList addStruct(Stype);
void displayType(Type_);
void translate_StructSpecifier(Node * node) {
	assert(node != NULL);
	// struct defination
	if(node->childnum == 5) {
		Type_ newType;
		newType.kind = STRUCTURE;
		newType.u.structure = DefListStruct(node->child[3]);
		node->inhtype = newType;

		if(node->child[1]->child[0] != NULL)
		{
			char *sname = node->child[1]->child[0]->idval;
			Stype newStruct;
			strcpy(newStruct.structname,sname);
			newStruct.structtype = newType;
			addStruct(newStruct);
		}
		return;
	}
	else {
		char * id = node->child[1]->child[0]->idval;

		Stype* stype = checkStruct(id);
		if(stype == NULL)
		{
			fprintf(stderr," struct : %s not defined\n",id);
		}
		else
		{
			node->inhtype = stype->structtype;
		}
		//Operand * sizeStruct = createOperand(OP_CONSTANT,size);
		//linkIRCode(createIRCodeNode(IR_DEC),decStruct,sizeStruct,NULL,NULL);
		// new IRNode and new result just like : DEC v3 8 t9 := &v3
		;
	}
}

// OptTag : ID
//    |epsilon
void translate_OptTag(Node * node) {
	if(node == NULL)
		return;
	else {
		;	
	}
}

// Tag : ID
void translate_Tag(Node * node) {
	;
}

///////////////////////////////////////////////////////////////



// VarDec : ID
//    | VarDec LB INT RB
char * translate_VarDec(Node * node, BOOL isParam) {
	assert(node != NULL);
	
		//printf("In VarDec, nodetype = %d childtype = %d\n", node->type, node->child[0]->type);
	//Struct Type ADD TO irTable
	
	if(node->childnum == 1 && node->inhtype.kind == STRUCTURE) 
	{
		addirTable(node->child[0]->idval,node->inhtype);
		Operand *re = createOperand(OP_VARIABLE,node->child[0]->idval);
		
		char *size = malloc(128);
		int s = getStructSize(node->inhtype);
		sprintf(size,"%d",s);

		Operand *op1 = createOperand(OP_CONSTANT,size);
		linkIRCode(createIRCodeNode(IR_DEC),re,op1,NULL,NULL);
	}
	else if(node->childnum==4)
	{
		node->child[0]->inhtype = node->inhtype;
	}
	// ID
	if(node->child[0]->type == 4) {
		if(isParam == TRUE) {
			Operand * operand = createOperand(OP_VARIABLE, node->child[0]->idval);
			operand->isParam = TRUE;
			IRCode * ircode = createIRCodeNode(IR_PARAM);
			linkIRCode(ircode, operand, NULL, NULL, NULL);			
		}
		//printf("in VarDec, child idval %s\n", node->child[0]->idval);
		return node->child[0]->idval;
	}
	// Array, one dimension 
	else {
		char * name = translate_VarDec(node->child[0], FALSE);
		// not one dimension, there need to print error info.
		if(name == NULL) {
			fprintf(stderr, "Hypothesis 2: there should not exist high dimension array.\n");
			IRError = TRUE;
			return NULL;
		}		
		if(isParam == TRUE) {
 			char * newname = malloc(BUFFERSIZE);
                        sprintf(newname, "v%d", definedVarCount++);
			Operand * operand = createOperand(OP_REF, newname);
			operand->isParam = TRUE;
			IRCode * ircode = createIRCodeNode(IR_PARAM);
			linkIRCode(ircode, operand, NULL, NULL, NULL);
		} 
		// local defination , DEC array size
		else {
			char * Sintval = malloc(BUFFERSIZE);
			sprintf(Sintval, "%d", 4*node->child[2]->intval);
			Operand * size = createOperand(OP_CONSTANT, Sintval);
			Operand * arr = createOperand(OP_REF, name);
			IRCode * ircode = createIRCodeNode(IR_DEC);
			linkIRCode(ircode, arr, size, NULL, NULL);
		}
	return NULL;
	}
}

//FunDec : ID LP VarList RP 
//    | ID LP RP
void translate_FunDec(Node * node) {
	assert(node != NULL);
	Operand * operand = createOperand(OP_FUNCTION, node->child[0]->idval);
	IRCode * ircode = createIRCodeNode(IR_FUNC_DEFINED);
	linkIRCode(ircode, operand, NULL, NULL, NULL);
	if(node->childnum == 4) {
		translate_VarList(node->child[2]);
	}
}

//VarList : ParamDec COMMA VarList 
//    | ParamDec
void translate_VarList(Node * node) {
	if(node == NULL) { return; }
	translate_ParamDec(node->child[0]);
	if(node->childnum == 3) {
		translate_VarList(node->child[2]);
	}
}

//ParamDec : Specifier VarDec
void translate_ParamDec(Node * node) {
	assert(node != NULL);
	translate_Specifier(node->child[0]);
	// is Param
	translate_VarDec(node->child[1], TRUE);
}


// CompSt : LC DefList StmtList RC 
void translate_CompSt(Node * node) {
	assert(node != NULL);
	translate_DefList(node->child[1]);
	translate_StmtList(node->child[2]);
}

// StmtList : Stmt StmtList
//   | epsilon
void translate_StmtList(Node * node) {
	if(node == NULL) { return; }
	assert(strcmp(node->strval, "StmtList") == 0);
	translate_Stmt(node->child[0]);
	translate_StmtList(node->child[1]);
}

// process 'IF [relop] ELSE STMT...' and other conditional jump we need.
void translate_ExpConditional(Node * node, Operand * labelTRUE, Operand * labelFALSE) {
	assert(node != NULL);
	
	// Exp AND Exp
	if(strcmp(node->child[1]->strval, "AND") == 0) {
		Operand * labeltrueNOW = createOperand(OP_LABEL, "");
		translate_ExpConditional(node->child[0], labeltrueNOW, labelFALSE);
		IRCode * ircode = createIRCodeNode(IR_LABEL);
		linkIRCode(ircode, labeltrueNOW, NULL, NULL, NULL);
		translate_ExpConditional(node->child[2], labelTRUE, labelFALSE);
		return ;
	}
	// Exp OR Exp
	else if(strcmp(node->child[1]->strval, "OR") == 0) {
		Operand * labelfalseNOW = createOperand(OP_LABEL, "");
		translate_ExpConditional(node->child[0], labelTRUE, labelfalseNOW);
		IRCode * ircode = createIRCodeNode(IR_LABEL);
		linkIRCode(ircode, labelfalseNOW, NULL, NULL, NULL);
		translate_ExpConditional(node->child[2], labelTRUE, labelFALSE);
	}
	// NOT Exp
	else if(strcmp(node->child[1]->strval, "NOT") == 0) {
		translate_ExpConditional(node, labelFALSE, labelTRUE);
		return ;
	}
	// Exp RELOP Exp
	else if(strcmp(node->child[1]->strval, "RELOP") == 0) {
		Operand * opt1 = createOperand(OP_TEMP, "");
		Operand * opt2 = createOperand(OP_TEMP, "");
		opt1 = translate_Exp(node->child[0], OP_TEMP);
		opt2 = translate_Exp(node->child[2], OP_TEMP);
		opt1 = dereference(opt1);
		opt2 = dereference(opt2);
		IRCode * ircodeTrue = createIRCodeNode(IR_IF_GOTO);
		linkIRCode(ircodeTrue, labelTRUE, opt1, opt2, node->child[1]->idval);
		IRCode * ircodeFalse = createIRCodeNode(IR_GOTO);
		linkIRCode(ircodeFalse, labelFALSE, NULL, NULL, NULL);
		return ;
	}
	// Exp
	else {
		Operand * operand = createOperand(OP_TEMP, "");
		operand = translate_Exp(node, OP_TEMP);
		operand = dereference(operand);
		Operand * zero = createOperand(OP_VARIABLE, "0");
		IRCode * ircodeTrue = createIRCodeNode(IR_IF_GOTO);
		linkIRCode(ircodeTrue, labelTRUE, operand, zero, "!=");
		IRCode * ircodeFalse = createIRCodeNode(IR_GOTO);
		linkIRCode(ircodeFalse, labelFALSE, NULL, NULL, NULL);
		return ;
	}
}

// Stmt : Exp SEMI
//     | CompSt
//     | RETURN Exp SEMI
//     | IF LP Exp RP Stmt
//     | IF LP Exp RP Stmt ELSE Stmt
//     | WHILE LP Exp RP Stmt
void translate_Stmt(Node * node) {
	assert(node != NULL);
	//printf("In Stmt\n");
	switch(node->childnum) {
		//     | CompSt
		case 1:
			translate_CompSt(node->child[0]);
			break;
		//     | Exp SEMI
		case 2:
			//printf("In Stmt, Exp SEMI\n");
			translate_Exp(node->child[0], OP_NOP);
			break;
		//     | RETURN Exp SEMI
		case 3: {
			Operand * operand = createOperand(OP_TEMP, "");
			operand = translate_Exp(node->child[1], OP_TEMP);
			IRCode * ircode = createIRCodeNode(IR_RETURN);
			operand = dereference(operand);
			linkIRCode(ircode, operand, NULL, NULL, NULL);
			break;
		}
		//     | IF LP Exp RP Stmt
		//     | WHILE LP Exp RP Stmt
		case 5:
			if(strcmp(node->child[0]->strval, "IF") == 0) {
				//printf("In Stmt if not else\n");
				Operand * labelTRUE = createOperand(OP_LABEL, "");
				Operand * labelFALSE = createOperand(OP_LABEL, "");
				translate_ExpConditional(node->child[2], labelTRUE, labelFALSE);
				IRCode * ircode1 = createIRCodeNode(IR_LABEL);
				linkIRCode(ircode1, labelTRUE, NULL, NULL, NULL);
				translate_Stmt(node->child[4]);
				IRCode * ircode2 = createIRCodeNode(IR_LABEL);
				linkIRCode(ircode2, labelFALSE, NULL, NULL, NULL);
			}
			else if(strcmp(node->child[0]->strval, "WHILE") == 0){
				Operand * beginLabel = createOperand(OP_LABEL, "");
				Operand * labelTRUE = createOperand(OP_LABEL, "");
				Operand * labelFALSE = createOperand(OP_LABEL, "");
				IRCode * IRBegin = createIRCodeNode(IR_LABEL);
				linkIRCode(IRBegin, beginLabel, NULL, NULL, NULL);
				translate_ExpConditional(node->child[2], labelTRUE, labelFALSE);
				IRCode * ircodeTrue = createIRCodeNode(IR_LABEL);
				linkIRCode(ircodeTrue, labelTRUE, NULL, NULL, NULL);
				translate_Stmt(node->child[4]);
				IRCode * ircodeGOTO = createIRCodeNode(IR_GOTO);
				linkIRCode(ircodeGOTO, beginLabel, NULL, NULL, NULL);
				IRCode * ircodeFalse = createIRCodeNode(IR_LABEL);
				linkIRCode(ircodeFalse, labelFALSE, NULL, NULL, NULL);
			}
			else {
				Assert("Should not be here.", __FILE__, __LINE__);
			}
			break;
		//     | IF LP Exp RP Stmt ELSE Stmt
		case 7: {
			Operand * labelTRUE = createOperand(OP_LABEL, "");
                        Operand * labelFALSE = createOperand(OP_LABEL, "");
                        Operand * labelELSE = createOperand(OP_LABEL, "");
			translate_ExpConditional(node->child[2], labelTRUE, labelFALSE);
			IRCode * ircodeTrue = createIRCodeNode(IR_LABEL);
                        linkIRCode(ircodeTrue, labelTRUE, NULL, NULL, NULL);			
			translate_Stmt(node->child[4]);
                        IRCode * ircodeGOTO = createIRCodeNode(IR_GOTO);
                        linkIRCode(ircodeGOTO, labelELSE, NULL, NULL, NULL);
			IRCode * ircodeFalse = createIRCodeNode(IR_LABEL);
                        linkIRCode(ircodeFalse, labelFALSE, NULL, NULL, NULL);
			translate_Stmt(node->child[6]);
			IRCode * ircodeELSE = createIRCodeNode(IR_LABEL);
                        linkIRCode(ircodeELSE, labelELSE, NULL, NULL, NULL);
			break;
		}
		default:
			assert(0);
			break;
	}
}


// DefList : Def DefList 
//    | epsilon
void translate_DefList(Node * node) {
	if(node == NULL) { return ; }

	translate_Def(node->child[0]);
	translate_DefList(node->child[1]);
}

// Def : Specifier DecList SEMI 
void translate_Def(Node * node) {
	assert(node != NULL);
	//printf("In Def\n");	
	translate_Specifier(node->child[0]);
	node->child[1]->inhtype = node->child[0]->inhtype;
	translate_DecList(node->child[1]);
}

// DecList : Dec
//    | Dec COMMA DecList 
void translate_DecList(Node * node) {
	//printf("In DecList\n");
	node->child[0]->inhtype = node->inhtype;
	if(node->childnum == 1) {
		translate_Dec(node->child[0]);
	}
	else if(node->childnum == 3) {
		translate_Dec(node->child[0]);
		node->child[2]->inhtype = node->inhtype;
		translate_DecList(node->child[2]);
	}
	else {
		Assert("Should not be here.", __FILE__, __LINE__);
	}
}

// Dec : VarDec
//     | VarDec ASSIGNOP Exp
void translate_Dec(Node * node) {
	assert(node != NULL);
		
	node->child[0]->inhtype = node->inhtype;
	//printf("In Dec, childnum = %d\n", node->childnum);
	char * vardec = translate_VarDec(node->child[0], FALSE);
	
		//printf("In Dec, %s\n", vardec);
	if(node->childnum == 3) {

		if(vardec != NULL) {
			Operand * operand = createOperand(OP_VARIABLE, vardec);
			Operand * op = translate_Exp(node->child[2], OP_TEMP);
			linkIRCode(createIRCodeNode(IR_ASSIGN), operand, op, NULL, NULL);
		}
		// local array
		else {
			;	
		}
	}
	// VarDec
	else {
		return ;
	}
}


// Exp : Exp ASSIGNOP Exp 
//     | Exp AND Exp
//     | Exp OR Exp
//     | Exp RELOP Exp
//     | Exp PLUS Exp
//     | Exp MINUS Exp
//     | Exp STAR Exp
//     | Exp DIV Exp
//     | LP Exp RP
//     | ID LP RP
//     | Exp DOT ID

//     | MINUS Exp
//     | NOT Exp

//     | ID LP Args RP
//     | Exp LB Exp RB

//     | ID
//     | INT
//     | FLOAT
char *getFieldOffset(Type,char *);
Type getVarType(char *);
Operand * translate_Exp(Node * node, OperandKind kind) {
	assert(node != NULL);
	
	Operand * temp = NULL;
	switch(kind) {
		case OP_TEMP:
			temp = createOperand(OP_TEMP, "");
			break;
		case OP_VARIABLE:{
			temp = createOperand(OP_VARIABLE, node->child[0]->idval);
			break;
		}
		case OP_NOP:
		case OP_REF:
			break;
		default:
			Assert("Should not be here.", __FILE__, __LINE__);
	}

	switch(node->childnum) {
		//     | ID
		//     | INT
		//     | FLOAT forbiden
		case 1:
			// ID : var or array
			if(strcmp(node->child[0]->strval, "ID") == 0) {
				Operand * operand = createOperand(OP_VARIABLE, node->child[0]->idval);
				temp = operand;
				/*
				// BASIC:int 
				if(node->child[0]->inhtype.kind == 0) {
					if(kind == OP_TEMP)
						temp->kind = OP_VARIABLE;
					else {
						IRCode * ircode = createIRCodeNode(IR_ASSIGN);
						linkIRCode(ircode, temp, operand, NULL, NULL); 
					}
				}
				// array, should be a pointer
				else {
					operand->kind = OP_REF;
					temp->kind = OP_REF;
					IRCode * ircode = createIRCodeNode(IR_REF);
					linkIRCode(ircode, temp, operand, NULL, NULL);
				}
				*/
			}
			// INT
			else if(strcmp(node->child[0]->strval, "INT") == 0) {
				if(kind == OP_TEMP || kind == OP_REF) {
					temp->kind = OP_CONSTANT;
					sprintf(temp->symbolName, "#%d", node->child[0]->intval);
				}
				else {
					IRCode * ircode = createIRCodeNode(IR_ASSIGN);
					char * constant = malloc(BUFFERSIZE);
					sprintf(constant, "#%d", node->child[0]->intval);
					Operand * opt = createOperand(OP_CONSTANT, constant);
					linkIRCode(ircode, temp, opt, NULL, NULL);
				}
			}
			else {
				IRError = TRUE;
				fprintf(stderr, "Float variable is not allowed.\n");
				return NULL;
			}
			break;
		//     | MINUS Exp 
		//     | NOT Exp  
		case 2:
			if(strcmp(node->child[0]->strval, "NOT") == 0) {
				Operand * labelTRUE = createOperand(OP_LABEL, "");
                                Operand * labelFALSE = createOperand(OP_LABEL, "");
                                Operand * zero = createOperand(OP_VARIABLE, "0");
                                Operand * one = createOperand(OP_VARIABLE, "1");
                                linkIRCode(createIRCodeNode(IR_ASSIGN), temp, zero, NULL, NULL);
                                translate_ExpConditional(node, labelTRUE, labelFALSE);
                                linkIRCode(createIRCodeNode(IR_LABEL), labelTRUE, NULL, NULL, NULL);
                                linkIRCode(createIRCodeNode(IR_ASSIGN), temp, one, NULL, NULL);
                                linkIRCode(createIRCodeNode(IR_LABEL), labelFALSE, NULL, NULL, NULL);
			}
			else {

				Operand * opt = createOperand(OP_TEMP, "");
				Operand * zero = createOperand(OP_VARIABLE, "#0");
				opt = dereference(translate_Exp(node->child[1], OP_TEMP));
				linkIRCode(createIRCodeNode(IR_SUB), temp, zero, opt, "-");
			}
			break;
		// Exp : Exp ASSIGNOP Exp 

		//     | Exp PLUS Exp
		//     | Exp MINUS Exp
		//     | Exp STAR Exp
		//     | Exp DIV Exp
		
		//     | Exp AND Exp
		//     | Exp OR Exp
		//     | Exp RELOP Exp

		//     | LP Exp RP   TODO
		//     | ID LP RP
		//     | Exp DOT ID  TODO
		case 3: {
			if(strcmp(node->child[1]->strval,"DOT") == 0)
			{
				if(strcmp(node->child[0]->child[0]->strval,"ID") == 0)
				{
					char *newname = malloc(BUFFERSIZE);
					Operand *re = createOperand(OP_TEMP,newname);
					re->kind = OP_REF;
					char *varname = node->child[0]->child[0]->idval;
					Operand *base = createOperand(OP_VARIABLE,varname);

					Type vtype = getVarType(varname);
					if(vtype == NULL)
					{
						fprintf(stderr,"should not happen,%s,%d\n",__FILE__,__LINE__);
					}
					else if(vtype->kind != STRUCTURE)
					{
						fprintf(stderr,"not struct\n");
					}

					char *fieldName = node->child[2]->idval;
					char *offs = getFieldOffset(vtype,fieldName);
					Operand *offset = createOperand(OP_CONSTANT,offs);
					
					linkIRCode(createIRCodeNode(IR_REF),re,base,offset,NULL);
					return re;
				}
				else
				{
					fprintf(stderr,"linenum:%d ,Exp DOT need todo\n",node->linenum);
				}
			}
			// ASSIGN
			else if(strcmp(node->child[1]->strval, "ASSIGNOP") == 0) {
				IRCode * irAssign = NULL;
				Operand * operandL = createOperand(OP_TEMP, "");
				operandL = translate_Exp(node->child[0], OP_TEMP);
				switch(operandL->kind) {
					case OP_VARIABLE:
					case OP_TEMP:{	
						Operand * operandR = translate_Exp(node->child[2], OP_TEMP);
                	                        IRCode * ircode = createIRCodeNode(IR_ASSIGN);
        	                                operandR = dereference(operandR);
	                                        linkIRCode(ircode, operandL, operandR, NULL, NULL);
						break;
					}
					case OP_REF: {
						//Operand * operandT = createOperand(OP_TEMP, "");
						//Operand * opt2 = createOperand(OP_TEMP, "");
						Operand* opt2 = translate_Exp(node->child[2], OP_TEMP);
						IRCode * ircode1 = createIRCodeNode(IR_DEREF_L);
						opt2 = dereference(opt2);
						linkIRCode(ircode1, operandL, opt2, NULL, NULL);
                	                   //     IRCode * ircode2 = createIRCodeNode(IR_ASSIGN);
        	                             //   operandT = dereference(operandT);
	                                      //  linkIRCode(ircode2, operandL, operandT, NULL, NULL);
						break;
					}
					default:	
						Assert("Not here.", __FILE__, __LINE__);
				}
				if(temp == NULL) {
					return NULL;
				}
			}
			// PLUS / SUB / STAR / DIV
			else if(strcmp(node->child[1]->strval, "PLUS") == 0 || strcmp(node->child[1]->strval, "MINUS") == 0 || strcmp(node->child[1]->strval, "STAR") == 0 || strcmp(node->child[1]->strval, "DIV") == 0) {
				Operand * opt1 = createOperand(OP_TEMP, "");
                                Operand * opt2 = createOperand(OP_TEMP, "");
				opt1 = translate_Exp(node->child[0], OP_TEMP);
				opt2 = translate_Exp(node->child[2], OP_TEMP);
				opt1 = dereference(opt1);
				opt2 = dereference(opt2);
				if(strcmp(node->child[1]->strval, "PLUS") == 0)
					linkIRCode(createIRCodeNode(IR_ADD), temp, opt1, opt2, "+");
				else if(strcmp(node->child[1]->strval, "MINUS") == 0)
					linkIRCode(createIRCodeNode(IR_SUB), temp, opt1, opt2, "-");
				else if(strcmp(node->child[1]->strval, "STAR") == 0) 
					linkIRCode(createIRCodeNode(IR_MUL), temp, opt1, opt2, "*");
				else if(strcmp(node->child[1]->strval, "DIV") == 0)
					linkIRCode(createIRCodeNode(IR_DIV), temp, opt1, opt2, "/");
			}
			else if(strcmp(node->child[1]->strval, "AND") == 0 || strcmp(node->child[1]->strval, "OR") == 0 || strcmp(node->child[1]->strval, "RELOP") == 0) {
				Operand * labelTRUE = createOperand(OP_LABEL, "");
				Operand * labelFALSE = createOperand(OP_LABEL, "");
				Operand * zero = createOperand(OP_VARIABLE, "0");
				Operand * one = createOperand(OP_VARIABLE, "1");
				linkIRCode(createIRCodeNode(IR_ASSIGN), temp, zero, NULL, NULL);
				translate_ExpConditional(node, labelTRUE, labelFALSE);
				linkIRCode(createIRCodeNode(IR_LABEL), labelTRUE, NULL, NULL, NULL);
				linkIRCode(createIRCodeNode(IR_ASSIGN), temp, one, NULL, NULL);
				linkIRCode(createIRCodeNode(IR_LABEL), labelFALSE, NULL, NULL, NULL);
			}
			// call functions
			else if(strcmp(node->child[0]->strval, "ID") == 0) {
				char * funcName = node->child[0]->idval;
				if(strcmp(funcName, "read") == 0) {
					Operand * op = createOperand(OP_TEMP, "");
					linkIRCode(createIRCodeNode(IR_READ), op, NULL, NULL, NULL);
					return op;
				} else {
                                	Operand * opfunc = createOperand(OP_FUNCTION, node->child[0]->idval);
					Operand * op = createOperand(OP_TEMP, "");
                                        linkIRCode(createIRCodeNode(IR_CALL), op, opfunc, NULL, NULL);
					return op;
				}
			}
			// LP Exp RP
			else if(strcmp(node->child[0]->strval, "LP") == 0) {
 				temp = translate_Exp(node->child[1], OP_TEMP);
			}
		}			
			break;
		//     | ID LP Args RP
		//     | Exp LB Exp RB
		case 4:
			// func
			if(strcmp(node->child[0]->strval, "ID") == 0) {
                                char * funcName = node->child[0]->idval;
				if(strcmp(funcName, "write") == 0) {
					Operand * arg = createOperand(OP_TEMP, "");
					arg = translate_Args_write(node->child[2]);
					arg = dereference(arg);
					linkIRCode(createIRCodeNode(IR_WRITE), arg, NULL, NULL, NULL);
					//TODO: write has returns to assign x=write(y)?
				} else {
					translate_Args(node->child[2]);
					Operand * opfunc = createOperand(OP_FUNCTION, node->child[0]->idval);
					char * newname = malloc(BUFFERSIZE);
					Operand *re = createOperand(OP_TEMP,newname);
					linkIRCode(createIRCodeNode(IR_CALL), re, opfunc, NULL, NULL);
					return re;
				}
			}
			//Exp -> Exp LB Exp RB
			else if(strcmp(node->child[0]->strval, "Exp") == 0) {
				char *rename = malloc(BUFFERSIZE); 
				Operand *re = createOperand(OP_TEMP,rename);
				
				Operand *base = translate_Exp(node->child[0],OP_TEMP);
				Operand *index = translate_Exp(node->child[2],OP_TEMP);

				char *ofname = malloc(BUFFERSIZE);
				Operand *offset = createOperand(OP_TEMP,ofname);

				//getTypeSize()
				linkIRCode(createIRCodeNode(IR_MUL),offset,index,createOperand(OP_CONSTANT,"#4"),NULL);
				linkIRCode(createIRCodeNode(IR_REF),re,base,offset,NULL);
				re->kind = OP_REF;
				return re;
				/*Operand * baseArr = createOperand(OP_TEMP, "");
				baseArr = translate_Exp(node->child[0], OP_TEMP);
				Operand * index = createOperand(OP_TEMP, "");
				index = translate_Exp(node->child[2], OP_TEMP);
				Operand * elementsize = createOperand(OP_CONSTANT, "#4");
				Operand * offset = createOperand(OP_TEMP, "");
				linkIRCode(createIRCodeNode(IR_MUL), offset, elementsize, index, "*");
				if(temp->kind == OP_TEMP || temp->kind == OP_REF) {
					temp->kind = OP_REF;
					linkIRCode(createIRCodeNode(IR_ADD), temp, baseArr, offset, "+");
				}	
				else {
					assert(temp->kind == OP_VARIABLE); // should be a variable so can be assigned
					Operand * tempRef = createOperand(OP_TEMP, "");
					tempRef->kind = OP_REF;
					linkIRCode(createIRCodeNode(IR_ADD), tempRef, baseArr, offset, "+");
					linkIRCode(createIRCodeNode(IR_DEREF_R), temp, tempRef, NULL, NULL);
				}*/
			}
			break;
	}	

	return temp;
}

// Args : Exp COMMA Args 
//     | Exp
Operand * translate_Args(Node * node) {
	if(node->childnum == 1) {
		Operand * op = translate_Exp(node->child[0], OP_TEMP);
		if(op->kind == OP_REF)
		{
			linkIRCode(createIRCodeNode(IR_ARG_REF),op,NULL,NULL,NULL);
		}
		else
		{
			linkIRCode(createIRCodeNode(IR_ARG),op,NULL,NULL,NULL);
		}
		return op;
	}
	else {
		translate_Args(node->child[2]);
		Operand * op = translate_Exp(node->child[0], OP_TEMP);
		if(op->kind == OP_REF)
		{
			linkIRCode(createIRCodeNode(IR_ARG_REF),op,NULL,NULL,NULL);
		}
		else
		{
			linkIRCode(createIRCodeNode(IR_ARG),op,NULL,NULL,NULL);
		}
		return op;
	}
}
Operand * translate_Args_write(Node * node) {
	if(node->childnum == 1) {
		Operand * op = translate_Exp(node->child[0], OP_TEMP);
		return op;
	}
	else {
		//TODO: this is not correct!!!
                Operand * op = translate_Exp(node->child[0], OP_TEMP);
		translate_Args(node->child[2]);
		return NULL;
	}
}


void printLine(FILE * out, IRCode * current) {
	switch(current->kind) {
		case IR_NOP :
			break;
		case IR_LABEL :
			fprintf(out, " LABEL %s : \n", current->result->symbolName);
			break;

		// case about function
		case IR_FUNC_DEFINED :
			fprintf(out, " FUNCTION %s : \n", current->result->symbolName);
			break;
                case IR_CALL :
                        fprintf(out, " %s := CALL %s \n", current->result->symbolName, current->opt1->symbolName);
                        break;
                case IR_RETURN :
                        fprintf(out, " RETURN %s \n", current->result->symbolName);
                        break;
                case IR_PARAM :
                        fprintf(out, " PARAM %s \n", current->result->symbolName);
                        break;
                case IR_ARG :
                        fprintf(out, " ARG %s \n", current->result->symbolName);
                        break;
				case IR_ARG_REF:
                        fprintf(out, " ARG *%s \n", current->result->symbolName);
						break;

		// case about assign operation
                case IR_ASSIGN :
                        fprintf(out, " %s := %s \n", current->result->symbolName, current->opt1->symbolName);
                        break;

		// case about Arithmetic
                case IR_ADD :
                        fprintf(out, " %s := %s + %s \n", current->result->symbolName, current->opt1->symbolName, current->opt2->symbolName);
                        break;
                case IR_SUB :
                        fprintf(out, " %s := %s - %s \n", current->result->symbolName, current->opt1->symbolName, current->opt2->symbolName);
                        break;
                case IR_MUL :
                        fprintf(out, " %s := %s * %s \n", current->result->symbolName, current->opt1->symbolName, current->opt2->symbolName);
                        break;
                case IR_DIV :
                        fprintf(out, " %s := %s / %s \n", current->result->symbolName, current->opt1->symbolName, current->opt2->symbolName);
                        break;

		// case about address operation
                case IR_REF :
			if(current->opt2 == NULL) {
				fprintf(out, " %s := &%s \n", current->result->symbolName, current->opt1->symbolName);
			} else {
				fprintf(out, " %s := &%s + %s \n", current->result->symbolName, current->opt1->symbolName, current->opt2->symbolName);
			}
                        break;
                case IR_DEREF_L :
                        fprintf(out, " *%s := %s \n", current->result->symbolName, current->opt1->symbolName);
                        break;
                case IR_DEREF_R :
                        fprintf(out, " %s := *%s \n", current->result->symbolName, current->opt1->symbolName);
                        break;

		// for jmp statements
                case IR_GOTO :
                        fprintf(out, " GOTO %s \n", current->result->symbolName);
                        break;
                case IR_IF_GOTO :
                        fprintf(out, " IF %s %s %s GOTO %s \n", current->opt1->symbolName, current->relop, current->opt2->symbolName, current->result->symbolName);
                        break;
               // case IR_RELOP :
               //         fprintf(out, "", current->);
               //         break;
			
		// for arrays
                case IR_DEC :
                        fprintf(out, " DEC %s %s \n", current->result->symbolName, current->opt1->symbolName);
                        break;

		// for read/write
                case IR_READ :
                        fprintf(out, " READ %s \n", current->result->symbolName);
                        break;
                case IR_WRITE :
                        fprintf(out, " WRITE %s \n", current->result->symbolName);
                        break;
		
		default : break;
	}
}

void printIR(FILE * out) {
	IRCode * head = IRListHead;
	while(head != NULL) {
		printLine(out, head);
		head = head->next;
	}
}

