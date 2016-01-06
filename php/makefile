
NAME			= diskerror_stem
INI_DIR			= /etc/php5/mods-available/
EXTENSION_DIR	= $(shell php-config --extension-dir)
EXTENSION 		= ${NAME}.so
INI 			= ${NAME}.ini

COMPILER		= g++
LINKER			= g++
COMPILER_FLAGS	= -Wall -c -O2 -std=c++11 -fpic  -I/usr/local/include
LINKER_FLAGS	= -shared

LDLIBS = \
	-lphpcpp \
	-lpcre2-8

CPP	= ${COMPILER} ${COMPILER_FLAGS} -include "precompile.hpp" $<

RM		= rm -f
CP		= cp -f
MKDIR	= mkdir -p

OBJECTS = \
	MultiTokenizer.o \
	Pcre2.o \
	Substitute.o \
	Match.o \
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


install:		
	${CP} ${EXTENSION} ${EXTENSION_DIR}
	chmod 755 ${EXTENSION_DIR}/${EXTENSION}
	echo "extension = "${EXTENSION}"\n" > ${INI_DIR}${INI}
	chmod 644 ${INI_DIR}${INI}
	ln -sf ${INI_DIR}${INI} /etc/php5/apache2/conf.d/
	ln -sf ${INI_DIR}${INI} /etc/php5/cli/conf.d/

uninstall:
	$(RM) ${EXTENSION_DIR}/${EXTENSION} ${INI_DIR}${INI} /etc/php5/apache2/conf.d/${INI} /etc/php5/cli/conf.d/${INI}

				
clean:
	${RM} ${EXTENSION} ${OBJECTS}

cleanpre:
	$(RM) precompile.o
