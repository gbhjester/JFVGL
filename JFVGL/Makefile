# I, Jester, hereby release this work, except as stated otherwise, into the public domain.

NAME=JFVGL

#WINDOWS, LINUX
ENV=WINDOWS
# 0, 1
DBG=0
# 0, 1
DBG_CMP=0
# 2, 6, s. 0 = disabled
OPT=6

DEFINES=-D$(ENV)
ifneq ($(DBG), 0)
	DEFINES+=-DDEBUG -D_DEBUG -DWXDEBUG
endif
ifneq ($(DBG_CMP), 0)
	DEFINES+=-H
	#DEFINES+=-Winvalid-pch
endif

# Codepath switches
#DEFINES+=-DWXIMAGE_USESOFTWAREIMAGEPROCESSING
#DEFINES+=-DWXIMAGE_USESOFTWAREIMAGEPREPROCESSING

IDIR=inc
LDIR=lib
ifeq ($(ENV), Linux)
	LDIR=lib/deb
else
	LDIR=lib/win64
endif
SDIR=src
ODIR=obj

CXX=g++
CXXFLAGS=-std=c++98 -Wall -I$(IDIR)

# Only enable optimizations on nondebug builds
ifeq ($(DBG), 0)
# If any optimizations enabled
ifneq ($(OPT), 0)
	CXXFLAGS+=-O$(OPT) -flto
# DANGER ZONE
ifeq ($(OPT), 6)
	CXXFLAGS+=-march=native -frename-registers -ffast-math
endif
endif
else
	CXXFLAGS+=-Og
endif

LDFLAGS=-L$(LDIR) -L$(LDIR)/wx
ifeq ($(ENV), LINUX)
	LDFLAGS+=-lGL -lGLU
	#LDFLAGS+=-lGL -lGLU $(LDIR)/wx/libwxbase31u.a $(LDIR)/wx/libwxmsw31u_core.a $(LDIR)/wx/libwxmsw31u_gl.a
else
	LDFLAGS+=-lshlwapi -lopengl32 -lglu32 $(LDIR)/wx/libwxbase31u.a $(LDIR)/wx/libwxmsw31u_core.a $(LDIR)/wx/libwxmsw31u_gl.a
ifeq ($(DBG), 0)
	LDFLAGS+=-mwindows
endif
endif

_SRC=Main WXApp WXWindow WXCanvas WXImage
#SRC=$(patsubst %,$(SDIR)/%.cpp,$(_SRC))
#DEPS=$(patsubst %,$(SDIR)/%.h,$(_SRC))
OBJ=$(patsubst %,$(ODIR)/%.o,$(_SRC))

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(DEFINES) -c $< -o$@

all: $(OBJ)
	$(CXX) -o$(NAME) $^ $(LDFLAGS)

#$(SDIR)/prec.h.gch: $(SDIR)/prec.h
#	$(CXX) $(CXXFLAGS) $(DEFINES) -c $< -o$@
#prec: $(SDIR)/prec.h.gch

clean:
	rm -f $(NAME)
	rm -f $(NAME).exe
	rm -r -f obj
	mkdir obj
