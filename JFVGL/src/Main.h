/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/**
 * Main.h
 */

#pragma once

#ifdef DEBUG
#include <cstdio>
#endif

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
	
	// If a == b, return a
	static inline int imin(int a, int b)
	{
		return (a <= b ? a : b);
	}
	
	// If a == b, return a
	static inline int imax(int a, int b)
	{
		return (a >= b ? a : b);
	}

	// FIXME Throws multiply defined compile error if not inline
	// Invariant : a <= x <= b
	// If a == x == b, return x
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
