/**
 * Prefs.h
 *
 * Created on September 19, 2021, 3:10 PM
 */

#include <iostream>
#include "wx/wx.h"
#include "Main.h"

namespace JFVGL {
	class Prefs {
	private:
		wxString *filename;
	public:
		Prefs(wxString filename);
		~Prefs();
		bool Load();
		bool Save();
		wxString Get(wxString key);
		bool Set(wxString key, wxString val);
	};
}
