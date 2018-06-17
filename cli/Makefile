COMP = g++
CXX	= $(COMP) -std=c++11 -Wall -Winvalid-pch -c -I/usr/local/include -I/usr/local/include/hs -O2
CPP	= $(CXX) -include "precompile.hpp" $< -o $@
RM	= rm -rf

LDLIBS = \
	-L/usr/local/lib \
	-Wl,-rpath,/usr/local/lib \
	-lhs

OBJECTS = \
	obj/MultiTokenizer.o \
	obj/Hyperscan.o \
	obj/HasMatch.o \
	obj/GetMatch.o \
	obj/RemoveMatch.o \
	obj/ReplaceMatch.o \
	obj/StemmerConst.o \
	obj/Stemmer.o \
	obj/main.o


all: stem Makefile

pre: cleanpre \
	obj/precompile.o

stem: obj/precompile.o $(OBJECTS)
	$(COMP) $(OBJECTS) $(LDLIBS) -o $@

obj/precompile.o: precompile.hpp
	mkdir -p obj
	$(CXX) -x c++-header $< -o $@

obj/Hyperscan.o: ../Hyperscan/Hyperscan.cp ../Hyperscan/Hyperscan.h
	$(CPP)

obj/HasMatch.o: ../Hyperscan/HasMatch.cp ../Hyperscan/HasMatch.h ../Hyperscan/Hyperscan.h
	$(CPP)

obj/GetMatch.o: ../Hyperscan/GetMatch.cp ../Hyperscan/GetMatch.h ../Hyperscan/Hyperscan.h
	$(CPP)

obj/RemoveMatch.o: ../Hyperscan/RemoveMatch.cp ../Hyperscan/RemoveMatch.h ../Hyperscan/Hyperscan.h
	$(CPP)

obj/ReplaceMatch.o: ../Hyperscan/ReplaceMatch.cp ../Hyperscan/ReplaceMatch.h ../Hyperscan/RemoveMatch.h
	$(CPP)

obj/MultiTokenizer.o: ../MultiTokenizer.cp ../MultiTokenizer.h
	$(CPP)

obj/StemmerConst.o: ../StemmerConst.cp ../Stemmer.h ../Hyperscan/HasMatch.h ../Hyperscan/Hyperscan.h ../Hyperscan/GetMatch.h ../Hyperscan/RemoveMatch.h ../Hyperscan/ReplaceMatch.h
	$(CPP)

obj/Stemmer.o: ../Stemmer.cp ../Stemmer.h ../Hyperscan/HasMatch.h ../Hyperscan/Hyperscan.h ../Hyperscan/GetMatch.h ../Hyperscan/RemoveMatch.h ../Hyperscan/ReplaceMatch.h
	$(CPP)

obj/main.o: main.cp ../MultiTokenizer.h ../Stemmer.h ../Hyperscan/HasMatch.h ../Hyperscan/Hyperscan.h ../Hyperscan/GetMatch.h ../Hyperscan/RemoveMatch.h ../Hyperscan/ReplaceMatch.h
	$(CPP)


clean:
	${RM} obj stem

cleanpre:
	$(RM) obj/precompile.o
