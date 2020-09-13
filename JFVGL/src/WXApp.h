/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/* 
 * File:   wxWindow.cpp
 * Author: Jester
 * 
 * Created on November 15, 2019, 8:26 PM
 */

#pragma once

#include "wx/wx.h"
#include "WXWindow.h"

namespace JFVGL
{
	class WXApp : public wxApp
	{
	public:
		bool OnInit();
	};

}
