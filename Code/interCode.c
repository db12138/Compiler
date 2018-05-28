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
			sprintf(operand->symbolName, "#%s", symbolName);
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
	if(strcmp("SEMI", node->child[1]->strval)==0 || strcmp("ExtDecList", node->child[1]->strval)==0) {
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
	switch(node->type) {
		case 2: // int
			break;
		case 3: // float
			IRError = TRUE;
			fprintf(stderr, "Hypothesis 1: there is no float defination.\n");
			break;
		case 0: //TODO: struct??? 
			break;
	}	
}

// StructSpecifier : STRUCT OptTag LC DefList RC
//    | STRUCT Tag
void translate_StructSpecifier(Node * node) {
	assert(node != NULL);
	// struct defination
	if(node->childnum == 5) {
		// TODO：这里应该有判断struct里面有多少个变量
		// TODO: 让DefList返回变量个数
		return;
	}
	else {
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

	// ID
	if(node->type == 4) {
		if(isParam == TRUE) {
			char * newname = malloc(BUFFERSIZE);
			sprintf(newname, "v%d", definedVarCount++);
			Operand * operand = createOperand(OP_VARIABLE, newname);
			operand->isParam = TRUE;
			IRCode * ircode = createIRCodeNode(IR_PARAM);
			linkIRCode(ircode, operand, NULL, NULL, NULL);			
		}
		return node->strval;
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
			sprintf(Sintval, "%d", node->child[2]->intval);
			Operand * size = createOperand(OP_CONSTANT, Sintval);
			char * newname = malloc(BUFFERSIZE);
                        sprintf(newname, "v%d", definedVarCount++);
			Operand * arr = createOperand(OP_REF, newname);
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
		linkIRCode(ircodeTrue, labelTRUE, opt1, opt2, node->child[1]->strval);
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
	
	switch(node->childnum) {
		//     | CompSt
		case 1:
			translate_CompSt(node->child[0]);
			break;
		//     | Exp SEMI
		case 2:
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
	
	translate_Specifier(node->child[0]);
	translate_DecList(node->child[1]);
}

// DecList : Dec
//    | Dec COMMA DecList 
void translate_DecList(Node * node) {
	if(node->childnum == 1) {
		translate_Dec(node->child[0]);
	}
	else if(node->childnum == 3) {
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

	char * vardec = translate_VarDec(node->child[0], FALSE);
	
	if(node->childnum == 3) {
		// local ID Definitions, so dont generate inter codes
		if(vardec != NULL) {
			//char * newname = malloc(BUFFERSIZE);
                        //sprintf(newname, "v%d", definedVarCount++);
			//Operand * operand = createOperand(OP_VARIABLE, newname);
			translate_Exp(node->child[2], OP_VARIABLE);
		}
		// local array
		else {
			;	
		}
	}
	else {
		Assert("Should not be here.", __FILE__, __LINE__);
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

Operand * translate_Exp(Node * node, OperandKind kind) {
	assert(node != NULL);
	
	Operand * temp;
	switch(kind) {
		case OP_TEMP:
			temp = createOperand(OP_TEMP, "");
			break;
		case OP_VARIABLE:{
			char * newname = malloc(BUFFERSIZE);
                        sprintf(newname, "v%d", definedVarCount++);
			temp = createOperand(OP_VARIABLE, newname);
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
        	                char * newname = malloc(BUFFERSIZE);
	                        sprintf(newname, "v%d", definedVarCount++);
				Operand * operand = createOperand(OP_VARIABLE, newname);
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
			}
			// INT
			else if(strcmp(node->child[0]->strval, "INT") == 0) {
				if(kind == OP_TEMP || kind == OP_REF) {
					temp->kind = OP_CONSTANT;
					sprintf(temp->symbolName, "#%d", node->intval);
				}
				else {
					IRCode * ircode = createIRCodeNode(IR_ASSIGN);
					char * constant = malloc(BUFFERSIZE);
					sprintf(constant, "#%d", node->intval);
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
			
			break;
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
		case 3:
			break;
		//     | ID LP Args RP
		//     | Exp LB Exp RB
		case 4:
			break;
	}	

	return temp;
}


// Args : Exp COMMA Args 
//     | Exp
void translate_Args(Node * node) {

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

