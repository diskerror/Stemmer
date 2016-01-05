
#include "Match.h"

using namespace Pcre2;
using namespace std;

Match::Match(const char* expression, const uint32_t syntaxOption)
	: Pcre2(expression, syntaxOption)
{
}

Match::Match(const string& expression, const uint32_t syntaxOption)
	: Pcre2(expression.c_str(), syntaxOption)
{
}

int32_t Match::doMatch(const char* subject, const uint32_t offset) const
{
	int32_t matchCount = pcre2_match(
		this->_regex,
		(const PCRE2_UCHAR*) subject,
		PCRE2_ZERO_TERMINATED,
		offset,
		0,	//	options
		this->_match_data,
		NULL
	);
	
	if ( matchCount < PCRE2_ERROR_NOMATCH )
		throw new Exception( matchCount );
	
	return matchCount;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  This only returns boolean of match.
 *
 * "subject" is null terminated.
 */
bool Match::operator()(const string& subject, const uint32_t offset) const
{
	int32_t matchCount = this->doMatch((const char*)subject.c_str(), offset);
	
	if ( matchCount == PCRE2_ERROR_NOMATCH )
		return false;
	
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
bool Match::operator()(const string& subject, vector<string>& matches, const uint32_t offset) const
{
	const char *subjectC(subject.c_str());
	
	int32_t matchCount = this->doMatch(subjectC, offset);
	
	matches.clear();
	if ( matchCount == PCRE2_ERROR_NOMATCH )
		return false;
	
	//	Now it must be good. Get the first set of captures.
	PCRE2_SIZE* ovector = pcre2_get_ovector_pointer(this->_match_data);
	PCRE2_SIZE i;
	for (i = 0; i < (PCRE2_SIZE) matchCount; i++) {
		matches.emplace_back( (subjectC + ovector[2*i]), (ovector[2*i+1] - ovector[2*i]) );
	}
	
	return true;
}
