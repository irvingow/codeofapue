#include "apue.h"

int main(void)
{
    FILE *fp;
    char *p;

    daemonize("getlog");
    p = getlogin();/* because we don't control terminal any more, so we probably will fail. */
    fp = fopen("/home/lwj/Documents/program/c/temp.out","wb+");
    if(fp != NULL)
    {
        if(p == NULL)
            fprintf(fp,"no login name");
        else 
            fprintf(fp,"login name: %s\n",p);
    }
    exit(0);
}
