#include "apue.h"
#include <string.h>
#include <stddef.h>
#include <pwd.h>

struct passwd *getpwnam(const char *name)
{
	struct passwd *ptr;
	setpwent();
	while((ptr = getpwent()) != NULL)
		if(strcmp(name,ptr->pw_name) == 0)
			break;		/* found a match */
	endpwent();
	return ptr;			/* ptr is NULL if no match found */
}


/* codes below is used for test the function of 'getpwnam' */
/*int main(int argc, char **argv)
 *{
 *    if(argc != 2)
 *        err_sys("usage:%s <name>",argv[0]);
 *    struct passwd *ptr;
 *    if((ptr = getpwnam(argv[1])) != NULL)
 *    {
 *        printf("usr name:%s\n",ptr->pw_name);
 *        printf("passwd:%s\n",ptr->pw_passwd);
 *        printf("usr ID:%d\n",ptr->pw_uid);
 *        printf("group ID:%d\n",ptr->pw_gid);
 *        printf("initial working directory:%s\n",ptr->pw_dir);
 *        printf("initial shell:%s\n",ptr->pw_shell);
 *    }
 *    else
 *        printf("no usr matches!\n");
 *    exit(0);
 *}*/
