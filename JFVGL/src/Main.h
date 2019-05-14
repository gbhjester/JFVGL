/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/**
 * Main.h
 */

#pragma once

#include "prec.h"

#if defined(__linux__) || defined(__linux__) || defined(__linux) || defined(linux) || defined(LINUX)
	#define LINUX
#elif defined (_WIN32) || defined(_WIN64)
	#define WINDOWS
#endif

/*#ifdef LINUX
	;
#elif WINDOWS
	;
#endif*/

namespace JFVGL
{

	template <typename T>
	void Swap(T &lhs, T &rhs)
	{
		T tmp(rhs);
		lhs = rhs;
		rhs = tmp;
	}

	// FIXME Throws multiply defined compile error if not inline

	static inline float fclamp(float a, float x, float b)
	{
		/*if (x < a)
			return a;
		else if (x > b)
			return b;
		else
			return x;*/
		// TODO test
		return (x < a ? a : (x > b ? b : x));
	}
}
