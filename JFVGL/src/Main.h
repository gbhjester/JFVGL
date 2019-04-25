/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/**
 * Main.h
 */

#pragma once

#include "GL/freeglut.h"

namespace JFVGL
{

	template <typename T>
	void Swap(T &lhs, T &rhs)
	{
		T tmp(rhs);
		lhs = rhs;
		rhs = tmp;
	}
}
