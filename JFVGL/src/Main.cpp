/*
 * I, Jester, hereby release this work, except as stated otherwise, into the public domain.
 */

/**
 * Main.c
 */

#include "wx/wx.h"
#include "Main.h"
#ifdef TARGET_GLUT
#include "GLUTWindow.h" // For now
#endif
#ifdef TARGET_WX
	#include "WXWindow.h"
#endif

#ifdef TARGET_WX
	// wx entry point. Replaces main()
	wxIMPLEMENT_APP(JFVGL::WXApp);
#else
int main(int argc, char **argv)
{
#ifdef DEBUG
	for (int i = 0; i < argc; i++)
		printf("%s\n", argv[i]);
#endif
#ifdef TARGET_GLUT
	JFVGL::GLUTWindow::DoGlutStuff(argc, argv);
	return 0;
#else
	printf("No target specified\n");
#endif
	return 0;
}
#endif
