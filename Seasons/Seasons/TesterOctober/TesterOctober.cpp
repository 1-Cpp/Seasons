/**
  * @Martin@
  * mbr 27.07.2015 09:13:53 
  * mbr $DATE$ $TIME$
  * (C) Copyright 2015 @Martin@
  *
  */
  
//#include "TesterOctober.h"

#include "Main.h"

#include "October/BTree.h"
#include "October/String.h"
#include "October/ArrayList.h"

#include "October/ArrayList.h"
#include "October/SortedArrayList.h"
#include "October/Stack.h"
#include "October/Debug.h"
#include "October/File.h"

#include "October/Data.h"
#include "October/DataLineReader.h"

//using namespace System::Collections;
//using namespace System::Diagnostics;
namespace Seasons
{
	enum MainState
	{
		Outside = 1,
		Inside = 2,
	};
	enum SubState
	{
		None = 0,
		LeftSide = 3,
		RightSide = 4,
		EOL = 5,
		InProduction = 6,
	};
	class Production;
	enum Modifier
	{
		mNone,
		Star,
		Plus
	};
}

class TokenImpl
{
public:
	enum Type
	{
		None = 0,
		Begin = 2,
		End = 3,
		Range = 4,
		Exclusion = 5,
		EscapeSeq = 6,
		Production = 7,
		Assignment = 8,
		EOL = 9,
		WhiteSpace = 10,
		Identifier = 11,
		SyntaxError = 12,
		String = 13,
		Line = 14,
		//			ParenthesisOpened = 15,
		//			ParenthesisClosed = 16,
		BracketsOpened = 17,
		BracketsClosed = 18,
		EOS = 19,
		OperatorOr = 21,
		OperatorStar = 22,
		OperatorPlus = 23,
		Anonymous = 30,
	};
	Type type = None;
	Seasons::MainState state;
	Seasons::SubState subState;
	int pos = 0;
	int count = 0;

	Seasons::Production * production = nullptr;
	TokenImpl()
	{

	}
	TokenImpl(Seasons::MainState state, Seasons::SubState subState, Type type, int pos, int count) :
		state(state), subState(subState), type(type), pos(pos), count(count)
	{

	}
};

namespace Seasons
{
	class Alternatives;
	class SeqElement;
	class BaseSequence
	{
	public:
	};
	class Sequence : public BaseSequence
	{
	public:
		int value = 11;
		Modifier modifier = mNone;
		Seasons::ArrayList<SeqElement> sequence;
		int compare(const Sequence&other) const
		{
			return value < other.value ? -1 : value > other.value ? 1 : 0;
		}
		void clear()
		{
			modifier = mNone;
			sequence.clear();
			value = 11;
		}
		void add(const TokenImpl&token);

		void add(const Alternatives&seq);
		bool isEmpty() const
		{
			return sequence.isEmpty();
		}
		void modifyLast(Modifier mode);
	};
	bool operator < (const Sequence&seqLeft, const Sequence&seqRight)
	{
		return seqLeft.compare(seqRight) < 0;
	}
	bool operator > (const Sequence&seqLeft, const Sequence&seqRight)
	{
		return seqLeft.compare(seqRight) > 0;
	}
	bool operator == (const Sequence&seqLeft, const Sequence&seqRight)
	{
		return seqLeft.compare(seqRight) == 0;
	}
	bool operator != (const Sequence&seqLeft, const Sequence&seqRight)
	{
		return seqLeft.compare(seqRight) != 0;
	}
	class Alternatives
	{
	public:

		Seasons::SortedArrayList<Sequence> alternatives;
		void clear()
		{
			alternatives.clear();
		}
		void insert(const Sequence& seq)
		{
			alternatives.insert(seq);
		}
	};
	class Production
	{
	public:
		TokenImpl identifier;
		Alternatives alternatives;
		void clear()
		{
			identifier = TokenImpl();
			alternatives.clear();
		}
		void insert(const Sequence&seq)
		{
			alternatives.insert(seq);
		}
	};
	class SeqElement
	{
	public:
		bool isAlternative = false;
		bool isToken = false;
		TokenImpl	token;
		Alternatives	sequence;
		Modifier	modifier = mNone;
		SeqElement()
		{

		}
		SeqElement(const TokenImpl &token) :token(token), isToken(true)
		{

		}
		SeqElement(const Alternatives&seq);
	};

