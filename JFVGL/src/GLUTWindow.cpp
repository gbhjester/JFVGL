/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/* 
 * File:   GLUTWindow.cpp
 * Author: Jester
 * 
 * Created on April 25, 2019, 1:57 AM
 */

#include <cerrno>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "GL/freeglut.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include "stb_image.h"
#include "GLUTWindow.h"

// TODO Move to class Preferences
#define FPS_TARGET 60
#define ZOOM_MIN 0.01f
#define ZOOM_MAX 10.f

JFVGL::GLUTWindow::GLUTWindow(){ }

JFVGL::GLUTWindow::~GLUTWindow(){ }

unsigned int texid;
unsigned char *img;
int w, h, ch;
float f = 1.f;
float px = 0, py = 0; // Previous mouse coords
float ppx = 0, ppy = 0; // Previous passive mouse coords (not updated while dragging)
float dx = 0, dy = 0; // Delta mouse coords (x - px)
float cx = 0, cy = 0;
int btnPressed; // Current button pressed, or -1

// For now
// TODO Remove / refactor
int JFVGL::GLUTWindow::DoGlutStuff(int argc, char **argv)
{
	const char *fn;
	if (argc == 2)
		fn = argv[1];
	else
	{
		//fn = "E:/torrents/updated mosaic.png";
		//fn = "table.jpg";
		//fn = "nrm.png";
		fn = "table2.png";
		//fn = "plasma.png";
	}
	img = stbi_load(fn, &w, &h, &ch, 3);
	if (img)
	{
		const char *format = NULL;
		switch (ch)
		{
		case 1:
			format = "g";
			break;
		case 2:
			format = "ga";
			break;
		case 3:
			format = "rgb";
			break;
		case 4:
			format = "rgba";
			break;
		default:
			format = "Unknown";
		}
		printf("Loaded image %s\nWidth : %d\nHeight : %d\nFormat : %s\n", fn, w, h, format);
	}
	else
	{
		printf("Image failed to load : %s (%s)\n", stbi_failure_reason(), strerror(errno));
		return -1;
	}
	/*for (int i = 0; i < w*h*3; i += 3)
	{
		printf("[%u %u %u]\n", img[i], img[i + 1], img[i + 2]);
	}
	return 0;*/
	glutInit(&argc, argv);

	if (img)
	{
		glutInitWindowSize(
			fclamp(w, w, glutGet(GLUT_SCREEN_WIDTH)),
			fclamp(h, h, glutGet(GLUT_SCREEN_HEIGHT)));
		/*f = fmax(
			(float)w / (float)glutGet(GLUT_SCREEN_WIDTH),
			(float)h / (float)glutGet(GLUT_SCREEN_HEIGHT));*/
	}
	else
	{
		glutInitWindowSize(
			glutGet(GLUT_SCREEN_WIDTH) / 3,
			glutGet(GLUT_SCREEN_HEIGHT) / 2);
	}
	glutInitWindowPosition(
		(glutGet(GLUT_SCREEN_WIDTH) - glutGet(GLUT_INIT_WINDOW_WIDTH)) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - glutGet(GLUT_INIT_WINDOW_HEIGHT)) / 2);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE /*| GLUT_MULTISAMPLE*/);
	glutCreateWindow("JFVGL");
	glutDisplayFunc([]()
	{
		glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		glScissor(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		glEnable(GL_SCISSOR_TEST);
		float v[] = {
			(float)-w, (float)h,
			(float)w, (float)h,
			(float)-w, (float)-h,
			(float)w, (float)-h
		};
		unsigned short vi[] = {0, 1, 2, 2, 3, 1};
		float uv[] = {
			0.f, 0.f,
			1.f, 0.f,
			0.f, 1.f,
			1.f, 1.f
		};
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glScalef(
			f / (float)glutGet(GLUT_WINDOW_WIDTH),
			f / (float)glutGet(GLUT_WINDOW_HEIGHT), 0.f);
		glTranslatef(
			((float)cx * 2.f),
			-((float)cy * 2.f), 0.f);
		glVertexPointer(2, GL_FLOAT, 0, v);
		glTexCoordPointer(2, GL_FLOAT, 0, uv);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindTexture(GL_TEXTURE_2D, texid);
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glColor3f(1.f, 1.f, 1.f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, vi);
		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glFlush();
	});
	glutMouseFunc([](int btn, int state, int x, int y)
	{
		if (state == 1)
		{
			btnPressed = -1;
			return;
		}
		btnPressed = btn;
	});
	glutMouseWheelFunc([](int wheel, int dir, int x, int y)
	{
		if (dir == 1)
		{
			//f *= 1.1f;
			f = fclamp(ZOOM_MIN, f * 1.1f, ZOOM_MAX);
		}
		else if (dir == -1)
		{
			//f *= 1.f / 1.1f;
			f = fclamp(ZOOM_MIN, f * (1.f / 1.1f), ZOOM_MAX);
		}
		glutPostRedisplay();
		printf("%f\n", f);
	});
	glutMotionFunc([](int x, int y)
	{
		dx = x - px;
		dy = y - py;
		if (btnPressed == GLUT_LEFT_BUTTON)
		{
			cx += dx / f;
				cy += dy / f;
		}
		else if (btnPressed == GLUT_RIGHT_BUTTON)
		{
			glutPositionWindow(
				x - glutGet(GLUT_WINDOW_BORDER_WIDTH) - ppx + glutGet(GLUT_WINDOW_X),
				y - glutGet(GLUT_WINDOW_BORDER_HEIGHT) - ppy + glutGet(GLUT_WINDOW_Y));
		}
		glutPostRedisplay();
		px = x;
		py = y;
	});
	glutPassiveMotionFunc([](int x, int y)
	{
		dx = x - px;
		dy = y - py;
		//glutPostRedisplay();
		px = x;
		py = y;
		ppx = x;
		ppy = y;
	});
	glutKeyboardFunc([](unsigned char key, int x, int y)
	{
		switch (key)
		{
		case 27: // Esc
			exit(27); // Panic quit for testing
			break;
		case 13: // Enter
			exit(0);
			break;
		default:
			break;
		}
	});
	glClearColor(0.25f, 0.25f, 0.25f, 1.f);
	glColor3f(0.5f, 0.5f, 1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGB,
		w,
		h,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		img);
	// TODO Integrate?
	while (true)
	{
		if (glutGet(GLUT_ELAPSED_TIME) % (int)(1000.f / FPS_TARGET) != 0)
			Sleep(1000 / FPS_TARGET);
		glutMainLoopEvent();
	}
	glDeleteTextures(1, &texid);
	stbi_image_free(img);
}

/* API */

void JFVGL::GLUTWindow::Start()
{
}
