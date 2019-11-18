#include<apue.h>
pid_t vfork(void);

int	globvar	= 6;	/* external variable in initialized data */

int
main(void)
{
	int	var;	/* automatic variable on the stack */
	pid_t	pid;
	int	ret;
	char buf[BUFSIZ];

	var = 88;
	printf("pid = %ld\n", (long)getpid());
	printf("before vfork\n");  /* we don't flush stdio */
	if(((pid = vfork()) < 0))
		err_sys("vfork error");
	else if(pid == 0){	/* child */
		printf("pid = %ld\n", (long)getpid());
		globvar++;	/* modify parent's variable */
		var++;
		fclose(stdout);
		exit(0);	/* child terminates */
	}
	/* parent continues here*/
	ret = printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), 
		globvar, var);
	sprintf(buf, "%d\n", ret);
	if(write(STDOUT_FILENO, buf, strlen(buf)) != strlen(buf))
		err_sys("write error");
	exit(0);
}
