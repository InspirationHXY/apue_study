#include<apue.h>
#include<sys/wait.h>

static void pr_siginf(siginfo_t *infop);
int
main(void)
{
	pid_t	pid;
	int	i = 100;
	siginfo_t	siginfo;
	
	if((pid = fork()) < 0)
		err_sys("fork error");
	else if(pid == 0)	/* child */
		exit(7);
	if(waitid(P_PID, pid, &siginfo, WEXITED) < 0)
		err_sys("waidid error");
	
	pr_siginf(&siginfo);

	if((pid = fork()) < 0)
		err_sys("fork error");
	else if(pid == 0)	/* child */
		abort();	/* generate SIGABRT */
	
	if(waitid(P_PID, pid, &siginfo, WEXITED) < 0)
		err_sys("waitid error");
	pr_siginf(&siginfo);

	if((pid = fork()) < 0)
		err_sys("fork error");
	else if(pid == 0)	/* child */
		i /= 0;		/* divide by 0 generates SIGFPE */
	
	if(waitid(P_PID, pid, &siginfo, WEXITED) < 0)
		err_sys("waitid error");
	pr_siginf(&siginfo);

	exit(0);
}

static void
pr_siginf(siginfo_t *infop)
{
	if(infop->si_signo == SIGCHLD) {	/* SIGCHLD */
		printf("child uid = %d, pid = %ld\n",
			infop->si_uid, (long)infop->si_pid);
		if(infop->si_code == CLD_EXITED)
			printf("normal termination, exit status = %d\n", infop->si_status);
		else if(infop->si_code == CLD_KILLED || infop->si_code == CLD_DUMPED)
			printf("abnormal termination, signal number = %d %s\n", infop->si_status,
				(infop->si_code == CLD_KILLED) ? "" : "(core dumped)");
		else if(infop->si_code == CLD_STOPPED)
			printf("child stopped, signal number = %d\n", infop->si_status);
		else if(infop->si_code == CLD_CONTINUED)
			printf("child continued by SIGCONT\n");
		else
			printf("traced child has trapped\n");

	}
	else 
	 printf(" other sigal\n");
}
