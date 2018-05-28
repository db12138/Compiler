#include <stdlib.h>
#include <stdio.h>
void Assert(char *log,char *file,int line)
{
	fprintf(stderr,"\033[31m%s AT FILE:%s LINE:%d\n \033[0m",log,file,line);
	abort();
	//fprintf(stderr,"\033[0m");
}
/*int main()
{
	Assert("Something need to do!");
	return 0;
}*/
