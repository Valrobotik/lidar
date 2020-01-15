#include "lidar.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glut.h>

void	form_bat(void)
{	
	glBegin(GL_LINE_STRIP);
		glVertex2i(-3, 0);
		glVertex2i(-1, 2);
		glVertex2i(0, 1);
		glVertex2i(1, 2);
		glVertex2i(3, 0);
		glVertex2i(1, -2);
		glVertex2i(0, -1);
		glVertex2i(-1, -2);
		glVertex2i(-3, 0);
	glEnd();
}

void	form_tri(void)
{	
	glBegin(GL_TRIANGLES);
		glVertex3f(-2.0f, -2.0f, 0.0f);
		glVertex3f(2.0f, 0.0f, 0.0);
		glVertex3f(0.0f, 2.0f, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex3f(2.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0);
		glVertex3f(2.0f, 2.0f, 0.0);
	glEnd();
}


