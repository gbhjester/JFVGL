/**
 * Main.h
 */

#pragma once

#ifdef DEBUG
#include <cstdio>
#endif

namespace JFVGL {
	// If a == b, return a
	static inline int imin(int a, int b) {
		return (a <= b ? a : b);
	}

	// If a == b, return a
	static inline int imax(int a, int b) {
		return (a >= b ? a : b);
	}

	// FIXME Throws multiply defined compile error if not inline
	// Invariant : a <= x <= b
	// If a == x == b, return x
	static inline float fclamp(float a, float x, float b) {
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
