/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/* 
 * File:   IBitmap.h
 * Author: Jester
 *
 * Created on May 11, 2019, 9:04 PM
 */

#pragma once

namespace JFVGL
{

	class IImage
	{
	private:
	protected:
	public:

		virtual ~IImage() { }

		/* API */

		virtual unsigned int Open(wxString filename) = 0;
		virtual void Close() = 0;
	};
}
