
#ifndef DISKERROR_HYPERSCAN_GETMATCH_H
#define DISKERROR_HYPERSCAN_GETMATCH_H

#include "Hyperscan.h"
#include <vector>
#include <string>

class GetMatch : public Hyperscan
{
	static int	_matchEvent(unsigned int, unsigned long long, unsigned long long, unsigned int, void*);

public:
	explicit GetMatch(const char*);
	std::string operator()(const std::string&) const;
};

#endif    //	DISKERROR_HYPERSCAN_GETMATCH_H