	SeqElement::SeqElement(const Alternatives&seq) :isAlternative(true), sequence(seq)
	{

	}
	void Sequence::modifyLast(Modifier mode)
	{
		if (!isEmpty())
		{
			sequence.getLast().modifier = mode;
		}
	}
	void Sequence::add(const TokenImpl&token)
	{
		sequence.add(SeqElement(token));
	}
	void Sequence::add(const Alternatives&seq)
	{
		sequence.add(SeqElement(seq));
	}

}

using namespace Seasons;
class LexerImpl
{
public:
	class InternalException
	{
	public:
	};
	Seasons::ArrayList<TokenImpl> tokens;
	MainState state = Outside;
	SubState subState = LeftSide;
	TokenImpl * currentIdentifier = nullptr;
	TokenImpl * currentSyntaxError = nullptr;
	TokenImpl * currentString = nullptr;
	TokenImpl * currentLine = nullptr;
	int posWhite = 0;
	int countWhite = 0;

	bool isIdentifier(wchar_t ch)
	{
		if ((ch >= L'A' && ch <= L'Z') || (ch >= L'a' && ch <= L'z'))
		{
			return true;
		}
		return false;
	}
	bool isWhite(wchar_t ch)
	{
		if (ch == L' ' || ch == '\t' || ch == '\v')
			return true;
		return false;
	}
	bool isEOL(wchar_t ch)
	{
		if (ch == '\n' || ch == '\r')
		{
			return true;
		}
		return false;
	}
	void closeIdentifier(TokenImpl * & currentIdentifier)
	{
		if (currentIdentifier != nullptr)
		{
			tokens.add(*currentIdentifier);
			delete currentIdentifier;
			currentIdentifier = nullptr;
		}

	}
	void closeSyntaxError(TokenImpl * &currentSyntaxError)
	{
		if (currentSyntaxError != nullptr)
		{
			tokens.add(*currentSyntaxError);
			delete currentSyntaxError;
			currentSyntaxError = nullptr;
		}
	}
	bool treatIdentifier(const wchar_t * p, int i)
	{
		if (isIdentifier(p[i]))
		{

			if (currentIdentifier == nullptr)
			{
				closeSyntaxError(currentSyntaxError);
				currentIdentifier = new TokenImpl(state, subState, TokenImpl::Identifier, i, 1);
			}
			else if (currentSyntaxError == nullptr)
				currentIdentifier->count++;
			else
			{
				currentSyntaxError->count++;
			}
			return true;
		}
		else if (currentIdentifier != nullptr)
		{
			closeIdentifier(currentIdentifier);
		}
		return false;
	}
	bool treatWhite(const wchar_t * p, int i)
	{
		if (state == Inside && subState == RightSide && isWhite(p[i]))
			return false;
		if (isWhite(p[i]) || (state == Outside && isEOL(p[i])))
		{
			closeSyntaxError(currentSyntaxError);
			if (countWhite == 0)
			{
				posWhite = i;
				countWhite = 1;
				closeIdentifier(currentIdentifier);
			}
			else
			{
				countWhite++;
			}
			return true;
		}
		countWhite = 0;
		return false;
	}
	void closeAll()
	{
		closeIdentifier(currentIdentifier);
		closeSyntaxError(currentSyntaxError);
	}
	void initState(MainState newState)
	{
		state = newState;
		subState = None;
	}
	void treatAsSyntaxError(const wchar_t*p, int i)
	{
		if (currentSyntaxError != nullptr)
		{
			currentSyntaxError->count++;
		}
		else
			currentSyntaxError = new TokenImpl(state, subState, TokenImpl::SyntaxError, i, 1);

	}
	void finishString(const wchar_t*p, int i)
	{
		/*if (currentString == nullptr)
		{
		currentString = new TokenImpl(state, subState, TokenImpl::String, i, 0);
		}*/
		if (currentString != nullptr)
		{
			tokens.add(*currentString);
			delete currentString;
		}
		currentString = nullptr;
	}
	void finishLine(const wchar_t*p, int i)
	{
		if (currentLine != nullptr)
		{
			currentLine->count = i - currentLine->pos;
			tokens.add(*currentLine);
			delete currentLine;
			currentLine = nullptr;
			return;
		}
		else
		{
			tokens.add(TokenImpl(state, subState, TokenImpl::EOL, i, 1));
		}

	}
	void treatRightSide(const wchar_t*p, int i)
	{
		if (currentString == nullptr)
		{
			currentString = new TokenImpl(state, subState, TokenImpl::String, i, 1);
		}
		else
		{
			currentString->count++;
		}
	}
	wchar_t * printSub(SubState sub)
	{
		switch (sub)
		{
		case LeftSide:
			return L"Left";
		case RightSide:
			return L"Right";
		case EOL:
			return L"EOL";
		case None:
			return L"None";
		case InProduction:
			return L"Prod";
		default:
			return L"Error";
		}
	}
#pragma comment(lib,"October.lib")

