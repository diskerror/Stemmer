/**

Based on the Porter 2 stemmer

http://tartarus.org/martin/PorterStemmer/
http://www.tartarus.org/~martin/PorterStemmer
http://snowball.tartarus.org
*/

#ifndef DISKERROR_STEMMER_H
#define DISKERROR_STEMMER_H
#pragma once

#include <regex>
#include <string>

class Stemmer
{
protected:

	static const std::regex_constants::syntax_option_type rc_opt;

	static const std::string s_R1;
// 	static const std::string s_R2;

	static const std::regex re_sTrim;

	//	prelude 1
	static const std::regex re_apos;
	
	//	step 0
	static const std::regex re_aposS;
	static const std::regex re_Sapos;
	
	//	over-stem
	static const std::regex re_generVC;
	
	//	prelude 2
	static const std::regex re_Vy;
	
	//	step 1a
	static const std::regex re_sses;
	static const std::regex re_ied_ies;
	static const std::regex re_us_ss;
	static const std::regex re_xVxs;
	
	//	step 1b
	static const std::regex re_eed_eedly;
	static const std::regex re_ed_ingly;
	static const std::regex re_at_bl_iz;
	static const std::regex re_dbl_end;
	static const std::regex re_VwxY;

	//	step 1c
	static const std::regex re_CyY;

	//	step 2
	static const std::regex re_anci;
	static const std::regex re_logi;
	static const std::regex re_bli;
	static const std::regex re_lessli;
	static const std::regex re_biliti;
	static const std::regex re_aliti;
	static const std::regex re_iviti;
	static const std::regex re_ational;
	static const std::regex re_tional;
	static const std::regex re_alism;
	static const std::regex re_ization;
	static const std::regex re_ation;
	static const std::regex re_ator;
	static const std::regex re_izer;
	static const std::regex re_fulness;

	//	step 3
// 	static const std::regex re_ational;	same as step 2
// 	static const std::regex re_tional;
	static const std::regex re_alize;
	static const std::regex re_icate;
	static const std::regex re_ful_ness;
	static const std::regex re_ative;

	//	step 4
	static const std::regex re_ement;
	static const std::regex re_ment;
	static const std::regex re_ent;
	static const std::regex re_al_er_ic;
	static const std::regex re_sion_tion;
	
	//	step 5
	static const std::regex re_R2e;
	static const std::regex re_ll;

public:
	
	static std::string StemWord(std::string in);
	
};

#endif	//	DISKERROR_STEMMER_H
