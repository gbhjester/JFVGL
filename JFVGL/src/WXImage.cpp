/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/* 
 * File:   WXImage.cpp
 * Author: Jester
 * 
 * Created on May 11, 2019, 9:17 PM
 */

#include <GL/glu.h>
#include "WXImage.h"
#include "wx/wx.h"

JFVGL::WXImage::WXImage()
{
	this->w = 0;
	this->h = 0;
	this->bpc = 0;
	this->id = 0;
}

JFVGL::WXImage::~WXImage(){ }

/* API */

unsigned int JFVGL::WXImage::Open(wxString filename)
{
	if (!wxFileExists(filename))
	{
		wxMessageBox(filename + " not found.", "Error");
		return 0;
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	wxImage *img = new wxImage(filename);
	w = img->GetWidth();
	h = img->GetHeight();
	bpc = 3;
	if (img->HasAlpha())
		bpc = 4;
	glClearColor(0.25f, 0.25f, 0.25f, 1.f);
	glColor3f(0.5f, 0.5f, 1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, bpc == 4 ? GL_RGBA : GL_RGB, w, h, 0, bpc == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, img->GetData());
	return id;
}

void JFVGL::WXImage::Close()
{
	glDeleteTextures(1, &id);
}
