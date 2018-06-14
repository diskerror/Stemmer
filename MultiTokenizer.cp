/**
*
* Tokenizer to break text by a list of delimeter characters.
*
*/

#include "MultiTokenizer.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
MultiTokenizer::MultiTokenizer()
{
	tokens = nullptr;

	//	This has every ASCII symbol and control char except apostrophy and back-tick.
	//	Using the plus (+) after the character class causes no empty tokens are returned.
	string d("[\\x00-\\x26\\x28-\\x2F\\x3A-\\x40\\x5B-\\x5F\\x7B-\\x7F]+");
	SetDelimiter(d);
}

//	Requires string formatted as a regex character class.
MultiTokenizer::MultiTokenizer(string& delims)
{
	tokens = nullptr;
	SetDelimiter(delims);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
MultiTokenizer::~MultiTokenizer()
{
	delete delimRegex;
	if ( tokens != nullptr ) {
		delete tokens;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void MultiTokenizer::SetDelimiter(string& delims)
{
	delimRegex = new regex( delims, regex_constants::ECMAScript|regex_constants::optimize );

	if ( tokens != nullptr ) {
		delete tokens;
		tokens = nullptr;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void MultiTokenizer::SetText(string& in)
{
	tokens = new stringstream( regex_replace(in, *delimRegex, "\x0A") );
}


////////////////////////////////////////////////////////////////////////////////////////////////////
string MultiTokenizer::Get()
{
	string t;
	if ( *tokens >> t ) {
		return t;
	}
	else {
		return "";
	}
}
