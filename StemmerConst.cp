/*
http://snowball.tartarus.org
See also http://www.tartarus.org/~martin/PorterStemmer
*/

#include "Stemmer.h"

using namespace std;
using namespace Pcre2;

//	Convienence strings for readability. R1 and R2 begin at the end of their regex placeholder.
//		Note that "cap" strings begin with a capture parenthesis.
#define S_R1	"^[^aeiouy]*[aeiouy]+[^aeiouy].*"
#define S_R1cap	"^([^aeiouy]*[aeiouy]+[^aeiouy].*"
#define S_R2	"^[^aeiouy]*[aeiouy]+[^aeiouy]+[aeiouy]+[^aeiouy].*"
#define S_R2cap	"^([^aeiouy]*[aeiouy]+[^aeiouy]+[aeiouy]+[^aeiouy].*"

Stemmer::Stemmer() :
	//	Prelude 1
	//	re_sTrim removes all control characters and spaces from both ends of a word
	//		and requires a word to have no imbedded control characters.
	re_sTrim	("^[\\x00- \\x7F]*([^\\x00-\\x1F\\x7F]+)[\\x00- \\x7F]*$",	"$1"),

	//	step 0
	//	Must have apostrophy on both sides.
	re_apos	("^(['`]?)(.+?)\\1$"),

	re_aposS	("['`]s['`]?$",				""),
	re_Sapos	("^([^'`]+[s'`])['`]+$",	"$1"),

	//	over-stem
	re_generVC	("^((?:gener|commun|arsen)[aeiouy]+[^aeiouy]).*$"),

	//	Prelude 2
// 	re_Vy		("(?<=[aeiou])y(?=[aeiou])",	"Y"),	//	"Substitute" is global

	//	Step_1a
	re_sses		("sses$"),				//	remove ending "es"
	re_ied_ies	("^..+(?:ied|ies)$"),	//	remove last 2 characters
	re_us_ss	("^.+(?:us|ss)$"),
	re_xVxs		("^.*[aeiouy].+s$"),	//	remove ending "s"

	//	step 1b
	re_eed_eedly(S_R1cap "ee)(?:d|dly)$"),				//	remove ending
	re_ed_ingly	(S_R1cap ")(?:ed|edly|ing|ingly)$"),	//	remove ending
	re_at_bl_iz	("(?:[^aeiou]at|bl|iz)$"),				//	add "e" to end
	re_dbl_end	("^..+([bdfgmnprt])\\1$"),				//	remove extra letter at end
	re_vwxY		("(?:[^aeiouywxy][aeiouy][^aeiouy]|[^aeiouy][aeiouy])$"),	//	Y

	re_cvc		("[^aeiou][aeiouy][^aeiouy]"),

	//	step 1c
	re_CyY		(".[^aeiou]y$"),	//	replace ending "y" with "i". (".[^aeiou][yY]$")

	//	step 2
	re_anci		(S_R1 "[ae]nci$"),	//	replace ending "nci" with "nce"
	re_logi		(S_R1 "logi$"),		//	remove ending "i"
	re_bli		(S_R1 "bli$"),		//	replace ending "bli" with "ble"
	re_lessli	(S_R1 "(?:less|ful|ous|ent|al|[cdeghkmnrt])li$"),	//	remove ending "li"
	re_biliti	(S_R1 "biliti$"),	//	replace ending "biliti" with "ble"
	re_aliti	(S_R1 "aliti$"),	//	remove ending "iti"
	re_iviti	(S_R1 "iviti$"),	//	replace ending "iviti" with "ive"
	re_ational	(S_R1 "ational$"),	//	replace ending "ational" with "ate"
	re_tional	(S_R1 "tional$"),	//	remove ending "al"
	re_alism	(S_R1 "alism$"),	//	remove ending "ism"
	re_ization	(S_R1 "ization$"),	//	replace ending "ization" with "ize"
	re_ation	(S_R1 "ation$"),	//	replace ending "ation" with "ate"
	re_ator		(S_R1 "ator$"),		//	replace ending "ator" with "ate"
	re_izer		(S_R1 "izer$"),		//	remove ending "r"
	re_fulness	(S_R1 "(?:ful|ous|ive)ness$"),	//	remove ending "ness"

	//	step 3
	// re_ational(S_R1cap ")ational$"),
	// re_tional	(S_R1cap ")tional$"),
	re_alize	(S_R1 "alize$"),				//	remove ending "ize"
	re_icate	(S_R1cap "ic)(?:ate|iti|al)$"),	//	remove ending
	re_ful_ness	(S_R1cap ")(?:ful|ness)$"),		//	remove ending
	re_ative	(S_R2 "ative$"),				//	remove ending "ative"

	//	step 4
	re_ement	(S_R1 "ement$"),	//	remove ending "ement"
	re_ment	(S_R1 "ment$"),			//	remove ending "ment"
	re_ent		(S_R1 "ent$"),		//	remove ending "ent"
	re_al_er_ic(S_R2cap ")(?:al|ance|ence|er|ic|able|abli|ible|ant|ism|ate|iti|ous|ive|ize)$"),
	re_R2stion	(S_R2 "[st]ion$"),	//	remove ending "ion"

	//	step 5
	re_R2e		("(" S_R2 "|" S_R1 "(?![^aeiouywxY][aeiouy][^aeiouy]))e$"),		//	remove ending "e"
	re_R2ll	(S_R2 "ll$")		//	remove ending "l"

{
}

// yellow
// sky
// beyond
