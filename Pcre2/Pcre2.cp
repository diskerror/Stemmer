
#include "Pcre2.h"

// using namespace Pcre2;

////////////////////////////////////////////////////////////////////////////////////////////////////
Pcre2::Pcre2::Pcre2(const char* expression)
{
	Pcre2::Pcre2::init(expression);
}

void Pcre2::Pcre2::init(const char* expression)
{
	int        errorCode = 0;
	PCRE2_SIZE errorOffset = 0;

	_regex = pcre2_compile(
		(PCRE2_SPTR) expression,
		strlen(expression),
		PCRE2_UTF | PCRE2_NO_UTF_CHECK,
		&errorCode,
		&errorOffset,
		NULL
	);
	if (_regex == NULL)
		throw Exception(errorCode);

	int jitError = pcre2_jit_compile(_regex, PCRE2_JIT_COMPLETE);
	if (jitError)
		throw Exception(jitError);

	_mcontext = pcre2_match_context_create(NULL);
	if (_mcontext == NULL)
		throw Exception(-1);

	_jit_stack = pcre2_jit_stack_create(8 * 1024, 256 * 1024, NULL);
	pcre2_jit_stack_assign(_mcontext, NULL, _jit_stack);

	_match_data = pcre2_match_data_create_from_pattern(_regex, NULL);
	if (_match_data == NULL)
		throw Exception(-1);
}

Pcre2::Pcre2::~Pcre2()
{
	pcre2_match_data_free(_match_data);
	pcre2_jit_stack_free(_jit_stack);
	pcre2_match_context_free(_mcontext);
	pcre2_code_free(_regex);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Pcre2::Exception::Exception(int32_t err)
{
	_err     = err;
	_message = NULL;
}

Pcre2::Exception::~Exception()
{
	if (_message != NULL)
		delete _message;
}

const unsigned char* Pcre2::Exception::what()
{
	if (_message == NULL) {
		uint32_t messgLen = 256;
		_message = new unsigned char(messgLen);
		pcre2_get_error_message(_err, (PCRE2_UCHAR8*) _message, messgLen);

		strcat((char*) _message, "\n");
		strcat((char*) _message, std::exception::what());
	}

	return (const unsigned char*) _message;
}
