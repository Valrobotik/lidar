#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "lidar.h"
#include "libft.h"
#include <errno.h>
#include <bcm2835.h>
#include <time.h>

#define NBR_PREMADE 10

int	fct_flash(char buffer[READ_BUFF])
{
	strcpy(buffer, "GD0044072501\n");
	return (0);
}

int	fct_decod_resp(void)
{
	int	pos;

	pos = 0;
	cmd_finder(g_buff, &pos);
	scnd_finder(g_buff, &pos);
	time_finder(g_buff, &pos);
	g_size = code_decode(g_buff, &pos, 3);
	return (2);
}

/*
 * same but wait to find the cmd to start the aquisition (line by line)
 */
int	fct_decod_resp_name(char *cmd)
{
	int	pos;

	pos = 0;
	if (cmd_finder_name(g_buff, &pos, cmd))
	{
		scnd_finder(g_buff, &pos);
		time_finder(g_buff, &pos);
		g_size = code_decode(g_buff, &pos, 3);
		return (1);
	}
	return (0);
}

int	fct_print(char buffer[READ_BUFF])
{
	int	wcount;

	strcpy(buffer, "GD0044072501\n");
	//strcpy(buffer, "MD004407250103\n");
	if (g_fd > 0)
		wcount = write(g_fd, buffer, strlen(buffer));
	if (wcount < 0)
	{
		perror("Write");
		return -1;
	}
	if (g_fd > 0)
		lidar_get_resp(g_fds, g_fd);
	return (fct_decod_resp());
}

int	fct_exit(char buffer[READ_BUFF])
{
	(void)buffer;
	ft_putstr("exiting\n");
	exit(0);
	return (0);
}

int	fct_led(char buffer[READ_BUFF])
{
	static int set;

	(void)buffer;
	if (!set)
		set = 1;
	if (set == -1)
		bcm2835_gpio_clr(PINOUT);
	else
		bcm2835_gpio_set(PINOUT);
	set = -1 * set;
	return (1);
}

int	fct_read(char buffer[READ_BUFF])
{
	(void)buffer;
	if (lidar_try_get_resp(g_fds, g_fd))
	{
		fct_decod_resp_name(CMD_INF);
		ft_putstr("here come the table of size:");
		ft_putnbr(g_size);
		ft_putstr("\n");
		ft_print_digit(g_range, g_size);
		ft_putstr("\n");
	}
		//write(1, g_buff, strlen(g_buff));
	return (1);
}

int	fct_read_no_print(char buffer[READ_BUFF])
{
	(void)buffer;
	if (lidar_try_get_resp(g_fds, g_fd))
		return (fct_decod_resp_name(CMD_INF));
	return (0);
}

int	fct_read_no_print2(char buffer[READ_BUFF])
{
	(void)buffer;
	if (lidar_try_get_resp(g_fds, g_fd))
		return (fct_decod_resp_name(CMD_INF));
	return (0);
}

static int	fct_read_loop(char *cmd)
{
	lidar_get_resp(g_fds, g_fd);
	fct_decod_resp_name(cmd);
	ft_putstr("here come the table of size:");
	ft_putnbr(g_size);
	ft_putstr("\n");
	ft_print_digit(g_range, g_size);
	ft_putstr("\n");
		//write(1, g_buff, strlen(g_buff));
	return (1);
}

int	fct_mes(char buffer[READ_BUFF])//we might have to clear the buffer before writing
{
	strcpy(buffer, "GD0044072501\n");
	write(g_fd, buffer, strlen(buffer));
	fct_read_loop("GD0044072501\n");
	return (1);
}

int	fct_auto(char buffer[READ_BUFF])
{
	strcpy(buffer, CMD_INF);
	write(g_fd, buffer, strlen(buffer));
	while (1)
	{
		if (fct_read_no_print(buffer))
			led_stop();
	}
	return (1);	
}

int	fct_loop(char buffer[READ_BUFF])
{
	while (1)
		fct_read(buffer);
	return (1);	
}

int	fct_loop2(char buffer[READ_BUFF])
{
	while (1)
		if (fct_read_no_print2(buffer))
			led_stop();
	return (1);	
}

int	fct_wait(char buffer[READ_BUFF])
{
	(void) buffer;
	int	valueReed;
	int	valueReset;
	int 	old;
	int	start;

	start = 1;
	old = bcm2835_gpio_lev(PINREED);
	while (1)
	{
		valueReset = bcm2835_gpio_lev(PINRESET);
		valueReed = bcm2835_gpio_lev(PINREED);
		if (valueReed == 0 && old == 1 && start == 1)
		{
			ft_putstr("there we go, tirette removed\n");
			start = 0;
		}
		old = valueReed;
		if (valueReset == 1)
		{
			ft_putstr("RESET THIS\n");
			start = 1;
		}
	}
	
}

int	lidar_cmd_is_premade(char buffer[READ_BUFF])
{
	char 	*list[NBR_PREMADE] = {"exit\n", "flash\n", "print\n",
			"led\n", "read\n", "auto\n", "mes\n", "loop\n",
			"loop2", "wait\n"};
	int	(*fonction[NBR_PREMADE])(char buffer[READ_BUFF]) = {
			fct_exit, fct_flash, fct_print, fct_led, fct_read,
			fct_auto, fct_mes, fct_loop, fct_loop2, fct_wait};
	int	k;

	k = 0;
	while (k < NBR_PREMADE)
	{
		if (!strcmp(buffer, list[k]))
			return (fonction[k](buffer));
		k++;
	}
	return (0);
}
