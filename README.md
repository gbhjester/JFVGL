# README
My personal image viewer.

## PLATFORMS
Primary target is Windows 10.
On Windows compiled with MinGW64 / GCC 8.1.0 / POSIX threads.
On Debian compiled with GCC 8.1.0.

## DEPENDENCIES
FreeGLUT (bundled, Windows only, to be removed).
wxWidgets (binary bundled, TODO bundle src).

## BUILDING
make clean ; make -j

Set switches (DBG, OPT, etc) in Makefile.

### Makefile switches (make variables):
Switch|Allowed Values|Status|Notes
:---:|:---:|:---:|:---:
ENV|WINDOWS, LINUX|Mandatory|Platform to target. Needs improvement
DBG|0, 1|Removed|Activate debugging flags
DBG_CMP|0, 1|Mandatory|Tell GCC to display compilation debugging information
OPT|0, 2, 6, s, d|Mandatory|Pass -Ox optimization flag to GCC. If d, do no optimization and compile with debug symbols
PEDANTIC_ERROR_OUT|0, 1|Mandatory|Show pedantic warnings as errors

### Codepath switches (-Dxxx):
Switch|Allowed Values|Status|Notes
:---:|:---:|:---:|:---:
TARGET_GLUT||Removed|Use GLUT codepath (no shared code)
TARGET_WX||Removed|Use wxWidgets for windowing frontend
DWXIMAGE_USESOFTWAREIMAGEPROCESSING||Optional|Read image buffer into system memory, filter, and pass filtered buffer to OpenGL
