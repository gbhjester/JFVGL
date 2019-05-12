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
	WXWindow *wnd = new WXWindow();
	int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
	wnd->canvas = new WXCanvas(wnd, args);
	wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(wnd->canvas, 1, wxEXPAND);
	wnd->SetSizer(sizer);
	wnd->SetAutoLayout(true);
	return wnd->Show(true);
}

BEGIN_EVENT_TABLE(JFVGL::WXCanvas, wxGLCanvas)
EVT_PAINT(JFVGL::WXCanvas::Render)
EVT_SIZE(JFVGL::WXCanvas::Resized)
END_EVENT_TABLE()

JFVGL::WXWindow::WXWindow() : wxFrame(NULL, wxID_ANY, "teeeeeeest")
{
}

JFVGL::WXWindow::~WXWindow(){ }

/* wxWidgets API */

/* API */

void JFVGL::WXWindow::Start(){ }

void JFVGL::WXWindow::Render(){ }
