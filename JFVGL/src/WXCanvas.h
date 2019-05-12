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
        
		/* wxWidgets variables */

		wxGLContext *context;

		/* wxWidgets API */

	protected:
	public:
        int mx;
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
        void MouseMiddleDoubleClick(wxMouseEvent &e);
        void KeyDown(wxKeyEvent &e);

		DECLARE_EVENT_TABLE()
	};
}
