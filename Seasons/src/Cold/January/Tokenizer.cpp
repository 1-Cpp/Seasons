#include "January\Tokenizer.h"

#include "October/String.h"
#include "October/Exception.h"
namespace Seasons
{
	class SyntaxError : public Exception
	{
	public:
		const String& str;
		int pos;
		wchar_t * errorText;
		SyntaxError(const String&source,int pos,wchar_t*text) :str(source),pos(pos),errorText(text)
		{

		}

	};
namespace Const {
	const String BEGIN = L"BEGIN";
	const String END = L"END";
	const String BEGINFILE = L"BEGINFILE";
	const String ENDFILE = L"ENDFILE";
	const String TYPE = L"TYPE";
	const String FILE = L"FILE";
	const String ENDIAN = L"ENDIAN";
	const String LITTLE = L"LITTLE";
	const String BIG = L"BIG";
	const String UNION = L"UNION";
	const String NEXT = L"NEXT";
	const String IF = L"IF";
	const String USTRING = L"USTRING";
	const String SIZE = L"SIZE";
	const String VERSION = L"VERSION";
	const String ELSE = L"ELSE";
	const String ALIGN = L"ALIGN";
	const String BYTE = L"BYTE";
	const String BIT = L"BIT";
	const String DESCRIPTION = L"DESCRIPTION";

	const String START_ARRAY = L"[";
	const String END_ARRAY = L"]";
	const String START_FUNCTION = L"(";
	const String END_FUNCTION = L")";
	const String BEGIN_DEFINITION = L":";
	const String EOL = L"\n";
}
using namespace Const;


Tokenizer::Tokenizer(const String&source):source(source)
{
}


Tokenizer::~Tokenizer()
{
}
bool isDelimiter(wchar_t ch) {
	return wcschr(L";,:[]()", ch) != nullptr;
}
bool isTokenChar(wchar_t ch) {
	if (iswalpha(ch))
		return true;
	if (iswalnum(ch))
		return true;
	if (ch == L'_')
		return true;
	return false;
}
void endToken() {
}
void endStatement(bool delimiter) {
}
void beginStatement() {

}
void beginToken() {
}
bool eatString(wchar_t*p, wchar_t*delimiter,int &pos, String&outString) {
	return true;
}
bool eatComment(wchar_t*p, int &pos, String&outString) {
	return true;
}
bool Tokenizer::tokenize()
{
	const wchar_t * p = (const wchar_t*)source;
	bool isComment = false;
	bool inToken = false;
	String token;
	int size = source.size();
	for (int i = 0; i < size; ++i) {
		wchar_t ch = p[i];
		if (isComment && ch != L'/')
			isComment = false;
		if (iswspace(ch))
		{
			if (inToken) {
				inToken = false;
				endToken();
			}
			else {
				continue;
			}
		}
		else if (ch == L'#') {
			break;
		}
		else if (ch == L'/') {
			if (isComment)
				break;
			isComment = true;
		}
		else if (isDelimiter(ch)) {
			if (inToken) {
				inToken = false;
				endToken();
			}
			if (ch == L';') {
				endStatement(true);
				beginStatement();
			}
			else {
				String delim;
				delim += ch;
				endToken();
			}
		}
		else if (isTokenChar(ch)) {
			if (inToken) {

			}
			else {
				inToken = true;
				beginToken();
			}
			token += ch;
		}
		else
			throw SyntaxError(source, i, L"wrong character - not allowed here");

	}

	return false;
}

}
