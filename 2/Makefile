#
# Created by gmakemake (Ubuntu Jul 25 2014) on Wed Oct 26 23:07:36 2016
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

FLAGS=  -ggdb -std=c99 -Wall -Wextra -pedantic

CLIBFLAGS= -lm

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	mmult-driver.c mmult.c
PS_FILES =	
S_FILES =	
H_FILES =	mmult.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	mmult.o 

#
# Main targets
#

all:	mmult-driver 

mmult-driver:	mmult-driver.o $(OBJFILES)
	$(CC) $(CFLAGS) -o mmult-driver mmult-driver.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

mmult-driver.o:	mmult.h
mmult.o:	mmult.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) mmult-driver.o core

realclean:        clean
	-/bin/rm -f mmult-driver 
