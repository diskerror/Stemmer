
COMP = g++
CXX	= $(COMP) -std=c++11 -Wall -Winvalid-pch -c -I/usr/local/include -O2
CPP	= $(CXX) -include "precompile.hpp" $<
RM	= rm -f

LDLIBS = \
	-L/usr/local/lib \
	-lpcre2-8

OBJECTS = \
	MultiTokenizer.o \
	Pcre2.o \
	Substitute.o \
	Match.o \
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

Pcre2.o: ../Pcre2/Pcre2.cp ../Pcre2/Pcre2.h
	$(CPP)

Substitute.o: ../Pcre2/Substitute.cp ../Pcre2/Substitute.h ../Pcre2/Pcre2.h
	$(CPP)

Match.o: ../Pcre2/Match.cp ../Pcre2/Match.h ../Pcre2/Pcre2.h
	$(CPP)

MultiTokenizer.o: ../MultiTokenizer.cp ../MultiTokenizer.h
	$(CPP)

StemmerConst.o: ../StemmerConst.cp ../Stemmer.h
	$(CPP)

Stemmer.o: ../Stemmer.cp ../Stemmer.h
	$(CPP)

main.o: main.cp ../MultiTokenizer.h ../Stemmer.h
	$(CPP)


clean:
	$(RM) $(OBJECTS) stem

cleanpre:
	$(RM) precompile.o
