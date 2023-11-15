#include "shell.h"

/**
 * main - Entry point for the custom shell program
 * @ac: Argument count
 * @av: Argument vector
 *
 * This function initializes the custom shell program by setting up required
 * structures and environment. It reads user input and processes commands
 * accordingly using the 'hsh' function.
 *
 * @ac: Number of arguments passed to the program.
 * @av: Array of strings containing the arguments.
 *
 * Return: Returns 0 on successful execution, 1 on encountered errors.
 */
int main(int ac, char **av)
{
    info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
