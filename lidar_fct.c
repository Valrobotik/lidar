#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "lidar.h"

#define BUFF_SIZE 4096
#define NBR_VAL 682


int	main(int argc, char **argv)
{
	char	buff[BUFF_SIZE];
	int	range[NBR_VAL];
	int	ret;
	int	fd;
	int	pos;
	char	id;
	int	size;

	if (argc < 2)
	{
		ft_putstr("put filename of encrypted data in arg");
		return (1);
	}
	if (argc < 3)
		id = 'a';
	else
		id = argv[2][0];
	fd = open(argv[1], O_RDONLY);
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
	if (id == 'c')
		ft_print_digit(range, size);
//	ft_putstr("\n   ----------------------------------------   \n");
	if (id == 'c')
		code_finder(buff, &pos);
	return (0);
}
