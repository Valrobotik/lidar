#include "libft.h"
#include "lidar.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define PROCESS 1
#define PENDING 0

#define ASK_POS "M114\n"
#define	PREC 5
#define	PREC_SQ PREC * PREC

void	display_move(t_pile *pile)
{
	printf("    wana go to X=");
	printf("%f", pile->x);
	printf("   and Y=");
	printf("%f", pile->y);
	printf("   and A=");
	printf("%f", pile->a);
	printf(" inside %f", pile->time);
	printf(" seconds transmit: %s\n", pile->cmd);
	
}

double	cmd_find(char elmt, char *str)
{
	int	k;

	k = 0;
	while (str[k] && str[k] != elmt)
		k++;
	if (str[k] == elmt)
		return (atof(str + k + 1));
	else
		return (-1);
}

double	cmd_find_remove(char elmt, char **str)
{
	int	k;
	double	res;
	char	c;

	k = 0;
	while ((*str)[k] && (*str)[k] != elmt)
		k++;
	if ((*str)[k] == elmt)
	{
		res = atof((*str) + k + 1);
		(*str)[k] = ' ';
		while ((c = (*str)[k + 1]) && (ft_isdigit(c) || c == '-' || c == '.'))
		{
			(*str)[k + 1] = ' ';
			k++;
		}
		return (res);

	}
	else
		return (-1);
}

int	is_move(char *str, t_pile **pile)
{
	if (cmd_find('G', str) == 0)
	{
		(*pile)->x = cmd_find('X', str);
		(*pile)->y = cmd_find('Y', str);
		(*pile)->a = cmd_find('A', str);
		(*pile)->time = cmd_find_remove('T', & str);
		(*pile)->cmd = str;
		return (1);
	}
	return (0);
}

void	add_list(t_pile **pile, char *str)
{
	t_pile	*new_pile;
	t_pile	*tmp;

	if (!(new_pile = (t_pile*)malloc(sizeof(t_pile))))
		return ;
	ft_memset(new_pile, 0, sizeof(new_pile));
	if (is_move(str, &new_pile))
	{
		new_pile->move = 1;
		display_move(new_pile);
	}
	else
	new_pile->move = 0;
	new_pile->next = NULL;
	new_pile->cmd = str;
	new_pile->status = PENDING; //to_process
	if (!(*pile))
		*pile = new_pile;
	else
	{
		tmp = *pile;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_pile;
	}
}

t_pile	*build_pile(void)
{
	t_pile	*first_elm;
	int	fd;
	char	*str;

	first_elm = NULL;
	fd = open("/home/pi/lidar/command_robot.txt", O_RDWR);
	ft_putstr("_________  LIST TO EXEC  ____________\n");
	while (get_next_line(fd, &str) > 0)
	{
		if (str && str[0] != '#' && str[0] != '/')//ignore comments 
		{
			ft_putstr("- ");
			ft_putstr(str);
			ft_putstr("\n");
			add_list(&first_elm, str);
		}
	}
	ft_putstr("_____________________________________\n");
	return (first_elm);
}

int	it_is_done(t_pile **pile)
{
	char	*str;
	double	x;
	double	y;
	double	x_obj;
	double	y_obj;
	double	dist;

	if (get_next_line(g_fd, &str) == 1 && str)
	{
		ft_putstr("response: ");
		ft_putstr(str);
	}
	return (0);
	write(g_fd, ASK_POS, ft_strlen(ASK_POS));
	get_next_line(g_fd, &str);
	{
		if (str && str[0])
		x = cmd_find('X', str);
		y = cmd_find('Y', str);
		x_obj = (*pile)->x;
		y_obj = (*pile)->y;
		dist = (x - x_obj) * (x - x_obj) + (y - y_obj) * (y - y_obj); 
		if (dist < PREC_SQ)
			return (1);
	}
	return (0);
}

/* Function qui pour chaque commande de la pile, envoie la demande au moteur, puis si la commande est faite
 * passe a la suivante*/
int	unpile_cmd(t_pile **pile)
{
	static clock_t		start;

	if (*pile)
	{
		if ((*pile)->status == PENDING)//if cmd not sent yet
		{
			ft_putstr("exec: ");
			ft_putstr((*pile)->cmd);
			ft_putstr("\n");
			start = clock();
			if (g_fd != -1)
			{
				write(g_fd, (*pile)->cmd, ft_strlen((*pile)->cmd));
				(*pile)->status = PROCESS;
			}
			else
				ft_putstr("cannot reach motion card\n");
		}
		else if (it_is_done(pile)
				|| (start && (*pile)->time != -1 && (clock() - start > (*pile)->time * 1000000)))
			*pile = (*pile)->next;
	}
	return (1);
}
