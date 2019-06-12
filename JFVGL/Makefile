# I, Jester, hereby release this work, except as stated otherwise, into the public domain.

ENV=$(shell uname)
# 0, 1
DBG=0
# 0, 1
DBG_CMP=0
# 2, 6, s. 0 = disabled
OPT=6

DEFINES=-DTARGET_WX
ifneq ($(DBG), 0)
	DEFINES+=-DDEBUG -D_DEBUG -DWXDEBUG
endif
ifneq ($(DBG_CMP), 0)
	DEFINES+=-Winvalid-pch -H
endif

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

ifeq ($(DBG), 0)
ifneq ($(OPT), 0)
	CXXFLAGS+=-O$(OPT)
ifeq ($(OPT), 6)
	CXXFLAGS+=-flto -march=native -frename-registers
endif
endif
else
	CXXFLAGS+=-Og
endif


LDFLAGS=-L$(LDIR) -L$(LDIR)/wx
ifeq ($(ENV), Linux)
	LDFLAGS+=# TODO add Linux wx linker args
else
	LDFLAGS+=-lshlwapi -lopengl32 -lglu32 $(LDIR)/wx/libwxbase31u.a $(LDIR)/wx/libwxmsw31u_core.a $(LDIR)/wx/libwxmsw31u_gl.a
ifeq ($(DBG), 0)
	LDFLAGS+=-mwindows
endif
endif

_DEPS=Main.h wxWindow.h wxCanvas.h WXImage.h
DEPS=$(patsubst %,$(SDIR)/%,$(_DEPS))

_OBJ=Main.o wxWindow.o wxCanvas.o WXImage.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

NAME=JFVGL

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(DEFINES) -c $< -o$@

all: $(OBJ)
	$(CXX) -o$(NAME) $^ $(LDFLAGS)

$(SDIR)/prec.h.gch: $(SDIR)/prec.h
	$(CXX) $(CXXFLAGS) $(DEFINES) -c $< -o$@

prec: $(SDIR)/prec.h.gch

clean:
	rm -f $(NAME)
	rm -r -f obj
	mkdir obj
