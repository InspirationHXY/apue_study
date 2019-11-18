#include<apue.h>
#include<errno.h>
#include<fcntl.h>
#define O_FLAG O_RDWR|O_CREAT|O_TRUNC
#define MODE   S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH

int
main(void)
{
	pid_t	pid, pgid;
	char	buf[BUFSIZ];
	int	fd;
	char	c;

	if((pid = fork()) < 0)
		err_sys("fork error");
	else if(pid > 0) { 	/* parent directly eixts */
		exit(0);
	} else {	/* child */
		if((fd = openat(AT_FDCWD, "errfile", O_FLAG, MODE)) < 0)	/* creat and open error record file */
			err_sys("open errfile error");	
		if((pgid = setsid()) < 0)
			err_sys("setsid error");
		
		if((c = getc(stdin)) == EOF)
			printf("getc() error");
		printf("no controlling termination\n");

		/*
		 * when creat a new session, there is no controlling termination
		 * associated with the calling process.
		 */
		snprintf(buf, BUFSIZ, "child: pid = %ld, pgid = %ld, ret = %ld\n",
			(long)getpid(), (long)getpgrp(), (long)pgid);
		if(open("/dev/tty", O_RDWR) < 0) {
			snprintf(buf+strlen(buf), BUFSIZ-strlen(buf)-1,
				"open /dev/tty error\n");
		}
		write(fd, buf, strlen(buf));
		close(fd);
		printf("no term\n");
		exit(0);
	}
}
