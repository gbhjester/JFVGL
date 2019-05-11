/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/* 
 * File:   GLUTWindow.h
 * Author: Jester
 *
 * Created on April 25, 2019, 1:57 AM
 */

#pragma once

#include "Main.h"
#include "IWindow.h"

// TODO Move to class Preferences
#define FPS_TARGET 60
#define ZOOM_MIN 0.01f
#define ZOOM_MAX 10.f

class GLUTWindow : public IWindow
{
private:
protected:
public:
	GLUTWindow();

	GLUTWindow(const GLUTWindow &other)
	{
		// Deep copy all member variables
		// eg this->x = other.x;
		;
	}

	GLUTWindow &operator=(GLUTWindow rhs);

	virtual ~GLUTWindow();

	friend void Swap(GLUTWindow &lhs, GLUTWindow &rhs)
	{
		using JFVGL::Swap;
		// Swap all member variables
		//swap(lhs.x, rhs.x);
	}

	/* API */

	virtual void Start(int argc, char **argv) override;
};
