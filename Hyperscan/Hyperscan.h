
#ifndef DISKERROR_HYPERSCAN_H
#define DISKERROR_HYPERSCAN_H
#pragma once

#include <hs/hs.h>

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

class found_t {
public:
	uint32_t size = 0;		//	count, or number used
	uint64_t from[8] = {};	//	array of values
	uint64_t to[8] = {};	//	array of values
};

#endif    //	DISKERROR_HYPERSCAN_H
