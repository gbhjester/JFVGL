/**
 * WXCanvas.h
 *
 * Created on May 11, 2019, 7:21 PM
 */

#pragma once

#include <GL/glu.h>
#include <GL/gl.h>
#include "wx/wx.h"
#include "wx/display.h"
//#include "wx/event.h"
#include "wx/glcanvas.h"
#include "Main.h"
#include "WXImage.h"
#include "Main.h"

namespace JFVGL {

	class WXCanvas : public wxGLCanvas {
	private:
		wxGLContext *context;
		wxFrame *fParent;
		float f;
		float px, py; // Previous mouse coords
		float ppx, ppy; // Previous passive mouse coords (not updated while dragging)
		float dx, dy; // Delta mouse coords (x - px)
		float cx, cy; // Camera coords
	protected:
	public:
		WXImage *img;

		WXCanvas(wxFrame *owner, int *args);

		/*WXCanvas(const WXCanvas &rhs)
		{
			// Deep copy all member variables
			this->context = rhs.;
			this->fParent = rhs.;
			this->f = rhs.;
			this->px = rhs.;
			this->py = rhs.;
			this->ppx = rhs.;
			this->ppy = rhs.;
			this->dx = rhs.;
			this->dy = rhs.;
			this->cx = rhs.;
			this->cy = rhs.;
		}

		WXCanvas &operator=(WXCanvas rhs)
		{
			swap(*this, rhs);
			return *this;
		}*/

		virtual ~WXCanvas();

		/*friend void swap(WXCanvas &lhs, WXCanvas &rhs)
		{
			using std::swap;
			// Swap all member variables
			swap(lhs., rhs.);
			swap(lhs., rhs.);
			swap(lhs., rhs.);
			swap(lhs., rhs.);
			swap(lhs., rhs.);
			swap(lhs., rhs.);
			swap(lhs., rhs.);
			swap(lhs., rhs.);
			swap(lhs., rhs.);
			swap(lhs., rhs.);
			swap(lhs., rhs.);
		}*/

		void SizeFormToImage(bool bCenter);

		DECLARE_EVENT_TABLE()

		void Render(wxPaintEvent &e);

		void Resized(wxSizeEvent &e);

		void MouseMoved(wxMouseEvent &e);

		void MouseWheel(wxMouseEvent &e);

		void MouseLeftDoubleClick(wxMouseEvent &e);

		void MouseMiddleDoubleClick(wxMouseEvent &e);

		void KeyDown(wxKeyEvent &e);
	};
}
