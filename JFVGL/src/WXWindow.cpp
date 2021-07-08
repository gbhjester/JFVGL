/**
 * WXWindow.cpp
 * 
 * Created on May 11, 2019, 3:24 PM
 */

#include "WXWindow.h"

JFVGL::WXWindow::WXWindow(int argc, wxChar **argv) : wxFrame(NULL, wxID_ANY, "JFVGL") {
	int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
	canvas = new WXCanvas(this, args);
	wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(canvas, 1, wxEXPAND);
	SetSizer(sizer);
	SetAutoLayout(true);
	Show(true);
	if (argc == 2) {
		canvas->img->Open(argv[1]);
	} else {
		canvas->img->Open("table2.png");
	}
	SetTitle(/*"JFVGL - " + */*canvas->img->filename);
	// TODO Set window to open on display mouse currently inside
	canvas->SizeFormToImage(true);
}
// WHY IS THIS DTOR EMPTY
//JFVGL::WXWindow::~WXWindow() {}

BEGIN_EVENT_TABLE(JFVGL::WXWindow, wxFrame)
EVT_CONTEXT_MENU(JFVGL::WXWindow::OnRightClick)
//EVT_(JFVGL::WXWindow::)
END_EVENT_TABLE()

void JFVGL::WXWindow::OnRightClick(wxContextMenuEvent &e) {
	GenerateAndShowContextMenu();
}

void JFVGL::WXWindow::GenerateAndShowContextMenu() {
	wxMenu cm;
	wxMenuItem it;
	cm.AppendCheckItem(JID_CM_PIN, "&Pin");
	cm.AppendSeparator();
	cm.Append(wxID_EXIT, "E&xit");
	//cm.Check(JID_CM_PIN, 1);
	cm.Bind(wxEVT_CONTEXT_MENU, &JFVGL::WXWindow::test, this, JID_CM_PIN);
	PopupMenu(&cm);
}

void JFVGL::WXWindow::test(wxContextMenuEvent &e) {
	wxMessageBox("one", "two");
	//Close(true);
}
