#include <bcm2835.h>
#include "lidar.h"

/* ask if we have time to continue (within 95 secs ?)*/
int	we_have_time(void)
{
	static int	loop_nbr;
	time_t	tmp;

	if (!loop_nbr)
		loop_nbr = 1;
	else
		loop_nbr++;
	if (clock() - g_time_start > STOP_TIME * 1000000)
	{
		tmp = time(&tmp);
		ft_putstr("\n----  END MATCH  ----\n");
		ft_putstr(asctime(gmtime(&tmp)));
		ft_putstr("\n");
		ft_putnbr(loop_nbr);
		ft_putstr(" loop done during the match\n");
		return (0);
	}
	return (1);
}

/* stop moving, the match ended, his sight is based on motion */
void	freez_end_match(void)
{
	//send command to motors and actionners to stop, or activate a relay
	//to shut down everything
	ft_putstr("asking robot to keep quiet\n");
}

void	print_side(void)
{
	g_side = bcm2835_gpio_lev(PINSIDE);
	ft_putstr("   + On Side: ");
	if (g_side == B_SIDE)
		ft_putstr("BLUE");
	else
		ft_putstr("YELLOW");
	ft_putstr(" +\n");
}

t_pile	*setup_robot(void)
{
	static int	nbr_reset;

	if (!nbr_reset)
		nbr_reset = 1;
	else
		nbr_reset++;
	ft_putstr("\e[1;1H\e[2J");
	if (nbr_reset > 1) 
	{
		ft_putnbr(nbr_reset);
		ft_putstr(" RESET THIS\n");
	}
	t_pile	*pile;
	pile = build_pile();//stack the written command on a file, in a pile
	g_side = bcm2835_gpio_lev(PINSIDE);
	ft_putstr("ROBOT READY, PULL STRING TO START\n");
	print_side();
	return (pile);
}

int	start_robot(void)
{
	int	valueReed;
	int	valueReset;
//	int	valueSide;
	int	start;
	time_t	tmp;
	t_pile	*pile;

	start = 0;
	pile = setup_robot();
	while (1)
	{
		if (start == 1 && !we_have_time())
		{
			freez_end_match();//freez the motors and all actionners
			start  = 2;
		}
		valueReset = bcm2835_gpio_lev(PINRESET);
		valueReed = bcm2835_gpio_lev(PINREED);
		if (detect_falling(valueReed, REED) && !start)
		{
			g_time_start = clock();
			tmp = time(&tmp);
			ft_putstr("\n----  START MATCH  ----\n");
			ft_putstr(asctime(gmtime(&tmp)));
			ft_putstr("\n");
			start = 1;
		}
		if (detect_rising(valueReset, RESET))
		{
			start = 0;
			pile = setup_robot();
		}
		if (start == 1)
		{
			unpile_cmd(&pile);//for each command, send order
			//and wait till it suceed to proceed to the following
		}
	}
	return (0);
}

