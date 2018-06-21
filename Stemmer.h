/**

Based on the Porter 2 stemmer

http://tartarus.org/martin/PorterStemmer/
http://www.tartarus.org/~martin/PorterStemmer
http://snowball.tartarus.org
*/

#ifndef DISKERROR_STEMMER_H
#define DISKERROR_STEMMER_H
#pragma once

#include "Pcre2/Substitute.h"
#include "Pcre2/Match.h"

class Stemmer
{
protected:

	//	prelude 1
	//	re_sTrim removes all control characters and spaces from both ends of a word
	//		and requires a word to have no imbedded control characters.
	const Pcre2::Substitute	re_sTrim;
	const Pcre2::Match		re_apos;

	//	step 0
	const Pcre2::Substitute	re_aposS;
	const Pcre2::Substitute	re_Sapos;

	//	over-stem
	const Pcre2::Match		re_generVC;

	//	prelude 2
// 	const Pcre2::Substitute	re_Vy;

	//	step 1a
	const Pcre2::Match		re_sses;
	const Pcre2::Match		re_ied_ies;
	const Pcre2::Match		re_us_ss;
	const Pcre2::Match		re_xVxs;

	//	step 1b
	const Pcre2::Match		re_eed_eedly;
	const Pcre2::Match		re_ed_ingly;
	const Pcre2::Match		re_at_bl_iz;
	const Pcre2::Match		re_dbl_end;
	const Pcre2::Match		re_vwxY;

	const Pcre2::Match		re_cvc;

	//	step 1c
	const Pcre2::Match		re_CyY;

	//	step 2
	const Pcre2::Match		re_anci;
	const Pcre2::Match		re_logi;
	const Pcre2::Match		re_bli;
	const Pcre2::Match		re_lessli;
	const Pcre2::Match		re_biliti;
	const Pcre2::Match		re_aliti;
	const Pcre2::Match		re_iviti;
	const Pcre2::Match		re_ational;
	const Pcre2::Match		re_tional;
	const Pcre2::Match		re_alism;
	const Pcre2::Match		re_ization;
	const Pcre2::Match		re_ation;
	const Pcre2::Match		re_ator;
	const Pcre2::Match		re_izer;
	const Pcre2::Match		re_fulness;

	//	step 3
// 	const Pcre2::Match		re_ational;	same as step 2
// 	const Pcre2::Match		re_tional;
	const Pcre2::Match		re_alize;
	const Pcre2::Match		re_icate;
	const Pcre2::Match		re_ful_ness;
	const Pcre2::Match		re_ative;

	//	step 4
	const Pcre2::Match		re_ement;
	const Pcre2::Match		re_ment;
	const Pcre2::Match		re_ent;
	const Pcre2::Match		re_al_er_ic;
	const Pcre2::Match		re_R2stion;

	//	step 5
	const Pcre2::Match		re_R2e;
	const Pcre2::Match		re_R2ll;

public:

	explicit Stemmer();
	std::string operator()(std::string in);

};

#endif	//	DISKERROR_STEMMER_H
