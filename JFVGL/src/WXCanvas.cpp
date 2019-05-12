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
#include "WXImage.h"

// TODO Move to class Preferences
#define FPS_TARGET 60
#define ZOOM_MIN 0.01f
#define ZOOM_MAX 10.f

JFVGL::WXCanvas::WXCanvas(wxFrame *owner, int *args)
: wxGLCanvas(owner, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
	this->context = new wxGLContext(this);
	SetCurrent(*context);
	this->img = new WXImage();
	
	this->f = 1.f;
	this->mx = 0;

	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}

JFVGL::WXCanvas::~WXCanvas()
{
	delete context;
}

// TODO Refactor into class WXCanvas
//float f = 1.f;
float px = 0, py = 0; // Previous mouse coords
float ppx = 0, ppy = 0; // Previous passive mouse coords (not updated while dragging)
float dx = 0, dy = 0; // Delta mouse coords (x - px)
float cx = 0, cy = 0;

/* Events */

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
		0.f - img->w, 0.f + img->h,
		0.f + img->w, 0.f + img->h,
		0.f - img->w, 0.f - img->h,
		0.f + img->w, 0.f - img->h
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
		(cx * 2.f),
		-(cy * 2.f), 0.f);
	glVertexPointer(2, GL_FLOAT, 0, v);
	glTexCoordPointer(2, GL_FLOAT, 0, uv);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D, img->id);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor3f(1.f, 1.f, 1.f);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, vi);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glFlush();
	SwapBuffers(); // If double buffering
}

void JFVGL::WXCanvas::Resized(wxSizeEvent &e){
	// NOTE On Linux, call Update() instead?
	//Refresh();
}

void JFVGL::WXCanvas::MouseMoved(wxMouseEvent &e)
{
	mx = e.GetX();
	dx = e.GetX() - px;
	dy = e.GetY() - py;
	if (e.LeftIsDown())
	{
		cx += dx / f;
		cy += dy / f;
	}
	else if (e.RightIsDown())
	{
		// TODO Drag window
		/*glutPositionWindow(
			x - glutGet(GLUT_WINDOW_BORDER_WIDTH) - ppx + glutGet(GLUT_WINDOW_X),
			e.m_y - glutGet(GLUT_WINDOW_BORDER_HEIGHT) - ppy + glutGet(GLUT_WINDOW_Y));*/
	}
	Refresh();
	px = e.GetX();
	py = e.GetY();
}

void JFVGL::WXCanvas::MouseWheel(wxMouseEvent &e)
{
	if (e.GetWheelRotation() > 0)
	{
		f = fclamp(ZOOM_MIN, f * 1.1f, ZOOM_MAX);
	}
	else if (e.GetWheelRotation() < 0)
	{
		f = fclamp(ZOOM_MIN, f * (1.f / 1.1f), ZOOM_MAX);
	}
	Refresh();
	printf("%f\n", f);
}

void JFVGL::WXCanvas::MouseMiddleDoubleClick(wxMouseEvent &e)
{
	GetParent()->Close(true);
}

void JFVGL::WXCanvas::KeyDown(wxKeyEvent &e)
{
	if (e.GetUnicodeKey() == 27 || e.GetUnicodeKey() == 13)
		GetParent()->Close(true);
}
