
#ifndef DISKERROR_HYPERSCAN_REPLACEMATCH_H
#define DISKERROR_HYPERSCAN_REPLACEMATCH_H

#include "RemoveMatch.h"

class ReplaceMatch : public RemoveMatch
{
	const char* _replacement;

public:
	explicit ReplaceMatch(const char*, const char*);
	void operator()(std::string&) const;
};

#endif    //	DISKERROR_HYPERSCAN_REPLACEMATCH_H
