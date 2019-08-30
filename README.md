# README
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

Set switches (DBG, OPT, etc) in Makefile.

### Makefile switches (make variables):
Switch|Status|Allowed Values|Notes
:---:|:---:|:---:|:---:
ENV|Active|WINDOWS, LINUX|Platform to target. Needs improvement
DBG|Active|0, 1|Enable debugging

### Codepath switches (-Dxxx):
Switch|Status|Allowed Values|Notes
:---:|:---:|:---:|:---:
TARGET_GLUT|Removed|0, 1|Use GLUT codepath (no shared code)
TARGET_WX|Depreciated|0, 1|Use wxWidgets for windowing
DWXIMAGE_USESOFTWAREIMAGEPROCESSING|Active|0, 1|Read image buffer into system memory, filter, and pass filtered buffer to OpenGL