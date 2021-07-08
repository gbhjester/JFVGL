/*
 * 
 */

/**
 * Main.c
 */

#include "wx/wx.h"
#include "Main.h"
#include "WXApp.h"

// wx entry point
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, wxCmdLineArgType, int nCmdShow) {
	return wxEntry(hInstance, hPrevInstance, __null, nCmdShow);
}

JFVGL::WXApp &wxGetApp() {
	return *(JFVGL::WXApp *) wxApp::GetInstance();
}

wxAppConsole *wxCreateApp() {
	wxAppConsole::CheckBuildOptions(
			"3" "." "1" "." "2" " (" "wchar_t" ",compiler with C++ ABI compatible with gcc 4" ",wx containers" ",compatible with 3.0" ")",
			"your program");
	return new JFVGL::WXApp;
}

wxAppInitializer wxTheAppInitializer((wxAppInitializerFunction) wxCreateApp);
