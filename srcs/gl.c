#include "lidar.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glut.h>

#define NB_LINE 5

void changeSize(int w, int h) {

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



float angle = 0.0f;

int	is_key(char key)
{
	if (g_flag & (1 << (key - 'a')))
		return (1);
	return (0);
}

void	invert_key(unsigned char key)
{
	int	mask;

	mask = 1 << (key - 'a');
	if (is_key(key))
		g_flag = g_flag & ~mask;
	else
		g_flag = g_flag | mask;
}
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
		"q  to quit"};

	x = -8;
	y = 3.8;
	k = 0;
	inter_line = 0.4;
//	glColor3f(0.0f, 1.0f, 0.8f);
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
		fct_print(buffer);
	if (is_key('r'))
	{
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		angle += 0.4f;
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
	glutSwapBuffers();
	glFlush();
}


void	setup_flag(void)
{
	g_flag = 0;
	invert_key('p');
	invert_key('l');
}

void	keyboard(unsigned char key, int x, int y)
{

	(void)x;
	(void)y;
	if (key == 'q')
		exit(0);
	else
		invert_key(key);
}

int display(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutCreateWindow("OpenGL - First window demo");
	glutDisplayFunc(renderFunction);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(renderFunction);
	glutMainLoop();    
	return 1;
}
