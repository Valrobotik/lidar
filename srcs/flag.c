#include "lidar.h"
#include "libft.h"
#include <stdlib.h>

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
	return (2);
}