	void read(Seasons::String& in)
	{
		state = Outside;
		subState = LeftSide;
		countWhite = 0;
		posWhite = 0;
		tokens.clear();
		//cli::pin_ptr<const wchar_t> pinned = ::PtrToStringChars(in);

		const wchar_t * pch = in;// pinned;
		//str = pch;
		const wchar_t * p = pch;
		int i = 0;
		int counter = 0;
		while (p[i])
		{
			Seasons::debugOut(L"Round %d: %p[%i]=%c state=%s,subState=%s\n", ++counter, p, i, p[i],
				state == Inside ? L"Inside" : state == Outside ? L"Outside" : L"Unknown", printSub(subState));
			if (treatWhite(p, i))
			{
				// ignore
				i++;
				continue;
			}
			else if ((state == Inside) && isEOL(p[i]))
			{
				if (subState == None)
				{
					finishLine(p, i);
					subState = EOL;
					i++;
					continue;
				}
				else if (subState == EOL)
				{
					i++;
					continue;
				}
				else if (subState == LeftSide)
				{
					treatAsSyntaxError(p, i);
					i++;
					continue;
				}
				finishString(p, i);
				closeAll();
				finishLine(p, i);
				subState = EOL;
				i++;
				continue;
			}
			else if (state == Inside && subState == EOL && !isEOL(p[i]))
			{
				subState = LeftSide;
				currentLine = new TokenImpl(state, subState, TokenImpl::Line, i, 0);
			}
			switch (state)
			{
			case Outside:
				switch (subState)
				{
				case LeftSide:
					switch (p[i])
					{
					case '=':
						subState = RightSide;
						closeAll();
						tokens.add(TokenImpl(state, subState, TokenImpl::Assignment, i, 1));
						break;
					default:
						if (!treatIdentifier(p, i))
						{
							treatAsSyntaxError(p, i);
						}
					}
					i++;
					continue;
					break;
				case RightSide:
					switch (p[i])
					{
					case '{':
						closeAll();
						tokens.add(TokenImpl(state, subState, TokenImpl::Begin, i, 1));
						initState(Inside);
						break;
					default:
						treatAsSyntaxError(p, i);
						break;
					}
					i++;
					continue;
					break;
				default:
					throw InternalException();
				}
				break;
			case Inside:
				switch (subState)
				{
				case LeftSide:
					if (!treatIdentifier(p, i))
					{
						switch (p[i])
						{
						case '\\':
							if (p[i + 1] == '=')
							{
								tokens.add(TokenImpl(state, subState, TokenImpl::EscapeSeq, i, 2));
								i += 2;
							}
							else
							{
								treatAsSyntaxError(p, i);
								i += 2;
								continue;
							}
							break;
						case '[':
							if (p[i + 1] == ']' && p[i + 2] == '=')
							{
								tokens.add(TokenImpl(state, subState, TokenImpl::Range, i, 3));
								i += 3;
							}
							else
							{
								treatAsSyntaxError(p, i);
								i += 2;
								continue;
							}
							break;
						case ':':
							if (p[i + 1] == '=')
							{
								tokens.add(TokenImpl(state, subState, TokenImpl::Production, i, 2));
								i += 2;
								subState = InProduction;
								closeAll();
								continue;
							}
							else
							{
								treatAsSyntaxError(p, i);
								i += 2;
								continue;
							}
							break;
						case '^':
							if (p[i + 1] == '=')
							{
								tokens.add(TokenImpl(state, subState, TokenImpl::Exclusion, i, 2));
								i += 2;
							}
							else
							{
								treatAsSyntaxError(p, i);
								i += 2;
								continue;
							}
							break;
						case '=':
							tokens.add(TokenImpl(state, subState, TokenImpl::Assignment, i, 1));
							i++;
							break;
						case '}':
							initState(Outside);
							tokens.add(TokenImpl(state, subState, TokenImpl::End, i, 1));
							closeAll();
							i++;
							continue;
						default:
							treatAsSyntaxError(p, i);
							i++;
							continue;
						}
						subState = RightSide;
						closeAll();
						continue;
					}
					i++;
					continue;
					break;
				case RightSide:
					if (isEOL(p[i]))
						throw InternalException();
					treatRightSide(p, i);
					i++;
					continue;
					break;
				case InProduction:
					if (!treatIdentifier(p, i))
					{
						switch (p[i])
						{
						case '+':
							closeAll();
							tokens.add(TokenImpl(state, subState, TokenImpl::OperatorPlus, i, 1));
							break;
						case '*':
							closeAll();
							tokens.add(TokenImpl(state, subState, TokenImpl::OperatorStar, i, 1));
							break;
						case '|':
							closeAll();
							tokens.add(TokenImpl(state, subState, TokenImpl::OperatorOr, i, 1));
							break;
							/*case '(':
							tokens.add(TokenImpl(state, subState, TokenImpl::ParenthesisOpened, i, 1));
							break;
							case ')':
							tokens.add(TokenImpl(state, subState, TokenImpl::ParenthesisClosed, i, 1));
							break;*/
						case '[':
							closeAll();
							tokens.add(TokenImpl(state, subState, TokenImpl::BracketsOpened, i, 1));
							break;
						case ']':
							closeAll();
							tokens.add(TokenImpl(state, subState, TokenImpl::BracketsClosed, i, 1));
							break;
						default:
							treatAsSyntaxError(p, i);
							break;
						}
					}
					i++;
					continue;
				default:
					throw InternalException();
				}
				break;
			default:
				throw InternalException();
			}
			throw InternalException();
		}
		tokens.add(TokenImpl(state, subState, TokenImpl::EOS, i, 0));
	}
	void fill(ArrayList<TokenImpl> & ar)
	{
		Production prod;
		Sequence sequence;
		Alternatives alternatives;
		Seasons::Stack<Sequence> stack;

		bool inProduction = false;
		int brackets = 0;


		for (int i = 0; i < tokens.size(); ++i)
		{
			TokenImpl & token = tokens[i];
			//Test::Token^ t = gcnew Test::Token(token);
			//ar->Add(t);
			ar.add(token);

			if (token.type == TokenImpl::Production)
			{
				if (i > 0 && tokens[i - 1].type == TokenImpl::Identifier)
				{
					prod.identifier = tokens[i - 1];
					inProduction = true;
				}
			}
			else if (token.type == TokenImpl::EOL ||
				token.type == TokenImpl::Line ||
				token.type == TokenImpl::End)
			{
				if (inProduction)
				{
					prod.insert(sequence);
					productions.add(prod);
					prod.clear();
					sequence.clear();
				}
				inProduction = false;
			}
			else if (inProduction)
			{
				if (token.type == TokenImpl::OperatorOr)
				{
					alternatives.insert(sequence);
					sequence.clear();
				}
				else if (token.type == TokenImpl::OperatorPlus)
				{
					sequence.modifyLast(Modifier::Plus);
				}
				else if (token.type == TokenImpl::OperatorStar)
				{
					sequence.modifyLast(Modifier::Star);
				}
				else if (token.type == TokenImpl::BracketsOpened)
				{
					stack.push(sequence);

					sequence.clear();
					brackets++;
				}
				else if (token.type == TokenImpl::BracketsClosed)
				{
					if (brackets < 1)
					{
						TokenImpl syntax(token);
						syntax.type = TokenImpl::SyntaxError;
						/*Test::Token^ tSyntax = gcnew Test::Token(syntax);
						ar->Add(t);*/
						continue;
					}
					alternatives.insert(sequence);
					stack.peek().add(alternatives);
					sequence = stack.pop();
					brackets--;
				}
				else if (token.type == TokenImpl::Identifier)
				{
					sequence.add(token);
				}
				else
				{
					throw InternalException();
				}
			}
		}
	}
	void getProductions(ArrayList<TokenImpl>&ar)
	{
		for (int i = 0; i < productions.size(); ++i)
		{
			//Test::Token^ t = gcnew Test::Token(productions[i].identifier);

			//ar->Add(t);
			ar.add(productions[i].identifier);
		}
	}
	Seasons::ArrayList<Production> productions;
};

