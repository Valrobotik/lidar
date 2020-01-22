#include "libft.h"
#include <poll.h>

#define LIDAR_BUFF 5600
#define READ_BUFF 200
#define NBR_VAL 682

char	g_buff[LIDAR_BUFF];
int	*g_range;
int	g_size;

int	decode(const char code[], int byte);
int	code_decode(char *str, int *pos, int range[682], int nb);
void	ft_print_digit(int *range, int size);
void	ft_print_digit_fd(int fd, int *range, int size);
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


	/* com function */

int	open_serial(void);
int	lidar_write(char *word, int fd);
int	lidar_read(char *buffer[4096], int fd);

int	lidar_cmd_is_premade(char buffer[READ_BUFF], struct pollfd fds[1], int fd);
void	lidar_get_resp(struct pollfd fds[1], int fd);
void	lidar_do_loop(struct pollfd fds[1], int fd);
