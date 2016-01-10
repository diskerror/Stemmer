
NAME			= diskerror_stem

PHPE			= /etc/php5
INI_DIR			= $(PHPE)/mods-available/
EXTENSION_DIR	= $(shell php-config --extension-dir)
EXTENSION 		= $(NAME).so
INI 			= $(NAME).ini

COMPILER		= g++
LINKER			= g++
COMPILER_FLAGS	= -Wall -c -O2 -std=c++11 -fpic -I/usr/local/include
LINKER_FLAGS	= -shared

LDLIBS = \
	-lphpcpp \
	-L/usr/local/lib \
	-Wl,-rpath,/usr/local/lib \
	-lpcre2-8

CPP	= $(COMPILER) $(COMPILER_FLAGS) -include "precompile.hpp" $<

OBJECTS = \
	MultiTokenizer.o \
	Pcre2.o \
	Substitute.o \
	Match.o \
	StemmerConst.o \
	Stemmer.o \
	main.o


all: $(EXTENSION)

pre: cleanpre \
	precompile.o

$(EXTENSION): $(OBJECTS) precompile.o
	$(LINKER) $(OBJECTS) $(LINKER_FLAGS) $(LDLIBS) -o $@

precompile.o: precompile.hpp
	$(COMPILER) $(COMPILER_FLAGS) $< -o $@


Pcre2.o: ../Pcre2/Pcre2.cp ../Pcre2/Pcre2.h
	$(CPP)

Substitute.o: ../Pcre2/Substitute.cp ../Pcre2/Substitute.h
	$(CPP)

Match.o: ../Pcre2/Match.cp ../Pcre2/Match.h
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
	cp -f $(EXTENSION) $(EXTENSION_DIR)
	chmod 644 $(EXTENSION_DIR)/$(EXTENSION)
	echo "extension = "$(EXTENSION)"\n" > $(INI_DIR)$(INI)
	chmod 644 $(INI_DIR)$(INI)
	if [ -d $(PHPE)/apache2/conf.d/ ]; then \
		ln -sf $(INI_DIR)$(INI) $(PHPE)/apache2/conf.d/;\
	fi
	if [ -d $(PHPE)/cli/conf.d/ ]; then \
		ln -sf $(INI_DIR)$(INI) $(PHPE)/cli/conf.d/;\
	fi
	if [ -d $(PHPE)/cgi/conf.d/ ]; then \
		ln -sf $(INI_DIR)$(INI) $(PHPE)/cgi/conf.d/;\
	fi

uninstall:
	rm -f $(EXTENSION_DIR)/$(EXTENSION) \
		$(INI_DIR)$(INI) \
		$(PHPE)/apache2/conf.d/$(INI) \
		$(PHPE)/cli/conf.d/$(INI) \
		$(PHPE)/cgi/conf.d/$(INI)

				
clean:
	rm -f $(EXTENSION) $(OBJECTS)

cleanpre:
	rm -f precompile.o
