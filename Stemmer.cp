/*
	See also http://www.tartarus.org/~martin/PorterStemmer
				http://snowball.tartarus.org

*/

#include "Stemmer.h"
#include <iostream>

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
Should vowels follow the perlmonks pattern?
http://www.perlmonks.org/?node_id=592883
my @vowels = ( /[aeiuo]/gi );
my @vowels = ( /[aeiou]|y(?![aeiou])/gi );
my @vowels = ( /[aeiou]|(?<![aeiou])y(?![aeiou])/gi );
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
string Stemmer::StemWord(string in)
{
	//	remove spaces at beginning and end of string
	in = re_sTrim(in);

	toLower(in);
// cout << setw(5) << left << __LINE__ << in << endl;

	//	Place to put captured matches.
	vector<string> matches;
	

	//	Prelude 1
	if ( re_apos(in, matches) )
		in = matches[2];
	
	//	Words two characters and shorter are not further altered.
	if (in.size() <= 2) {
		return in;
	}
	
	//	Step 0
	in = re_aposS(in);
	//	Only remove trailing apostrophe when preceeded by an S.
	//	This departs from the descriptive text AND ALSO
	//	departs from the sample output, which doesn't match the description.
	in = re_Sapos(in);

	//	Words two characters and shorter are not further altered.
	if (in.size() <= 2) {
		return in;
	}


	//	Exception 1
	if ( in == "skis" )		return (string) "ski";
	if ( in == "skies" )	return (string) "sky";
	if ( in == "dying" )	return (string) "die";
	if ( in == "lying" )	return (string) "lie";
	if ( in == "tying" )	return (string) "tie";

	if ( in == "idly" )		return (string) "idl";
	if ( in == "gently" )	return (string) "gentl";
	if ( in == "ugly" )		return (string) "ugli";
	if ( in == "early" )	return (string) "earli";
	if ( in == "only" )		return (string) "onli";
	if ( in == "singly" )	return (string) "singl";

	if (
		in == "sky" || in == "news" || in == "howe" ||
		in == "atlas" || in == "cosmos" || in == "bias" || in == "andes"
	) {
		return in;
	}
	
	
	//	Over-stemmed words: match "gener" + one or more vowels + one consonant
	if ( re_generVC(in, matches) ) {
		return matches[1];
	}
	

	//	Prelude 2
	in = re_Vy(in);


	//	Step_1a
	if ( re_sses(in) ) {
		in.resize(in.size()-2);
	}
	else if ( re_ied_ies(in) ) {
		in.resize(in.size()-2);
	}
	else if ( re_us_ss(in) ) {
		;	//	do nothing
	}
	else if ( re_xVxs(in) ) {
		in.resize(in.size()-1);
	}


	//	Exception 2
	if (
		in == "inning" || in == "outing" || in == "canning" || in == "herring" || in == "earring" ||
		in == "proceed" || in == "exceed" || in == "succeed"
	) {
		return in;
	}
	
// cout << setw(5) << left << __LINE__ << in << endl;
	//	Step 1b
	if ( re_eed_eedly(in, matches) ) {
		in = matches[1];
	}
	else if ( re_ed_ingly(in, matches) ) {
		in = matches[1];
// cout << setw(5) << left << __LINE__ << in << endl;
		if ( re_at_bl_iz(in) ) {
			in += "e";
		}
		else if ( re_dbl_end(in) ) {
			in.resize(in.size()-1);
		}
		else if ( re_vwxY(in) ) {
			in += "e";
		}
	}
// cout << setw(5) << left << __LINE__ << in << endl;
	//	My addition that solves some "e" endings.
	if ( in.size() == 2 ) {
		in += "e";
		toLower(in);
		return in;
	}
	else {
		switch( in.size() ) {
			case 3:
			if ( re_cvc(in) ) {
				in += "e";
			}
			case 1:
			toLower(in);
			return in;
		}
	}


	//	Step 1c
	if ( re_CyY(in) )
		in[in.size()-1] = 'i';

// cout << setw(5) << left << __LINE__ << in << endl;
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
			if ( re_anci(in) ) {
				in[in.size()-1] = 'e';
			}
			break;

			case 'g':
			if ( re_logi(in) ) {
				in.resize(in.size()-1);
			}
			break;

			case 'l':
			if ( re_bli(in) ) {
				in[in.size()-1] = 'e';
			}
			else if (re_lessli(in)) {
				in.resize(in.size()-2);
			}
			break;

			case 't':
			if ( re_biliti(in) ) {
				in.resize(in.size()-5);
				in += "le";
			}
			else if ( re_aliti(in) ) {
				in.resize(in.size()-3);
			}
			else if (re_iviti(in)) {
				in.resize(in.size()-2);
				in[in.size()-1] = 'e';
			}
			break;
		}
		break;

		case 'l':
		if ( re_ational(in) ) {
			in.resize(in.size()-4);
			in[in.size()-1] = 'e';
		}
		else if ( re_tional(in) ) {
			in.resize(in.size()-2);
		}
		break;

		case 'm':
		if ( re_alism(in) ) {
			in.resize(in.size()-3);
		}
		break;

		case 'n':
		if ( re_ization(in) ) {
			in.resize(in.size()-4);
			in[in.size()-1] = 'e';
		}
		else if ( re_ation(in) ) {
			in.resize(in.size()-2);
			in[in.size()-1] = 'e';
		}
		break;

		case 'r':
		if ( re_ator(in) ) {
			in.resize(in.size()-1);
			in[in.size()-1] = 'e';
		}
		else if ( re_izer(in) ) {
			in.resize(in.size()-1);
		}
		break;

		case 's':
		if ( re_fulness(in) ) {
			in.resize(in.size()-4);
		}
		break;
	}
// cout << setw(5) << left << __LINE__ << in << endl;

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
	if ( re_ational(in) ) {
		in.resize(in.size()-4);
		in[in.size()-1] = 'e';
	}
	else if ( re_tional(in) ) {
		in.resize(in.size()-2);
	}
	else if ( re_alize(in) ) {
		in.resize(in.size()-3);
	}
	else if ( re_icate(in, matches) ) {
		in = matches[1];
	}
	else if ( re_ful_ness(in, matches) ) {
		in = matches[1];
	}
	else if ( re_ative(in) ){
		in.resize(in.size()-5);
	}
// cout << setw(5) << left << __LINE__ << in << endl;

	//	Step 4
	if ( re_ement(in) ) {
		in.resize(in.size()-5);
	}
	else if ( re_ment(in, matches) ) {
		in.resize(in.size()-4);
	}
	else if ( re_ent(in, matches) ) {
		in.resize(in.size()-3);
	}
	else if ( re_al_er_ic(in, matches) ) {
		in = matches[1];
	}
	else if ( re_R2stion(in) ) {
		in.resize(in.size()-3);
	}
// cout << setw(5) << left << __LINE__ << in << endl;

	//	Step 5 (partial)
	if ( re_R2e(in) ) {
		in.resize(in.size()-1);
	}
	else if ( re_R2ll(in) ) {
		in.resize(in.size()-1);
	}
	

	//	postlude
	//	Change Y to y.
	toLower(in);
	
	return in;
}
