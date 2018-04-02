
NAME			= diskerror_stem

EXTENSION_DIR	= $(shell php-config --extension-dir)
EXTENSION 		= $(NAME).so
INI 			= $(NAME).ini
INI_PATH        = $(shell php --ini | head -1 | sed -r 's/.+: (.+)\/cli/\1/')

COMPILER		= g++
LINKER			= g++
COMPILER_FLAGS	= -Wall -c -O2 -std=c++11 -fPIC -I/usr/local/include
LINKER_FLAGS	= -shared

LDLIBS = \
	-lphpcpp \
	-L/usr/local/lib \
	-Wl,-rpath,/usr/local/lib \
	-lpcre2-8

CPP	= $(COMPILER) $(COMPILER_FLAGS) -include precompile.hpp $< -o $@

OBJECTS = \
	obj/MultiTokenizer.o \
	obj/Pcre2.o \
	obj/Substitute.o \
	obj/Match.o \
	obj/StemmerConst.o \
	obj/Stemmer.o \
	obj/main.o


all: $(EXTENSION)

pre: cleanall \
	obj/precompile.o

$(EXTENSION): obj/precompile.o $(OBJECTS)
	$(LINKER) $(OBJECTS) $(LINKER_FLAGS) $(LDLIBS) -o $@

obj/precompile.o: precompile.hpp
	mkdir -p obj
	$(COMPILER) $(COMPILER_FLAGS) $< -o $@


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


# Installation and cleanup. (tested on Debian 8 and CentOS 6)
install: $(EXTENSION)
	cp -f $(EXTENSION) $(EXTENSION_DIR)
	chmod 644 $(EXTENSION_DIR)/$(EXTENSION)
	if [ -d $(INI_PATH)/mods-available/ ]; then \
		echo "extension = "$(EXTENSION) > $(INI_PATH)/mods-available/$(INI); \
		chmod 644 $(INI_PATH)/mods-available/$(INI); \
		if [ -d $(INI_PATH)/apache2/conf.d/ ]; then \
			ln -sf $(INI_PATH)/mods-available/$(INI) $(INI_PATH)/apache2/conf.d/; \
		fi; \
		if [ -d $(INI_PATH)/cli/conf.d/ ]; then \
			ln -sf $(INI_PATH)/mods-available/$(INI) $(INI_PATH)/cli/conf.d/; \
		fi; \
		if [ -d $(INI_PATH)/cgi/conf.d/ ]; then \
			ln -sf $(INI_PATH)/mods-available/$(INI) $(INI_PATH)/cgi/conf.d/; \
		fi; \
	fi
	if [ -d /etc/php.d/ ]; then \
		echo "extension = "$(EXTENSION) > /etc/php.d/$(INI);\
		chmod 644 /etc/php.d/$(INI);\
	fi
	if [ -d /etc/php-zts.d/ ]; then \
		echo "extension = "$(EXTENSION) > /etc/php-zts.d/$(INI);\
		chmod 644 /etc/php-zts.d/$(INI);\
	fi

uninstall:
	rm -f $(EXTENSION_DIR)/$(EXTENSION)
	find $(INI_PATH) -name $(INI) | xargs rm -f
	rm -f /etc/php.d/$(INI) /etc/php-zts.d/$(INI)

clean:
	rm -f $(EXTENSION) $(OBJECTS)

# remove all objects including precompiled header
cleanall:
	rm -rf $(EXTENSION) obj
