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
	return wnd->Show(true);
}

JFVGL::WXWindow::WXWindow() : wxFrame(NULL, wxID_ANY, "teeeeeeest")
{
	//Bind(wxEVT_CLOSE_WINDOW, &WXWindow::OnExit, this, wxID_EXIT);
}

JFVGL::WXWindow::~WXWindow(){ }

/* wxWidgets API */

void JFVGL::WXWindow::OnExit(wxCommandEvent &evt)
{
	Close(true);
}

/* API */

void JFVGL::WXWindow::Start(){ }
