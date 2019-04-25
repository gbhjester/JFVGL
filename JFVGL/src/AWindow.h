/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/* 
 * File:   AWindow.h
 * Author: Jester
 *
 * Created on April 25, 2019, 12:22 AM
 */

#pragma once

#include "Main.h"

class AWindow
{
public:
	AWindow();

	AWindow(const AWindow &other)
	{
		// Deep copy all member variables
		// eg this->x = other.x;
	}

	AWindow &operator=(AWindow rhs)
	{
		if (this == &rhs)
			return *this;
		swap(*this, rhs);
		return *this;
	}
	virtual ~AWindow();

	friend void swap(AWindow &lhs, AWindow &rhs)
	{
		using JFVGL::swap;
		// Swap all member variables
		//swap(lhs.x, rhs.x);
	}
	
	void init(int argc, char **argv);

private:
};
