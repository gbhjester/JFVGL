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

#include <GL/gl.h>
#include "wx/image.h"
#include "Main.h"
#include "IImage.h"

namespace JFVGL
{

	class WXImage : public IImage
	{
	private:
	protected:
	public:

		//wxImage *img;
        unsigned int w, h;
        unsigned char bpc;
        unsigned int id;

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

		virtual unsigned int Open(wxString filename) override;
		virtual void Close() override;
	};
}
