#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>

#define MAXSTRINGSZ 4096

static pthread_key_t key;
pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;

extern char **environ;

static void thread_init(void)
{
    pthread_key_create(&key, free);
}

/* 'getenv_r' will never be reentrant because it calls 'malloc' which itself is not async-signal safe */
char *getenv_r(const char *name, char *buf, int buflen)
{
    int i, len;
    char *envbuf;

    /* use 'pthread_once to guarantee that 'thread_init' will be called
     * only once, on the first call to pthread_once */
    pthread_once(&init_done, thread_init);
    pthread_mutex_lock(&env_mutex);
    envbuf = (char *)pthread_getspecific(key);
    if(envbuf == NULL)
    {
        envbuf = malloc(MAXSTRINGSZ);
        if(envbuf == NULL)
        {
            pthread_mutex_unlock(&env_mutex);
            return (NULL);
        }
        pthread_setspecific(key, envbuf);
    }
    len = strlen(name);
    for(i = 0; environ[i] != NULL; i++)
    {
        /* environment characters stored like this: "name=value" so we need to
         * control length and then compare if the next character is '='
         * */
        if((strncmp(name, environ[i], len) == 0) && (environ[i][len] == '='))
        {
            strncpy(envbuf, &environ[i][len + 1], MAXSTRINGSZ - 1);
            pthread_mutex_unlock(&env_mutex);
            return envbuf;
        }
    }
    pthread_mutex_unlock(&env_mutex);
    return (NULL);
}
