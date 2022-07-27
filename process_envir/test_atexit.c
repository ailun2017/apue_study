#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void f1(void)
{
	puts("f1 called\n");
}

void f2(void)
{
    puts("f2 called\n");
}

void f3(void)
{
    puts("f3 called\n");
}

int main(void)
{
	puts("start\n");
	atexit(f1);
	atexit(f2);
	atexit(f3);
	puts("end\n");
	//exit(0);
	//_exit(0);
	//_Exit(0);
	return 0;
}
