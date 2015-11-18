
NAME			= diskerror_stem
INI_DIR			= /etc/php5/mods-available/
EXTENSION_DIR	= $(shell php-config --extension-dir)
EXTENSION 		= ${NAME}.so
INI 			= ${NAME}.ini

COMPILER		= g++
LINKER			= g++
COMPILER_FLAGS	= -Wall -c -O2 -std=c++11 -fpic
LINKER_FLAGS	= -shared

LDLIBS = \
	-lphpcpp

CPP	= ${COMPILER} ${COMPILER_FLAGS} -include "precompile.hpp" $<

RM		= rm -f
CP		= cp -f
MKDIR	= mkdir -p

OBJECTS = \
	MultiTokenizer.o \
	StemmerConst.o \
	Stemmer.o \
	main.o


all: ${EXTENSION}

pre: cleanpre \
	precompile.o

${EXTENSION}: ${OBJECTS} precompile.o
	${LINKER} ${LDLIBS} ${OBJECTS} ${LINKER_FLAGS} -o $@

precompile.o: precompile.hpp
	${COMPILER} ${COMPILER_FLAGS} -I/usr/include $< -o $@

MultiTokenizer.o: ../MultiTokenizer.cp ../MultiTokenizer.h
	$(CPP)

StemmerConst.o: ../StemmerConst.cp ../Stemmer.h
	$(CPP)

Stemmer.o: ../Stemmer.cp ../Stemmer.h
	$(CPP)

main.o: main.cp ../Stemmer.h ../MultiTokenizer.h
	$(CPP)

install:		
	${CP} ${EXTENSION} ${EXTENSION_DIR}
	chmod 755 ${EXTENSION_DIR}/${EXTENSION}
	echo "extension = "${EXTENSION}"\n" > ${INI_DIR}${INI}
	chmod 644 ${INI_DIR}${INI}
				
clean:
	${RM} ${EXTENSION} ${OBJECTS} precompile.o

cleanpre:
	$(RM) precompile.o
