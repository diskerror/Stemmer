
#include "RemoveMatch.h"

RemoveMatch::RemoveMatch(const char* expression) :
	Hyperscan(expression, HS_FLAG_SOM_LEFTMOST)
{
}

void RemoveMatch::operator()(std::string& input) const
{
	found_t	found;

	hs_error_t res = hs_scan(_database, input.c_str(), input.size(), 0, _scratch, _matchEvent, &found);

	if (res != HS_SUCCESS && res != HS_SCAN_TERMINATED) {
		throw std::runtime_error((char *) "An error occured during scan.");
	}

	//	We would return an array of strings if we wanted all matches.
	while(found.size > 0) {
		--found.size;
		input.erase(
			found.from[found.size],
			found.to[found.size] - found.from[found.size]
		);
	}
}

int RemoveMatch::_matchEvent(unsigned int, unsigned long long from, unsigned long long to, unsigned int, void* ctx)
{
	((found_t*)ctx)->from[((found_t*)ctx)->size] = from;
	((found_t*)ctx)->to[((found_t*)ctx)->size] = to;
	++((found_t*)ctx)->size;
	return 0;	//	zero means keep looking
}
