
COMP = g++
CXX	= $(COMP) -std=c++11 -Wall -Winvalid-pch -c -I/opt/local/include -I/usr/include -O2
CPP	= $(CXX) -include "precompile.hpp" $<
RM	= rm -f

LDLIBS= \
#	-L/opt/local/lib \
	-lboost_system-mt

SOURCES= \
	Stemmer.cp \
	main.cp

OBJECTS=$(subst .cp,.o,$(subst .cpp,.o,$(SOURCES)))


all: stem

pre: cleanpre \
	precompile.o

stem: $(OBJECTS) precompile.o
	$(COMP) $(LDLIBS) $(OBJECTS) -o $@

precompile.o: precompile.hpp
	$(CXX) -x c++-header $< -o $@

Stemmer.o: ../Stemmer.cp ../Stemmer.h
	$(CPP)

main.o: main.cp ../Stemmer.h
	$(CPP)


clean:
	$(RM) $(OBJECTS) precompile.o stem

cleanpre:
	$(RM) precompile.o
