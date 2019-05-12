/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/* 
 * File:   wxWindow.cpp
 * Author: Jester
 * 
 * Created on May 11, 2019, 3:24 PM
 */

#include "WXWindow.h"

// TODO Move to Preferences
#define WND_WMIN 400
#define WND_HMIN 300

bool JFVGL::WXApp::OnInit()
{
	wxInitAllImageHandlers();
	WXWindow *wnd = new WXWindow();
	wxDisplay disp(wxDisplay::GetFromWindow(wnd));
	wnd->SetSize(
		disp.GetClientArea().width / 4, disp.GetClientArea().height / 4,
		disp.GetClientArea().width / 2, disp.GetClientArea().height / 2);
	int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
	wnd->canvas = new WXCanvas(wnd, args);
	wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(wnd->canvas, 1, wxEXPAND);
	wnd->SetSizer(sizer);
	wnd->SetAutoLayout(true);
	if (wxApp::argc == 2)
		wnd->canvas->img->Open(wxApp::argv[1]);
	else
		wnd->canvas->img->Open("table2.png");
	wnd->SetTitle("JFVGL - " + *wnd->canvas->img->filename);
	// TODO Set display to display mouse currently inside
	wnd->SetSize(
		JFVGL::fclamp(WND_WMIN, wnd->canvas->img->w, disp.GetClientArea().width),
		JFVGL::fclamp(WND_HMIN, wnd->canvas->img->h, disp.GetClientArea().height));
	wnd->SetPosition(wxPoint(
		(disp.GetClientArea().width - wnd->GetSize().x) / 2,
		(disp.GetClientArea().height - wnd->GetSize().y) / 2));
	return wnd->Show(true);
}

BEGIN_EVENT_TABLE(JFVGL::WXCanvas, wxGLCanvas)
EVT_PAINT(JFVGL::WXCanvas::Render)
EVT_SIZE(JFVGL::WXCanvas::Resized)
EVT_MOTION(JFVGL::WXCanvas::MouseMoved)
EVT_MOUSEWHEEL(JFVGL::WXCanvas::MouseWheel)
EVT_MIDDLE_DCLICK(JFVGL::WXCanvas::MouseMiddleDoubleClick)
EVT_KEY_DOWN(JFVGL::WXCanvas::KeyDown)
//EVT_(JFVGL::WXCanvas::)
END_EVENT_TABLE()

JFVGL::WXWindow::WXWindow() : wxFrame(NULL, wxID_ANY, "JFVGL"){ }

JFVGL::WXWindow::~WXWindow(){ }

/* wxWidgets API */

/* API */

void JFVGL::WXWindow::Start(){ }

void JFVGL::WXWindow::Render(){ }
