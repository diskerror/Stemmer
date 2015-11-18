
#include <fstream>
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
			throw new invalid_argument("file name required or bad file");
		}

// 		if ( argc > 2 ) {
// 			ofstream out(argv[2]);
// 		}
// 		else {
// 			ostream out &= cout;
// 		}

		string line;
		Stemmer Stem;
		while ( in >> line ) {
			cout << line << "\t\t" << Stem.StemWord(line) << endl;
		}
	}
	catch (regex_error& e) {
		cerr << e.code() << " " << e.what() << endl;
		return ERROR_UNHANDLED_EXCEPTION;
	}
	catch (exception& e) {
		cerr << e.what() << endl;
		return ERROR_UNHANDLED_EXCEPTION;
	}

	return SUCCESS;

} // main
