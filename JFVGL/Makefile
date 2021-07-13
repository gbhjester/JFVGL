NAME=JFVGL

#WINDOWS, LINUX
ENV=WINDOWS
DEFINES=-D$(ENV)

# Debug compilation
# 0, 1
DBG_CMP=0

# d, 0, 1, f
# d : debug (-Og)
# 0 : no optimization (no -Ox flag set)
# 1 : -O3 and some -fflags to ensure attempt autovectorization
# f : -Ofast and break everything
OPT=f

# Use OpenMP and parallel glibc
# 0, 1
OMP=1

# Logical threadcount passed to GCC
LTC=16

# PEDANTIC MODE.
# 0, 1
PEDANTIC_ERROR_OUT=0

# Codepath switches
#DEFINES+=-DWXIMAGE_USESOFTWAREIMAGEPROCESSING
#DEFINES+=-DWXIMAGE_USESOFTWAREIMAGEPREPROCESSING

IDIR=inc
LDIR=.
ifeq ($(ENV), LINUX)
	LDIR=lib/deb
endif
ifeq ($(ENV), WINDOWS)
	LDIR=lib/win64
endif
SDIR=src
ODIR=obj

CXX=g++
CXXFLAGS=-std=c++98 -Wall -I"$(IDIR)"

ifneq ($(DBG_CMP), 0)
	DEFINES+=-H
	#DEFINES+=-Winvalid-pch
endif

ifneq ($(PEDANTIC_ERROR_OUT), 0)
	CXXFLAGS+=-Wextra -Werror -Wpedantic
endif

ifeq ($(OPT), d)
	CXXFLAGS+=-Og
	DEFINES+=-DDEBUG -D_DEBUG -DWXDEBUG
else
    CXXFLAGS+=-s
endif
ifeq ($(OPT), 1)
	CXXFLAGS+=-O3 -frename-registers -funroll-loops -fpeel-loops -ftree-vectorize -ftree-parallelize-loops=$(LTC) -march=native
endif
ifeq ($(OPT), f)
	CXXFLAGS+=-Ofast -frename-registers -funroll-loops -fpeel-loops -ffast-math -ffinite-math-only -fno-signed-zeros -fno-trapping-math -ftree-vectorize -ftree-parallelize-loops=$(LTC) -march=native
endif
ifneq ($(OMP), 0)
	CXXFLAGS+=-fopenmp
	LDFLAGS+=-fopenmp
	DEFINES+=-D_LIBGCXX_PARALLEL
endif

LDFLAGS=-L$(LDIR) -L$(LDIR)/wx
ifeq ($(ENV), LINUX)
	LDFLAGS+=-lGL -lGLU
	#LDFLAGS+=-lGL -lGLU $(LDIR)/wx/libwxbase31u.a $(LDIR)/wx/libwxmsw31u_core.a $(LDIR)/wx/libwxmsw31u_gl.a
endif
ifeq ($(ENV), WINDOWS)
	LDFLAGS+=-lshlwapi -lopengl32 -lglu32 $(LDIR)/wx/libwxbase31u.a $(LDIR)/wx/libwxmsw31u_core.a $(LDIR)/wx/libwxmsw31u_gl.a -mwindows -flto
endif

# Source files to generate object files for
_SRC=Main WXApp WXWindow WXCanvas WXImage
SRC=$(patsubst %,$(SDIR)/%.cpp,$(_SRC))
OBJ=$(patsubst %,$(ODIR)/%.o,$(_SRC))

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CXX) -c "$<" -o"$@" $(CXXFLAGS) $(DEFINES)

all: $(OBJ)
	$(CXX) -o"$(NAME)" $^ $(LDFLAGS)

#$(SDIR)/prec.h.gch: $(SDIR)/prec.h
#	$(CXX) $(CXXFLAGS) $(DEFINES) -c $< -o$@
#prec: $(SDIR)/prec.h.gch

clean:
	rm -f $(NAME)
	rm -f $(NAME).exe
	rm -r -f obj
	mkdir obj
