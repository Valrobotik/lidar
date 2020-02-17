#include "lidar.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

void	get_resp(struct pollfd fds[1], int fd)
{
	int	ret;
	int	res;

		ret = poll(fds, 1, 1000);
		if (ret > 0)
		{
			if (fds[0].revents & POLLRDNORM)
			{
				res = read(fd, g_buff, LIDAR_BUFF);
				g_buff[res] = '\0';
			}
		}
}

int	interface_condition(void)
{
	char	buffer[READ_BUFF];
	int	wcount;

	while (1)
	{
		wcount = read(g_fd, buffer, READ_BUFF);
		ft_putstr("respond :");
		wcount = write(1, buffer, wcount);	//sinon transmet au lidar
		ft_putstr("\n");
		ft_putstr("please enter a command for the robot\n");
		wcount = read(0, buffer, READ_BUFF);
		wcount = write(g_fd, buffer, wcount);	//sinon transmet au lidar
		ft_putstr("send :");
		wcount = write(1, buffer, wcount);	//sinon transmet au lidar
		ft_putstr("<<<\n");
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
