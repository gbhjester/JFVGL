/*
 * File:   GLUTWindow.h
 * Author: Jester
 *
 * Created on April 25, 2019, 1:57 AM
 */

#pragma once

#include "IWindow.h"

namespace JFVGL {

	class GLUTWindow : public IWindow {
	private:
	protected:
	public:
		GLUTWindow();

		GLUTWindow(const GLUTWindow &other) {
			// Deep copy all member variables
			// eg this->x = other.x;
			;
		}

		GLUTWindow &operator=(GLUTWindow rhs) {
			if (this == &rhs)
				return *this;
			Swap(*this, rhs);
			return *this;
		}

		virtual ~GLUTWindow();

		friend void Swap(GLUTWindow &lhs, GLUTWindow &rhs) {
			using JFVGL::Swap;
			// Swap all member variables
			//swap(lhs.x, rhs.x);
		}

		static int DoGlutStuff(int argc, char **argv);

		/* API */

		virtual void Start() override;

		virtual void Render() override;
	};
}
