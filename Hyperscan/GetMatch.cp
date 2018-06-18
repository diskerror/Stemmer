
#include "GetMatch.h"

GetMatch::GetMatch(const char* expression) :
	Hyperscan(expression, HS_FLAG_SOM_LEFTMOST)
{
}

std::string GetMatch::operator()(const std::string& input) const
{
	std::vector<uint64_t>	found;

	hs_error_t res = hs_scan(_database, input.c_str(), input.size(), 0, _scratch, _matchEvent, &found);

	if (res != HS_SUCCESS && res != HS_SCAN_TERMINATED) {
		throw std::runtime_error((char *) "An error occured during scan.");
	}

	//	We would return an array of strings if we wanted all matches.
	if(found.size() > 0)
		return input.substr(found[0], found[1]);

	return "";
}

int GetMatch::_matchEvent(unsigned int, unsigned long long from, unsigned long long to, unsigned int, void* ctx)
{
	//	If this has been called then there was a match and stop looking, returning the first match.
	((std::vector<uint64_t>*)ctx)->emplace_back(from);		//	position
	((std::vector<uint64_t>*)ctx)->emplace_back(to-from);	//	length
	return 1;
}
