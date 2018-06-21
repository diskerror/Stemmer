
#ifndef DISKERROR_PCRE2_H
#define DISKERROR_PCRE2_H
#pragma once

#define PCRE2_CODE_UNIT_WIDTH 8

namespace Pcre2
{

class Pcre2
{
	Pcre2(){};
	void init(const char *);

protected:
	pcre2_code          *_regex;
	pcre2_match_data    *_match_data;
	pcre2_match_context *_mcontext;
	pcre2_jit_stack     *_jit_stack;

public:
	Pcre2(const char*);
	virtual ~Pcre2();

	// 	virtual bool	exec(const char*) = 0;	--	OR
	// 	virtual const char*	exec(const char*) = 0;

};

////////////////////////////////////////////////////////////////////////////////////////////////////
class Exception : public std::exception
{
	int32_t       _err;
	unsigned char *_message;

public:
	Exception(int32_t);
	virtual ~Exception();

	const unsigned char *what();
};

}

#endif    //	DISKERROR_PCRE2_H
