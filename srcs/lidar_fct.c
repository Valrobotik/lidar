#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include "lidar.h"

#define BUFF_SIZE 4096
#define NBR_VAL 682


#include <poll.h>
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

    // Set up Serial Configuration
    
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

    serial.c_cc[VMIN] = 0; //read does not block
    serial.c_cc[VTIME] = 0; //time out : 5 = 0.5 sec 

    serial.c_iflag &= ~(IXON | IXOFF | IXANY);

    serial.c_cflag |=  (CLOCAL | CREAD);
    serial.c_cflag &=  (PARENB | PARODD);
    serial.c_cflag |=  parity;
    serial.c_cflag &=  ~CSTOPB;
    serial.c_cflag &= ~CRTSCTS;

    tcsetattr(fd, TCSANOW, &serial); // Apply configuration
    return (0);
}

int main(int argc, char* argv[])
{

	(void)argc;
	(void)argv;


    char* str = "BM\n";
    char buffer[10];
    struct pollfd fds[1];
    int	variable;
    int	ret,res;

    int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd == -1)
    {
        perror(argv[1]);
        return -1;
    }

    set_interface_attribs(fd, BAUDRATE, 0);

    fds[0].fd = fd;
    fds[0].events = POLLRDNORM;

    // Attempt to send and receive
    printf("Sending: %s\n", str);
    int wcount = write(fd, &str, strlen(str));
    if (wcount < 0) {
        perror("Write");
        return -1;
    }
    else {
        printf("Sent %d characters\n", wcount);
    }
    while(1)
    {
	    ret = poll(fds, 1, 1000);
	    if (ret > 0)
	    {
		    if (fds[0].revents & POLLRDNORM)
			{
				res = read(fd, buffer, 255);
				buffer[res] = 0;
				sscanf(buffer, "%d\n", &variable);
				printf("Received %d\n", variable);
		    }
	    }
    }
//	usleep(1000);
	/*
    int rcount = read(fd, &buffer, sizeof(buffer));
    if (rcount < 0) {
        perror("Read");
        return -1;
    }
    else {
        printf("Received %d characters\n", rcount);
    }

    buffer[rcount] = '\0';

    printf("Received: %s\n", buffer);

    close(fd);*/
}

/*
int	main(int argc, char **argv)
{
	int fdr;
	int fdw;
	char *buffer;

	(void)argc;
	(void)argv;

	if (!(buffer = (char*)malloc(sizeof(char) * 4096)))
		return (1);
	//fd = open_serial();
	
	if (!(fdw = open("/dev/ttyACM0", O_WRONLY)))
		return (-1);
	if (!(fdr= open("/dev/ttyACM0", O_RDONLY)))
		return (-1);

	if (fdr < 0 || fdw < 0)
		ft_putstr("pb is:");
	else
		ft_putstr("ok is:");
	ft_putnbr(fdr);
	ft_putstr(" and:");
	ft_putnbr(fdw);
	ft_putstr("\n");
	
	ft_putstr("open done\n");
	lidar_write("VV\n", fdw);
	ft_putstr("write done\n");
	lidar_read(&buffer, fdr);
	ft_putstr("read done\n");
	write(1, buffer, 4096);
	write(1, "\n", 1);
	return (0);

 fonction display existing curve
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
	if (id == 'c')
		ft_print_digit(range, size);
//	ft_putstr("\n   ----------------------------------------   \n");
	if (id == 'c')
		code_finder(buff, &pos);
	display(argc, argv);
	return (0);

}*/
