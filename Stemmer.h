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
// #include "Hyperscan/ReplaceMatch.h"
#include <string>

class Stemmer
{
protected:

	//	prelude 1
	//	re_sTrim removes all control characters and spaces from both ends of a word
	const RemoveMatch	rm_lsTrim;
	const RemoveMatch	rm_rsTrim;

	//	step 0
	const RemoveMatch	rm_aposS;

	//	over-stem
	const GetMatch		gm_generVC;

// 	//	prelude 2
// 	const std::regex		re_Vy;

	//	Step_1a
// 	const HasMatch		hm_sses;
// 	const HasMatch		hm_ied_ies;
// 	const HasMatch		hm_us_ss;
	const HasMatch		hm_xVxs;

	//	step 1b
	const HasMatch		hm_eed;
	const HasMatch		hm_eedly;
	const HasMatch		hm_ed_ingly;
	const RemoveMatch	rm_ed_ingly;
	const HasMatch		hm_at_bl_iz;
	const HasMatch		hm_dbl_end;
	const HasMatch		hm_vwxY;

	const HasMatch		hm_cvc;

	//	step 1c
	const HasMatch		hm_CyY;

	//	step 2
	const HasMatch		hm_anci;
	const HasMatch		hm_logi;
	const HasMatch		hm_bli;
	const HasMatch		hm_lessli;
	const HasMatch		hm_biliti;
	const HasMatch		hm_aliti;
	const HasMatch		hm_iviti;
	const HasMatch		hm_ational;
	const HasMatch		hm_tional;
	const HasMatch		hm_alism;
	const HasMatch		hm_ization;
	const HasMatch		hm_ation;
	const HasMatch		hm_ator;
	const HasMatch		hm_izer;
	const HasMatch		hm_fulness;

	//	step 3
// 	const HasMatch		hm_ational;
// 	const HasMatch		hm_tional;
	const HasMatch		hm_alize;
	const HasMatch		hm_icate;
	const HasMatch		hm_ical;
	const HasMatch		hm_ful;
	const HasMatch		hm_ness;
	const HasMatch		hm_ative;

	//	step 4
	const HasMatch		hm_ement;
	const HasMatch		hm_ment;
	const HasMatch		hm_ent;
	const HasMatch		hm_al_er_ic;
	const HasMatch		hm_ant_ize;
	const HasMatch		hm_ance_ible;
	const HasMatch		hm_R2stion;

	//	step 5
	const HasMatch		hm_R2e;
	const HasMatch		hm_R2ll;

public:

	explicit Stemmer();
	std::string operator()(std::string in);

};

#endif	//	DISKERROR_STEMMER_H
