#include <stdio.h>
#include "common.h"
extern BOOL hasError;
/*
 * i : error type
 * j : error line
 * var: error variable
 */
void errorPrint(int i, int j, char *var) {
	hasError = TRUE;
	fprintf(stderr,"Error type %d at Line %d: ", i, j);
	switch(i) {
		case 1: fprintf(stderr,"Undefined variable \"%s\".\n", var); break;
		case 2: fprintf(stderr,"Undefined function \"%s\".\n", var); break;
		case 3: fprintf(stderr,"Redefined variable \"%s\".\n", var); break;
		case 4: fprintf(stderr,"Redefiend function \"%s\".\n", var); break;
		case 5: fprintf(stderr,"Type mismatched for assignment.\n"); break;
		case 6: fprintf(stderr,"The left-hand side of an assignment must be a variable..\n"); break;
		case 7: fprintf(stderr,"Type mismatched for operands.\n"); break;
		case 8: fprintf(stderr,"Type mismatched for return.\n"); break;
		case 9:	fprintf(stderr,"Function \"func(int)\" is not applicable for arguments \"(int, int)\".\n"); break;
		case 10: fprintf(stderr,"\"%s\" is not an array.\n", var); break;
		case 11: fprintf(stderr,"\"%s\" is not a function.\n", var); break;
		case 12: fprintf(stderr,"\"%s\" is not an integer.\n", var); break;
		case 13: fprintf(stderr,"Illegal use of \".\".\n"); break;
		case 14: fprintf(stderr,"Non-existent field \"%s\".\n", var); break;
		case 15: fprintf(stderr,"Redefined field \"%s\".\n", var); break;
		case 16: fprintf(stderr,"Duplicated name \"%s\".\n", var); break;
		case 17: fprintf(stderr,"Undefined structure \"%s\".\n", var); break;
		case 18: fprintf(stderr,"Undefined function \"%s\".\n", var); break;
		case 19: fprintf(stderr,"Inconsistent declaration of function \"%s\".\n", var); break;
		default: break;
	}
}
