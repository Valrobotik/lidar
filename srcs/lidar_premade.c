#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "lidar.h"
#include <errno.h>

#define NBR_PREMADE 3

int	fct_flash(char buffer[READ_BUFF], struct pollfd fds[1], int fd)
{
	(void)fds;
	(void)fd;
	strcpy(buffer, "GD0044072501\n");
	return (0);
}

int	fct_print(char buffer[READ_BUFF], struct pollfd fds[1], int fd)
{
	int	wcount;
	int	pos;
	int	range[NBR_VAL];

	strcpy(buffer, "GD0044072501\n");
	//strcpy(buffer, "MS004407250103\n");
	wcount = write(fd, buffer, strlen(buffer));
	if (wcount < 0)
	{
		perror("Write");
		return -1;
	}
	lidar_get_resp(fds, fd);
	ft_putstr(g_buff);
	ft_putstr("\n\nthen\n\n");
	pos = 0;
	cmd_finder(g_buff, &pos);
	scnd_finder(g_buff, &pos);
	time_finder(g_buff, &pos);
	g_size = code_decode(g_buff, &pos, g_range, 3);
	ft_print_digit(range, g_size);
	g_range = range;
	return (2);
}

int	fct_exit(char buffer[READ_BUFF], struct pollfd fds[1], int fd)
{
	(void)fds;
	(void)fd;
	(void)buffer;
	ft_putstr("exiting\n");
	exit(0);
	return (0);
}

int	lidar_cmd_is_premade(char buffer[READ_BUFF], struct pollfd fds[1], int fd)
{
	char 	*list[NBR_PREMADE] = {"exit\n", "flash\n", "print\n"};
	int	(*fonction[NBR_PREMADE])(char buffer[READ_BUFF], struct pollfd fds[1],
			int fd) = {
			fct_exit, fct_flash, fct_print};
	int	k;

	k = 0;
	while (k < NBR_PREMADE)
	{
		if (!strcmp(buffer, list[k]))
			return (fonction[k](buffer, fds, fd));
		k++;
	}
	return (0);
}
