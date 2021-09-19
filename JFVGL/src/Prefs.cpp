/**
 * Prefs.cpp
 *
 * Created on September 19, 2021, 3:10 PM
 */

#include "Prefs.h"

JFVGL::Prefs::Prefs(wxString filename) {
	this->filename = new wxString(filename);
}

JFVGL::Prefs::~Prefs() {
}

bool JFVGL::Prefs::Load() {
}

bool JFVGL::Prefs::Save() {
}

wxString JFVGL::Prefs::Get(wxString key) {
}

bool JFVGL::Prefs::Set(wxString key, wxString val) {
}
