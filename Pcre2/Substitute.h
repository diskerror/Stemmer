
#ifndef DISKERROR_PCRESUBSTITUTE_H
#define DISKERROR_PCRESUBSTITUTE_H
#pragma once

#include "Pcre2.h"

namespace Pcre2 {

class Substitute : public Pcre2
{
	const char*	_replace;

public:
		Substitute(const char*, const char*);

	std::string	operator() (const std::string&) const;

};

}

#endif	//	DISKERROR_PCRESUBSTITUTE_H
