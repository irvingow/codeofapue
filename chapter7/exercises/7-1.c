#include <stdio.h>

/* In fact, we will not get 13 as return value, I guess gcc may implicit 
 * add 'exit' for us, so the return value is still 0
 * */
int main(void)
{
	printf("hello, world\n");
}
