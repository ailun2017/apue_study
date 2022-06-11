#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void compare_sysio_and_stdio()
{
	putchar('a');
	write(1, "b", 1);
    putchar('a');
    write(1, "b", 1);
}

int main(void)
{
	compare_sysio_and_stdio();
	exit(0);
}
