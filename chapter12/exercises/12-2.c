#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

extern char **environ;

pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;

int putenv(char *str)
{
    int keylen = 0, i = 0;
    int len = strlen(str);

    for(int i = 0; i < len; i++)
    {
        if(str[i] == '=')
            break;
    }
    if(i == len || i == 0)

    {
        errno = EINVAL;
        return -1;
    }
    keylen = i;

    pthread_mutex_lock(&env_mutex);
    sigset_t oldmask, newmask;
    sigfillset(&newmask);

    pthread_sigmask(SIG_BLOCK,&newmask,&oldmask);

    for(i = 0; environ[i] != NULL;i++)
    {
        if(strncmp(str,environ[i],keylen) == 0)
        {
            environ[i] = str;
            pthread_mutex_unlock(&env_mutex);
            return 0;
        }
    }

    /* if we are here, it turns out that we need to add str to the environ.
     * Because we use malloc, so we need to block all signals to make this 
     * function async-signal safe. In addition, we need to dynamically allocate
     * a new space for environ.
     * */
    char **newEnviron;
    newEnviron = realloc(environ,((i+2)*sizeof(char *)));
    if(newEnviron == NULL)
    {
        errno = ENOMEM;
        return -1;
    }
    newEnviron[i] = str;
    newEnviron[i+1] = NULL;
    environ = newEnviron;

    pthread_mutex_unlock(&env_mutex);
    pthread_sigmask(SIG_SETMASK,&oldmask,NULL);
    return 0;
}

