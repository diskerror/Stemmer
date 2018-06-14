/**
*
* Tokenizer to break text by a list of delimeter characters.
*
*/

#ifndef DISKERROR_MULTITOKENIZER_H
#define DISKERROR_MULTITOKENIZER_H
#pragma once

#include <regex>
#include <sstream>
#include <string>

class MultiTokenizer
{
		protected:

		std::regex * delimRegex;

	std::stringstream* tokens;

	public:
	MultiTokenizer();
	MultiTokenizer(std::string&);

//	MultiTokenizer(const MultiTokenizer&){}
//	void MultiTokenizer operator=(const MultiTokenizer&){}

	~MultiTokenizer();

	void SetDelimiter(std::string&);

	void SetText(std::string&);

	std::string        Get();

};

#endif    //	DISKERROR_MULTITOKENIZER_H
