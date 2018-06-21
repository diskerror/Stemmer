# Stemmer
A stemmer based on the Porter 2 stemmer primarily using regular expressions. There is also a simple command line version.

# Hyperscan
Until further notice this branch has been abandonded.

There are many reports of Hyperscan being upwards of 10 times faster than PCRE2 but that didn't prove to be the case in this implimentation. Also, the compiler (gcc version 4.9.2) reported that Hyperscan needs to be compiled with the "-fPIC" option in order to be linked to a PHP extension. That makes too much work for an implemention that's is slower than the original.

The command line version is functional and takes both text directly and reads files with the "-f" option.
