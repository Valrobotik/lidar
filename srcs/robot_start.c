#include <bcm2835.h>
#include "lidar.h"

/* ask if we have time to continue (within 95 secs ?)*/
int	we_have_time(void)
{
	//ask the time, compare to start time and keep on the loop
	return (1);
}

/* stop moving, the match ended, his sight is based on motion */
void	freez_end_match(void)
{
	//send command to motors and actionners to stop, or activate a relay
	//to shut down everything
	ft_putstr("END OF MATCH, WHO WIN ?\n");
}


int	start_robot(void)
{
	int	valueReed;
	int	valueReset;
	int	start;
	time_t	tmp;
	t_pile	*pile;

	start = 0;
	pile = build_pile();//stack the written command on a file, in a pile
	while (we_have_time())//check the time, beware of the 100 sec
	{
		valueReset = bcm2835_gpio_lev(PINRESET);
		valueReed = bcm2835_gpio_lev(PINREED);
		if (detect_falling(valueReed, REED) && !start)
		{
			tmp = time(&tmp);
			ft_putstr("there we go, tirette removed\n");
			g_time_start = gmtime(&tmp);
			ft_putstr(asctime(g_time_start));
			start = 1;
		}
		if (detect_rising(valueReset, RESET))
		{
			ft_putstr("RESET THIS\n");
			start = 0;
		}
		if (start == 1)
		{
			unpile_cmd(pile);//for each command, send order
			//and wait till it suceed to proceed to the following
		}
	}
	freez_end_match();//freez the motors and all actionners
	return (0);
}

