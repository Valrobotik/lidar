#include "lidar.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <unistd.h>

#define NB_LINE 6

/*
 * exemple took on internet on window resize, optional in our case
*/

void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}


// global variable, used to make some test
float angle = 0.0f;

/*
 * bit wise function, g_flag is an int (32 bits), 'a' to 'z' are the first 27 bit, if needed more still 5 bits disponible ()
 * used to know if a key have been pressed
 */
int	is_key(char key)
{
	if (g_flag & (1 << (key - 'a')))
		return (1);
	return (0);
}

/*
 * active the bit assigne to the pressed key if OFF, or clear it if ON
 */
void	invert_key(unsigned char key)
{
	int	mask;

	mask = 1 << (key - 'a');
	if (is_key(key))
		g_flag = g_flag & ~mask;
	else
		g_flag = g_flag | mask;
}

/*
 * display a string on the current position of the cursor
 */
void gl_put_str(char *str)
{
	int	k;

	k = 0;
	while (str[k])
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[k]);
		k++;
	}
}

/*
 * display the tab of information about the key pressed
 */
void display_tab(void)
{
	float	x;
	float	y;
	int	k;
	float	inter_line;
	char	*str[NB_LINE] = {"a  to automatic display",
		"p  to display polar",
		"l  to display linear",
		"b  to print the current view",
		"q  to quit",
		"s  to secure stop"};

	x = -8;
	y = 3.8;
	k = 0;
	inter_line = 0.4;
	while (k < NB_LINE)
	{
		if (is_key(str[k][0]))
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);
		glRasterPos2f(x, y - k * inter_line);
		gl_put_str(str[k]);
		k++;
	}
}

void display_mes(char *str)
{
	int	k;

	glRasterPos2f(-4, 0);
	k = 0;
	while (str[k])
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[k]);
		k++;
	}
}
/*
 * loop of the function display
 */
void renderFunction(void)
{
	char	buffer[READ_BUFF];

	//glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glLoadIdentity();

	gluLookAt(	0.0f, 0.0f, 10.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f);
	display_tab();
	if (is_key('b'))
	{
		fct_print(buffer);
		invert_key('b');
	}
	if (is_key('a'))
	{
		lidar_try_get_resp(g_fds, g_fd);
		fct_decod_resp_name(CMD_INF);
	}
	if (is_key('r'))
	{
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		angle += 0.4f;
	}
	if (is_key('m'))
	{
		display_mes("HOLA A TODOS!");
	}
	if (is_key('l'))
	{
		glColor3f(1.0, 1.0, 0.0);
		linear_display();
	}
	if (is_key('p'))
	{
		glColor3f(1.0, 0.0, 1.0);
		polar_display(-2.0944, 2.0944);
	}
	if (is_key('s'))
		led_stop();
	glutSwapBuffers();
	glFlush();
}

/*
 * initialize the status of the flags: polar and linear display activate by default
 */
void	setup_flag(void)
{
	g_flag = 0;
	if (g_fd > 0)
	{
		invert_key('p');
		invert_key('l');
	}
}

/*
 * function called when a key is pressed
 */
void	keyboard(unsigned char key, int x, int y)
{
	char	buffer[READ_BUFF];

	(void)x;
	(void)y;
	if (key == 'a')
	{
		if (is_key('a'))
		{
			write(g_fd, "QT\n", 3);
			write(1, "QT\n", 3);
		}
		else
		{
			strcpy(buffer, CMD_INF);
			write(g_fd, buffer, strlen(buffer));
			write(1, "MDSTUFF\n", 8);
		}
	}
	if (key == 'q')
	{
		exit(0);
	}
	else
	{
		invert_key(key);
	}
}

int display(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutCreateWindow("OpenGL - First window demo");
	glutDisplayFunc(renderFunction);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(renderFunction);
	glutMainLoop();    
	return (1);
}
