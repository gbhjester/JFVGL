/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/**
 * Main.h
 */

#pragma once

namespace JFVGL
{

	template <typename T>
	void Swap(T &lhs, T &rhs)
	{
		T tmp(rhs);
		lhs = rhs;
		rhs = tmp;
	}

	inline float fclamp(float a, float x, float b)
	{
		/*if (x < a)
			return a;
		else if (x > b)
			return b;
		else
			return x;*/
		return (x < a ? a : (x > b ? b : x));
	}
}
