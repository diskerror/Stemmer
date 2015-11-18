
COMP = g++
CXX	= $(COMP) -std=c++11 -Wall -Winvalid-pch -c -I/opt/local/include -I/usr/include -O2
CPP	= $(CXX) -include "precompile.hpp" $<
RM	= rm -f

LDLIBS = \
#	-L/opt/local/lib

OBJECTS = \
	MultiTokenizer.o \
	StemmerConst.o \
	Stemmer.o \
	main.o


all: stem

pre: cleanpre \
	precompile.o

stem: $(OBJECTS) precompile.o
	$(COMP) $(LDLIBS) $(OBJECTS) -o $@

precompile.o: precompile.hpp
	$(CXX) -x c++-header $< -o $@

MultiTokenizer.o: ../MultiTokenizer.cp ../MultiTokenizer.h
	$(CPP)

StemmerConst.o: ../StemmerConst.cp ../Stemmer.h
	$(CPP)

Stemmer.o: ../Stemmer.cp ../Stemmer.h
	$(CPP)

main.o: main.cp ../MultiTokenizer.h ../Stemmer.h
	$(CPP)


clean:
	$(RM) $(OBJECTS) precompile.o stem

cleanpre:
	$(RM) precompile.o
