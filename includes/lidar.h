int	*g_range;
int	g_size;

int	decode(const char code[], int byte);
int	code_decode(char *str, int *pos, int range[682], int nb);
void	ft_print_digit(int *range, int size);
void	ft_print_digit_fd(int fd, int *range, int size);
void	ft_putnbr(int nbr);
void	ft_putnbr_fd(int fd, int nbr);
void	ft_putstr(char *str);
void	ft_putstr_fd(int fd,char *str);
char	*cmd_finder(char *str, int *pos);
char	*scnd_finder(char *str, int *pos);
char	*time_finder(char *str, int *pos);
char	*code_finder(char *str, int *pos);

	/* diplay function */

void	linear_display(void);
void	polar_display(double start, double end);
int	display(int argc, char **argv);
void	form_bat(void);
void	form_tri(void);
