# I, Jester, hereby release this work, except as stated otherwise, into the public domain.

ENV=$(shell uname)
DBG=1

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

LFLAGS=-L$(LDIR)
ifeq ($(ENV), Linux)
	LFLAGS+=# TODO add Linux linker args
else
	LFLAGS+= #-mwindows
endif

_WXDEFINES=WIN32 WINVER=0X400 __WXMSW__ _WINDOWS WXUSINGDLL wxUSE_GUI=1 _UNICODE
ifneq ($(DBG), 0)
	_WXDEFINES+=_DEBUG
endif
WXDEFINES=$(patsubst %,-D%,$(_WXDEFINES))

_DEPS=Main.h wxWindow.h
DEPS=$(patsubst %,$(SDIR)/%,$(_DEPS))

_OBJ=Main.o wxWindow.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

NAME=JFVGL

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o$@

all: $(OBJ)
	$(CXX) -o$(NAME) $^ $(LFLAGS)

clean:
	rm -f $(NAME)
	rm -r -f obj
	mkdir obj
