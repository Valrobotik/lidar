#include "lidar.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int	interface_condition(void)
{
	char	buffer[READ_BUFF];
	int	wcount;

	while (1)
	{
		ft_putstr("please enter a command for the robot\n");
		wcount = read(0, buffer, READ_BUFF);
		buffer[wcount] = 0;
		wcount = write(g_fd, buffer, strlen(buffer));	//sinon transmet au lidar
		wcount = read(g_fd, buffer, READ_BUFF);
	}
}

int 	real_condition(void)
{
	ft_putstr("start_programm\n");
	start_robot();
	return (1);
}

int	do_flag(char *str)
{
	if (!strcmp(str, "-r"))
	{
		return (real_condition());
	}
	if (!strcmp(str, "-i"))
		return (interface_condition());
	return (2);
}
