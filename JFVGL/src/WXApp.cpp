/**
 * WXWindow.cpp
 *
 * Created on November 15, 2019, 8:26 PM
 */

#include "WXApp.h"

bool JFVGL::WXApp::OnInit() {
	wxInitAllImageHandlers();
	wnd = new WXWindow(wxApp::argc, wxApp::argv);
	/*wxDisplay disp(wxDisplay::GetFromWindow(wnd));
	wnd->SetSize(
			disp.GetClientArea().width / 4, disp.GetClientArea().height / 4,
			disp.GetClientArea().width / 2, disp.GetClientArea().height / 2);*/
	return true;
}
