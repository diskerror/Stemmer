/*
http://snowball.tartarus.org
See also http://www.tartarus.org/~martin/PorterStemmer
*/

#include "Stemmer.h"

using namespace std;

//	Convienence strings for readability. R1 and R2 begin at the end of their regex placeholder.
//		Note that "cap" strings begin with a capture parenthesis.
const string	Stemmer::s_R1	("^[^aeiouy]*[aeiouy]+[^aeiouy].*");
const string	Stemmer::s_R2	("^[^aeiouy]*[aeiouy]+[^aeiouy]+[aeiouy]+[^aeiouy].*");

//	Prelude 1
//	re_sTrim removes all control characters and spaces from both ends of a word.
const RemoveMatch	Stemmer::rm_lsTrim	("^[\\x00- \\x7F'`]+");
const RemoveMatch	Stemmer::rm_rsTrim	("[\\x00- \\x7F'`]+$");

//	step 0
const RemoveMatch	Stemmer::rm_aposS	("['`]s$");

//	over-stem
const GetMatch		Stemmer::gm_generVC	("^(gener|commun|arsen)[aeiouy]+[^aeiouy]");

//	Prelude 2
// const regex			Stemmer::re_Vy	(
// 	"([aeiou])y([aeiou])",
// 	regex_constants::ECMAScript|regex_constants::optimize
// 	);	//	replace with Y

//	Step_1a
// const HasMatch		Stemmer::hm_sses	("sses$");				//	remove ending "es"
// const HasMatch		Stemmer::hm_ied_ies	("(ied|ies)$");			//	remove last 2 characters
// const HasMatch		Stemmer::hm_us_ss	("(us|ss)$");			//	leave alone
const HasMatch		Stemmer::hm_xVxs	("[aeiouy].+s$");	//	remove ending "s"

//	step 1b
const HasMatch		Stemmer::hm_eed		(s_R1 + "eed$");					//	remove ending
const HasMatch		Stemmer::hm_eedly	(s_R1 + "eedly$");					//	remove ending
const HasMatch		Stemmer::hm_ed_ingly(s_R1 + "(ed|edly|ing|ingly)$");	//	check ending
const RemoveMatch	Stemmer::rm_ed_ingly("(ed|edly|ing|ingly)$");			//	remove ending
const HasMatch		Stemmer::hm_at_bl_iz("([^aeiou]at|bl|iz)$");			//	add "e" to end
const HasMatch		Stemmer::hm_dbl_end	("..+(bb|dd|ff|gg|mm|nn|pp|rr|tt)$");	//	remove extra letter at end
const HasMatch		Stemmer::hm_vwxY	("([^aeiouywxy][aeiouy][^aeiouy]|[^aeiouy][aeiouy])$");	//	Y

const HasMatch		Stemmer::hm_cvc		("[^aeiou][aeiouy][^aeiouy]");

//	step 1c
const HasMatch		Stemmer::hm_CyY		(".[^aeiou]y$");		//	replace ending "y" with "i". (".[^aeiou][yY]$")

//	step 2
const HasMatch		Stemmer::hm_anci	(s_R1 + "[ae]nci$");	//	replace ending "nci" with "nce"
const HasMatch		Stemmer::hm_logi	(s_R1 + "logi$");		//	remove ending "i"
const HasMatch		Stemmer::hm_bli		(s_R1 + "bli$");		//	replace ending "bli" with "ble"
const HasMatch		Stemmer::hm_lessli	(s_R1 + "(?:less|ful|ous|ent|al|[cdeghkmnrt])li$");	//	remove ending "li"
const HasMatch		Stemmer::hm_biliti	(s_R1 + "biliti$");		//	replace ending "biliti" with "ble"
const HasMatch		Stemmer::hm_aliti	(s_R1 + "aliti$");		//	remove ending "iti"
const HasMatch		Stemmer::hm_iviti	(s_R1 + "iviti$");		//	replace ending "iviti" with "ive"
const HasMatch		Stemmer::hm_ational	(s_R1 + "ational$");	//	replace ending "ational" with "ate"
const HasMatch		Stemmer::hm_tional	(s_R1 + "tional$");		//	remove ending "al"
const HasMatch		Stemmer::hm_alism	(s_R1 + "alism$");		//	remove ending "ism"
const HasMatch		Stemmer::hm_ization	(s_R1 + "ization$");	//	replace ending "ization" with "ize"
const HasMatch		Stemmer::hm_ation	(s_R1 + "ation$");		//	replace ending "ation" with "ate"
const HasMatch		Stemmer::hm_ator	(s_R1 + "ator$");		//	replace ending "ator" with "ate"
const HasMatch		Stemmer::hm_izer	(s_R1 + "izer$");		//	remove ending "r"
const HasMatch		Stemmer::hm_fulness	(s_R1 + "(?:ful|ous|ive)ness$");	//	remove ending "ness"

//	step 3
// const HasMatch		Stemmer::hm_ational	(s_R1 + "ational$");
// const HasMatch		Stemmer::hm_tional	(s_R1 + "tional$");
const HasMatch		Stemmer::hm_alize	(s_R1 + "alize$");			//	remove ending "ize"
const HasMatch		Stemmer::hm_icate	(s_R1 + "ic(ate|iti)$");	//	remove ending (3)
const HasMatch		Stemmer::hm_ical	(s_R1 + "ical$");			//	remove 2
const HasMatch		Stemmer::hm_ful		(s_R1 + "ful$");			//	remove ending (3)
const HasMatch		Stemmer::hm_ness	(s_R1 + "ness$");			//	remove ending
const HasMatch		Stemmer::hm_ative	(s_R2 + "ative$");			//	remove ending "ative"

// //	step 4
// const Match		Stemmer::re_ement	(s_R1 + "ement$");		//	remove ending "ement"
// const Match		Stemmer::re_ment	(s_R1 + "ment$");		//	remove ending "ment"
// const Match		Stemmer::re_ent		(s_R1 + "ent$");		//	remove ending "ent"
// const Match		Stemmer::re_al_er_ic(s_R2 + "(?:al|ance|ence|er|ic|able|abli|ible|ant|ism|ate|iti|ous|ive|ize)$");
// const Match		Stemmer::re_R2stion	(s_R2 + "[st]ion$");	//	remove ending "ion"
//
// //	step 5
// const Match		Stemmer::re_R2e		("(" + s_R2 + "|" + s_R1 + "(?![^aeiouywxY][aeiouy][^aeiouy]))e$");		//	remove ending "e"
// const Match		Stemmer::re_R2ll	(s_R2 + "ll$");		//	remove ending "l"

// yellow
// sky
// beyond
