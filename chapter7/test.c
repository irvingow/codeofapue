#include "apue.h"

static char buf[] = "helloworld";

int main(void)
{
    int ch;
    FILE *fp;
    int a;

    if((fp = fmemopen(buf, strlen(buf), "r+")) < 0)
        err_sys("fmemopen error");
    while((ch = fgetc(fp)) != EOF)
        printf("get %c\n", ch);
    if( (a = fprintf(fp, "12345") ) < 0)
        printf("fprintf error");
    fseek(fp, 0, SEEK_SET);
    if( (a = fprintf(fp, "12345")) < 0)
        printf("fprintf error again");
    fflush(fp);
    printf("after fflush: %s", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf));
    fclose(fp);
    return 0;
}
