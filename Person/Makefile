# Makefile without UserDefined Classes

###############################################################################

#include $(ROOTSYS)/etc/Makefile.arch

###############################################################################

OBJ = main
MainFile = $(OBJ).cpp 
#LinkFile = LinkDef.hh
#UserDict = $(OBJ)Dict.cc

###############################################################################

SourceFile := $(wildcard $(shell pwd)/src/*.c $(shell pwd)/src/*.C $(shell pwd)/src/*.cc $(shell pwd)/src/*.cpp $(shell pwd)/src/*.cxx) 
IncludeFile := $(wildcard $(shell pwd)/include/*.h $(shell pwd)/include/*.hh) 

###############################################################################

GXX = g++

ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs)
ROOTGLIBS   = $(shell root-config --glibs)

DIR_INC = -I$(ROOTSYS)/include -I$(shell pwd)/include #-I$(TARTSYS)/include
CFLAGS = -Wall -O2 $(DIR_INC) -lXMLParser -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -lSpectrum  #-L$(TARTSYS)/lib -lanacore

###############################################################################

all:$(OBJ)
$(OBJ): $(MainFile) $(SourceFile) #$(UserDict)
	$(GXX) -o $@ $(MainFile) $(SourceFile) $(ROOTCFLAGS) $(ROOTLIBS) $(ROOTGLIBS) $(CFLAGS) #$(UserDict) 
	@echo "=============================================================="
	@echo "$@ done !"
	@echo "=============================================================="
#	
#$(UserDict): $(IncludeFile) $(LinkFile)
#	@echo "=============================================================="
#	@echo "Generating dictionary $@..."
#	@echo "=============================================================="
#	rootcint -f $@ -c $(DIR_INC) $^ 	
clean:
	rm -f *.o *.d *Dict* $(OBJ)
	
###############################################################################
