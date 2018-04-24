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
	char* name;
	Type type;
	FieldList tail;
}FieldList_;

typedef struct Vtable
{
	Type_ type;
	char name[100];
}Vtable;

typedef struct Ftable
{
	Type_ retn;    //the type of return
	int paranum;   //the number of parameters 
	Type_ paralist[30]; //the most number of parameters is 30;
}Ftable;

#endif
