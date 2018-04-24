#include <assert.h>
#include <stdio.h>
void Assert(char *log)
{
	fprintf(stderr,"\033[31m%s  ",log);
	assert(0);
	fprintf(stderr,"\033[0m");
}
/*int main()
{
	Assert("Something need to do!");
	return 0;
}*/
