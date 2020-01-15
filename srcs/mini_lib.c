#include <unistd.h>

int	decode(const char code[], int byte)
{
	int	value = 0;
	int	i;

	for (i = 0; i < byte; ++i)
	{
		value <<= 6;
		value &= ~0x3f;
		value |= code[i] - 0x30;
	}
	return (value);
}

void	ft_putnbr(int nbr)
{
	long	dec;
	char	n;
	long	nbrl;

	nbrl = nbr;
	if (nbr == 0)
		write(1, "0", 1);
	if (nbr < 0)
	{
		nbrl = -nbr;
		write(1, "-", 1);
	}
	dec = 1;
	while (nbrl / dec)
		dec = dec * 10;
	dec = dec / 10;
	while (dec > 0)
	{
		n = nbrl / dec;
		nbrl = nbrl - n * dec;
		dec = dec / 10;
		n = n + '0';
		write(1, &n, 1);
	}
}

void	ft_putnbr_fd(int fd, int nbr)
{
	long	dec;
	char	n;
	long	nbrl;

	nbrl = nbr;
	if (nbr == 0)
		write(fd, "0", 1);
	if (nbr < 0)
	{
		nbrl = -nbr;
		write(fd, "-", 1);
	}
	dec = 1;
	while (nbrl / dec)
		dec = dec * 10;
	dec = dec / 10;
	while (dec > 0)
	{
		n = nbrl / dec;
		nbrl = nbrl - n * dec;
		dec = dec / 10;
		n = n + '0';
		write(fd, &n, 1);
	}
}


void	ft_putstr(char *str)
{
	int	k;

	k = 0;
	while (str[k])
		k++;
	write(1, str, k);
}

void	ft_putstr_fd(int fd, char *str)
{
	int	k;

	k = 0;
	while (str[k])
		k++;
	write(fd, str, k);
}

void	ft_print_digit(int *range, int size)
{
	int	k;

	k = 0;
	while (k < size)
	{
		ft_putnbr(range[k]);
		ft_putstr(" ");
		k++;
	}
}

void	ft_print_digit_fd(int fd, int *range, int size)
{
	int	k;

	k = 0;
	while (k < size)
	{
		ft_putnbr_fd(fd, range[k]);
		ft_putstr_fd(fd, " ");
		k++;
	}
}
