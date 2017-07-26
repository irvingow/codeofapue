#include "apue.h"

int main(void)
{
	int c;

	while((c = getc(stdin)) != EOF)
		if(putc(c,stdout) == EOF)//putc will return EOF on error and EOF has no specific meaning
			err_sys("output error");

	if(ferror(stdin))
		err_sys("input error");

	exit(0);
}
