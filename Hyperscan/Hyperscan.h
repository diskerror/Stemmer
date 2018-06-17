
#ifndef DISKERROR_HYPERSCAN_H
#define DISKERROR_HYPERSCAN_H
#pragma once

#include <hs.h>

class Hyperscan
{
protected:
	hs_database_t*		_database;
	hs_scratch_t*		_scratch;
	hs_compile_error_t*	_compile_err;

public:
	explicit Hyperscan(const char*, uint32_t);
	~Hyperscan();
};

#endif    //	DISKERROR_HYPERSCAN_H
