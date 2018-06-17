
#include "HasMatch.h"

HasMatch::HasMatch(const char* expression) :
	Hyperscan(expression, HS_FLAG_SINGLEMATCH)
{
}

HasMatch::HasMatch(const std::string& expression) :
	Hyperscan(expression.c_str(), HS_FLAG_SINGLEMATCH)
{
}

bool HasMatch::operator()(const std::string& input) const
{
	bool found = false;

	hs_error_t res = hs_scan(_database, input.c_str(), input.size(), 0, _scratch, _matchEvent, &found);

	if (res != HS_SUCCESS && res != HS_SCAN_TERMINATED) {
		throw std::runtime_error((char *) "An error occured during scan.");
	}

	return found;
}

int HasMatch::_matchEvent(unsigned int, unsigned long long, unsigned long long, unsigned int, void* ctx)
{
	bool *found = (bool *) ctx;

	//	If this has been called then there was a match and stop looking.
	*found = true;
	return 1;
}
