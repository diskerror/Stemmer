/**

Based on the Porter 2 stemmer

http://tartarus.org/martin/PorterStemmer/
http://www.tartarus.org/~martin/PorterStemmer
http://snowball.tartarus.org
*/

#ifndef DISKERROR_STEMMER_H
#define DISKERROR_STEMMER_H
#pragma once

#include "Hyperscan/HasMatch.h"
#include "Hyperscan/GetMatch.h"
#include "Hyperscan/RemoveMatch.h"
#include "Hyperscan/ReplaceMatch.h"
#include <string>

class Stemmer
{
protected:

	//	Convienence strings for readability. R1 and R2 begin at the end of their regex placeholder.
	static const std::string	s_R1;
	static const std::string	s_R2;

	//	prelude 1
	//	re_sTrim removes all control characters and spaces from both ends of a word
	//		and requires a word to have no imbedded control characters.
	static const RemoveMatch	rm_lsTrim;
	static const RemoveMatch	rm_rsTrim;

	//	step 0
	static const RemoveMatch	rm_aposS;

	//	over-stem
	static const GetMatch		gm_generVC;

// 	//	prelude 2
// 	static const std::regex		re_Vy;

	//	Step_1a
// 	static const HasMatch		hm_sses;
// 	static const HasMatch		hm_ied_ies;
// 	static const HasMatch		hm_us_ss;
	static const HasMatch		hm_xVxs;

	//	step 1b
	static const HasMatch		hm_eed;
	static const HasMatch		hm_eedly;
	static const HasMatch		hm_ed_ingly;
	static const RemoveMatch	rm_ed_ingly;
	static const HasMatch		hm_at_bl_iz;
	static const HasMatch		hm_dbl_end;
	static const HasMatch		hm_vwxY;

	static const HasMatch		hm_cvc;

	//	step 1c
	static const HasMatch		hm_CyY;

	//	step 2
	static const HasMatch		hm_anci;
	static const HasMatch		hm_logi;
	static const HasMatch		hm_bli;
	static const HasMatch		hm_lessli;
	static const HasMatch		hm_biliti;
	static const HasMatch		hm_aliti;
	static const HasMatch		hm_iviti;
	static const HasMatch		hm_ational;
	static const HasMatch		hm_tional;
	static const HasMatch		hm_alism;
	static const HasMatch		hm_ization;
	static const HasMatch		hm_ation;
	static const HasMatch		hm_ator;
	static const HasMatch		hm_izer;
	static const HasMatch		hm_fulness;

	//	step 3
// 	static const HasMatch		hm_ational;
// 	static const HasMatch		hm_tional;
	static const HasMatch		hm_alize;
	static const HasMatch		hm_icate;
	static const HasMatch		hm_ical;
	static const HasMatch		hm_ful;
	static const HasMatch		hm_ness;
	static const HasMatch		hm_ative;

	//	step 4
	static const HasMatch		hm_ement;
	static const HasMatch		hm_ment;
	static const HasMatch		hm_ent;
	static const HasMatch		hm_al_er_ic;
	static const HasMatch		hm_ant_ize;
	static const HasMatch		hm_ance_ible;
	static const HasMatch		hm_R2stion;

	//	step 5
	static const HasMatch		hm_R2e;
	static const HasMatch		hm_R2ll;

public:

	static std::string StemWord(std::string in);

};

#endif	//	DISKERROR_STEMMER_H
