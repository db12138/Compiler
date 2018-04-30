#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
typedef struct Type_* Type;
typedef struct FieldList_* FieldList;

typedef struct Type_
{
	enum {BASIC,ARRAY,STRUCTURE} kind;
	union
	{
		int basic;

		struct {Type elem;int size;} array;

		FieldList structure;
	}u;
}Type_;
typedef struct FieldList_
{
	char name[50];
	int linenum;
	Type type;
	FieldList tail;
}FieldList_;

typedef struct Vtype
{
	Type type;
	char name[100];
}Vtype;

typedef struct Ftype
{
	char name[100];
	Type_ retn;    //the type of return
	int paranum;   //the number of parameters 
	FieldList paralist; 
}Ftype;
typedef struct Stype
{
	char structname[50];
	Type_ structtype;
}Stype;

typedef struct Dtype
{
	char name[100];
	Type_ retn;
	int paranum;
	FieldList paralist;
	int defined;
	int linenum;
}Dtype;

#endif
