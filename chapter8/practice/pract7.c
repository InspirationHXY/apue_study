#include<apue.h>
#include<fcntl.h>
#include<dirent.h>
int
main(void)
{
	int	status;
	int	fd;
	DIR 	*dp;
	int 	*fdp;
	/*
	 * open root dir
	 */
	if((fd = open("/", O_RDONLY)) < 0)
		err_sys("open error");
	
	if((status = fcntl(fd, F_GETFD, 0)) < 0)
		err_sys("fcntl error");
	
	printf("CLOEXEC is %d\n", status);
	if(close(fd) < 0)
		err_sys("close error");
	
	/*
	 * opendir root dir
	 */
	if((dp = opendir("/")) == NULL)	
		err_sys("opendir error");
	fdp = dp->__fd;
	fd = *fdp;
	if((status = fcntl(fd, F_GETFD, 0)) < 0)
		err_sys("fcntl error");
	
	printf("CLOEXEC (opendir) is %d\n", status);
	exit(0);
	
}
