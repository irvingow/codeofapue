#include "apue.h"
#include <time.h>

#define MAXSIZE 255

int main(void)
{
    time_t t;
    struct tm *tmp;
    char buf2[MAXSIZE];

    time(&t);
    tmp = localtime(&t);
    if(strftime(buf2, MAXSIZE, "%Y %m %d %A %T %Z", tmp) > 0)
        printf("%s\n", buf2);
	else{
		err_sys("strftime error");
	}
    exit(0);
}
