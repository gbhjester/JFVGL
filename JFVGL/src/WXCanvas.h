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

#include "Main.h"
#include "WXImage.h"

namespace JFVGL
{

	class WXCanvas : public wxGLCanvas
	{
	private:
		float f;
		float px, py; // Previous mouse coords
		float ppx, ppy; // Previous passive mouse coords (not updated while dragging
		float dx, dy; // Delta mouse coords (x - px)
		float cx, cy; // Camera coords

		/* wxWidgets variables */

		wxGLContext *context;

		/* wxWidgets API */

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

		/* API */

		/* wxWidgets API */

		/* Events */

		void Render(wxPaintEvent &e);
		void Resized(wxSizeEvent &e);
		void MouseMoved(wxMouseEvent &e);
		void MouseWheel(wxMouseEvent &e);
		void MouseLeftDoubleClick(wxMouseEvent &e);
		void MouseMiddleDoubleClick(wxMouseEvent &e);
		void KeyDown(wxKeyEvent &e);

		DECLARE_EVENT_TABLE()
	};
}
