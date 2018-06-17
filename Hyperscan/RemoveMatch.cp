
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
	while(found.size() > 0) {
		auto cnt = found.back(); found.pop_back();
		auto pos = found.back(); found.pop_back();
		input.erase(pos, cnt);
	}
}

int RemoveMatch::_matchEvent(unsigned int, unsigned long long from, unsigned long long to, unsigned int, void* ctx)
{
	std::vector<uint64_t>*	found = (std::vector<uint64_t>*) ctx;

	found->emplace_back(from);	//	position
	found->emplace_back(to-from);	//	length
	return 0;	//	zero means keep looking
}
