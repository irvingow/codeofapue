#include "apue.h"

/* you can't just use makefile to compile this file, we need use 
 * > gcc -D_GUN_SOURCE -o 7-5 7-5.c apue.o
 * to define macro **_GNU_SOURCE **
 * */
int main(int argc, char **argv)
{
	int i;
	for(i = 0; environ[i] != NULL; i++)/* echo all command-line args */
		printf("evviron[%d]: %s\n",i,environ[i]);
	exit(0);
}
