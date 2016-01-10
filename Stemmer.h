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
#include <string>

class Stemmer
{
protected:

	static const std::string s_R1cap;
	static const std::string s_R1;
	static const std::string s_R2cap;
	static const std::string s_R2;

	static const Pcre2::Substitute	re_sTrim;

	//	prelude 1
	static const Pcre2::Match		re_apos;
	
	//	step 0
	static const Pcre2::Substitute	re_aposS;
	static const Pcre2::Substitute	re_Sapos;
	
	//	over-stem
	static const Pcre2::Match		re_generVC;
	
	//	prelude 2
	static const Pcre2::Substitute	re_Vy;
	
	//	step 1a
	static const Pcre2::Match		re_sses;
	static const Pcre2::Match		re_ied_ies;
	static const Pcre2::Match		re_us_ss;
	static const Pcre2::Match		re_xVxs;
	
	//	step 1b
	static const Pcre2::Match		re_eed_eedly;
	static const Pcre2::Match		re_ed_ingly;
	static const Pcre2::Match		re_at_bl_iz;
	static const Pcre2::Match		re_dbl_end;
	static const Pcre2::Match		re_vwxY;

	static const Pcre2::Match		re_cvc;

	//	step 1c
	static const Pcre2::Match		re_CyY;

	//	step 2
	static const Pcre2::Match		re_anci;
	static const Pcre2::Match		re_logi;
	static const Pcre2::Match		re_bli;
	static const Pcre2::Match		re_lessli;
	static const Pcre2::Match		re_biliti;
	static const Pcre2::Match		re_aliti;
	static const Pcre2::Match		re_iviti;
	static const Pcre2::Match		re_ational;
	static const Pcre2::Match		re_tional;
	static const Pcre2::Match		re_alism;
	static const Pcre2::Match		re_ization;
	static const Pcre2::Match		re_ation;
	static const Pcre2::Match		re_ator;
	static const Pcre2::Match		re_izer;
	static const Pcre2::Match		re_fulness;

	//	step 3
// 	static const Pcre2::Match		re_ational;	same as step 2
// 	static const Pcre2::Match		re_tional;
	static const Pcre2::Match		re_alize;
	static const Pcre2::Match		re_icate;
	static const Pcre2::Match		re_ful_ness;
	static const Pcre2::Match		re_ative;

	//	step 4
	static const Pcre2::Match		re_ement;
	static const Pcre2::Match		re_ment;
	static const Pcre2::Match		re_ent;
	static const Pcre2::Match		re_al_er_ic;
	static const Pcre2::Match		re_R2stion;
	
	//	step 5
	static const Pcre2::Match		re_R2e;
	static const Pcre2::Match		re_R2ll;

public:
	
	static std::string StemWord(std::string in);
	
};

#endif	//	DISKERROR_STEMMER_H
