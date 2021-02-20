/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/* 
 * File:   WXImage.cpp
 * Author: Jester
 * 
 * Created on May 11, 2019, 9:17 PM
 */

#ifdef WXIMAGE_USESOFTWAREIMAGEPREPROCESSING
#include <fstream>
using namespace std;
#endif

#include "WXImage.h"

JFVGL::WXImage::WXImage()
{
	this->w = 0;
	this->h = 0;
	this->bpc = 0;
	this->id = 0;
	this->filename = new wxString();
	this->supportedFileTypes[0] = wxString(".bmp");
	this->supportedFileTypes[1] = wxString(".jpg");
	this->supportedFileTypes[2] = wxString(".jpeg");
	this->supportedFileTypes[3] = wxString(".pcx");
	this->supportedFileTypes[4] = wxString(".png");
	this->supportedFileTypes[5] = wxString(".tga");
	this->supportedFileTypes[6] = wxString(".tif");
	this->supportedFileTypes[7] = wxString(".tiff");
	this->supportedFileTypes[8] = wxString(".gif");
	this->supportedFileTypes[9] = wxString("");
	// Last supportedFileType must be ""
	//this->supportedFileTypes[9] = wxString("");
}

JFVGL::WXImage::~WXImage()
{
	delete filename;
}

/* API */

unsigned int JFVGL::WXImage::Open(wxString fn)
{
	wxLogNull DONTLOGME;
	if (!wxFileExists(fn))
	{
		// TODO Log
		wxMessageBox(fn + " not found.", "Error");
		return 0;
	}

	// Memory leak protection
	if (id != 0)
		Close();

	*this->filename = fn;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	wxImage *img = new wxImage(fn);
	w = img->GetWidth();
	h = img->GetHeight();
	bpc = 3;
	if (img->HasAlpha())
		bpc = 4;
#ifdef DEBUG
	printf("bpc : %hhu\n", bpc);
#endif
#ifdef WXIMAGE_USESOFTWAREIMAGEPREPROCESSING
	wifstream file(fn);	// TODO Test for unicode filenames. Might have to convert to uft8
	bool bFoundAPP1 = false, bRevByteListings = false;
	if (!file || !file.is_open())
	{
		// TODO Log
		wxMessageBox("Unable to open " + fn + " for preprocessing.", "Error");
		goto WXIMAGE_USESOFTWAREIMAGEPREPROCESSING_end;
	}
	// Determine if file is jpeg
	if (!(file.get() == 0xFF && file.get() == 0xD8))
		goto WXIMAGE_USESOFTWAREIMAGEPREPROCESSING_end;
	printf("SOI\n");
	// TODO Find start IFD
	// Scan file for exif chunk
	while (file.good())
	{
		char ch[2];
		if (bFoundAPP1 == false)
		{
			if (file.get() == 0xFF && file.get() == 0xE1)
			{
				printf("APP1 : %d\n", (int)file.tellg());
				bFoundAPP1 = true;
			}
			
			if (file.get() == 0x49 && file.get() == 0x49)
			{
				printf("Little-endian\n");
				bRevByteListings = true;
			}
		}
		else
		{if (file.get() == 0x49 && file.get() == 0x49)
			{
				printf("Little-endian\n");
				bRevByteListings = true;
			}
			ch[0] = file.get();
			ch[1] = file.get();
			if (bRevByteListings)
			{
				char tch = ch[0];
				ch[0] = ch[1];
				ch[1] = tch;
			}
			if (ch[0] == 0x01 && ch[1] == 0x12)
			{
				//unsigned short orient = (unsigned short)file.get();
				unsigned short orient = 0;
				printf("Orientation : %hu\n", orient);
				break;
			}
		}
	}
	// TODO Figure out endianness
	// Scan for Orientation EXIF tag
	/*while (file.good())
	{
		;
	}*/
	file.close();
WXIMAGE_USESOFTWAREIMAGEPREPROCESSING_end:
#endif
#ifdef WXIMAGE_USESOFTWAREIMAGEPROCESSING
	unsigned char *buf = new unsigned char[w * h * bpc];
	unsigned char *data = img->GetData();
	unsigned char *alpha = img->GetAlpha();
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			buf[x + y * w * bpc + 0] = data[x + y * w * 3];
			buf[x + y * w * bpc + 1] = data[x + y * w * 3 + 1];
			buf[x + y * w * bpc + 2] = data[x + y * w * 3 + 2];
			if (bpc == 4)
				buf[x + y * w * bpc + 3] = alpha[x + y * w];
		}
	}
#endif
	// TODO Move clear color to preferences as background color
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);
	glColor3f(0.5f, 0.5f, 1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
#ifdef WXIMAGE_USESOFTWAREIMAGEPROCESSING
	glTexImage2D(GL_TEXTURE_2D, 0, bpc == 4 ? GL_RGB : GL_RGB, w, h, 0, bpc == 4 ? GL_RGB : GL_RGB, GL_UNSIGNED_BYTE, buf);
	delete buf;
#else
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img->GetData());
#endif
	delete img;
	return id;
}

void JFVGL::WXImage::Close()
{
	// TODO Test VERY IMPORTANT TO ENSURE IMAGES ARE RELEASED FROM VRAM
	// Seems to work
	glDeleteTextures(1, &id);
	id = 0;
}

void JFVGL::WXImage::TraverseDirectory(int delta)
{
	if (delta == 0)
		return;
	wxString prunedFilename(*filename);
	prunedFilename = prunedFilename.Mid(0, prunedFilename.Find('/', true));
	prunedFilename = prunedFilename.Mid(0, prunedFilename.Find('\\', true));
#ifdef DEBUG
	printf("WXImage::TraverseDirectory() Directory name:\n\t[%s]\n", prunedFilename.c_str().AsChar());
#endif
	wxArrayString asfiles, supportedFiles;
	// NOTE GetAllFiles(...) and manually traversing is probably slower than Traverse(...)
	wxDir::GetAllFiles(prunedFilename, &asfiles, wxString("*.*"), wxDIR_FILES | wxDIR_NO_FOLLOW);
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
			if (delta < 0) // Backward
			{
				if (i > 0)
				{
					Close();
					Open(supportedFiles[i - 1]);
					return;
				}
			}
			else if (delta > 0) // Forward
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
