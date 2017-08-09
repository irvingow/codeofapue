#include "apue.h"
#include <sys/select.h>
#include <poll.h>

void sleep_us1(unsigned int nusecs)
{
    struct timeval tval;

    tval.tv_sec = nusecs / 1000000;
    tval.tv_usec = nusecs % 1000000;
    select(0,NULL,NULL,NULL,&tval);
}

void sleep_us2(unsigned int nusecs)
{

    struct pollfd dummy;
    int timeout;

    if((timeout = nusecs / 1000) <= 0)
        timeout = 1;
    poll(&dummy,0,timeout);/* we don't need to initalize dummy because the second argument imply that the element number is zero. */
}
