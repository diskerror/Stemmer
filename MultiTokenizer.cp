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
	this->tokens = nullptr;
	
	//	This has every ASCII symbol and control char except apostrophy and back-tick.
	//	Using the plus (+) after the character class means no empty tokens are returned.
	string d("[\\x00-\\x26\\x28-\\x2F\\x3A-\\x40\\x5B-\\x5F\\x7B-\\x7F]+");
	this->SetDelimiter(d);
}

//	Requires string formatted as a regex character class.
MultiTokenizer::MultiTokenizer(string& delims)
{
	this->tokens = nullptr;
	this->SetDelimiter(delims);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
MultiTokenizer::~MultiTokenizer()
{
	delete this->delimRegex;
	if ( this->tokens != nullptr ) {
		delete this->tokens;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void MultiTokenizer::SetDelimiter(string& delims)
{
	this->delimRegex = new regex( delims, regex_constants::ECMAScript|regex_constants::optimize );
	
	if ( this->tokens != nullptr ) {
		delete this->tokens;
		this->tokens = nullptr;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void MultiTokenizer::SetText(string& in)
{
	this->tokens = new stringstream( regex_replace(in, *this->delimRegex, "\x0A") );
}


////////////////////////////////////////////////////////////////////////////////////////////////////
string MultiTokenizer::Get()
{
	string t;
	if ( *this->tokens >> t ) {
		return t;
	}
	else {
		return "";
	}
}
