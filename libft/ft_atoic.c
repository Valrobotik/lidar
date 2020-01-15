/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 04:08:27 by roliveir          #+#    #+#             */
/*   Updated: 2019/11/02 09:59:27 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_atoic(const char *str)
{
	long		final;
	int			i;

	final = 0;
	i = 0;
	while (str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		return (0);
	if (str[i] > '9' || str[i] < '0')
		return (0);
	while (str[i] <= '9' && str[i] >= '0')
	{
		final *= 10;
		final += (str[i] - '0');
		i++;
		if (final > MAX_SHORT)
			return (0);
	}
	return (1);
}
