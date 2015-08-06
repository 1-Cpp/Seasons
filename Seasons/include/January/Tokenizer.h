#pragma once


namespace Seasons
{

class String;
class Tokenizer
{
protected:
	const String& source;
public:
	
	Tokenizer(const String&source);
	virtual ~Tokenizer();
	virtual bool tokenize();
};

}
