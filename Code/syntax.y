%{
#include<stdio.h>
#include "common.h"
#include <stdlib.h>
/*typedef struct Node
{
	int intval;
	float floatval;
	char strval[50];
	struct Node * node;
}Node;*/

#define ERR_COMMA "\",\""
#define ERR_LP   "Missing \"(\""
#define ERR_RP   "Missing \")\""
#define ERR_LB   "Missing \"[\""
#define ERR_RB   "Missing \"]\""
#define ERR_RC   "Missing \"}\""
#define ERR_LC   "Missing \"{\""
#define ERR_SEMI "Missing \";\""

extern BOOL hasError;
extern int errorCount;

Node *root;
Node *NewNodeSyn(char *,int);
Node *MergeNode1(Node*,Node*);
Node *MergeNode2(Node*,Node*,Node*);
Node *MergeNode3(Node*,Node*,Node*,Node*);
Node *MergeNode4(Node*, Node*,Node*,Node*,Node*);
Node *MergeNode5(Node*, Node*,Node*,Node*,Node*,Node*);
Node *MergeNode7(Node*, Node*,Node*,Node*,Node*,Node*,Node* ,Node*);

%}
/*---declared type---*/
%union{
	Node *type_node;
}
/*declared token*/
%token <type_node> INT
%token <type_node> FLOAT 
%token <type_node> ID
%token <type_node> PLUS MINUS STAR DIV AND OR NOT/*yun suan fu*/
%token <type_node> DOT RELOP SEMI COMMA ASSIGNOP LP RP LB RB LC RC
%token <type_node> TYPE
%token <type_node> STRUCT RETURN
%token <type_node> IF ELSE WHILE

%type <type_node> Program ExtDefList ExtDef Specifier ExtDecList FunDec CompSt 
%type <type_node> VarDec DefList StmtList DecList
%type <type_node> StructSpecifier OptTag Tag
%type <type_node> VarList ParamDec Stmt Exp Dec Def Args

%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT
%left DOT LB RB LP RP

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
Program : ExtDefList {Node* p=NewNodeSyn("Program",@$.first_line);$$=MergeNode1(p,$1);root=$$;}
    ;
ExtDefList : ExtDef ExtDefList {Node *p=NewNodeSyn("ExtDefList",@$.first_line); $$=MergeNode2(p,$1,$2);}
    |{$$=NULL;}
    ;
ExtDef : Specifier ExtDecList SEMI {Node* p=NewNodeSyn("ExtDef",@$.first_line);$$=MergeNode3(p,$1,$2,$3);}
    | Specifier ExtDecList error SEMI { yyclearin; yyerrok; }
    | Specifier ExtDecList error Specifier{ yyerror(ERR_SEMI);yyerrok; }
    | Specifier SEMI {Node *p=NewNodeSyn("ExtDef",@$.first_line); $$=MergeNode2(p,$1,$2);}
    | error SEMI {$$ = NewNodeSyn("error",@$.first_line); yyerror("some error in this defination.");yyerrok; yyclearin; }
    | Specifier error SEMI {yyerror("syntax error, wrong expression."); yyerrok; }
    | Specifier FunDec CompSt {Node *p=NewNodeSyn("ExtDef",@$.first_line); $$=MergeNode3(p,$1,$2,$3);}
    | Specifier FunDec error LC { yyerror(ERR_RP); yyerrok; }
    | Specifier FunDec error RC { yyerror(ERR_RP" or \"{\"."); yyerrok; }
    ;
ExtDecList : VarDec {Node *p=NewNodeSyn("ExtDecList",@$.first_line); $$=MergeNode1(p,$1);}
    | VarDec COMMA ExtDecList {Node *p=NewNodeSyn("ExtDecList",@$.first_line); $$=MergeNode3(p,$1,$2,$3);}
    ;

/*-----------Specifier------------*/
Specifier : TYPE {Node* p=NewNodeSyn("Specifier",@$.first_line);$$=MergeNode1(p,$1);}
    | StructSpecifier {Node *p=NewNodeSyn("Specifier",@$.first_line); $$=MergeNode1(p,$1);}
    ;
