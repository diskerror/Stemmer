
#ifndef DISKERROR_HYPERSCAN_HASMATCH_H
#define DISKERROR_HYPERSCAN_HASMATCH_H

#include "Hyperscan.h"
#include <string>

class HasMatch : public Hyperscan
{
	static int	_matchEvent(unsigned int, unsigned long long, unsigned long long, unsigned int, void*);

public:
	explicit HasMatch(const char*);
	explicit HasMatch(const std::string&);
	bool operator()(const std::string&) const;
};

#endif    //	DISKERROR_HYPERSCAN_HASMATCH_H
