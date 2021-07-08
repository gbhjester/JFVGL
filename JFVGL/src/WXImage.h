/**
 * WXImage.h
 *
 * Created on May 11, 2019, 9:17 PM
 */

#pragma once

#ifdef WINDOWS
#include <shlwapi.h>
#endif

#include <GL/glu.h>
#include <GL/gl.h>
#include "wx/wx.h"
#include "wx/dir.h"
#include "wx/frame.h"
#include "wx/image.h"
#include "Main.h"

namespace JFVGL {
	class WXImage {
	private:
		// TODO Move to class Preferences
		// TODO Make some kind of smart array type with API
		wxString supportedFileTypes[10];

	protected:
	public:
		int w, h;
		unsigned char bpc;
		unsigned int id;
		wxString *filename;

		WXImage();

		WXImage(const WXImage &rhs) {
			// Deep copy all member variables
			this->w = rhs.w;
			this->h = rhs.h;
			this->bpc = rhs.bpc;
			this->id = rhs.id;
			this->filename = new wxString(*rhs.filename);
		}

		WXImage &operator=(WXImage rhs) {
			swap(*this, rhs);
			return *this;
		}

		virtual ~WXImage();

		friend void swap(WXImage &lhs, WXImage &rhs) {
			using std::swap;
			// Swap all member variables
			swap(lhs.w, rhs.w);
			swap(lhs.h, rhs.h);
			swap(lhs.bpc, rhs.bpc);
			swap(lhs.id, rhs.id);
			swap(lhs.filename, rhs.filename);
		}

		static int _wxStrCmpLogical(const wxString &first, const wxString &second) {
#ifdef DEBUG
			wprintf(L"WXImage::_wxStrCmpLogical() first.wc.str():\n\t[%s]\n", first.wc_str());
#endif
#ifdef WINDOWS
			const wchar_t *psz1 = first.c_str();
			const wchar_t *psz2 = second.c_str();
			return StrCmpLogicalW(psz1, psz2);
#else
			// TODO Implement StrCmpLogicalW locally
			return 0;
#endif
		}

		virtual unsigned int Open(wxString filename);
		virtual void Close();
		void TraverseDirectory(int delta);
	};
}
