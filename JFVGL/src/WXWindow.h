/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/* 
 * File:   wxWindow.h
 * Author: Jester
 *
 * Created on May 11, 2019, 3:24 PM
 */

#pragma once

#include "wx/wx.h"
#include "wx/display.h"
#include "wx/frame.h"
#include "Main.h"
#include "WXCanvas.h"

namespace JFVGL
{

	class WXApp : public wxApp
	{
	public:
		bool OnInit();
	};

	class WXWindow : public wxFrame
	{
	private:

		/* wxWidgets variables */

		/* wxWidgets API */

	protected:
	public:
		WXCanvas *canvas;

		WXWindow();

		WXWindow(const WXWindow &other)
		{
			// Deep copy all member variables
			// eg this->x = other.x;
			;
		}

		WXWindow &operator=(WXWindow rhs)
		{
			if (this == &rhs)
				return *this;
			Swap(*this, rhs);
			return *this;
		}

		virtual ~WXWindow();

		void Swap(WXWindow &lhs, WXWindow &rhs)
		{
			using JFVGL::Swap;
			// Swap all member variables
			//swap(lhs.x, rhs.x);
		}
	};
}
