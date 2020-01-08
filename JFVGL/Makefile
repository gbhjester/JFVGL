# I, Jester, hereby release this work, except as stated otherwise, into the public domain.

NAME=JFVGL

#WINDOWS, LINUX
ENV=WINDOWS
# 0, 1
DBG=0
# 0, 1
DBG_CMP=0
# 0, 1
OPT=1

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
#LDIR=lib
ifeq ($(ENV), Linux)
	LDIR=lib/deb
else
	LDIR=lib/win64
endif
SDIR=src
ODIR=obj

CXX=g++
CXXFLAGS=-std=c++98 -Wall -I$(IDIR)

ifeq ($(DBG), 1)
	CXXFLAGS+=-Og
else
    CXXFLAGS+=-s
endif
ifeq ($(OPT), 1)
	CXXFLAGS+=-Ofast -frename-registers -funroll-loops -fpeel-loops -ffast-math -ffinite-math-only -fno-signed-zeros -fno-trapping-math -ftree-vectorize -ftree-parallelize-loops=4 -march=znver2 -fopenmp
endif

LDFLAGS=-L$(LDIR) -L$(LDIR)/wx
ifeq ($(ENV), LINUX)
	LDFLAGS+=-lGL -lGLU
	#LDFLAGS+=-lGL -lGLU $(LDIR)/wx/libwxbase31u.a $(LDIR)/wx/libwxmsw31u_core.a $(LDIR)/wx/libwxmsw31u_gl.a
else
	LDFLAGS+=-lshlwapi -lopengl32 -lglu32 $(LDIR)/wx/libwxbase31u.a $(LDIR)/wx/libwxmsw31u_core.a $(LDIR)/wx/libwxmsw31u_gl.a -flto
ifeq ($(DBG), 0)
	LDFLAGS+=-mwindows
endif
endif

_SRC=Main WXApp WXWindow WXCanvas WXImage
#SRC=$(patsubst %,$(SDIR)/%.cpp,$(_SRC))
#DEPS=$(patsubst %,$(SDIR)/%.h,$(_SRC))
OBJ=$(patsubst %,$(ODIR)/%.o,$(_SRC))

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CXX) -c $< -o"$@" $(CXXFLAGS) $(DEFINES)

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
