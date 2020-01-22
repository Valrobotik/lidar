#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include "lidar.h"

#define NBR_VAL 682

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stropts.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include <errno.h>


#define BAUDRATE B19200

int	set_interface_attribs(int fd, int speed, int parity)
{
	struct termios serial;

	if (tcgetattr(fd, &serial) < 0) {
		perror("Getting configuration");
		return -1;
	}
	memset(&serial, 0, sizeof(serial));
	if (tcgetattr(fd, &serial) != 0)
	{
		ft_putstr("can't get attributes of tty\n");
		return (-1);
	}
	cfsetospeed(&serial, speed);
	cfsetispeed(&serial, speed);
	serial.c_cflag = (serial.c_cflag & ~CSIZE) | CS8;	//8 bits char
	serial.c_iflag &= ~IGNBRK;				//Ignore break in input flags, do not take \00 as break
	serial.c_oflag = 0;
	serial.c_lflag = 0;
	serial.c_cc[VMIN] = 0;					//read does not block
	serial.c_cc[VTIME] = 0;					//time out : 5 = 0.5 sec 
	serial.c_iflag &= ~(IXON | IXOFF | IXANY);
	serial.c_cflag |=  (CLOCAL | CREAD);
	serial.c_cflag &=  (PARENB | PARODD);
	serial.c_cflag |=  parity;
	serial.c_cflag &=  ~CSTOPB;
	serial.c_cflag &= ~CRTSCTS;
	tcsetattr(fd, TCSANOW, &serial);			// Apply configuration
	return (0);
}

void	lidar_do_loop(struct pollfd fds[1], int fd)
{
	int	ret;
	int	res;
	char	buffer[LIDAR_BUFF];
	int	end;

	end = 1;
	while(end)
	{
		ret = poll(fds, 1, 1000);
		if (ret > 0)
		{
			if (fds[0].revents & POLLRDNORM)
			{
				res = read(fd, buffer, LIDAR_BUFF);
				buffer[res] = 0;
				write(1, buffer, strlen(buffer));
				end = 0;
			}
		}
	}
}

void	lidar_get_resp(struct pollfd fds[1], int fd)
{
	int	ret;
	int	res;
	int	end;

	end = 1;
	while(end)
	{
		ret = poll(fds, 1, 1000);
		if (ret > 0)
		{
			if (fds[0].revents & POLLRDNORM)
			{
				res = read(fd, g_buff, LIDAR_BUFF);
				g_buff[res] = '\0';
				end = 0;
			}
		}
	}
}
/*
int main(int argc, char* argv[])
{
	char	buff[BUFF_SIZE];
	int	range[NBR_VAL];
	int	ret;
	int	fd;
	int	pos;
	char	id;
	int	size;

	if (argc < 2)
		fd = open("../encryptx.txt", O_RDONLY);
	else
		fd = open(argv[1], O_RDONLY);
	if (argc < 3)
		id = 'a';
	else
		id = argv[2][0];
	ret = read(fd, buff, BUFF_SIZE);
	close(fd);
	if (ret == 0)
		return (1);
	buff[ret] = 0;
	if (id == 'b' || id == 'c')
	{
		ft_putstr("----  found: ----\n");
		ft_putstr(buff);
		ft_putstr("\n ---------------------------- \n");
	}
	pos = 0;
	cmd_finder(buff, &pos);
	scnd_finder(buff, &pos);
	time_finder(buff, &pos);
//	ft_putstr("trad :");
	size = code_decode(buff, &pos, range, 3);
//	ft_putstr("\n   ----------------------------------------   \n");
	fd = open("tmp", O_CREAT | O_WRONLY | O_TRUNC);
	ft_print_digit_fd(fd, range, size);
	g_range = range;
	g_size = size;
	display(argc, argv);
	return (0);

}*/
int 	main(int argc, char** argv)
{
	struct pollfd fds[1];
	int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NONBLOCK);
	int	wcount;
	char	buffer[READ_BUFF];
	int	res;
	int	*range;

	range = (int*)malloc(sizeof(int) * NBR_VAL);
	g_range = range;

	if (fd == -1)
	{
		perror(argv[1]);
		return -1;
	}
	//set_interface_attribs(fd, BAUDRATE, 0);		//setup de l'interfacage
	fds[0].fd = fd;
	fds[0].events = POLLRDNORM;
	while (1)
	{
		ft_putstr("please enter a command\n");
		wcount = read(0, buffer, READ_BUFF);
		buffer[wcount] = 0;
		if (!(res = lidar_cmd_is_premade(buffer, fds, fd)))
		{	//effectue la fonction si la commande est pre-enregistree
			wcount = write(fd, buffer, strlen(buffer));	//sinon transmet au lidar
			if (wcount < 0)
			{
				perror("Write");
				return -1;
			}
			lidar_do_loop(fds, fd);
		}
		//display(argc, argv);
		if (res == 2)
			display(argc, argv);
	}
}
