/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/* 
 * File:   Image.cpp
 * Author: Jester
 * 
 * Created on May 11, 2019, 9:17 PM
 */

#include <GL/gl.h>

#include "WXImage.h"
#include "wx/filefn.h"

JFVGL::WXImage::WXImage()
{
	img = nullptr;
}

JFVGL::WXImage::~WXImage(){ }

/* API */

bool JFVGL::WXImage::Open(wxString filename)
{
	if (wxFileExists(filename))
		return false;
	img = new wxImage(filename);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void JFVGL::WXImage::Close(){ }
