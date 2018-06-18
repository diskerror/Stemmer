
#include "../MultiTokenizer.h"
#include "../Stemmer.h"


using namespace std;

int main(int argc, char** argv)
{
	try {
		vector<string> args;
		int32_t i;
		for(i=0; i<argc; ++i)
			args.emplace_back(argv[i]);


		//	check for filename parameter
		string text;
		bool useFile = false;
		for(i=0; i<argc; ++i) {
			if (args[i] == "-f") {
				useFile = true;
				ifstream in(args[++i]);

				if ( !in )  {
					throw invalid_argument("file name required or bad file");
				}

				text.assign((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
			}
		}

		//	must mean to use params as input text
		if (!useFile) {
			text = args[1];
			for(i=2; i<argc; ++i)
				text += " " + args[i];
		}


        MultiTokenizer tokenizer;
        tokenizer.SetText(text);
		string token;

		static Stemmer stem;

		while ( (token = tokenizer.Get()) != "" ) {
			cout << setw(30) << left << token << stem(token) << endl;
		}
	}
	catch (exception& e) {
		cerr << e.what() << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

} // main
