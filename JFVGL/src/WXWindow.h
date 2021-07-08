/**
 * WXWindow.h
 *
 * Created on May 11, 2019, 3:24 PM
 */

#pragma once

#include "wx/wx.h"
#include "wx/display.h"
#include "wx/frame.h"
#include "Main.h"
#include "WXCanvas.h"

#define JID_CM_PIN 6900

namespace JFVGL {
	class WXWindow : public wxFrame {
	private:
		/* wxWidgets variables */
		/* wxWidgets API */
	protected:
	public:
		WXCanvas *canvas;
		WXWindow(int argc, wxChar **argv);
		DECLARE_EVENT_TABLE()
		void OnRightClick(wxContextMenuEvent &e);
		void GenerateAndShowContextMenu();
		void test(wxContextMenuEvent &e);
	};
}
