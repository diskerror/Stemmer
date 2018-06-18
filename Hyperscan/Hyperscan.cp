
#include "Hyperscan.h"

Hyperscan::Hyperscan(const char* expression, uint32_t flags) :
	_database(nullptr),
	_scratch(nullptr),
	_compile_err(nullptr)
{
// 	flags |= (HS_FLAG_UTF8 | HS_FLAG_UCP);
	if (hs_compile(expression, flags, HS_MODE_BLOCK, NULL, &_database, &_compile_err) != HS_SUCCESS) {
		throw std::runtime_error((char *) _compile_err->message);
	}

	if (hs_alloc_scratch(_database, &_scratch) != HS_SUCCESS) {
		throw std::runtime_error((char *) "Unable to allocate scratch space.");
	}
}

Hyperscan::~Hyperscan()
{
	hs_free_scratch(_scratch);
	hs_free_database(_database);
	hs_free_compile_error(_compile_err);
}
