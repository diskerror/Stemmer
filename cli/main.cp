
#include <fstream>
#include "../MultiTokenizer.h"
#include "../Stemmer.h"

namespace
{
	const size_t SUCCESS = 0;
// 	const size_t ERROR_IN_COMMAND_LINE = 1;
	const size_t ERROR_UNHANDLED_EXCEPTION = 2;
} // namespace

using namespace std;
// using namespace boost;
// namespace fs = filesystem;

int main(int argc, char** argv)
{
	try {
		ifstream in(argv[1]);
// 		ifstream in2(argv[2]);

		if ( !in )  {
			throw invalid_argument("file name required or bad file");
		}

// 		if ( argc > 2 ) {
// 			ofstream out(argv[2]);
// 		}
// 		else {
// 			ostream out &= cout;
// 		}

		std::string text((std::istreambuf_iterator<char>(in)),
                		 std::istreambuf_iterator<char>());
        
        MultiTokenizer tokenizer;
        tokenizer.SetText(text);
		string token;

		while ( (token = tokenizer.Get()) != "" ) {
			cout << setw(30) << left << token << Stemmer::StemWord(token) << endl;
		}
	}
	catch (exception& e) {
		cerr << e.what() << endl;
		return ERROR_UNHANDLED_EXCEPTION;
	}

	return SUCCESS;

} // main
