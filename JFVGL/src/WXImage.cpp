/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/* 
 * File:   WXImage.cpp
 * Author: Jester
 * 
 * Created on May 11, 2019, 9:17 PM
 */

#include "WXImage.h"

JFVGL::WXImage::WXImage()
{
	this->w = 0;
	this->h = 0;
	this->bpc = 0;
	this->id = 0;
	this->filename = new wxString();
	this->supportedFileTypes[0] = wxString(".bmp");
	this->supportedFileTypes[1] = wxString(".gif");
	this->supportedFileTypes[2] = wxString(".jpg");
	this->supportedFileTypes[3] = wxString(".jpeg");
	this->supportedFileTypes[4] = wxString(".pcx");
	this->supportedFileTypes[5] = wxString(".png");
	this->supportedFileTypes[6] = wxString(".tga");
	this->supportedFileTypes[7] = wxString(".tif");
	this->supportedFileTypes[8] = wxString(".tiff");
	this->supportedFileTypes[9] = wxString("");
}

JFVGL::WXImage::~WXImage()
{
	delete filename;
}

/* API */

unsigned int JFVGL::WXImage::Open(wxString filename)
{
	wxLogNull DONTLOGME;
	if (!wxFileExists(filename))
	{
		wxMessageBox(filename + " not found.", "Error");
		return 0;
	}
	if (id != 0)
		Close();
	*this->filename = filename;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	wxImage *img = new wxImage(filename);
	w = img->GetWidth();
	h = img->GetHeight();
	bpc = 3;
	if (img->HasAlpha())
		bpc = 4;
#ifdef DEBUG
	printf("bpc : %d\n", bpc);
#endif
	/*unsigned char *buf = new unsigned char[w * h * bpc];
	unsigned char *data = img->GetData();
	unsigned char *alpha = img->GetAlpha();
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			buf[x + y * w  * bpc + 0] = data[x + y * w  * 3];
			buf[x + y * w  * bpc + 1] = data[x + y * w  * 3 + 1];
			buf[x + y * w  * bpc + 2] = data[x + y * w  * 3 + 2];
			if (bpc == 4)
				buf[x + y * w * bpc + 3] = alpha[x + y * w];
		}
	}*/
	glClearColor(0.25f, 0.25f, 0.25f, 1.f);
	glColor3f(0.5f, 0.5f, 1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexImage2D(GL_TEXTURE_2D, 0, bpc == 4 ? GL_RGBA : GL_RGB, w, h, 0, bpc == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, buf);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img->GetData());
	delete img;
	return id;
}

void JFVGL::WXImage::Close()
{
	// TODO Test VERY IMPORTANT TO ENSURE IMAGES ARE RELEASED FROM VRAM
	// Seems to work
	//glDeleteTextures(1, &id);
	id = 0;
}

void JFVGL::WXImage::TraverseDirectory(int delta)
{
	if (delta == 0)
		return;
	// TODO Rename tstr
	wxString tstr(*filename);
	char *tstrcstr = (char *)tstr.c_str().AsChar();
	for (int i = tstr.length() - 1; i >= 0; i--)
	{
		if (tstrcstr[i] == '/' || tstrcstr[i] == '\\')
		{
			tstr = tstr.Mid(0, i);
			break;
		}
	}
#ifdef DEBUG
	printf("WXImage::TraverseDirectory() Directory name:\n\t[%s]\n", tstr.c_str().AsChar());
#endif
	wxArrayString asfiles, supportedFiles;
	// NOTE GetAllFiles(...) and manually traversing is probably slower than Traverse(...)
	wxDir::GetAllFiles(tstr, &asfiles, wxString("*.*"), wxDIR_FILES | wxDIR_NO_FOLLOW);
	for (size_t i = 0; i < asfiles.Count(); i++)
	{
		int o = 0;
		while (supportedFileTypes[o] != "")
		{
			if (asfiles[i].Lower().EndsWith(supportedFileTypes[o]))
				supportedFiles.Add(asfiles[i]);
			o++;
		}
	}
	supportedFiles.Sort(_wxStrCmpLogical);
#ifdef DEBUG
	printf("WXImage::TraverseDirectory() Files:\n");
	for (size_t i = 0; i < supportedFiles.Count(); i++)
		printf("\t>%s\n", supportedFiles[i].c_str().AsChar());
#endif
	// TODO Optimize. Traversing to big files is SLOW
	// TODO Find current file in list
	for (size_t i = 0; i < supportedFiles.Count(); i++)
	{
		if (*filename == supportedFiles[i])
		{
			if (delta < 0)	// Backward
			{
				if (i > 0)
				{
					Close();
					Open(supportedFiles[i - 1]);
					return;
				}
			}
			else if (delta > 0)	// Forward
			{
				if (i < supportedFiles.Count() - 1)
				{
					Close();
					Open(supportedFiles[i + 1]);
					return;
				}
			}
		}
	}
}
