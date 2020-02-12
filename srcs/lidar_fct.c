#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include "lidar.h"
#include <bcm2835.h>

#define NBR_VAL 682

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stropts.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#include <bcm2835.h>
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

void	lidar_get_resp_print(struct pollfd fds[1], int fd)
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
				write(1, "resp\n\n", 5);
				res = read(fd, buffer, LIDAR_BUFF);
				buffer[res] = 0;
				write(1, buffer, strlen(buffer));
				end = 0;
			}
		}
	}
}

int	lidar_try_get_resp_print(struct pollfd fds[1], int fd)
{
	int	ret;
	int	res;
	char	buffer[LIDAR_BUFF];

	ret = poll(fds, 1, 1000);
	if (ret > 0)
	{
		if (fds[0].revents & POLLRDNORM)
		{
			write(1, "resp\n\n", 5);
			res = read(fd, buffer, LIDAR_BUFF);
			buffer[res] = 0;
			write(1, buffer, strlen(buffer));
			return (1);
		}
	}
	return (0);
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

int	lidar_try_get_resp(struct pollfd fds[1], int fd)
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
			return (1);
		}
	}
	return (0);
}

void	max_baudrate(void)
{
	char *buff = "SS115200\n";

	write(g_fd, buff, strlen(buff));		//change baude rate lidar
	set_interface_attribs(g_fd, 115200, 0);		//chage bauderate de l'interfacage
}

int 	main(int argc, char** argv)
{
	int	wcount;
	char	buffer[READ_BUFF];
	int	res;

	g_fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (g_fd == -1)
	{
		perror(argv[1]);
	}
	if (g_fd > 0)
		set_interface_attribs(g_fd, BAUDRATE, 0);		//setup de l'interfacage
	g_fds[0].fd = g_fd;
	g_fds[0].events = POLLRDNORM;
	if (!bcm2835_init())
		return (1);
	bcm2835_gpio_fsel(PINOUT, BCM2835_GPIO_FSEL_OUTP);	
	bcm2835_gpio_fsel(PINREED, BCM2835_GPIO_FSEL_INPT);	
	bcm2835_gpio_fsel(PINRESET, BCM2835_GPIO_FSEL_INPT);	
	bcm2835_gpio_fsel(PINSIDE, BCM2835_GPIO_FSEL_INPT);	
	if (argc > 1) //fonction avec les flags
	{
		set_interface_attribs(g_fd, 115200, 0);		//chage bauderate de l'interfacage
		do_flag(argv[1]);
		return (0);
	}
	max_baudrate();
	g_range = (int*)malloc(sizeof(int) * NBR_VAL);
	if (g_fd > 0)
		lidar_get_resp_print(g_fds, g_fd);
	while (1)
	{
		ft_putstr("please enter a command\n");
		wcount = read(0, buffer, READ_BUFF);
		buffer[wcount] = 0;
		if (!(res = lidar_cmd_is_premade(buffer)))
		{	//effectue la fonction si la commande est pre-enregistree
			wcount = write(g_fd, buffer, strlen(buffer));	//sinon transmet au lidar
			if (wcount < 0)
			{
				perror("Write");
				return -1;
			}
			lidar_get_resp_print(g_fds, g_fd);
		}
		if (res == 2)
		{
			ft_putstr("disp on\n");
			setup_flag();
			display(argc, argv);
		}
	}
}
