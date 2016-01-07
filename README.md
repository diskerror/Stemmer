# Stemmer
Realization of Porter 2 stemmer primarily using regular expressions. This implimentation is not a fully accurate version of the stemmer as it contains some alternate and additional rules.

It was written as a personal exercise in C++ programming and for building PHP extensions. There is also a simple command line version. The PHP extension requires the Copernica [PHP-CPP](http://www.phpcpp.com) API to be installed on the host system.

Sample text files are from http://snowball.tartarus.org.

[PCRE2](http://www.pcre.org) (v10.20) was used to replace the C++11 "regex" library for version 0.3 of the stemmer. PCRE2 processes the 42,600 word file "voc2.txt" in 1/4 the time as "regex". Compiling this code requires that PCRE2 library be installed on the local system.

Command line makefile has been tested on Debian 8.

# MultiTokenizer
This is used with the Stemmer PHP extension. It's a simple text tokenizer that allows for multiple characters to be used as a delimiter.
