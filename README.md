# Stemmer
A stemmer based on the Porter 2 stemmer primarily using regular expressions. It was written as a personal exercise in C++ programming, PCRE2 regular expressions, and for building PHP extensions. There is also a simple command line version.

Sample text files are at http://snowball.tartarus.org.

## Testing
The makefiles have been tested on Debian 8 with PHP 5.6 and 7.2,  and CentOS 6 with PHP 5.5.

## MultiTokenizer
This is used with the Stemmer PHP extension. It's a simple text tokenizer that allows for multiple characters to be used as a delimiter.

## CLI
The CLI version accepts text from the command line (STDIN) or from a file with the "-f" option. All output is directed to the command line (STDOUT).

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
The [PCRE2](http://www.pcre.org) library must be downloaded and installed.
```
 > ./configure --enable-jit --enable-newline-is-anycrlf
 > make
 > sudo make install
```

## PHP-CPP
The [Copernica](http://www.copernica.com) [PHP-CPP](http://www.php-cpp.com/) library is used to build the PHP extension.
```
 > make release
 > sudo make install
```
Just using ```make``` will create a slower debug version.

# Hyperscan
Until further notice the "hyperscan" branch has been abandoned.

There are many reports of the Hyperscan regular expression engine being upwards of 10 times faster than PCRE but that didn't prove to be the case in this implimentation. It happens that it is 10%-15% slower than the PCRE2 version. Also, the compiler (gcc version 4.9.2) reported that Hyperscan needs to be compiled with the "-fPIC" option in order to be linked to a PHP extension. Customizing someone elses code makes this too much work for an implemention that's already slower than the original design.

The command line version is functional and takes both text directly and reads files with the "-f" option.
