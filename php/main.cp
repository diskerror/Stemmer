
#include "../MultiTokenizer.h"
#include "../Stemmer.h"

using namespace std;

enum {
	DISKERROR_STEM_RETURN_ARRAY = 1,
	DISKERROR_STEM_RETURN_BIGRAM
};

Php::Value stem(Php::Parameters &params)
{
	static MultiTokenizer tokenizer;

	string p = params[0];
	tokenizer.SetText(p);
	int prefs = 0;

	if (params.size() > 1) {
		prefs = (int) params[1];
	}

	string outputText, token, thisOne, lastOne;
	static Stemmer stem;
	vector<string> outputArray;

	switch (prefs) {
		case 0:
			while ((token = tokenizer.Get()) != "") {
				outputText += stem(token) + " ";
			}

			if (outputText.size()) {
				outputText.pop_back();    //	remove extra space at end if not empty
			}

			return outputText;

		case DISKERROR_STEM_RETURN_ARRAY:
			while ((token = tokenizer.Get()) != "") {
				outputArray.emplace_back(stem(token));
			}
			return outputArray;

		case DISKERROR_STEM_RETURN_BIGRAM:
			while ((token = tokenizer.Get()) != "") {
				thisOne = stem(token);
				outputText += (lastOne + thisOne + " ");
				lastOne = thisOne;
			}
			outputText += lastOne;
			return outputText;

		case DISKERROR_STEM_RETURN_ARRAY | DISKERROR_STEM_RETURN_BIGRAM:
			while ((token = tokenizer.Get()) != "") {
				thisOne = stem(token);
				outputArray.emplace_back(lastOne + thisOne);
				lastOne = thisOne;
			}
			outputArray.emplace_back(lastOne);
			return outputArray;

		default:
			throw Php::Exception("option does not exist");
	}
}


extern "C" {

    PHPCPP_EXPORT void *get_module()
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension extension("diskerror_stem", "0.4");

        extension.add(Php::Constant("DISKERROR_STEM_RETURN_ARRAY", DISKERROR_STEM_RETURN_ARRAY));
        extension.add(Php::Constant("DISKERROR_STEM_RETURN_BIGRAM", DISKERROR_STEM_RETURN_BIGRAM));

		extension.add<stem>( "Diskerror\\stem", {
        	Php::ByVal("subject", Php::Type::String),
        	Php::ByVal("options", Php::Type::Numeric, false)
        } );

        // return the extension
        return extension;
    }
}
