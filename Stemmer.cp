/*
	See also http://www.tartarus.org/~martin/PorterStemmer
				http://snowball.tartarus.org

*/

#include "Stemmer.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
void toLower(string& in)
{
	for(auto &c : in) {
		c = tolower(c);
	}
}


/**
is vowel
Should vowels include an apostrophy? ie. "don't"?
http://www.perlmonks.org/?node_id=592883
my @vowels = ( /[aeiuo]/gi );
my @vowels = ( /[aeiou]|y(?![aeiou])/gi );
my @vowels = ( /[aeiou]|(?<![aeiou])y(?![aeiou])/gi );
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
string Stemmer::StemWord(string in)
{
	//	remove spaces at beginning and end of string
	in = regex_replace(in, re_sTrim, "$1");

	toLower(in);

	//	Prelude 1
	in = regex_replace(in, re_apos, "$2");
	//	Words two characters and shorter are not further altered.
	if (in.size() <= 2) {
		return in;
	}
	
	//	Step 0
	in = regex_replace(in, re_aposS, "");
	//	Only remove trailing apostrophe when preceeded by an S.
	//	This departs from the descriptive text AND ALSO
	//	departs from the sample output, which doesn't match the description.
	in = regex_replace(in, re_Sapos, "$1");

	//	Words two characters and shorter are not further altered.
	if (in.size() <= 2) {
		return in;
	}


	//	Exception 1
	if ( in == "skis" ) return (string) "ski";
	if ( in == "skies" ) return (string) "sky";
	if ( in == "dying" ) return (string) "die";
	if ( in == "lying" ) return (string) "lie";
	if ( in == "tying" ) return (string) "tie";

	if ( in == "idly" ) return (string) "idl";
	if ( in == "gently" ) return (string) "gentl";
	if ( in == "ugly" ) return (string) "ugli";
	if ( in == "early" ) return (string) "earli";
	if ( in == "only" ) return (string) "onli";
	if ( in == "singly" ) return (string) "singl";

	if (
		in == "sky" || in == "news" || in == "howe" ||
		in == "atlas" || in == "cosmos" || in == "bias" || in == "andes"
	) {
		return in;
	}
	
	
	smatch match;

	//	Over-stemmed words: match "gener" + one or more vowels + one consonant
	if ( regex_search(in, match, re_generVC) ) {
		return match[1];
	}
	

	//	Prelude 2
	in = regex_replace(in, re_Vy, "$1Y");


	//	Step_1a
	if ( regex_match(in, match, re_sses) ) {
		in = match[1];
		in += "ss";
	}
	else if ( regex_match(in, match, re_ied_ies) ) {
		in = match[1];
		in += "i";
	}
	else if ( regex_match(in, re_us_ss) ) {
		;	//	do nothing
	}
	else if ( regex_match(in, match, re_xVxs) ) {
		in = match[1];
	}


	//	Exception 2
	if (
		in == "inning" || in == "outing" || in == "canning" || in == "herring" || in == "earring" ||
		in == "proceed" || in == "exceed" || in == "succeed"
	) {
		return in;
	}
	

	//	Step 1b
	if ( regex_match(in, match, re_eed_eedly) ) {
		in = match[1];
	}
	else if ( regex_match(in, match, re_ed_ingly) ) {
		in = match[1];
		
		if ( regex_match(in, re_at_bl_iz) ) {
			in += "e";
		}
		else if ( regex_match(in, match, re_dbl_end) ) {
			in = match[1];
		}
		else if ( regex_match(in, re_VwxY) ) {
			in += "e";
		}
	}
	
	//	My addition that solves some "e" endings.
	if ( in.size() == 2 ) {
		in += "e";
		toLower(in);
		return in;
	}
	else {
		switch( in.size() ) {
			case 1:
			case 3:
			toLower(in);
			return in;
		}
	}


	//	Step 1c
	in = regex_replace(in, re_CyY, "$1i");


	/**
	Step 2 suffixes sorted alphabetically R to L, longest to shortest
	Groupings help identify which items must be done in a particular order.

	   anci:   replace by ance
	   enci:   replace by ence

		ogi:   replace by og if preceded by l

	   abli:   replace by able
		bli:   replace by ble

	 lessli:   replace by less
	  fulli:   replace by ful
	  ousli:   replace by ous
	  entli:   replace by ent
	   alli:   replace by al
		 li:   delete if preceded by a valid li-ending

	 biliti:   replace by ble
	  aliti:   replace by al
	  iviti:   replace by ive

	ational:   replace by ate
	 tional:   replace by tion

	  alism:   replace by al

	ization:   replace by ize
	  ation:   replace by ate

	   izer:   replace by ize
	   ator:   replace by ate

	fulness:   replace by ful
	ousness:   replace by ous
	iveness:   replace by ive
	*/
	switch ( in.back() ) {
		case 'i':
		switch ( in[in.size()-2] ) {
			case 'c':
			in = regex_replace(in, re_anci, "$1e");
			break;

			case 'g':
			in = regex_replace(in, re_logi, "$1");
			break;

			case 'l':
			if ( regex_match(in, match, re_bli) ) {
				in = match[1];
				in += "e";
			}
			else {
				in = regex_replace(in, re_lessli, "$1");
			}
			break;

			case 't':
			if ( regex_match(in, match, re_biliti) ) {
				in = match[1];
				in += "ble";
			}
			else if ( regex_match(in, match, re_aliti) ) {
				in = match[1];
				in += "al";
			}
			else {
				in = regex_replace(in, re_iviti, "$1ive");
			}
			break;
		}
		break;

		case 'l':
		if ( regex_match(in, match, re_ational) ) {
			in = match[1];
			in += "ate";
		}
		else {
			in = regex_replace(in, re_tional, "$1tion");
		}
		break;

		case 'm':
		in = regex_replace(in, re_alism, "$1al");
		break;

		case 'n':
		if ( regex_match(in, match, re_ization) ) {
			in = match[1];
			in += "ize";
		}
		else {
			in = regex_replace(in, re_ation, "$1ate");
		}
		break;

		case 'r':
		if ( regex_match(in, match, re_ator) ) {
			in = match[1];
			in += "e";
		}
		else {
			in = regex_replace(in, re_izer, "$1e");
		}
		break;

		case 's':
		in = regex_replace(in, re_fulness, "$1");
		break;
	}
	

	/**
	Step 3
	ational:   replace by ate
	 tional:   replace by tion

	  alize:   replace by al
	  icate:   replace by ic
	  iciti:   replace by ic
	   ical:   replace by ic

	  ative:   delete if in R2

	    ful:   delete
	   ness:   delete
	*/
	if ( regex_match(in, match, re_ational) ) {
		in = match[1];
		in += "ate";
	}
	else if ( regex_match(in, match, re_tional) ) {
		in = match[1];
		in += "tion";
	}
	else if ( regex_match(in, match, re_alize) ) {
		in = match[1];
	}
	else if ( regex_match(in, match, re_icate) ) {
		in = match[1];
	}
	else if ( regex_match(in, match, re_ful_ness) ) {
		in = match[1];
	}
	else {
		in = regex_replace(in, re_ative, "$1");
	}


	//	Step 4
	if ( regex_match(in, match, re_ement) ) {
		in = match[1];
	}
	else if ( regex_match(in, match, re_ment) ) {
		in = match[1];
	}
	else if ( regex_match(in, match, re_ent) ) {
		in = match[1];
	}
	else if ( regex_match(in, match, re_al_er_ic) ) {
		in = match[1];
	}
	else {
		in = regex_replace(in, re_sion_tion, "$1");
	}
	

	//	Step 5 (partial)
	if ( regex_match(in, match, re_R2e) ) {
		in = match[1];
	}
	else {
		in = regex_replace(in, re_ll, "$1l");
	}
	

	//	postlude
	//	Change Y to y.
	toLower(in);
	
	return in;
}
