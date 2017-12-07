# Stemmer
Warning: The are serious errors in the implementation of this algorithm.

Realization of Porter 2 stemmer primarily using regular expressions. It was written as a personal exercise in C++ programming and for building PHP extensions. There is also a simple command line version.

Sample text files are at http://snowball.tartarus.org.

The makefiles have been tested on Debian 8 with PHP 5.6 and CentOS 6 with PHP 5.5

## MultiTokenizer
This is used with the Stemmer PHP extension. It's a simple text tokenizer that allows for multiple characters to be used as a delimiter.

# Requirements For Compiling
GCC, Make, and the standard libraries are required to build and install the custom extension, as is the PHP development libraries.

CentOS 6 requires at least devtoolset-2 to compile PHP-CPP.
```
 > cd /etc/yum.repos.d
 > wget http://people.centos.org/tru/devtools-2/devtools-2.repo
 > yum --enablerepo=testing-devtools-2-centos-6 install devtoolset-2-gcc devtoolset-2-gcc-c++
 > scl enable devtoolset-2 bash
```

## PCRE2
The PCRE2 library must be installed and the source can be found [here](http://www.pcre.org).
```
 > ./configure --enable-jit --enable-newline-is-anycrlf
 > make
 > sudo make install
```

## PHP-CPP
The [Copernica](http://www.copernica.com) PHP-CPP library is used to build the PHP extension.
```
 > make release
 > sudo make install
```
Just using ```make``` will create a slower debug version.
