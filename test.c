#include "unistd.h"
# include "stdio.h"
# include "stdlib.h"
# include <errno.h>
# include "signal.h"
# include <fcntl.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

int main(void)
{
	int pipes[2];
	char *test;

	pipe(pipes);
	test = malloc (5 * sizeof (char));
	//dup2(STDIN_FILENO, pipes[0]);
	write(pipes[1], "test", 5);
	read(pipes[0], test, 5);
	printf("%s", test);
	return (0);
}