
COMP = g++
CXX	= $(COMP) -std=c++11 -Wall -Winvalid-pch -c -I/usr/local/include -O2
CPP	= $(CXX) -include "precompile.hpp" $<
RM	= rm -f

LDLIBS = \
	-L/usr/local/lib \
	-Wl,-rpath,/usr/local/lib \
	-lpcre2-8

OBJECTS = \
	obj/MultiTokenizer.o \
	obj/Pcre2.o \
	obj/Substitute.o \
	obj/Match.o \
	obj/StemmerConst.o \
	obj/Stemmer.o \
	obj/main.o


all: stem

pre: cleanpre \
	precompile.o

stem: $(OBJECTS) precompile.o
	$(COMP) $(LDLIBS) $(OBJECTS) -o $@

obj/precompile.o: precompile.hpp
	$(CXX) -x c++-header $< -o $@

obj/Pcre2.o: ../Pcre2/Pcre2.cp ../Pcre2/Pcre2.h
	$(CPP)

obj/Substitute.o: ../Pcre2/Substitute.cp ../Pcre2/Substitute.h
	$(CPP)

obj/Match.o: ../Pcre2/Match.cp ../Pcre2/Match.h
	$(CPP)

obj/MultiTokenizer.o: ../MultiTokenizer.cp ../MultiTokenizer.h
	$(CPP)

obj/StemmerConst.o: ../StemmerConst.cp ../Stemmer.h
	$(CPP)

obj/Stemmer.o: ../Stemmer.cp ../Stemmer.h
	$(CPP)

obj/main.o: main.cp ../MultiTokenizer.h ../Stemmer.h
	$(CPP)


clean:
	$(RM) $(OBJECTS) stem

cleanpre:
	$(RM) precompile.o
