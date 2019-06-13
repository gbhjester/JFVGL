/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/* 
 * File:   WXCanvas.cpp
 * Author: Jester
 * 
 * Created on May 11, 2019, 7:21 PM
 */

#include "WXCanvas.h"

// TODO Move to class Preferences
#define WND_WMIN 300
#define WND_HMIN 300
#define FPS_TARGET 60
#define ZOOM_MIN 0.01f
#define ZOOM_MAX 10.f

JFVGL::WXCanvas::WXCanvas(wxFrame *owner, int *args)
: wxGLCanvas(owner, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
	this->context = new wxGLContext(this);
	SetCurrent(*context);
	this->fParent = owner;
	this->img = new WXImage();

	this->f = 1.f;
	this->px = 0, this->py = 0;
	this->ppx = 0, this->ppy = 0;
	this->dx = 0, this->dy = 0;
	this->cx = 0, this->cy = 0;

	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}

JFVGL::WXCanvas::~WXCanvas()
{
	delete context;
}

void JFVGL::WXCanvas::SizeFormToImage(bool bCenter)
{
	wxDisplay disp(wxDisplay::GetFromWindow(fParent));
	cx = 0;
	cy = 0;
	f = 1.f;
	if (img->w > disp.GetClientArea().width)
	{
		f = fclamp(ZOOM_MIN, (float) disp.GetClientArea().width / img->w, ZOOM_MAX);
	}
	if (img->h > disp.GetClientArea().height)
	{
		f = fclamp(ZOOM_MIN, (float) disp.GetClientArea().height / img->h, ZOOM_MAX);
	}
	if (!fParent->IsMaximized())
	{
		wxSize oldSize(fParent->GetSize());
		oldSize -= fParent->GetSize() - fParent->GetClientSize();
		wxPoint oldCenter(fParent->GetPosition());
		oldCenter.x += (oldSize.x) / 2;
		oldCenter.y += (oldSize.y) / 2;
		fParent->SetClientSize(
			JFVGL::fclamp(WND_WMIN, img->w * f, disp.GetClientArea().width),
			JFVGL::fclamp(WND_HMIN, img->h * f, disp.GetClientArea().height));
		if (bCenter)
		{
			fParent->SetPosition(wxPoint(
				(disp.GetClientArea().width - fParent->GetSize().x) / 2,
				(disp.GetClientArea().height - fParent->GetSize().y) / 2));
		}
		else
		{
			fParent->SetPosition(wxPoint(
				oldCenter.x - (GetSize().x / 2),
				oldCenter.y - (GetSize().y / 2)));
		}
	}
}

BEGIN_EVENT_TABLE(JFVGL::WXCanvas, wxGLCanvas)
EVT_PAINT(JFVGL::WXCanvas::Render)
EVT_SIZE(JFVGL::WXCanvas::Resized)
EVT_MOTION(JFVGL::WXCanvas::MouseMoved)
EVT_MOUSEWHEEL(JFVGL::WXCanvas::MouseWheel)
EVT_LEFT_DCLICK(JFVGL::WXCanvas::MouseLeftDoubleClick)
EVT_MIDDLE_DCLICK(JFVGL::WXCanvas::MouseMiddleDoubleClick)
EVT_KEY_DOWN(JFVGL::WXCanvas::KeyDown)
//EVT_(JFVGL::WXCanvas::)
END_EVENT_TABLE()

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
	dx = e.GetX() - px;
	dy = e.GetY() - py;
	if (e.LeftIsDown()) // LMB - pan window
	{
		if (!((wxFrame *)GetParent())->IsMaximized())
		{
			GetParent()->Move(
				e.GetX() - ppx + GetParent()->GetPosition().x,
				e.GetY() - ppy + GetParent()->GetPosition().y);
		}
	}
	else if (e.RightIsDown()) // RMB - pan view
	{
		cx += dx / f;
		cy += dy / f;
	}
	else // Nothing pressed
	{
		ppx = e.GetX();
		ppy = e.GetY();
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
#ifdef DEBUG
	printf("Zoom %f%%\n", f * 100);
#endif
}

void JFVGL::WXCanvas::MouseLeftDoubleClick(wxMouseEvent &e)
{
	fParent->Maximize(!fParent->IsMaximized());
}

void JFVGL::WXCanvas::MouseMiddleDoubleClick(wxMouseEvent &e)
{
	GetParent()->Close(true);
}

void JFVGL::WXCanvas::KeyDown(wxKeyEvent &e)
{
	if (e.GetKeyCode() == WXK_ESCAPE || e.GetKeyCode() == WXK_RETURN)
	{
		fParent->Close(true);
		return;
	}
	
	if (e.GetKeyCode() == WXK_LEFT || e.GetKeyCode() == WXK_RIGHT)
	{
		fParent->SetTitle("Loading...");
		if (e.GetKeyCode() == WXK_LEFT)
			img->TraverseDirectory(-1);
		else if (e.GetKeyCode() == WXK_RIGHT)
			img->TraverseDirectory(1);
		fParent->SetTitle(*img->filename);
		SizeFormToImage(false);
		Refresh();
	}
}
