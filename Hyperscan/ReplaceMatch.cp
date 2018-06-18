
#include "ReplaceMatch.h"

ReplaceMatch::ReplaceMatch(const char* expression, const char* replace) :
	RemoveMatch(expression),
	_replacement(replace)
{
}

void ReplaceMatch::operator()(std::string& input) const
{
	found_t	found;

	hs_error_t res = hs_scan(_database, input.c_str(), input.size(), 0, _scratch, _matchEvent, &found);

	if (res != HS_SUCCESS && res != HS_SCAN_TERMINATED) {
		throw std::runtime_error((char *) "An error occured during scan.");
	}

	while(found.size > 0) {
		--found.size;
		input.replace(
			found.from[found.size],
			found.to[found.size] - found.from[found.size],
			_replacement
		);
	}
}
