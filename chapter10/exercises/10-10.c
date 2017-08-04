#include "apue.h"
#include <time.h>

/* cron calls sleep every 60 seconds as well to 
 * schedule the next 60 seconds, but occasionally 
 * resyncs time with a sleep(59).(sometimes may much
 * small than 60 to synchronize)
 *  */
void printTime(void)
{
    int i = 0;
    time_t t;
    struct tm *ptm;

    for(;;)
    {
        if((i++) % 5 == 0)
        {
            t = time(NULL);
            ptm = localtime(&t);
			printf("%d\n",ptm->tm_sec);
        }
		sleep(60);
    }
	exit(0);
}

int main(void)
{
	printTime();
	exit(0);
}
