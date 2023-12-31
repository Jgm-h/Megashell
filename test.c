#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"
#include "dirent.h"
#include "limits.h"
#include <sys/types.h>
# include <fcntl.h>
# define T_BOOL unsigned int
# define TRUE 1
# define FALSE 0


int main(int argc, char **argv, char **envp)
{
	int fd;

	fd = access("1", O_WRONLY);
	dup2(STDOUT_FILENO, fd);
	close(fd);
	printf("%s", "moiiiiifuyigi");
	return (0);
}
