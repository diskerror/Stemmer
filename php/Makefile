
NAME			= diskerror_stem

EXTENSION_DIR	= $(shell php-config --extension-dir)
EXTENSION 		= $(NAME).so
INI 			= $(NAME).ini
INI_PATH        = $(shell php --ini | head -1 | sed -r 's/.+: (.+)\/cli/\1/')

COMP			= g++
# COMPILER_FLAGS	= -Wall -c -O2 -std=c++11 -fPIC -I/usr/local/include
COMPILER_FLAGS	= -Wall -c -O2 -std=c++11 -Winvalid-pch -fPIC -I/usr/local/include
CPP	= $(COMP) $(COMPILER_FLAGS) -include precompile.hpp $< -o $@

LDLIBS = \
	-lphpcpp \
	-L/usr/local/lib \
	-Wl,-rpath,/usr/local/lib \
	-lhs

OBJECTS = \
	obj/main.o \
	obj/MultiTokenizer.o \
	obj/Stemmer.o \
	obj/StemmerConst.o \
	obj/HasMatch.o \
	obj/Hyperscan.o \
	obj/GetMatch.o \
	obj/RemoveMatch.o


all: $(EXTENSION)

$(EXTENSION): obj/precompile.o $(OBJECTS)
	$(COMP) $(OBJECTS) -shared $(LDLIBS) -o $@

obj/precompile.o: precompile.hpp
	mkdir -p obj
	$(COMP) $(COMPILER_FLAGS) $< -o $@


obj/Hyperscan.o: ../Hyperscan/Hyperscan.cp ../Hyperscan/Hyperscan.h Makefile
	$(CPP)

obj/HasMatch.o: ../Hyperscan/HasMatch.cp ../Hyperscan/HasMatch.h ../Hyperscan/Hyperscan.h Makefile
	$(CPP)

obj/GetMatch.o: ../Hyperscan/GetMatch.cp ../Hyperscan/GetMatch.h ../Hyperscan/Hyperscan.h Makefile
	$(CPP)

obj/RemoveMatch.o: ../Hyperscan/RemoveMatch.cp ../Hyperscan/RemoveMatch.h ../Hyperscan/Hyperscan.h Makefile
	$(CPP)

obj/MultiTokenizer.o: ../MultiTokenizer.cp ../MultiTokenizer.h Makefile
	$(CPP)

obj/StemmerConst.o: ../StemmerConst.cp ../Stemmer.h ../Hyperscan/HasMatch.h ../Hyperscan/Hyperscan.h ../Hyperscan/GetMatch.h ../Hyperscan/RemoveMatch.h Makefile
	$(CPP)

obj/Stemmer.o: ../Stemmer.cp ../Stemmer.h ../Hyperscan/HasMatch.h ../Hyperscan/Hyperscan.h ../Hyperscan/GetMatch.h ../Hyperscan/RemoveMatch.h Makefile
	$(CPP)

obj/main.o: main.cp ../MultiTokenizer.h ../Stemmer.h ../Hyperscan/HasMatch.h ../Hyperscan/Hyperscan.h ../Hyperscan/GetMatch.h  ../Hyperscan/RemoveMatch.h Makefile
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
	rm -rf $(EXTENSION) obj
