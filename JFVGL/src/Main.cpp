/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/**
 * Main.c
 */

#include "Main.h"
#include "GLUTWindow.h"

//#define epsilon powf(2, -23)

int main(int argc, char **argv)
{
	for (int i = 0; i < argc; i++)
		printf("%s\n", argv[i]);
	GLUTWindow wnd;
	wnd.Start(argc, argv);
	return 0;
}
