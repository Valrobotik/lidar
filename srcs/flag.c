#include "lidar.h"
#include "libft.h"
#include "time.h"
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
	//clock_t	start;

	while (1)
	{
		//wcount = write(g_fd, "M18\n", 4);	//sinon transmet au lidar
		ft_putstr("please enter a command for the robot\n");
		wcount = read(0, buffer, READ_BUFF);
		wcount = write(g_fd, "\n", 1);	//sinon transmet au lidar
		wcount = write(g_fd, buffer, wcount);	//sinon transmet au lidar
		/*
		ft_putstr("send :");
		wcount = write(1, buffer, wcount);	//sinon transmet au lidar
		ft_putstr("<<<\n");
		start = clock();
		while (clock() - start < 3000000)
		{
			wcount = read(g_fd, buffer, READ_BUFF);
			if (wcount > 0)
			{
				ft_putstr("respond :");
				wcount = write(1, buffer, wcount);	//sinon transmet au lidar
				ft_putstr("\n");
			}
		}
		*/
	}
}

int 	real_condition(void)
{
	ft_putstr("start_programm\n");
	start_robot();
	return (1);
}

#define LEN 3000
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int	reader(void)
{
	int	size;
	char	buff[LEN];
	int	fd_rd;
	int	fd_wr;

	fd_rd = open("/dev/ttyACM0", O_RDONLY | O_NOCTTY | O_NONBLOCK);
	fd_wr = open("/dev/ttyACM0", O_WRONLY | O_NOCTTY | O_NONBLOCK);
	write(fd_wr, "M666\n", 5);
	while (1)
	{
		size = read(0, buff, LEN);
		if (size > 0)
		{
			buff[size] = 0;
			ft_putstr("cmd: ");
			ft_putstr(buff);
			write(fd_wr, buff, ft_strlen(buff));
		}
		size = read(fd_rd, buff, LEN);
		if (size > 0)
		{
			buff[size] = 0;
			ft_putstr("response: ");
			ft_putstr(buff);
		}

	}
	return (0);
}

int	do_flag(char *str)
{
	if (!strcmp(str, "-m"))
	{
		return (real_condition());
	}
	if (!strcmp(str, "-i"))
		return (interface_condition());
	if (!strcmp(str, "-r"))
		return (reader());
	return (2);
}
