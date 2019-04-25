/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/* 
 * File:   GLUTWindow.cpp
 * Author: Jester
 * 
 * Created on April 25, 2019, 1:57 AM
 */

#include "GLUTWindow.h"

GLUTWindow::GLUTWindow(){ }

GLUTWindow::~GLUTWindow(){ }

GLUTWindow &GLUTWindow::operator=(GLUTWindow rhs)
{
	if (this == &rhs)
		return *this;
	Swap(*this, rhs);
	return *this;
}

/* API */

void GLUTWindow::Start(int argc, char **argv)
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
	glClearColor(0.25f, 0.25f, 0.25f, 1.f);
	glColor3f(0.5f, 0.5f, 1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glutMainLoop();
}
