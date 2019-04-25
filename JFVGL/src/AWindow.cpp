/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/* 
 * AWindow.cpp
 * @author Jester
 */

#include "AWindow.h"

AWindow::AWindow()
{
}

AWindow::~AWindow()
{
}

void AWindow::init(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(
		glutGet(GLUT_SCREEN_WIDTH) / 3,
		glutGet(GLUT_SCREEN_HEIGHT) / 2);
	glutInitWindowPosition(
		(glutGet(GLUT_SCREEN_WIDTH) - glutGet(GLUT_INIT_WINDOW_WIDTH)) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - glutGet(GLUT_INIT_WINDOW_HEIGHT)) / 2);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("JFVGL");
	glutDisplayFunc([]()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(0.5, -0.5);
		glEnd();
		glFlush();
	});
	glClearColor(0.0, 0.0, 0.0, 1.0); // JMU Gold
	glColor3f(.5, 0.5, 1.000); // JMU Purple
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glutMainLoop();
}
