
#include "Substitute.h"

//using namespace Pcre2;

////////////////////////////////////////////////////////////////////////////////////////////////////
Pcre2::Substitute::Substitute(const char* expression, const char* replacement = "") :
	Pcre2(expression),
	_replace(replacement)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string Pcre2::Substitute::operator()(const std::string& subject) const
{
	uint32_t subjectLen = subject.size();

	PCRE2_SIZE bufferSize = ( subjectLen < 192 ) ? 256 : (subjectLen*1.2);
	PCRE2_UCHAR outputBuffer[bufferSize];

	auto erro = pcre2_substitute(
		_regex,
		(const PCRE2_UCHAR*) subject.c_str(),
		PCRE2_ZERO_TERMINATED,
		0,   //offset
		PCRE2_NO_UTF_CHECK|PCRE2_NOTEMPTY,
		_match_data,
		_mcontext,
		(const PCRE2_UCHAR*) _replace,
		PCRE2_ZERO_TERMINATED,
		outputBuffer,
		&bufferSize
	);

	if ( erro < PCRE2_ERROR_NOMATCH )
		throw new Exception( erro );

	return std::string((char*) outputBuffer);
}
