
#ifndef DISKERROR_PCRE2_H
#define DISKERROR_PCRE2_H
#pragma once

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

#include <string>
#include <stdexcept>

namespace Pcre2 {

class Pcre2
{
			Pcre2(){};
	void	init(const char*, uint32_t = 0);
	
protected:
	pcre2_code*			_regex;
	pcre2_match_data*	_match_data;

public:
			Pcre2(const char*, uint32_t = 0);
			Pcre2(const std::string&, uint32_t = 0);
	virtual ~Pcre2();
		
// 	virtual bool	exec(const char*, uint32_t = 0) = 0;	--	OR
// 	virtual const char*	exec(const char*, uint32_t = 0) = 0;

};

////////////////////////////////////////////////////////////////////////////////////////////////////
class Exception : public std::exception
{
	int32_t			_err;
	unsigned char*	_message;

public:
		Exception(int32_t err);
		virtual ~Exception();
	
	const unsigned char* what();
};

}

#endif	//	DISKERROR_PCRE2_H
