
COMP = g++
CXX	= $(COMP) -std=c++11 -Wall -Winvalid-pch -c -I/usr/local/include -O2
CPP	= $(CXX) -include "precompile.hpp" $< -o $@
RM	= rm -rf

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
	obj/precompile.o

stem: obj/precompile.o $(OBJECTS)
	$(COMP) $(OBJECTS) $(LDLIBS) -o $@

# precompiled header intentionally does not depend on changes to this file
# use "clean" or "cleanpre" if necessary
obj/precompile.o: precompile.hpp
	mkdir -p obj
	$(CXX) -x c++-header $< -o $@

obj/Pcre2.o: ../Pcre2/Pcre2.cp ../Pcre2/Pcre2.h Makefile
	$(CPP)

obj/Substitute.o: ../Pcre2/Substitute.cp ../Pcre2/Substitute.h ../Pcre2/Pcre2.h Makefile
	$(CPP)

obj/Match.o: ../Pcre2/Match.cp ../Pcre2/Match.h ../Pcre2/Pcre2.h Makefile
	$(CPP)

obj/MultiTokenizer.o: ../MultiTokenizer.cp ../MultiTokenizer.h Makefile
	$(CPP)

obj/StemmerConst.o: ../StemmerConst.cp ../Stemmer.h ../Pcre2/Substitute.h ../Pcre2/Pcre2.h ../Pcre2/Match.h Makefile
	$(CPP)

obj/Stemmer.o: ../Stemmer.cp ../Stemmer.h ../Pcre2/Substitute.h ../Pcre2/Pcre2.h ../Pcre2/Match.h Makefile
	$(CPP)

obj/main.o: main.cp ../MultiTokenizer.h ../Stemmer.h ../Pcre2/Substitute.h ../Pcre2/Pcre2.h ../Pcre2/Match.h Makefile
	$(CPP)


clean:
	$(RM) obj stem

cleanpre:
	$(RM) obj/precompile.o
