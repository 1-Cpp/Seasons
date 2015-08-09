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
class TesterOctober : public Main {
public:
	BTree<String, String> varMap;

	std::vector<const BTree<String, String>::BTN *> vec;
	int run() {
		arraylist();
		btree();
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
