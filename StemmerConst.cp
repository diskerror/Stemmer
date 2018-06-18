/*
http://snowball.tartarus.org
See also http://www.tartarus.org/~martin/PorterStemmer
*/

#include "Stemmer.h"

using namespace std;

//	Convienence strings for readability. R1 and R2 begin at the end of their regex placeholder.
#define S_R1	"^[^aeiouy]*[aeiouy]+[^aeiouy].*"
#define S_R2	"^[^aeiouy]*[aeiouy]+[^aeiouy]+[aeiouy]+[^aeiouy].*"

Stemmer::Stemmer() :
	//	Prelude 1
	//	re_sTrim removes all control characters and spaces from both ends of a word.
	rm_lsTrim	("^[\\x00- \\x7F'`]+"),
	rm_rsTrim	("[\\x00- \\x7F'`]+$"),

	//	step 0
	rm_aposS	("['`]s$"),

	//	over-stem
	gm_generVC	("^(gener|commun|arsen)[aeiouy]+[^aeiouy]"),

	//	Prelude 2
// 	const regex			Stemmer::re_Vy	(
// 		"([aeiou])y([aeiou])",
// 		regex_constants::ECMAScript|regex_constants::optimize
// 		);	//	replace with Y

	//	Step_1a
// 	hm_sses	("sses$"),				//	remove ending "es"
// 	hm_ied_ies	("(ied|ies)$"),		//	remove last 2 characters
// 	hm_us_ss	("(us|ss)$"),		//	leave alone
	hm_xVxs		("[aeiouy].+s$"),	//	remove ending "s"

	//	step 1b
	hm_eed		(S_R1 "eed$"),							//	remove ending
	hm_eedly	(S_R1 "eedly$"),						//	remove ending
	hm_ed_ingly	(S_R1 "(ed|edly|ing|ingly)$"),			//	check ending
	rm_ed_ingly	("(ed|edly|ing|ingly)$"),				//	remove ending
	hm_at_bl_iz	("([^aeiou]at|bl|iz)$"),				//	add "e" to end
	hm_dbl_end	("..+(bb|dd|ff|gg|mm|nn|pp|rr|tt)$"),	//	remove extra letter at end
	hm_vwxY		("([^aeiouywxy][aeiouy][^aeiouy]|[^aeiouy][aeiouy])$"),	//	Y

	hm_cvc		("[^aeiou][aeiouy][^aeiouy]"),

	//	step 1c
	hm_CyY		(".[^aeiou]y$"),	//	replace ending "y" with "i". (".[^aeiou][yY]$")

	//	step 2
	hm_anci		(S_R1 "[ae]nci$"),			//	replace ending "nci" with "nce"
	hm_logi		(S_R1 "logi$"),				//	remove ending "i"
	hm_bli		(S_R1 "bli$"),				//	replace ending "bli" with "ble"
	hm_lessli	(S_R1 "(less|ful|ous|ent|al|[cdeghkmnrt])li$"),	//	remove ending "li"
	hm_biliti	(S_R1 "biliti$"),			//	replace ending "biliti" with "ble"
	hm_aliti	(S_R1 "aliti$"),			//	remove ending "iti"
	hm_iviti	(S_R1 "iviti$"),			//	replace ending "iviti" with "ive"
	hm_ational	(S_R1 "ational$"),			//	replace ending "ational" with "ate"
	hm_tional	(S_R1 "tional$"),			//	remove ending "al"
	hm_alism	(S_R1 "alism$"),			//	remove ending "ism"
	hm_ization	(S_R1 "ization$"),			//	replace ending "ization" with "ize"
	hm_ation	(S_R1 "ation$"),			//	replace ending "ation" with "ate"
	hm_ator		(S_R1 "ator$"),				//	replace ending "ator" with "ate"
	hm_izer		(S_R1 "izer$"),				//	remove ending "r"
	hm_fulness	(S_R1 "(ful|ous|ive)ness$"),//	remove ending "ness"

	//	step 3
// 	hm_ational	(S_R1 "ational$"),
// 	hm_tional	(S_R1 "tional$"),
	hm_alize	(S_R1 "alize$"),		//	remove ending "ize"
	hm_icate	(S_R1 "ic(ate|iti)$"),	//	remove ending (3)
	hm_ical		(S_R1 "ical$"),			//	remove 2
	hm_ful		(S_R1 "ful$"),			//	remove ending (3)
	hm_ness		(S_R1 "ness$"),			//	remove ending
	hm_ative	(S_R2 "ative$"),		//	remove ending "ative"

	//	step 4
	hm_ement	(S_R1 "ement$"),	//	remove ending "ement"
	hm_ment		(S_R1 "ment$"),		//	remove ending "ment"
	hm_ent		(S_R1 "ent$"),		//	remove ending "ent"
	hm_al_er_ic	(S_R2 "(al|er|ic)$"),
	hm_ant_ize	(S_R2 "(ant|ism|ate|iti|ous|ive|ize)$"),
	hm_ance_ible(S_R2 "(ance|ence|able|abli|ible)$"),
	hm_R2stion	(S_R2 "[st]ion$"),	//	remove ending "ion"

	//	step 5
	hm_R2e	("(" S_R2 "|" S_R1 "[aeiouywxY][^aeiouy][aeiouy])e$"),		//	remove ending "e"
	hm_R2ll	(S_R2 "ll$")		//	remove ending "l"

{
}

// yellow
// sky
// beyond
