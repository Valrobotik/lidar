#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "lidar.h"
#include "libft.h"

int	open_serial(void)
{
	int	fd;

	if (!(fd = open("/dev/ttyACM0", O_RDWR)))
		return (-1);
	return (fd);
}

int	lidar_read(char *buffer[LIDAR_BUFF], int fd)
{
	int	err;

	err = read(fd, *buffer, LIDAR_BUFF);
	buffer[err] = 0;
	ft_putstr(*buffer);
	ft_putstr(" < is ok\n");
	return (err);
}

int	lidar_write(char *word, int fd)
{
	int	size;

	size = 0;
	while (word && word[size])
		size++;
	if (size <= 0)
		return (-1);
	write(fd, &word, size);
	return (0);
}


