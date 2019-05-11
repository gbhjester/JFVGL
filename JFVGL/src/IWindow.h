/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/* 
 * File:   IWindow.h
 * Author: Jester
 *
 * Created on April 25, 2019, 12:22 AM
 */

#pragma once

#include "Main.h"

namespace JFVGL
{
	class IWindow
	{
	private:
	protected:
	public:

		virtual ~IWindow() { }

		/* API */

		virtual void Start() = 0;
	};
}
