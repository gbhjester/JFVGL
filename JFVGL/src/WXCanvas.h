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

#include "wx/wx.h"
#include "wx/glcanvas.h"

namespace JFVGL
{

	class WXCanvas : public wxGLCanvas
	{
	private:

		/* wxWidgets variables */

		wxGLContext *context;

		/* wxWidgets API */

	protected:
	public:
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

		void Render(wxPaintEvent &e);
		void Resized(wxSizeEvent &e);
        
		/* wxWidgets API */

        DECLARE_EVENT_TABLE()
	};
}
