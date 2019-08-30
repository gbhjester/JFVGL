# *** README ***
This is my image viewer.

## PLATFORMS
Primary target is Windows 7 64bit, should theoretically compile on XP, haven't tried.
On Windows I compile with MinGW64 / GCC 8.1.0 / POSIX threads.

Linux (Debian stretch) support is planned.
On Debian I compile with GCC 8.1.0.

## DEPENDENCIES
FreeGLUT (bundled, not working under Linux atm, to be removed).
wxWidgets (bundled).

## BUILDING
make clean ; make -j

### Set switches (DBG, OPT, etc) in Makefile.

### Makefile switches (make variables):
	

### Codepath switches (-Dxxx):
Switch | Status | Discription
--- | --- | ---
TARGET_GLUT | Removed | Use GLUT
TARGET_WX | Depreciated | Use wxWidgets
