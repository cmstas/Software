include Makefile.arch

ROOTINCDIR := $(shell $(ROOTCONFIG) --incdir)
LDFLAGS    += -fPIC

SIMPLETABLEH = CTable.h CNumBase.h
SIMPLETABLEO = ${SIMPLETABLEH:.h=.o  } SimpleTableDict.o 
SIMPLETABLES = ${SIMPLETABLEH:.o=.cpp}

all: libSimpleTable.so

libSimpleTable.so: LinkDef.h $(SIMPLETABLEO)
	$(LD) $(LDFLAGS) $(ROOTLIBS) -Wno-deprecated $(SOFLAGS) $(SIMPLETABLEO) -o $@

%.o : %.cpp %.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

SimpleTableDict.cpp : $(SIMPLETABLEH)
	rootcint -v3 -f $@ -c -I$(ROOTINCDIR) -p $(SIMPLETABLEH) LinkDef.h 

clean:
	@rm -f core *.o *.so SimpleTableDict.* test