StructSpecifier : STRUCT OptTag LC DefList RC {Node *p=NewNodeSyn("StructSpecifier",@$.first_line); $$=MergeNode5(p,$1,$2,$3,$4,$5);}
    | STRUCT Tag {Node *p=NewNodeSyn("StructSpecifier",@$.first_line); $$=MergeNode2(p,$1,$2);}
    | STRUCT OptTag LC error RC { yyerror("Wrong defination in struct."); yyerrok; }
    ;
OptTag : ID {Node *p=NewNodeSyn("OptTag",@$.first_line); $$=MergeNode1(p,$1);}
    | {$$=NULL;}/*empty*/
    ;
Tag : ID {Node *p=NewNodeSyn("Tag",@$.first_line); $$=MergeNode1(p,$1);}
    ;
/*--------------Declarator-------------*/
VarDec : ID {Node *p=NewNodeSyn("VarDec",@$.first_line); $$=MergeNode1(p,$1);}
    | VarDec LB INT RB {Node *p=NewNodeSyn("VarDec",@$.first_line); $$=MergeNode4(p,$1,$2,$3,$4);}
    ;
FunDec : ID LP VarList RP {Node *p=NewNodeSyn("FunDec",@$.first_line);$$=MergeNode4(p,$1,$2,$3,$4);}
    | ID LP RP {Node *p=NewNodeSyn("FunDec",@$.first_line);$$=MergeNode3(p,$1,$2,$3);}
    | ID LP error RP { yyerror(ERR_RP); yyerrok; }
    ;
VarList : ParamDec COMMA VarList {Node *p=NewNodeSyn("VarList",@$.first_line);$$=MergeNode3(p,$1,$2,$3);}
    | ParamDec {Node *p=NewNodeSyn("VarList",@$.first_line);$$=MergeNode1(p,$1);}
    | error RP {yyerror("Wrong defination!");}
    ;
ParamDec : Specifier VarDec {Node *p=NewNodeSyn("ParamDec",@$.first_line);$$=MergeNode2(p,$1,$2);}
    ;
/*--------------Statements---------------*/
CompSt : LC DefList StmtList RC {Node *p=NewNodeSyn("Compst",@$.first_line);$$=MergeNode4(p,$1,$2,$3,$4);}
    | LC CompSt error { yyerror("Wrong end here."); }
    ;
StmtList : Stmt StmtList {Node *p=NewNodeSyn("StmtList",@$.first_line);$$=MergeNode2(p,$1,$2);}
    |{$$=NULL;} /*empty*/
    ;
Stmt : Exp SEMI {Node *p=NewNodeSyn("Stmt",@$.first_line);$$=MergeNode2(p,$1,$2);}
    | error RC { yyerror(ERR_LC); yyclearin; yyerrok; }
    | CompSt {Node *p=NewNodeSyn("Stmt",@$.first_line);$$=MergeNode1(p,$1);}
    | RETURN Exp SEMI {Node *p=NewNodeSyn("Stmt",@$.first_line);$$=MergeNode3(p,$1,$2,$3);}
    | RETURN Exp error SEMI { yyerror(ERR_SEMI); yyerrok;}
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {Node *p=NewNodeSyn("Stmt",@$.first_line);$$=MergeNode5(p,$1,$2,$3,$4,$5);}
    | IF LP Exp RP Stmt ELSE Stmt {Node *p=NewNodeSyn("Stmt",@$.first_line);$$=MergeNode7(p,$1,$2,$3,$4,$5,$6,$7);}
    | IF LP Exp error Stmt ELSE Stmt{ yyerror(ERR_RP); yyerrok;}
    | WHILE LP Exp RP Stmt {Node *p=NewNodeSyn("Stmt",@$.first_line);$$=MergeNode5(p,$1,$2,$3,$4,$5);}
    | WHILE LP error RP { yyerror("while syntax error."); yyerrok; }
    | error SEMI { yyerror(ERR_SEMI); yyclearin; }
    ;
/*--------Local Definitions----------*/
DefList : Def DefList {Node *p=NewNodeSyn("DefList",@$.first_line);$$=MergeNode2(p,$1,$2);}
    | {$$=NULL;}/*empty*/
    ;
Def : Specifier DecList SEMI {Node *p=NewNodeSyn("Def",@$.first_line);$$=MergeNode3(p,$1,$2,$3);}
    | Specifier error DecList SEMI  { yyerrok; }
    | Specifier DecList error SEMI  { yyclearin; yyerrok; }
    ;
