/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/* 
 * File:   WXCanvas.h
 * Author: Jester
 *
 * Created on May 11, 2019, 7:21 PM
 */

#pragma once

#include <GL/glu.h>
#include <GL/gl.h>
#include "wx/wx.h"
#include "wx/display.h"
#include "wx/glcanvas.h"
#include "Main.h"
#include "WXImage.h"
#include "Main.h"

namespace JFVGL
{

	class WXCanvas : public wxGLCanvas
	{
	private:
		wxGLContext *context;
		wxFrame *fParent;
		float f;
		float px, py; // Previous mouse coords
		float ppx, ppy; // Previous passive mouse coords (not updated while dragging
		float dx, dy; // Delta mouse coords (x - px)
		float cx, cy; // Camera coords
	protected:
	public:
		WXImage *img;

		WXCanvas(wxFrame *owner, int *args);

		// TODO Does copy ctor make sense for canvas?
		/*WXCanvas(const WXCanvas &other)
		{
			// Deep copy all member variables
			// eg this->x = other.x;
			;
		}*/

		/*WXCanvas &operator=(WXCanvas rhs)
		{
			if (this == &rhs)
				return *this;
			Swap(*this, rhs);
			return *this;
		}*/

		virtual ~WXCanvas();

		/*friend void Swap(WXCanvas &lhs, WXCanvas &rhs)
		{
			using JFVGL::Swap;
			// Swap all member variables
			//swap(lhs.x, rhs.x);
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
