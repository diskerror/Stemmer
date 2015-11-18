/**

Based on the Porter 2 stemmer

http://tartarus.org/martin/PorterStemmer/
http://www.tartarus.org/~martin/PorterStemmer
http://snowball.tartarus.org
*/

#ifndef DISKERROR_STEMMER_H
#define DISKERROR_STEMMER_H
#pragma once

#include <string>
#include <regex>

class Stemmer
{
protected:

	const std::regex_constants::syntax_option_type rcOpt;

	const std::string s_R1;
// 	const std::string s_R2;

	const std::regex re_sTrim;

	//	prelude 1
	const std::regex re_apos;
	
	//	step 0
	const std::regex re_aposS;
	
	//	over-stem
	const std::regex re_generVC;
	
	//	prelude 2
	const std::regex re_Vy;
	
	//	step 1a
	const std::regex re_sses;
	const std::regex re_ied_ies;
	const std::regex re_us_ss;
	const std::regex re_xVxs;
	
	//	step 1b
	const std::regex re_eed_eedly;
	const std::regex re_ed_ingly;
	const std::regex re_at_bl_iz;
	const std::regex re_dbl_end;
	const std::regex re_VwxY;

	//	step 1c
	const std::regex re_CyY;

	//	step 2
	const std::regex re_anci;
	const std::regex re_logi;
	const std::regex re_bli;
	const std::regex re_lessli;
	const std::regex re_biliti;
	const std::regex re_aliti;
	const std::regex re_iviti;
	const std::regex re_ational;
	const std::regex re_tional;
	const std::regex re_alism;
	const std::regex re_ization;
	const std::regex re_ation;
	const std::regex re_ator;
	const std::regex re_izer;
	const std::regex re_fulness;

	//	step 3
// 	const std::regex re_ational;	same as step 2
// 	const std::regex re_tional;
	const std::regex re_alize;
	const std::regex re_icate;
	const std::regex re_ful_ness;
	const std::regex re_ative;

	//	step 4
	const std::regex re_ement;
	const std::regex re_ment;
	const std::regex re_ent;
	const std::regex re_al_er_ic;
	const std::regex re_sion_tion;
	
	//	step 5
	const std::regex re_R2e;
	const std::regex re_ll;

public:
			Stemmer();
// 			Stemmer(const Stemmer&){}
// 	void	Stemmer operator=(const Stemmer&){}
			~Stemmer();
	
	std::string	StemWord(std::string in);
	
};

#endif	//	DISKERROR_STEMMER_H
