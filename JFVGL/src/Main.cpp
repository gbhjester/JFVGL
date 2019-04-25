/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/**
 * Main.c
 */

#include <stdio.h>
#include "main.h"
#include "AWindow.h"

int main(int argc, char **argv)
{
	AWindow wnd;
	wnd.init(argc, argv);
	return 0;
}
