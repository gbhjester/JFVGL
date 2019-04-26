/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/* 
 * File:   GLUTWindow.cpp
 * Author: Jester
 * 
 * Created on April 25, 2019, 1:57 AM
 */

#include <cmath>
#include <cstdio>
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

float s(float p, float t)
{
	return p*t;
}

void GLUTWindow::Start(int argc, char **argv)
{
	static float f = 1.f;
	glutInit(&argc, argv);
	glutInitWindowSize(
		glutGet(GLUT_SCREEN_WIDTH) / 3,
		glutGet(GLUT_SCREEN_HEIGHT) / 2);
	glutInitWindowPosition(
		(glutGet(GLUT_SCREEN_WIDTH) - glutGet(GLUT_INIT_WINDOW_WIDTH)) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - glutGet(GLUT_INIT_WINDOW_HEIGHT)) / 2);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE /*| GLUT_MULTISAMPLE*/);
	glutCreateWindow("JFVGL");
	glutDisplayFunc([]()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_POLYGON);
		float t = f;
		float x = -0.5f;
		float y = -0.5f;
		glVertex2f(s(x, t), s(y, t));
		x = -0.5f;
		y = 0.5f;
		glVertex2f(s(x, t), s(y, t));
		x = 0.5f;
		y = 0.5f;
		glVertex2f(s(x, t), s(y, t));
		x = 0.5f;
		y = -0.5f;
		glVertex2f(s(x, t), s(y, t));
		/*glVertex2f(-0.5, -0.5);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(0.5, -0.5);*/
		glEnd();
		glFlush();
	});
	glutMouseFunc([](int btn, int state, int x, int y)
	{
		if (state == 1)
			return;
		float s = 0.1f;
		if (btn == GLUT_LEFT_BUTTON)
		{
			f += s;
		}
		else if (btn == GLUT_RIGHT_BUTTON)
		{
			f -= s;
		}
		glutPostRedisplay();
		printf("%f\n", f);
	});
	glClearColor(0.25f, 0.25f, 0.25f, 1.f);
	glColor3f(0.5f, 0.5f, 1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	while (true)
	{
		glutMainLoopEvent();
	}
}
