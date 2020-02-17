#include "libft.h"
#include <poll.h>
#include <time.h>

#define LIDAR_BUFF 6000 //dix fois trop grand pour l'essai
#define READ_BUFF 200
#define NBR_VAL 682
#define WIN_HEIGHT 600
#define WIN_WIDTH 1200

#define GNL_BUFF_SIZE 2048

#define CMD_INF "MD0044072501000\n" //command used to do infinite resp, terminated by QT\n command

#define PINOUT 21
#define PINREED 27
#define PINRESET 22
#define PINSIDE 17

#define	B_SIDE 0
#define Y_SIDE 1

#define STOP_TIME 97 	//prevoir une secu, genre 95/100

#define SIDE 4
#define REED 3
#define RESET 2		//1 is reserved for static initialisation


char		g_buff[LIDAR_BUFF];
int		*g_range;
int		g_size;
struct pollfd 	g_fds[1];
int		g_fd;
int		g_wr;
int		g_rd;
int		g_flag;
int		g_side;
clock_t		g_time_start;

	/* chained list, containing a status (in process or not procceded) and a command  */

typedef struct		s_pile
{
	struct s_pile	*next;
	char		*cmd;
	int		status;
	int		move;
	double		x;
	double		y;
	double		a;
	double		time;

}			t_pile;

	/* decode function */

//	find command, and srip it
char	*cmd_finder(char *str, int *pos);
//	find command and wait till it's the right one, and srip it
int	cmd_finder_name(char *str, int *pos, char *cmd);
//	find second element which is the status, and strip it
char	*scnd_finder(char *str, int *pos);
//	find the time stamp and strip it
char	*time_finder(char *str, int *pos);
//	find the code and decode (call decoder) it into the buffer
char	*code_finder(char *str, int *pos);
//	decode the data field (and might be inproved to check)
int	code_decode(char *str, int *pos, int nb);
//	decode 2 or 3 byte according to the lidar encodage into an int
int	decode(const char code[], int nbr_bytes);

	/* new lib functions */

void	ft_print_digit(int *range, int size);
void	ft_print_digit_fd(int fd, int *range, int size);
int	fct_print(char buffer[READ_BUFF]);
void	led_stop(void);
int	fct_decod_resp(void);
int	fct_decod_resp_name(char *cmd);
//int	get_next_line(char **str, char buffer[GNL_BUFF_SIZE]);

	/* diplay function */

//	display x function theta
void	linear_display(void);
//	display x function theta in polar
void	polar_display(double start, double end);
//	Main of the display element
int	display(int argc, char **argv);
//	Pre made forms, could be deleted
void	form_bat(void);
void	form_tri(void);

	/* flag functions */

void	setup_flag(void);

	/* com function */

int	open_serial(void);
int	lidar_write(char *word, int fd);
int	lidar_read(char *buffer[4096], int fd);

	/* aquisition function used to get the information sent by Lidar 
	 * try: will check if something is to be read or left
	 * 	otherwise it will continue until someting is to be read
	 * 	return wether it succed or not
	 * print: */

void	lidar_get_resp(struct pollfd fds[1], int fd);
int	lidar_try_get_resp(struct pollfd fds[1], int fd);
void	lidar_get_resp_print(struct pollfd fds[1], int fd);
int	lidar_try_get_resp_print(struct pollfd fds[1], int fd);

int	lidar_cmd_is_premade(char buffer[READ_BUFF]);

/*	FONCTION REAL CONDITIONS */

int	start_robot(void);
int	do_flag(char *str);
int	real_condition(void);

/*	FONCTION RISE & FALL	*/

int	detect_rising(int value, int elmt);
int	detect_falling(int value, int elmt);

/*	FONCTION PILE HUNDLER	*/

t_pile	*build_pile(void);
int	unpile_cmd(t_pile **pile);
void	get_resp(struct pollfd fds[1], int fd);
//int 	wait_tirette(void);
