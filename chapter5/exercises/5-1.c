#include "apue.h"

/* use 'setvbuf' to replace 'setbuf' */
void mysetbuf(FILE *restrict fp, char *restrict buf)
{
	/* if buf is NULL, we will turn buffer off 
	 * otherwise buffer fully buffered and notice the size must be BUFSIZ.
	 * */
    if(buf == NULL)
    {
        if(setvbuf(fp, NULL, _IONBF, 0) < 0)
            err_ret("setvbuf error");
        return;
    }
    if(setvbuf(fp, buf, _IOFBF, BUFSIZ) < 0)
        err_ret("setvbuf error");
}
