
#include "Match.h"

using namespace Pcre2;
using namespace std;

Match::Match(const char* expression)
	: Pcre2(expression)
{
}

Match::Match(const string& expression)
	: Pcre2(expression.c_str())
{
}

/**
 *  This only returns boolean of match.
 *
 * "subject" is null terminated.
 */
bool Match::operator()(const string& subject) const
{
	int32_t matchCount = pcre2_match(
		_regex,
		(const PCRE2_UCHAR*) subject.c_str(),
		subject.size(),
		0,       // offset
		PCRE2_NO_UTF_CHECK|PCRE2_NOTEMPTY,
		_match_data,
		_mcontext
	);

	if ( matchCount == PCRE2_ERROR_NOMATCH )
		return false;

	if ( matchCount < PCRE2_ERROR_NOMATCH )
		throw new Exception( matchCount );

	return true;
}

/**
 *  This returns boolean of match.
 *	"match" contains only the first set of matches:
 *		[0] contains the entire match,
 *		[1..n] contains the captured matches.
 *
 * "subject" is null terminated.
 * "matches" must be a valid pointer to a vector of strings.
 */
bool Match::operator()(const string& subject, vector<string>& matches) const
{
	const char *subjectC(subject.c_str());

	int32_t matchCount = pcre2_match(
		_regex,
		(const PCRE2_UCHAR*) subjectC,
		strlen(subjectC),
		0,       // offset
		PCRE2_NO_UTF_CHECK|PCRE2_NOTEMPTY,
		_match_data,
		_mcontext
	);

	matches.clear();
	if ( matchCount == PCRE2_ERROR_NOMATCH )
		return false;

	if ( matchCount < PCRE2_ERROR_NOMATCH )
		throw new Exception( matchCount );

	//	Now it must be good. Get the first set of captures.
	PCRE2_SIZE* ovector = pcre2_get_ovector_pointer(this->_match_data);
	PCRE2_SIZE i;
	for (i = 0; i < (PCRE2_SIZE) matchCount; i++) {
		matches.emplace_back( (subjectC + ovector[2*i]), (ovector[2*i+1] - ovector[2*i]) );
	}

	return true;
}
