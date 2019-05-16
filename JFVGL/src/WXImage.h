/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/* 
 * File:   WXImage.h
 * Author: Jester
 *
 * Created on May 11, 2019, 9:17 PM
 */

#pragma once

#include <GL/glu.h>
#include <GL/gl.h>
#include "wx/wx.h"
#include "wx/dir.h"
//#include "wx/display.h"
#include "wx/frame.h"
//#include "wx/glcanvas.h"
#include "wx/image.h"
#include "Main.h"

namespace JFVGL
{

	class WXImage
	{
	private:
		// TODO Move to class Preferences
		wxString supportedFileTypes[10];

	protected:
	public:
		int w, h;
		unsigned char bpc;
		unsigned int id;
		wxString *filename;

		WXImage();

		WXImage(const WXImage &other)
		{
			// Deep copy all member variables
			// eg this->x = other.x;
			;
		}

		WXImage &operator=(WXImage rhs)
		{
			if (this == &rhs)
				return *this;
			Swap(*this, rhs);
			return *this;
		}

		virtual ~WXImage();

		friend void Swap(WXImage &lhs, WXImage &rhs)
		{
			using JFVGL::Swap;
			// Swap all member variables
			//swap(lhs.x, rhs.x);
		}

		/* API */

		virtual unsigned int Open(wxString filename);
		virtual void Close();
		void TraverseDirectory(int delta);
	};
}
