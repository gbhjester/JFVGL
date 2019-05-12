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

bool JFVGL::WXApp::OnInit()
{
	wxInitAllImageHandlers();
	WXWindow *wnd = new WXWindow();
	int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
	wnd->canvas = new WXCanvas(wnd, args);
	wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(wnd->canvas, 1, wxEXPAND);
	wnd->SetSizer(sizer);
	wnd->SetAutoLayout(true);
	wnd->canvas->img->Open("table2.png");
	return wnd->Show(true);
}

BEGIN_EVENT_TABLE(JFVGL::WXCanvas, wxGLCanvas)
EVT_PAINT(JFVGL::WXCanvas::Render)
EVT_SIZE(JFVGL::WXCanvas::Resized)
EVT_MOTION(JFVGL::WXCanvas::MouseMoved)
EVT_MOUSEWHEEL(JFVGL::WXCanvas::MouseWheel)
/*EVT_LEFT_DOWN(JFVGL::WXCanvas::)
EVT_LEFT_UP(JFVGL::WXCanvas::)
EVT_LEFT_DCLICK(JFVGL::WXCanvas::)
EVT_MIDDLE_DOWN(JFVGL::WXCanvas::)
EVT_MIDDLE_UP(JFVGL::WXCanvas::)*/
EVT_MIDDLE_DCLICK(JFVGL::WXCanvas::MouseMiddleDoubleClick)
/*EVT_RIGHT_DOWN(JFVGL::WXCanvas::)
EVT_RIGHT_UP(JFVGL::WXCanvas::)
EVT_RIGHT_DCLICK(JFVGL::WXCanvas::)*/
/*EVT_MOUSE_AUX1_DOWN(JFVGL::WXCanvas::)
EVT_MOUSE_AUX1_UP(JFVGL::WXCanvas::)
EVT_MOUSE_AUX1_DCLICK(JFVGL::WXCanvas::)
EVT_KEY_DOWN(JFVGL::WXCanvas::)
EVT_KEY_UP(JFVGL::WXCanvas::)
//EVT_(JFVGL::WXCanvas::)*/
END_EVENT_TABLE()

JFVGL::WXWindow::WXWindow() : wxFrame(NULL, wxID_ANY, "JFVGL")
{
}

JFVGL::WXWindow::~WXWindow(){ }

/* wxWidgets API */

/* API */

void JFVGL::WXWindow::Start(){ }

void JFVGL::WXWindow::Render(){ }
