#include "lidar.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glut.h>

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

void renderFunction(void)
{
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glLoadIdentity();

	gluLookAt(	0.0f, 0.0f, 10.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f);

	//glRotatef(angle, 0.0f, 1.0f, 0.0f);

	linear_display();

	glColor3f(1.0, 0.0, 1.0);
	polar_display(-2.0944, 2.0944);

	//angle += 0.4f;
	glutSwapBuffers();
	//glFlush();
}

int display(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(1200,600);
	glutCreateWindow("OpenGL - First window demo");

	glutDisplayFunc(renderFunction);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderFunction);
	glutMainLoop();    
	return 1;
}
