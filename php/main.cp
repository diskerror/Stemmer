
#include "../MultiTokenizer.h"
#include "../Stemmer.h"

#include <phpcpp.h>

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
	
	if ( params.size() > 1 ) {
		prefs = (long) params[1];
	}
	
	string outputText, token, thisOne, lastOne;
	Php::Array outputArray;
	int i = 0;
	Php::Value outputData;
	
    switch ( prefs ) {
    	case 0:
		while( (token = tokenizer.Get()) != "" ) {
			outputText += Stemmer::StemWord(token) + " ";
		}
		
		if ( outputText.size() ) {
			outputText.pop_back();	//	remove extra space at end if not empty
		}
		
		outputData = outputText;
    	break;
    	
    	
    	case DISKERROR_STEM_RETURN_ARRAY:
		while( (token = tokenizer.Get()) != "" ) {
			outputArray[i++] = Stemmer::StemWord(token);
		}
		outputData = outputArray;
    	break;
    	
    	
    	case DISKERROR_STEM_RETURN_BIGRAM:
		while( (token = tokenizer.Get()) != "" ) {
			thisOne = Stemmer::StemWord(token);
			outputText += (lastOne + thisOne + " ");
			lastOne = thisOne;
		}
		outputText += lastOne;
		outputData = outputText;
    	break;
    	
    	
    	case DISKERROR_STEM_RETURN_ARRAY|DISKERROR_STEM_RETURN_BIGRAM:
		while( (token = tokenizer.Get()) != "" ) {
			thisOne = Stemmer::StemWord(token);
			outputArray[i++] = (lastOne + thisOne);
			lastOne = thisOne;
		}
		outputArray[i] = lastOne;
		outputData = outputArray;
    	break;
    }
    
    return outputData;
}


extern "C" {
    
    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension extension("diskerror_stem", "0.3");
        
        extension.add(Php::Constant("DISKERROR_STEM_RETURN_ARRAY", DISKERROR_STEM_RETURN_ARRAY));
        extension.add(Php::Constant("DISKERROR_STEM_RETURN_BIGRAM", DISKERROR_STEM_RETURN_BIGRAM));
        
//        extension.add( "Diskerror\\Stem", stem, {
//        	Php::ByVal("subject", Php::Type::String),
//        	Php::ByVal("options", Php::Type::Numeric, false)
//        } );
		extension.add<stem>( "Diskerror\\Stem" );

        // return the extension
        return extension;
    }
}
