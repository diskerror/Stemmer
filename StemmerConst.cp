/*
http://snowball.tartarus.org
See also http://www.tartarus.org/~martin/PorterStemmer
*/

#include "Stemmer.h"

using namespace std;
using namespace Pcre2;

//	shortv ==

//	Convienence strings for readability. R1 and R2 begin at the end of their regex placeholder.
//		Note that "cap" strings begin with a capture parenthesis.
const string		Stemmer::s_R1cap	("^([^aeiouy]*[aeiouy]+[^aeiouy].*");
const string		Stemmer::s_R1		("^[^aeiouy]*[aeiouy]+[^aeiouy].*");
const string		Stemmer::s_R2cap	("^([^aeiouy]*[aeiouy]+[^aeiouy]+[aeiouy]+[^aeiouy].*");
const string		Stemmer::s_R2		("^[^aeiouy]*[aeiouy]+[^aeiouy]+[aeiouy]+[^aeiouy].*");

//	re_sTrim removes all control characters and spaces from both ends of a word
//		and requires a word to have no imbedded control characters.
const Substitute	Stemmer::re_sTrim	("^[\\x00- \\x7F]*([^\\x00-\\x1F\\x7F]+)[\\x00- \\x7F]*$",	"$1");

//	Must have apostrophy on both sides.
const Match			Stemmer::re_apos	("^(['`]?)(.+?)\\1$");

const Substitute	Stemmer::re_aposS	("['`]s['`]?$",				"");
const Substitute	Stemmer::re_Sapos	("^([^'`]+[s'`])['`]+$",	"$1");

//	over-stem
const Match			Stemmer::re_generVC	("^((?:gener|commun|arsen)[aeiouy]+[^aeiouy]).*$");

//	Prelude 2
const Substitute	Stemmer::re_Vy		("(?<=[aeiou])y(?=[aeiou])",	"Y");	//	"Substitute" is global

//	Step_1a
const Match		Stemmer::re_sses	("sses$");				//	remove ending "es"
const Match		Stemmer::re_ied_ies	("^..+(?:ied|ies)$");	//	remove last 2 characters
const Match		Stemmer::re_us_ss	("^.+(?:us|ss)$");
const Match		Stemmer::re_xVxs	("^.*[aeiouy].+s$");	//	remove ending "s"

//	step 1b
const Match		Stemmer::re_eed_eedly(s_R1cap + "ee)(?:d|dly)$");			//	remove ending
const Match		Stemmer::re_ed_ingly(s_R1cap + ")(?:ed|edly|ing|ingly)$");	//	remove ending
const Match		Stemmer::re_at_bl_iz("(?:[^aeiou]at|bl|iz)$");				//	add "e" to end
const Match		Stemmer::re_dbl_end	("^..+([bdfgmnprt])\\1$");				//	remove extra letter at end
const Match		Stemmer::re_vwxY	("(?:[^aeiouywxy][aeiouy][^aeiouy]|[^aeiouy][aeiouy])$");	//	Y

const Match		Stemmer::re_cvc		("[^aeiou][aeiouy][^aeiouy]");

//	step 1c
const Match		Stemmer::re_CyY		(".[^aeiou]y$");		//	replace ending "y" with "i". (".[^aeiou][yY]$")

//	step 2
const Match		Stemmer::re_anci	(s_R1 + "[ae]nci$");	//	replace ending "nci" with "nce"
const Match		Stemmer::re_logi	(s_R1 + "logi$");		//	remove ending "i"
const Match		Stemmer::re_bli		(s_R1 + "bli$");		//	replace ending "bli" with "ble"
const Match		Stemmer::re_lessli	(s_R1 + "(?:less|ful|ous|ent|al|[cdeghkmnrt])li$");	//	remove ending "li"
const Match		Stemmer::re_biliti	(s_R1 + "biliti$");		//	replace ending "biliti" with "ble"
const Match		Stemmer::re_aliti	(s_R1 + "aliti$");		//	remove ending "iti"
const Match		Stemmer::re_iviti	(s_R1 + "iviti$");		//	replace ending "iviti" with "ive"
const Match		Stemmer::re_ational	(s_R1 + "ational$");	//	replace ending "ational" with "ate"
const Match		Stemmer::re_tional	(s_R1 + "tional$");		//	remove ending "al"
const Match		Stemmer::re_alism	(s_R1 + "alism$");		//	remove ending "ism"
const Match		Stemmer::re_ization	(s_R1 + "ization$");	//	replace ending "ization" with "ize"
const Match		Stemmer::re_ation	(s_R1 + "ation$");		//	replace ending "ation" with "ate"
const Match		Stemmer::re_ator	(s_R1 + "ator$");		//	replace ending "ator" with "ate"
const Match		Stemmer::re_izer	(s_R1 + "izer$");		//	remove ending "r"
const Match		Stemmer::re_fulness	(s_R1 + "(?:ful|ous|ive)ness$");	//	remove ending "ness"

//	step 3
// const Match		Stemmer::re_ational(s_R1cap + ")ational$");
// const Match		Stemmer::re_tional	(s_R1cap + ")tional$");
const Match		Stemmer::re_alize	(s_R1 + "alize$");					//	remove ending "ize"
const Match		Stemmer::re_icate	(s_R1cap + "ic)(?:ate|iti|al)$");	//	remove ending
const Match		Stemmer::re_ful_ness(s_R1cap + ")(?:ful|ness)$");		//	remove ending
const Match		Stemmer::re_ative	(s_R2 + "ative$");					//	remove ending "ative"

//	step 4
const Match		Stemmer::re_ement	(s_R1 + "ement$");		//	remove ending "ement"
const Match		Stemmer::re_ment	(s_R1 + "ment$");		//	remove ending "ment"
const Match		Stemmer::re_ent		(s_R1 + "ent$");		//	remove ending "ent"
const Match		Stemmer::re_al_er_ic(s_R2cap + ")(?:al|ance|ence|er|ic|able|abli|ible|ant|ism|ate|iti|ous|ive|ize)$");
const Match		Stemmer::re_R2stion	(s_R2 + "[st]ion$");	//	remove ending "ion"

//	step 5
const Match		Stemmer::re_R2e		("(" + s_R2 + "|" + s_R1 + "(?![^aeiouywxY][aeiouy][^aeiouy]))e$");		//	remove ending "e"
const Match		Stemmer::re_R2ll	(s_R2 + "ll$");		//	remove ending "l"

// yellow
// sky
// beyond
