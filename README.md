# README
This is my image viewer.

## PLATFORMS
Primary target is Windows 10 64bit, should theoretically compile on XP, haven't tried.
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
Switch|Allowed Values|Status|Notes
:---:|:---:|:---:|:---:
ENV|WINDOWS, LINUX|Mandatory|Platform to target. Needs improvement
DBG|0, 1|Mandatory|Activate debugging flags
DBG_CMP|0, 1|Mandatory|Tell GCC to display compilation debugging information
OPT|0, 2, 6, s|Mandatory|Pass -Ox optimization flag to GCC

### Codepath switches (-Dxxx):
Switch|Allowed Values|Status|Notes
:---:|:---:|:---:|:---:
TARGET_GLUT|0, 1|Removed|Use GLUT codepath (no shared code)
TARGET_WX|0, 1|Depreciated|Use wxWidgets for windowing frontend
DWXIMAGE_USESOFTWAREIMAGEPROCESSING|0, 1|Optional (defaults to undefined)|Read image buffer into system memory, filter, and pass filtered buffer to OpenGL
