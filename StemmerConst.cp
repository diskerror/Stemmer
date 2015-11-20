/*
	http://snowball.tartarus.org
	See also http://www.tartarus.org/~martin/PorterStemmer
*/

#include "Stemmer.h"

using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////
const regex_constants::syntax_option_type Stemmer::rc_opt =
	regex_constants::syntax_option_type( regex_constants::ECMAScript /*| regex_constants::optimize*/ );
	
const string Stemmer::s_R1	= string("^([^aeiouy]*[aeiouy]+[^aeiouy].*");

// const string Stemmer::s_R2	= string("^([^aeiouy]*[aeiouy]+[^aeiouy]+[aeiouy]+[^aeiouy].*");
	//	re_sTrim removes all control characters and spaces from both ends of a word
	//		and requires a word to have no imbedded control characters.
const regex Stemmer::re_sTrim	= regex("^[\\x00- \\x7F]*([^\\x00-\\x1F\\x7F]+)[\\x00- \\x7F]*$", rc_opt);

//	Must have apostrophy on both sides.
const regex Stemmer::re_apos	= regex("^(['`]?)(.+?)\\1$", rc_opt);
const regex Stemmer::re_aposS	= regex("['`]s['`]?$", rc_opt);
const regex Stemmer::re_Sapos	= regex("^([^'`]+[s'`])['`]+$", rc_opt);

	//	over-stem
const regex Stemmer::re_generVC	= regex("^((?:gener|commun|arsen)[aeiouy]+[^aeiouy]).*$", rc_opt);

	//	Prelude 2
const regex Stemmer::re_Vy	= regex("([aeiou])y", rc_opt);

	//	Step_1a
const regex Stemmer::re_sses	= regex("^(.*)sses$", rc_opt);
const regex Stemmer::re_ied_ies	= regex("^(..+)(?:ied|ies)$", rc_opt);
const regex Stemmer::re_us_ss	= regex("^.+(?:us|ss)$", rc_opt);
const regex Stemmer::re_xVxs	= regex("^(.*[aeiouy].+)s$", rc_opt);

	//	step 1b
const regex Stemmer::re_eed_eedly	= regex(s_R1 + "ee)(?:d|dly)$", rc_opt);
const regex Stemmer::re_ed_ingly	= regex(s_R1 + ")(?:ed|edly|ing|ingly)$", rc_opt);
const regex Stemmer::re_at_bl_iz	= regex("(?:at|bl|iz)$", rc_opt);
const regex Stemmer::re_dbl_end		= regex("^(..+([bdfgmnprt]))\\2$", rc_opt);
const regex Stemmer::re_VwxY =
	regex("(^.*(?:[^aeiouywxY]+[aeiouy][^aeiouywxY]|^[^aeiouy]+[aeiouy][^aeiouy]))$", rc_opt);

	//	step 1c
const regex Stemmer::re_CyY		= regex("(.[^aeiou])[yY]$", rc_opt);

	//	step 2
const regex Stemmer::re_anci	= regex(s_R1 + "[ae]nc)i$", rc_opt);
const regex Stemmer::re_logi	= regex("^([^aeiouy]*[aeiouy]+.*log)i$", rc_opt);
const regex Stemmer::re_bli		= regex("^([^aeiouy]*[aeiouy]+.*bl)i$", rc_opt);
const regex Stemmer::re_lessli =
	regex("^([^aeiouy]*[aeiouy]+.*(?:less|ful|[^aeiouy]ous|[^aeiouy]ent|[^aeiouy]al|[cdeghkmnrt]))li$", rc_opt);
const regex Stemmer::re_biliti	= regex(s_R1 + ")biliti$", rc_opt);
const regex Stemmer::re_aliti	= regex(s_R1 + ")aliti$", rc_opt);
const regex Stemmer::re_iviti	= regex(s_R1 + ")iviti$", rc_opt);
const regex Stemmer::re_ational	= regex(s_R1 + ")ational$", rc_opt);
const regex Stemmer::re_tional	= regex(s_R1 + ")tional$", rc_opt);
const regex Stemmer::re_alism	= regex(s_R1 + ")alism$", rc_opt);
const regex Stemmer::re_ization	= regex(s_R1 + ")ization$", rc_opt);
const regex Stemmer::re_ation	= regex(s_R1 + ")ation$", rc_opt);
const regex Stemmer::re_ator	= regex(s_R1 + "at)or$", rc_opt);
const regex Stemmer::re_izer	= regex(s_R1 + "iz)er$", rc_opt);
const regex Stemmer::re_fulness	= regex(s_R1 + "(?:ful|ous|ive))ness$", rc_opt);

	//	step 3
// const regex Stemmer::re_ational	= regex("^([^aeiouy]*[aeiouy]+[^aeiouy].*)ational$", rc_opt);
// const regex Stemmer::re_tional	= regex("^([^aeiouy]*[aeiouy]+[^aeiouy].*)tional$", rc_opt);
const regex Stemmer::re_alize	= regex("^([^aeiouy]*[aeiouy]+[^aeiouy].*al)ize$", rc_opt);
const regex Stemmer::re_icate	= regex("^([^aeiouy]*[aeiouy]+[^aeiouy].*ic)(?:ate|iti|al)$", rc_opt);
const regex Stemmer::re_ful_ness = regex("^([^aeiouy]*[aeiouy]+[^aeiouy].*)(?:ful|ness)$", rc_opt);
const regex Stemmer::re_ative	= regex("^([^aeiouy]*[aeiouy]+[^aeiouy]+[aeiouy]+[^aeiouy].*)ative$", rc_opt);

	//	step 4
const regex Stemmer::re_ement	= regex("^([^aeiouy]*[aeiouy]+[^aeiouy]+[aeiouy]+[^aeiouy].*)ement$", rc_opt);
const regex Stemmer::re_ment	= regex("^([^aeiouy]*[aeiouy]+[^aeiouy]+[aeiouy]+[^aeiouy].*)ment$", rc_opt);
const regex Stemmer::re_ent		= regex("^([^aeiouy]*[aeiouy]+[^aeiouy]+[aeiouy]+[^aeiouy].*)ent$", rc_opt);
const regex Stemmer::re_al_er_ic =
	regex("^([^aeiouy]*[aeiouy]+[^aeiouy]+[aeiouy]+[^aeiouy].*)(?:al|ance|ence|er|ic|able|abli|ible|ant|ism|ate|iti|ous|ive|ize)$", rc_opt);
const regex Stemmer::re_sion_tion	= regex("^([^aeiouy]*[aeiouy]+[^aeiouy]+[aeiouy]+[^aeiouy].*(?:s|t))ion$", rc_opt);

	//	step 5
const regex Stemmer::re_R2e	= regex("^([^aeiouy]*[aeiouy]+[^aeiouy]+[aeiouy]+[^aeiouy].*)e$", rc_opt);
const regex Stemmer::re_ll	= regex("^([^aeiouy]*[aeiouy]+[^aeiouy]+[aeiouy]+[^aeiouy].*l)l$", rc_opt);
