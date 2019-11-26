#include <stdio.h>
#include <unistd.h>
#include "lidar.h"

/*
** Analyse the first line, command recap
*/

char	*cmd_finder(char *str, int *pos)
{
//	int	tmp;

//	tmp = *pos;
	if (!str || !str[*pos])
		return (0);
	while (str[*pos] && str[*pos] != '\n')
		(*pos)++;
//	ft_putstr("CMD : `");
//	write(1, str + tmp, *pos - tmp);
//	ft_putstr("'\n");
	if (str[*pos])
		(*pos)++;
	return (str);
}

/*
** Analyse the second line, verif/secu
*/

char	*scnd_finder(char *str, int *pos)
{
//	int	tmp;
//
//	tmp = *pos;
	if (!str || !str[*pos])
		return (0);
	while (str[*pos] && str[*pos] != '\n')
		(*pos)++;
//	ft_putstr("STATUS : `");
//	write(1, str + tmp, *pos - tmp);
//	ft_putstr("'\n");
	if (str[*pos])
		(*pos)++;
	return (str);

}

/*
** Analyse the third line, time stamp information
*/

char	*time_finder(char *str, int *pos)
{
	int	tmp;

	tmp = *pos;
	if (!str || !str[*pos])
		return (0);
	while (str[*pos] && str[*pos] != '\n')
		(*pos)++;
//	ft_putstr("TIME stamp : `");
//	write(1, str + tmp, *pos - tmp);
//	ft_putstr("'\n");
	if (str[*pos])
		(*pos)++;
	return (str + tmp);

}

char	*code_finder(char *str, int *pos)
{
	int	tmp;
	int	nb_line;
//	int	res;

	nb_line = 1;
	if (!str || !str[*pos])
		return (0);
	while (str[*pos])
	{
		tmp = *pos;
		while (str[*pos] && str[*pos] != '\n')
			(*pos)++;
//		ft_putnbr(nb_line);
//		ft_putstr(" line : `");
//		write(1, str + tmp, *pos - tmp);
//		ft_putstr("'\n");
//		res = decode(str + tmp, 3);
//		ft_putstr("Decoded 1st: ");
//		ft_putnbr(res);
//		ft_putstr("\n");
		if (str[*pos])
			(*pos)++;
		nb_line++;
	}
	return (str + tmp);
}

int	code_decode(char *str, int *pos, int range[682], int nb)
{
	int	k;
	char	caract;
	char	tmp[3];
	int	ind;
	int	i;
	int	nbr;
	int	checksum;

	i = 0;
	k = 0;
	ind = 0;
	checksum = 0;
	while ((caract = str[*pos + k]))
	{
		if (k % 66 != 64 && k % 66 != 65)
		{
			tmp[i] = caract;
			checksum += caract;
			if (i == nb - 1)
			{
				nbr = decode(tmp, nb);
				if (ind >= 0 && ind < 682)
				{
					range[ind] = nbr;
					ind++;
				}
				i = 0;
			//	ft_putnbr(nbr);
			//	ft_putstr(" _ ");
			}
			else
				i++;
		}
		if (k % 66 == 64)
		{
			checksum &= 0x3f;
			checksum += 48;
//			ft_putnbr(ind);
//			ft_putstr(" expected: ");
//			write(1, &checksum, 1);
//			ft_putstr("\n");
//			ft_putstr("real: ");
//			write(1, &caract, 1);
//			ft_putstr("\n");
			checksum = 0;
		}
		k++;
	}
	return (ind);
}
