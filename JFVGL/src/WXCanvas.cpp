/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/* 
 * File:   WXCanvas.cpp
 * Author: Jester
 * 
 * Created on May 11, 2019, 7:21 PM
 */

#include <GL/glu.h>
#include <GL/gl.h>
#include "WXCanvas.h"

JFVGL::WXCanvas::WXCanvas(wxFrame *owner, int *args)
: wxGLCanvas(owner, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
	context = new wxGLContext(this);

	//SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}

JFVGL::WXCanvas::~WXCanvas()
{
	delete context;
}

unsigned int texid;
unsigned char *img;
int w, h, ch;
float f = 1.f;
float px = 0, py = 0; // Previous mouse coords
float ppx = 0, ppy = 0; // Previous passive mouse coords (not updated while dragging)
float dx = 0, dy = 0; // Delta mouse coords (x - px)
float cx = 0, cy = 0;

void JFVGL::WXCanvas::Render(wxPaintEvent& e)
{
	if (!IsShown())
		return;

	wxGLCanvas::SetCurrent(*context);
	wxPaintDC(this);

	glViewport(0, 0, GetClientSize().x, GetClientSize().y);
	glScissor(0, 0, GetClientSize().x, GetClientSize().y);
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
		f / (float)GetClientSize().x,
		f / (float)GetClientSize().y, 0.f);
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
	SwapBuffers(); // If double buffering
}

void JFVGL::WXCanvas::Resized(wxSizeEvent& e)
{
	// NOTE On Linux, call Update() instead?
	Refresh();
}
