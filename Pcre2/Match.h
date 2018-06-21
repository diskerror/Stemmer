
#ifndef DISKERROR_PCREHASMATCH_H
#define DISKERROR_PCREHASMATCH_H
#pragma once

#include "Pcre2.h"

namespace Pcre2 {

class Match : public Pcre2
{
public:
		Match(const char*);

	bool operator()(const std::string&) const;
	bool operator()(const std::string&, std::vector<std::string>&) const;

};

}

#endif	//	DISKERROR_PCREHASMATCH_H