namespace Seasons
{
	extern wchar_t * pszOctober;
}
#define M(x) L##x
#define X(x) L#x

#define COPY L"(C) Copyright @Martin@"

#ifdef _DEBUG
#define L(x,y,z) L"@(#)DEBUG:  " M(x) L" "  M(y) L" MSC:" X(z) L" TesterOctober.exe" COPY
#else
#define L(x,y,z) L"@(#)RELEASE:" M(x) L" "  M(y) L" MSC:" X(z) L" TesterOctober.exe" COPY
#endif

static wchar_t * p = L(__DATE__,__TIME__,_MSC_FULL_VER) ;

#pragma comment(lib,"October.lib")

using namespace Seasons;
typedef std::vector<const BTree<String, String>::BTN *> Vector;
void dump(std::vector<const BTree<String, String>::BTN *>&vec)
{
	Vector::iterator i = vec.begin();
	wprintf(L"\n%d elements:\n", vec.size());
	for (; i != vec.end(); ++i)
	{
		String str = (*i)->key;
		//wprintf(L"<%s>\t", (const wchar_t*)str);
		(*i)->dump();
		//wprintf(L"\n");
	}
	wprintf(L"\n");
}
void Dump(BTree<String, String>::BTN*p,int level = 0)
{
	if (!p)
	{
		for (int i = 0; i < level; ++i)
			wprintf(L"\t");
		wprintf(L"(null)\n");
		return;
	}
	Dump(p->black, level + 1);
	for (int i = 0; i < level; ++i)
		wprintf(L"\t");
	wprintf(L"%s\n", (const wchar_t*)p->key);
	//wprintf(L"\n");
	Dump(p->red, level + 1);

}
void Dump(ArrayList<String>&array)
{
	for (int i = 0; i < array.length; ++i)
	{
		wprintf(L"<%s>\n", (const wchar_t*)array[i]);
	}
}
void Dump(ArrayList<TokenImpl>&array,String&str)
{
	for (int i = 0; i < array.length; ++i)
	{
		wprintf(L"<%s>\n", (const wchar_t*)str.substr(array[i].pos,array[i].count));
	}
}
void lexer()
{
	File file(L"d:\\Source\\1-cpp\\Seasons\\Seasons\\res\\March\\lexer.lex");
	Seasons::Data data;
	Seasons::ArrayList<TokenImpl> list;
	file.readAll(data);
	Seasons::DataLineReader reader(data);
	String out, str;
	while (reader.readLine(out))
	{
		str += out;
	}
	LexerImpl impl;
	impl.read(str);
	impl.fill(list);


}
class TesterOctober : public Main {
public:
	BTree<String, String> varMap;

