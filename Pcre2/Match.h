
#ifndef DISKERROR_PCREHASMATCH_H
#define DISKERROR_PCREHASMATCH_H
#pragma once

#include "Pcre2.h"
#include <vector>
#include <string>

namespace Pcre2 {

class Match : public Pcre2
{
	int32_t	doMatch(const char*, const uint32_t = 0) const;
	
public:
		Match(const char*, const uint32_t = 0);
		Match(const std::string&, const uint32_t = 0);
	
	bool operator()(const std::string&, const uint32_t = 0) const;
	bool operator()(const std::string&, std::vector<std::string>&, const uint32_t = 0) const;
	
};

}

#endif	//	DISKERROR_PCREHASMATCH_H
