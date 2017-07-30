#include <sys/utsname.h>
#include "apue.h"

/* It seems that os must be utsname rather than a pointer to utsname 
 * When I use os which is a pointer to utsname as argument passed to 'uname', I got 
 * a runtime error. And I couldn't find why the problem appeared.
 * below is code that can't be run on my computer.
 * */
/*int main(void)
 *{
 *    struct utsname *os;
 *    if(uname(os) < 0)
 *    {
 *        printf("uname error");
 *        exit(0);
 *    }
 *    printf("os name:%s\n",os->sysname);
 *    printf("node name:%s\n",os->nodename);
 *    printf("current release of os:%s\n",os->release);
 *    printf("current version of this release:%s\n",os->version);
 *    printf("name of hardware type:%s\n",os->machine);
 *    exit(0);
 *}*/

int main(void)
{
	struct utsname os;
	if(uname(&os) < 0)
	{
		printf("uname error");
		exit(0);
	}	
	printf("os name:%s\n",os.sysname);
	printf("node name:%s\n",os.nodename);
	printf("current release of os:%s\n",os.release);
	printf("current version of this release:%s\n",os.version);
	printf("name of hardware type:%s\n",os.machine);
	exit(0);
}
