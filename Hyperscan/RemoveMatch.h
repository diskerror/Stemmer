
#ifndef DISKERROR_HYPERSCAN_REMOVEMATCH_H
#define DISKERROR_HYPERSCAN_REMOVEMATCH_H

#include "Hyperscan.h"
#include <vector>
#include <string>

class RemoveMatch : public Hyperscan
{
protected:
	static int	_matchEvent(unsigned int, unsigned long long, unsigned long long, unsigned int, void*);

public:
	explicit RemoveMatch(const char*);
	void operator()(std::string&) const;
};

#endif    //	DISKERROR_HYPERSCAN_REMOVEMATCH_H
