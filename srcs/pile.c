#include "lidar.h"
#include <stdlib.h>

t_pile	*build_pile(void)
{
	t_pile	*first_elm;
	int	not_end;

	not_end = 1;
	first_elm = NULL;
	while (not_end)
	{
		//here you pile up for each line found,
		//and if the file is ended (or to long) you quit
		ft_putstr("generating the pile\n");
		not_end = 0;
	}
	return (first_elm);
}

	// start to give cmd to robot, pile is composed of cmd
	//a cmd have to status to_process or in_process
	//once it is complete it is removed from the pile
	//in_process mean you ask the motor block were it is
	//have to do an estimation of the time to not disturb 
	//asservissement to much
int	unpile_cmd(t_pile *pile)
{
	static int k;

	(void)pile;
	if (!k)
		k = 1;
	if (k < 7)
	{
		ft_putstr("do_stuff robot please\n");
		k++;
	}
	return (1);
}
