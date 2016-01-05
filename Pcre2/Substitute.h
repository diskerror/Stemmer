
#ifndef DISKERROR_PCRESUBSTITUTE_H
#define DISKERROR_PCRESUBSTITUTE_H
#pragma once

#include "Pcre2.h"
#include <string>

namespace Pcre2 {

class Substitute : public Pcre2
{
	const char*	_replace;

public:
		Substitute(const char*, const char*, const uint32_t = 0);
		Substitute(const std::string&, const char*, const uint32_t = 0);
	
	std::string	operator() (const std::string&, const uint32_t = 0) const;
	
};

}

#endif	//	DISKERROR_PCRESUBSTITUTE_H
