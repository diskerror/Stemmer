# Stemmer
Realization of Porter 2 stemmer using primarily regular expressions. This implimentation is not a fully accurate version of the stemmer but is still quite useful in this form.

It was written as a personal exercise in C++ programming and for building PHP extensions. There is also a simple command line version. The PHP extension requires the Copernica http://www.phpcpp.com API to be installed on the host system.

Sample text files are from http://snowball.tartarus.org.

Command line makefile has been tested on Debian 8 and OSX 10.10.

# MultiTokenizer
This is used with the Stemmer PHP extension. It's a simple text tokenizer that allows for multiple characters to be used as a delimiter.
