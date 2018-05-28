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
	}
	return operand;
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


//VarList : ParamDec COMMA VarList 
//    | ParamDec


//ParamDec : Specifier VarDec






void printLine(FILE * out, IRCode * current) {
	switch(current->kind) {
		case IR_NOP :
			break;
		case IR_LABEL :
			fprintf(out, " LABEL label%d : \n", current->result->u.intval);
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
                        fprintf(out, " GOTO label%d \n", current->result->u.intval);
                        break;
                case IR_IF_GOTO :
                        fprintf(out, " IF %s %s %s GOTO label%d \n", current->opt1->symbolName, current->relop, current->opt2->symbolName, current->result->u.intval);
                        break;
               // case IR_RELOP :
               //         fprintf(out, "", current->);
               //         break;
			
		// for arrays
                case IR_DEC :
                        fprintf(out, " DEC %s %d \n", current->result->symbolName, current->opt1->u.intval);
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

