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

JFVGL::WXWindow::WXWindow() : wxFrame(NULL, wxID_ANY, "JFVGL"){ }
//JFVGL::WXWindow::~WXWindow(){ }

BEGIN_EVENT_TABLE(JFVGL::WXWindow, wxFrame)
EVT_CONTEXT_MENU(JFVGL::WXWindow::OnRightClick)
//EVT_(JFVGL::WXWindow::)
END_EVENT_TABLE()

void JFVGL::WXWindow::OnRightClick(wxContextMenuEvent &e)
{
	GenerateAndShowContextMenu();
}

void JFVGL::WXWindow::GenerateAndShowContextMenu()
{
	wxMenu cm;
	wxMenuItem it;
	cm.AppendCheckItem(JID_CM_PIN, "&Pin");
	cm.AppendSeparator();
	cm.Append(wxID_EXIT, "E&xit");
	//cm.Check(JID_CM_PIN, 1);
	cm.Bind(wxEVT_CONTEXT_MENU, &JFVGL::WXWindow::test, this, JID_CM_PIN);
	PopupMenu(&cm);
}

void JFVGL::WXWindow::test(wxContextMenuEvent &e)
{
	wxMessageBox("one", "two");
	//Close(true);
}
