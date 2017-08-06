#include <limits.h>
#include <string.h>

#define MAXSTRINGSZ 4096

static char envbuf[MAXSTRINGSZ];

extern char **environ;

/* this version is not reentrant because the string returned is stored 
 * in a single static buffer that is shared by all threads calling getenv 
 * */
char *getenv(const char *name)
{
    int i, len;

    len = strlen(name);
    for(i = 0; environ[i] != NULL; i++)
    {
        /* environment characters stored like this: "name=value" so we need to
         * control length and then compare if the next character is '='
         * */
        if((strncmp(name, environ[i],len) == 0) && (environ[i][len] == '='))
        {
            strncpy(envbuf,&environ[i][len+1],MAXSTRINGSZ-1);
            return envbuf;
        }
    }
    return NULL;
}
