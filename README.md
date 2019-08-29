# *** README ***
This is my image viewer.

## PLATFORMS
Primary target is Windows 7 64bit. Should theoretically compile on XP, haven't tried.
On Windows I compile with MinGW64 / GCC 8.1.0 / POSIX threads.

Linux (Debian stretch) support is planned.
On Debian I compile with GCC 8.1.0.

## DEPENDENCIES
FreeGLUT (bundled, not working under Linux atm, to be removed).
wxWidgets (bundled).

## BUILDING
make clean ; make -j

Set switches (DBG, OPT, etc) in Makefile.
