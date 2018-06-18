
#include "RemoveMatch.h"

RemoveMatch::RemoveMatch(const char* expression) :
	Hyperscan(expression, HS_FLAG_SOM_LEFTMOST)
{
}

void RemoveMatch::operator()(std::string& input) const
{
	std::vector<unsigned long long>	found;

	hs_error_t res = hs_scan(_database, input.c_str(), input.size(), 0, _scratch, _matchEvent, &found);

	if (res != HS_SUCCESS && res != HS_SCAN_TERMINATED) {
		throw std::runtime_error((char *) "An error occured during scan.");
	}

	//	We would return an array of strings if we wanted all matches.
	uint32_t fs = found.size();
	while(fs > 0) {
		auto cnt = found[--fs];
		auto pos = found[--fs];
		input.erase(pos, cnt);
	}
}

int RemoveMatch::_matchEvent(unsigned int, unsigned long long from, unsigned long long to, unsigned int, void* ctx)
{
	((std::vector<uint64_t>*)ctx)->emplace_back(from);		//	position
	((std::vector<uint64_t>*)ctx)->emplace_back(to-from);	//	length
	return 0;	//	zero means keep looking
}
