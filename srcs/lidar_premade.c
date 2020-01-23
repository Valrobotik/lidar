#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "lidar.h"
#include <errno.h>

#define NBR_PREMADE 3

int	fct_flash(char buffer[READ_BUFF])
{
	strcpy(buffer, "GD0044072501\n");
	return (0);
}

int	fct_print(char buffer[READ_BUFF])
{
	int	wcount;
	int	pos;

	strcpy(buffer, "GD0044072501\n");
	//strcpy(buffer, "MS004407250103\n");
	wcount = write(g_fd, buffer, strlen(buffer));
	if (wcount < 0)
	{
		perror("Write");
		return -1;
	}
	ft_putstr(" mid way\n");
	lidar_get_resp(g_fds, g_fd);
	pos = 0;
	cmd_finder(g_buff, &pos);
	scnd_finder(g_buff, &pos);
	time_finder(g_buff, &pos);
	g_size = code_decode(g_buff, &pos, 3);
	return (2);
}

int	fct_exit(char buffer[READ_BUFF])
{
	(void)buffer;
	ft_putstr("exiting\n");
	exit(0);
	return (0);
}

int	lidar_cmd_is_premade(char buffer[READ_BUFF])
{
	char 	*list[NBR_PREMADE] = {"exit\n", "flash\n", "print\n"};
	int	(*fonction[NBR_PREMADE])(char buffer[READ_BUFF]) = {
			fct_exit, fct_flash, fct_print};
	int	k;

	k = 0;
	while (k < NBR_PREMADE)
	{
		if (!strcmp(buffer, list[k]))
			return (fonction[k](buffer));
		k++;
	}
	return (0);
}
