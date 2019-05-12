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

#include "wx/image.h"
#include "wx/wx.h"
#include "WXCanvas.h"
#include "IWindow.h"

namespace JFVGL
{

	class WXApp : public wxApp
	{
	public:
		bool OnInit() override;
	};

	class WXWindow : public IWindow, public wxFrame
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

		friend void Swap(WXWindow &lhs, WXWindow &rhs)
		{
			using JFVGL::Swap;
			// Swap all member variables
			//swap(lhs.x, rhs.x);
		}

		/* API */

		virtual void Start() override;
        virtual void Render() override;

		/* wxWidgets API */

	};
}
