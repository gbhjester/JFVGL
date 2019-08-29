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
	wnd->SetTitle("JFVGL");
	wnd->Show(true);
	if (wxApp::argc == 2)
		wnd->canvas->img->Open(wxApp::argv[1]);
	else
		wnd->canvas->img->Open("table2.png");
	wnd->SetTitle(/*"JFVGL - " + */*wnd->canvas->img->filename);
	// TODO Set display to display that mouse currently inside
	wnd->canvas->SizeFormToImage(true);
	return true;
}

JFVGL::WXWindow::WXWindow() : wxFrame(NULL, wxID_ANY, "JFVGL"){ }
JFVGL::WXWindow::~WXWindow(){ }