	std::vector<const BTree<String, String>::BTN *> vec;
	int run() {
		arraylist();
		btree();
		lexer();
		return 0;
	}
	void arraylist()
	{
		ArrayList<String> array1, array2, array3, array4, array5, * array;
		array1.add(L"Martin");
		array1.add(L"Regina");
		array1.add(L"Johanna");
		array1.add(L"Joachim");
		array1.add(L"Reinhard");
		array1.add(L"Christian");
		array2.add(L"Roswitha");
		array2.add(L"Hildegard");
		array3.add(L"Reinhold");
		array3.add(L"Anita");
		array3.add(L"Alfred");
		array3.add(L"Franz");
		array3.add(L"Konrad");
		array3.add(L"Traudl");
		array4.add(L"Emma");
		array4.add(L"Peter");
		array5.add(L"Antonie");
		array5.add(L"Albert");
		array = new ArrayList<String>();
		array->reserve(64);
		array->add(array1);
		
		array->add(array2);
		array->add(array3);
		array->add(array4);
		array->add(array5);
		Dump(*array);
		array->clear();
		delete array;
	}
	void btree()
	{
		const BTree<String, String>::BTN *p = nullptr;
		p = varMap.insert(L"Text", L"Inhalt");
		vec.push_back(p);
		varMap.root->dump();
		dump(vec);
		p = varMap.insert(L"ABC", L"ABCInhalt");
		varMap.root->dump();
		vec.push_back(p);
		dump(vec);
		p = varMap.insert(L"CDE", L"InhaltCDE");
		vec.push_back(p);
		varMap.root->dump();
		dump(vec);
		p = varMap.insert(L"EFG", L"Inhalt2");
		vec.push_back(p);
		varMap.root->dump();
		dump(vec);
		p = varMap.insert(L"HIJ", L"Inhalt3");
		vec.push_back(p);
		varMap.root->dump();
		dump(vec);
		p = varMap.insert(L"KLM", L"Inhalt4");
		vec.push_back(p);
		varMap.root->dump();
		dump(vec);
		p = varMap.insert(L"XYZJJJ", L"Inhalt4");
		vec.push_back(p);
		varMap.root->dump();
		dump(vec);
		p = varMap.insert(L"Jupp", L"Inhalt4");
		vec.push_back(p);
		varMap.root->dump();
		dump(vec);
		p = varMap.insert(L"Irmgard", L"Inhalt4");
		vec.push_back(p);
		varMap.root->dump();
		dump(vec);
		p = varMap.insert(L"Martin", L"Inhalt4");
		vec.push_back(p);
		varMap.root->dump();
		dump(vec);
		p = varMap.insert(L"Birgit", L"Inhalt4");
		vec.push_back(p);
		varMap.root->dump();
		dump(vec);
		p = varMap.insert(L"Heike", L"Inhalt4");
		vec.push_back(p);
		varMap.root->dump();
		dump(vec);
		p = varMap.insert(L"Bernadette", L"Inhalt4");
		vec.push_back(p);
		varMap.root->dump();
		dump(vec);
		p = varMap.insert(L"ABCDEFG", L"Inhalt4");
		vec.push_back(p);
		varMap.root->dump();
		dump(vec);
		p = varMap.insert(L"12345", L"Inhalt4");
		vec.push_back(p);
		varMap.root->calcWeight();
		varMap.root->dump();
		dump(vec);
		BTree<String, String>::BTN * node = varMap.find(L"EFG");
		wprintf(L"<%s>\n",node != nullptr ? (const wchar_t*)node->value:nullptr);
		Dump(varMap.root);
		for (BTree<String, String>::BTN node : varMap)
		{
			node.dump();
			wprintf(L"\n");
		}
		return;
	}
};

int wmain(int argc, wchar_t ** argv) {
	TesterOctober program;
	wprintf(L"%s", pszOctober);
	if(program.evalArgs(argc,argv) ) {
		return program.run();
	}
	else {
		program.help();
	}
	return 0;
}