DecList :Dec  {Node *p=NewNodeSyn("DecList",@$.first_line);$$=MergeNode1(p,$1);}
    | Dec COMMA DecList {Node *p=NewNodeSyn("DecList",@$.first_line);$$=MergeNode3(p,$1,$2,$3);}
    | error SEMI { yyerror("Wrong defination."); yyclearin; }
    ;
Dec : VarDec {Node *p=NewNodeSyn("Dec",@$.first_line);$$ =MergeNode1(p,$1);}
    | VarDec ASSIGNOP Exp  {Node *p=NewNodeSyn("Dec",@$.first_line);$$=MergeNode3(p,$1,$2,$3);}
    | LB error ASSIGNOP {yyerror(ERR_RB); yyclearin; yyerrok; }
    | VarDec ASSIGNOP error SEMI{ yyerror("Missing operation numbers."); yyclearin; yyerrok; }
    ;
/*----------Expressions---------------*/
Exp : Exp ASSIGNOP Exp {Node *p=NewNodeSyn("Exp",@$.first_line);$$=MergeNode3(p,$1,$2,$3);}
    | Exp ASSIGNOP error SEMI { yyerror("wrong assign expression."); }
    | Exp AND Exp {Node *p=NewNodeSyn("Exp",@$.first_line);$$=MergeNode3(p,$1,$2,$3);}
    | Exp OR Exp {Node *p=NewNodeSyn("Exp",@$.first_line);$$=MergeNode3(p,$1,$2,$3);}
    | Exp RELOP Exp {Node *p=NewNodeSyn("Exp",@$.first_line);$$=MergeNode3(p,$1,$2,$3);}
    | Exp PLUS Exp {Node *p=NewNodeSyn("Exp",@$.first_line);$$=MergeNode3(p,$1,$2,$3);}
    | Exp MINUS Exp {Node *p=NewNodeSyn("Exp",@$.first_line);$$=MergeNode3(p,$1,$2,$3);} 
    | Exp STAR Exp {Node *p=NewNodeSyn("Exp",@$.first_line);$$=MergeNode3(p,$1,$2,$3);}
    | Exp DIV Exp {Node *p=NewNodeSyn("Exp",@$.first_line);$$=MergeNode3(p,$1,$2,$3);}
    | LP Exp RP  {Node *p=NewNodeSyn("Exp",@$.first_line);$$=MergeNode3(p,$1,$2,$3);}
    | MINUS Exp {Node *p=NewNodeSyn("Exp",@$.first_line);$$=MergeNode2(p,$1,$2);}
    | NOT Exp {Node *p=NewNodeSyn("Exp",@$.first_line);$$=MergeNode2(p,$1,$2);}
    | ID LP Args RP {Node *p=NewNodeSyn("Exp",@$.first_line);$$=MergeNode4(p,$1,$2,$3,$4);}
    | ID LP RP {Node *p=NewNodeSyn("Exp",@$.first_line);$$=MergeNode3(p,$1,$2,$3);}
    | ID LP error SEMI { yyerror(ERR_RP); yyclearin; }
    | Exp LB Exp RB  {Node *p=NewNodeSyn("Exp",@$.first_line);$$=MergeNode4(p,$1,$2,$3,$4);}
    | Exp DOT ID {Node *p=NewNodeSyn("Exp",@$.first_line);$$=MergeNode3(p,$1,$2,$3);}
    | ID {Node *p=NewNodeSyn("Exp",@$.first_line);$$=MergeNode1(p,$1);}
    | INT {Node *p=NewNodeSyn("Exp",@$.first_line);$$=MergeNode1(p,$1);}
    | FLOAT {Node *p=NewNodeSyn("Exp",@$.first_line);$$=MergeNode1(p,$1);}
    | Exp LB error RB { yyerror("Wrong VarDec."); yyerrok; }
    | ID LP error RP { yyerror("check LP and RP."); yyerrok; }
    ;
Args : Exp COMMA Args {Node *p=NewNodeSyn("Args",@$.first_line);$$=MergeNode3(p,$1,$2,$3);}
    | Exp {Node *p=NewNodeSyn("Args",@$.first_line);$$=MergeNode1(p,$1);}
    ;
%%
