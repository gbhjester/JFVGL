# I, Jester, hereby release this work, except as stated otherwise, into the public domain.

ENV=$(shell uname)
DEFINES=-DTARGET_WX
DEFINES+= -DDEBUG

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
CXXFLAGS=-std=c++11 -Wall -Wpedantic -I$(IDIR)

LDFLAGS=-L$(LDIR) -L$(LDIR)/wx
ifeq ($(ENV), Linux)
	LDFLAGS+=# TODO add Linux wx linker args
else
	LDFLAGS+=$(LDIR)/wx/libwxbase31u.a $(LDIR)/wx/libwxmsw31u_core.a
ifndef DEBUG
	LDFLAGS+=-mwindows
endif
endif

WXDEFINES=
ifndef DEBUG
	WXDEFINES+=-D_DEBUG
endif

_DEPS=Main.h wxWindow.h
DEPS=$(patsubst %,$(SDIR)/%,$(_DEPS))

_OBJ=Main.o wxWindow.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

NAME=JFVGL

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(WXDEFINES) $(DEFINES) -c $< -o$@

all: $(OBJ)
	$(CXX) -o$(NAME) $^ $(LDFLAGS)

clean:
	rm -f $(NAME)
	rm -r -f obj
	mkdir obj
