/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/**
 * Main.c
 */

#include <cerrno>
#include <cstdlib>
#include "Main.h"
#include "GLUTWindow.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include "stb_image.h"

unsigned int texid;
unsigned char *img;
int px = 0, py = 0;
int dx = 0, dy = 0;
int cx = 0, cy = 0;
int w, h, ch;

int main(int argc, char *argv[])
{
	/*GLUTWindow wnd;
	wnd.Start(argc, argv);
	return 0;*/
	//const char *fn = "E:/torrents/updated mosiac.png";
	const char *fn = "table.jpg";
	w = 3840;
	h = 2160;
	//const char *fn = "nrm.png";w = 1024;h = 1024;
	//const char *fn = "table2.png";w = 375;h = 375;
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
		glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		glScissor(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		glEnable(GL_SCISSOR_TEST);
		/*float v[] = {
			-1.f, 1.f,
			1.f, 1.f,
			-1.f, -1.f,
			1.f, -1.f
		};*/
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
			((float)cx * (2.f / 1)),
			-((float)cy * (2.f / 1)), 0.f);
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
		/*glClear(GL_COLOR_BUFFER_BIT);
		glDrawPixels(w, h, GL_RGB, GL_UNSIGNED_BYTE, img);*/
	});
	glutMouseFunc([](int btn, int state, int x, int y)
	{
		if (state == 1)
			return;
	});
	glutMouseWheelFunc([](int wheel, int dir, int x, int y)
	{
		/*auto fmin = [](float a, float b)
		{
			if (a < b)
				return a;
			else
				return b;
		};
		auto fmax = [](float a, float b)
		{
			if (a > b)
				return a;
			else
				return b;
		};
		auto fclamp = [](float a, float x, float b)
		{
			if (x < a)
				return a;
			else if (x > b)
				return b;
			else
				return x;
		};
		float s = 0.1f;*/
		if (dir == 1)
		{
			//f = fmin(f + s, 2.f);
			//f = fclamp(0.5f, f + s, 2.f);
			f *= 1.1f;
		}
		else if (dir == -1)
		{
			//f = fmax(f - s, 0.5f);
			//f = fclamp(0.5f, f - s, 2.f);
			f *= 1.f / 1.1f;
		}
		glutPostRedisplay();
		printf("%f\n", f);
	});
	glutMotionFunc([](int x, int y)
	{
		dx = x - px;
		dy = y - py;
		cx += dx;
		cy += dy;
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
	while (true)
	{
		glutMainLoopEvent();
	}
	glDeleteTextures(1, &texid);
	stbi_image_free(img);
	return 0;
}
