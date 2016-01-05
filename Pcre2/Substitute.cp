
#include "Substitute.h"

using namespace Pcre2;

////////////////////////////////////////////////////////////////////////////////////////////////////
Substitute::Substitute(const char* expression, const char* replacement, const uint32_t syntaxOption)
	: Pcre2(expression, syntaxOption)
{
	this->_replace = replacement;
}

Substitute::Substitute(const std::string& expression, const char* replacement, const uint32_t syntaxOption)
	: Pcre2(expression.c_str(), syntaxOption)
{
	this->_replace = replacement;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string Substitute::operator()(const std::string& subject, uint32_t offset) const
{
	uint32_t subjectLen = subject.size();
	
	PCRE2_SIZE bufferSize = ( subjectLen < 8192 ) ? 16384 : (subjectLen*1.2);
	PCRE2_UCHAR outputBuffer[bufferSize];
	
	auto erro = pcre2_substitute(
		this->_regex,
		(const PCRE2_UCHAR*) subject.c_str(),
		PCRE2_ZERO_TERMINATED,
		offset,
		PCRE2_SUBSTITUTE_GLOBAL,	//	options
		this->_match_data,
		NULL,		//	match context
		(const PCRE2_UCHAR*) this->_replace,
		PCRE2_ZERO_TERMINATED,
		outputBuffer,
		&bufferSize
	);
	
	if ( erro < PCRE2_ERROR_NOMATCH )
		throw new Exception( erro );
	
// 	if ( erro == PCRE2_ERROR_NOMATCH || erro == 0 )
// 		return subject;
	
	return std::string((char*) outputBuffer);
}
