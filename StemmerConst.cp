/*
http://snowball.tartarus.org
See also http://www.tartarus.org/~martin/PorterStemmer
*/

#include "Stemmer.h"

using namespace std;
using namespace Pcre2;


//	Convienence strings for readability. R1 and R2 begin at the end of their regex placeholder.
//		Note that both strings begin with a capture parenthesis.
const string		Stemmer::s_R1		("^([^aeiouy]*[aeiouy]+[^aeiouy].*");
const string		Stemmer::s_R2		("^([^aeiouy]*[aeiouy]+[^aeiouy]+[aeiouy]+[^aeiouy].*");

//	re_sTrim removes all control characters and spaces from both ends of a word
//		and requires a word to have no imbedded control characters.
const Substitute	Stemmer::re_sTrim	("^[\\x00- \\x7F]*([^\\x00-\\x1F\\x7F]+)[\\x00- \\x7F]*$",	"$1");

//	Must have apostrophy on both sides.
const Substitute	Stemmer::re_apos	("^(['`]?)(.+?)\\1$",		"$2");
const Substitute	Stemmer::re_aposS	("['`]s['`]?$",				"");
const Substitute	Stemmer::re_Sapos	("^([^'`]+[s'`])['`]+$",	"$1");

//	over-stem
const Match			Stemmer::re_generVC	("^((?:gener|commun|arsen)[aeiouy]+[^aeiouy]).*$");

//	Prelude 2
const Substitute	Stemmer::re_Vy		("([aeiou])y",	"$1Y");

//	Step_1a
const Match			Stemmer::re_sses	("^(.*)sses$");
const Match			Stemmer::re_ied_ies	("^(..+)(?:ied|ies)$");
const Match			Stemmer::re_us_ss	("^.+(?:us|ss)$");
const Match			Stemmer::re_xVxs	("^(.*[aeiouy].+)s$");

//	step 1b
const Match			Stemmer::re_eed_eedly(s_R1 + "ee)(?:d|dly)$");
const Match			Stemmer::re_ed_ingly(s_R1 + ")(?:ed|edly|ing|ingly)$");
const Match			Stemmer::re_at_bl_iz("(?:at|bl|iz)$");
const Match			Stemmer::re_dbl_end	("^(..+([bdfgmnprt]))\\2$");
const Match			Stemmer::re_vwxY	("(^.*(?:[^aeiouywxY]+[aeiouy][^aeiouywxY]|^[^aeiouy]+[aeiouy][^aeiouy]))$");

//	step 1c
const Substitute	Stemmer::re_CyY		("(.[^aeiou])[yY]$",	"$1i");

//	step 2
const Substitute	Stemmer::re_anci	(s_R1 + "[ae]nc)i$",	"$1e");
const Substitute	Stemmer::re_logi	("^([^aeiouy]*[aeiouy]+.*log)i$",	"$1");
const Match			Stemmer::re_bli		("^([^aeiouy]*[aeiouy]+.*bl)i$");
const Substitute	Stemmer::re_lessli
	("^([^aeiouy]*[aeiouy]+.*(?:less|ful|[^aeiouy]ous|[^aeiouy]ent|[^aeiouy]al|[cdeghkmnrt]))li$",	"$1");
const Match			Stemmer::re_biliti	(s_R1 + ")biliti$");
const Match			Stemmer::re_aliti	(s_R1 + ")aliti$");
const Substitute	Stemmer::re_iviti	(s_R1 + ")iviti$",		"$1ive");
const Match			Stemmer::re_ational	(s_R1 + ")ational$");
const Substitute	Stemmer::re_tional	(s_R1 + ")tional$",		"$1tion");
const Substitute	Stemmer::re_alism	(s_R1 + ")alism$",		"$1al");
const Match			Stemmer::re_ization	(s_R1 + ")ization$");
const Substitute	Stemmer::re_ation	(s_R1 + ")ation$",		"$1ate");
const Match			Stemmer::re_ator	(s_R1 + "at)or$");
const Substitute	Stemmer::re_izer	(s_R1 + "iz)er$",		"$1e");
const Substitute	Stemmer::re_fulness	(s_R1 + "(?:ful|ous|ive))ness$",	"$1");

//	step 3
// const Match			Stemmer::re_ational(s_R1 + ")ational$");
const Match			Stemmer::re_tionalm	(s_R1 + ")tional$");
const Match			Stemmer::re_alize	(s_R1 + "al)ize$");
const Match			Stemmer::re_icate	(s_R1 + "ic)(?:ate|iti|al)$");
const Match			Stemmer::re_ful_ness(s_R1 + ")(?:ful|ness)$");
const Substitute	Stemmer::re_ative	(s_R2 + ")ative$",	"$1");

//	step 4
const Match			Stemmer::re_ement	(s_R2 + ")ement$");
const Match			Stemmer::re_ment	(s_R2 + ")ment$");
const Match			Stemmer::re_ent		(s_R2 + ")ent$");
const Match			Stemmer::re_al_er_ic(s_R2 + ")(?:al|ance|ence|er|ic|able|abli|ible|ant|ism|ate|iti|ous|ive|ize)$");
const Substitute	Stemmer::re_R2stion	(s_R2 + "(?:s|t))ion$",	"$1");

//	step 5
const Match			Stemmer::re_R2e		(s_R2 + ")e$");
const Substitute	Stemmer::re_R2ll	(s_R2 + "l)l$",		"$1");
