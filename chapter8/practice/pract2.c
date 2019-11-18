#include<apue.h>

pid_t vfork(void);

static void testfunc(void);

int 
main(void)
{
	int	num = 5;
	int	op = 88;
	
	printf("test vfork\n");
	testfunc();
	printf("done\n");
	exit(0);
}

static void
testfunc(void)
{
	pid_t	pid;
	
	printf("in testfunc\n");
	if((pid = vfork()) < 0)
		err_sys("vfork error");
	else if(pid == 0) {	/* child */
		printf(" in child\n");
	}
	else	/* parent */
		printf(" in parent\n");
}
