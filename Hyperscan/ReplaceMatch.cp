
#include "ReplaceMatch.h"

ReplaceMatch::ReplaceMatch(const char* expression, const char* replace) :
	RemoveMatch(expression),
	_replacement(replace)
{
}

void ReplaceMatch::operator()(std::string& input) const
{
	std::vector<uint64_t>	found;

	hs_error_t res = hs_scan(_database, input.c_str(), input.size(), 0, _scratch, _matchEvent, &found);

	if (res != HS_SUCCESS && res != HS_SCAN_TERMINATED) {
		throw std::runtime_error((char *) "An error occured during scan.");
	}

	while(found.size() > 0) {
		auto cnt = found.back(); found.pop_back();
		auto pos = found.back(); found.pop_back();
		input.replace(pos, cnt, _replacement);
	}
}
