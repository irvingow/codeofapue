#include"apue.h"
#include<stdarg.h>
#include<errno.h>
#include<fcntl.h>
/*
 * #include<stdio.h>
 * #include<string.h>
 * #include<stdlib.h>
 * */

/* variables defined for TELL_WAIT,TELL_PARENT,TELL_CHILD,WAIT_PARENT and WAIT_CHILD */
static volatile sig_atomic_t sigflag;	/* set nonzero by sig handler */
static sigset_t newmask, oldmask, zeromask;
/* end */

static void err_doit(int, int, const char *, va_list);

void
err_quit(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
    exit(1);

}

void err_cont(int error, const char *fmt,...)
{
    va_list ap;

    va_start(ap,fmt);
    err_doit(1,error,fmt,ap);
    va_end(ap);
}

void
err_msg(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);

}

void
err_exit(int error, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, error, fmt, ap);
    va_end(ap);
    exit(1);

}


void
err_dump(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    abort();
    exit(1);

}

void
err_sys(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    exit(1);

}

void
err_ret(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);

}

void
err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
    char buf[MAXLINE];
    vsnprintf(buf, MAXLINE - 1, fmt, ap);
    if (errnoflag)
        snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ": %s", strerror(error));
    strcat(buf, "\n");
    fflush(stdout);
    fputs(buf, stderr);
    fflush(NULL);

}

void clr_fl(int fd, int flags)/* flags are file status flags to turn off */
{
    int val;

    if((val = fcntl(fd,F_GETFL,0)) < 0)
        err_sys("fcntl F_GETFL error");

    val &= ~flags;       /* turn off flags */

    if(fcntl(fd,F_SETFL,val) < 0)
        err_sys("fcntl F_SETFL error");
}

void set_fl(int fd, int flags)/* flags are file status flags to turn on */
{
    int val;

    if((val = fcntl(fd,F_GETFL,0)) < 0)
        err_sys("fcntl F_GETFL error");

    val |= flags;       /* turn on flags */

    if(fcntl(fd,F_SETFL,val) < 0)
        err_sys("fcntl F_SETFL error");
}

int
lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    return(fcntl(fd, cmd, &lock));

}

pid_t
lock_test(int fd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    if (fcntl(fd, F_GETLK, &lock) < 0)
        err_sys("fcntl error");

    if (lock.l_type == F_UNLCK)
        return(0);
    return(lock.l_pid);

}

int
lockfile(int fd)
{
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;
    return(fcntl(fd, F_SETLK, &fl));

}


/* code below is the definition of TELL_WAIT,TELL_PARENT,TELL_CHILD,WAIT_PARENT and WAIT_CHILD */

static void sig_usr(int signo)		/* one signal handler for SIGUSR1 and SIGUSR2 */
{
    sigflag = 1;
}

void TELL_WAIT(void)
{
    if(signal(SIGUSR1, sig_usr) == SIG_ERR)
        err_sys("signal(SIGUSR1) error");
    if(signal(SIGUSR2, sig_usr) == SIG_ERR)
        err_sys("signal(SIGUSR2) error");
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    /* Block SIGUSR1 and SIGUSR2, and save current signal mask */
    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        err_sys("SIG_BLOCK error");
}

void TELL_PARENT(pid_t pid)
{
    kill(pid, SIGUSR2);			/* tell parent we're done */
}

void WAIT_PARENT(void)
{
    while(sigflag == 0)
        sigsuspend(&zeromask);	/* and wait for parent */
    sigflag = 0;

    /* Reset signal mask to original value */
    if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_sys("SIG_SETMASK error");
}

void TELL_CHILD(pid_t pid)
{
    kill(pid, SIGUSR1);			/* tell child we're done */
}

void WAIT_CHILD(void)
{
    while(sigflag == 0)
        sigsuspend(&zeromask);	/* and wait for child */
    sigflag = 0;

    /* Reset signal mask to original value */
    if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_sys("SIG_SETMASK error");
}


