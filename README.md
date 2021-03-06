# README
My personal image viewer.

## PLATFORMS
Primary target is Windows 10.

Windows -- compiled with MinGW64 / GCC 10.3.0 / POSIX threads.

Debian -- not built currently. todoo

## DEPENDENCIES
FreeGLUT (bundled, Windows only, to be removed).

wxWidgets (binary bundled, TODO bundle src).

## BUILDING
make clean ; make
make clean ; make -j<n>

Set switches (DBG, OPT, etc) in Makefile.

### Makefile switches (make variables):
Switch|Allowed Values|Status|Notes
:---:|:---:|:---:|:---:
ENV|WINDOWS, LINUX|Mandatory|Platform to target. Needs improvement
DBG|0, 1|Removed|Activate debugging flags
DBG_CMP|0, 1|Mandatory|Tell GCC to display compilation debugging information
OPT|d, 0, 2, 6, s|Mandatory|Pass -Ox optimization flag to GCC. If d, do no optimization and compile with debug symbols
PEDANTIC_ERROR_OUT|0, 1|Mandatory|Show pedantic warnings as errors

### Codepath switches (-Dxxx):
Switch|Allowed Values|Status|Notes
:---:|:---:|:---:|:---:
TARGET_GLUT||Removed|Use GLUT codepath (no shared code)
TARGET_WX||Removed|Use wxWidgets for windowing frontend
DWXIMAGE_USESOFTWAREIMAGEPROCESSING||Optional (wip, broken)|Read image buffer into system memory, filter, and pass filtered buffer to OpenGL
DWXIMAGE_USESOFTWAREIMAGEPREPROCESSING||Optional (wip, broken)|Parse jpegs for metadata

## Attributions
See LICENSES. I would like to thank the developers of FreeGLUT, wxWidgets, and stb_image for releasing their respective libraries.
