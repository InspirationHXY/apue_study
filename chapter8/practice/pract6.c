#include<apue.h>
#define PRT(n)	printf("ps -p" #n " u\n")

#ifdef	SOLARIS
#define PSCMD	"ps -a -o pid,ppid,s,tty,comm"
#else
#define	PSCMD	"ps -o pid,ppid,state,tty,comm"
#endif

int 
main(void)
{
	pid_t	pid;
	
	if((pid = fork()) < 0)
		err_sys("fork error");
	else if(pid == 0) {	/* child */
		exit(0);
	}
	
	/* parent */
	sleep(5);
	if(system(PSCMD) < 0)
		err_sys("system error");
	
	PRT(pid);
	exit(0);
}
