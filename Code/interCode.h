#include "common.h"

#define BUFFERSIZE 64

// OP_NOP just used for translate_Exp, in translate_Stmt
typedef enum OperandKind_ {
	OP_TEMP, OP_VARIABLE, OP_CONSTANT, OP_LABEL, OP_FUNCTION, OP_REF, OP_NOP
} OperandKind;

typedef struct Operand_ {
	OperandKind kind;
	union {
		// for int or some
		int intval;
		// for label
		int var_no;
        //	float floatval; hypothesis 1:there is no float variable.
	} u;
	// symbolName : func/var/tempvar... is name only, for int is form of ' #value'.
	char symbolName[BUFFERSIZE];
	// classify VarDec ID
	BOOL isParam;
} Operand;

typedef enum IRKind_ {
	IR_NOP,     // just used for begin
	IR_LABEL,   // LABEL result :
        
	IR_FUNC_DEFINED,    // FUNCTION result :
        IR_CALL,    // result := CALL arg1
        IR_RETURN,  // RETURN result
        IR_PARAM,   // PARAM result
        IR_ARG,     // ARG result
        
	IR_ASSIGN,  // result := opt1
        
	IR_ADD,     // result := opt1 + opt2
        IR_SUB,     // result := opt1 - opt2
        IR_MUL,     // result := opt1 * opt2
        IR_DIV,     // result := opt1 / opt2

        IR_REF,     // result  := &opt1
        IR_DEREF_R, // result  := *opt1
        IR_DEREF_L, // *result :=  opt1

        IR_GOTO,     // GOTO result
	IR_IF_GOTO,  // IF opt1 [relop] opt2 GOTO result
        
	IR_DEC,      // DEC result [size]

        IR_READ,    // READ result
        IR_WRITE    // WRITE result
} IRKind;

typedef struct IRCode_ {
	IRKind kind;
	// for if... else... statements if [relop] else
	char * relop;
	struct IRCode_ *pre, *next;     // Doubly linked list
	Operand *result, *opt1, *opt2;  // Three address code
} IRCode;

IRCode * IRListHead;
IRCode * IRListTail;

IRCode * createIRCodeNode(IRKind kind);
Operand * createOperand(OperandKind kind, char * symbolName);
Operand * dereference(Operand * operand);
void linkIRCode(IRCode * IR, Operand * result, Operand * opt1, Operand * opt2, char * relop);
void printIR(FILE * out);
void printLine(FILE * out, IRCode * head);
void translate_Program();
void translate_ExtDefList(Node * node);
void translate_ExtDef(Node * node);
void translate_ExtDecList(Node * node);
void translate_Specifier(Node * node);
void translate_StructSpecifier(Node * node);
void translate_OptTag(Node * node);
void translate_Tag(Node * node);
char * translate_VarDec(Node * node, BOOL isParam);
void translate_FunDec(Node * node);
void translate_VarList(Node * node);
void translate_ParamDec(Node * node);
void translate_CompSt(Node * node);
void translate_StmtList(Node * node);
void translate_Stmt(Node * node);
void translate_ExpConditional(Node * node, Operand * labelTRUE, Operand * labelFALSE);
void translate_DefList(Node * node);
void translate_Def(Node * node);
Operand * translate_Exp(Node * node, OperandKind kind); 
void translate_DecList(Node * node);
void translate_Dec(Node * node);
void translate_Args(Node * node);



