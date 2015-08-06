#pragma once
#include "October/String.h"
#include "October/Stack.h"
namespace Seasons
{
	class InternalException
	{

	};
	template<typename KEY> class less
	{
	public:
		bool operator()(const KEY& keyLeft, const KEY & keyRight)
		{
			return keyLeft < keyRight;
		}
	};
	template <typename KEY, typename VALUE,typename COMPARATOR=less<KEY>> class BTree
	{
	public:
		COMPARATOR comp;
		enum StateColor
		{
			BLACKBLACK = -2,
			BLACK = -1,
			NONE = 0,
			RED = 1,
			REDRED = 2,
		};
		class BTN
		{
		public:
			StateColor color = NONE;
			BTN * black = nullptr;
			BTN * red = nullptr;
			int weight = 1;
			KEY		key;
			VALUE	value;
			BTN(const KEY & key, const VALUE & value) :key(key), value(value)
			{

			}
			void dump() const
			{
				wprintf(L"c=%s %p red=%p;black=%p;<%s>\t<%s><%s>(%d)\n",
					color == BLACK ? L"BLACK" : color == RED ? L"RED  " :
					color == NONE ? L"NONE " : L"XXXXX", this, red, black,
					(const wchar_t*)key, red == nullptr ? nullptr : (const wchar_t*)red->key,
					black == nullptr ? nullptr : (const wchar_t*)black->key,weight);
			}
			BTN * find(const KEY & key)
			{
				if (COMPARATOR()(key, this->key))
					return red != nullptr ? red->find(key) : red;
				else if (COMPARATOR()(this->key, key))
					return black != nullptr ? black->find(key) : black;
				else
					return this;

			}
			int getWeight()
			{
				return weight ;
			}
			int calcWeight()
			{
				weight = 1;
				if (black != nullptr)
					weight += black->calcWeight();
				if (red != nullptr)
					weight += red->calcWeight();
				return weight;
			}
			void setOnlyColorRecursively()
			{
				int blackWeight = black == nullptr ? 0 : black->getWeight();
				int redWeight = red == nullptr ? 0 : red->getWeight();
				if (blackWeight > redWeight)
					color = BLACK;
				else if (redWeight > blackWeight)
					color = RED;
				else
					color = NONE;
				if (black != nullptr)
					black->setOnlyColorRecursively();
				if (red != nullptr)
					red->setOnlyColorRecursively();
			}
			void setColor()
			{
				calcWeight();
				int blackWeight = black == nullptr ? 0 : black->getWeight();
				int redWeight = red == nullptr ? 0 : red->getWeight();
				if(blackWeight > redWeight)
					color = BLACK;
				else if (redWeight > blackWeight)
					color = RED;
				else
					color = NONE;
			}
			void reset()
			{
				black = nullptr;
				red = nullptr;
				color = NONE;
				weight = 1;
			}
		};
		BTN * replace(BTN*&where, BTN*node)
		{
			BTN * old = where;
			bool both = true;
			if (where->black != node)
			{
				node->black = where->black;
			}
			else
				both = false;
			if (where->red != node)
			{
				node->red = where->red;
			}
			else
				both = false;
			where = node;
			where->setColor();
			old->reset();
			return old;
		}
		BTN *findLeftest(BTN*node)
		{
			if (node == nullptr)
				throw InternalException();
			if (node->red == nullptr)
				return node;
			return findLeftest(node->red);
		}
		BTN *findRightest(BTN*node)
		{
			if (node == nullptr)
				throw InternalException();
			if (node->black == nullptr)
				return node;
			return findRightest(node->black);
		}
		BTN * findLeftestRight(BTN*&where)
		{
			if (where->black == nullptr)
				throw InternalException();
			return findLeftest(where->black);
		}
		BTN * findRightestLeft(BTN*&where)
		{
			if (where->red == nullptr)
				throw InternalException();
			return findRightest(where->red);
		}
		BTN *findCutLeftest(BTN*node)
		{
			if (node == nullptr)
				throw InternalException();
			if (node->red == nullptr)
				throw InternalException();
			if (node->red->red == nullptr)
			{
				BTN * red = node->red;
				node->red = nullptr;
				node->setColor();
				return red;
			}
			BTN * ret = findCutLeftest(node->red);
			
			return ret;
		}
		BTN *findCutRightest(BTN*node)
		{
			if (node == nullptr)
				throw InternalException();
			if (node->black == nullptr)
				throw InternalException();
			if (node->black->black == nullptr)
			{
				BTN * black = node->black;
				node->black = nullptr;
				node->setColor();
				return black;
			}
			BTN * ret =  findCutRightest(node->black);
			
			return ret;
		}
		BTN * findCutLeftestRight(BTN*&where)
		{
			if (where->black == nullptr)
			{
				throw InternalException();
			}
			if (where->black->red == nullptr)
			{
				BTN * red = where->black;
				where->black = nullptr;
				where->setColor();
				return red;
			}
			return findCutLeftest(where->black);
		}
		BTN * findCutRightestLeft(BTN*&where)
		{
			if (where->red == nullptr)
			{
				throw InternalException();
			}
			if (where->red->black == nullptr)
			{
				BTN * red = where->red;
				where->red = nullptr;
				where->setColor();
				return red;
			}
			return findCutRightest(where->red);
		}
		void insertLeftest(BTN*&where, BTN*node)
		{
			if (where->red == nullptr)
			{
				node->color = NONE;
				node->black = nullptr;
				node->red = nullptr;
				where->red = node;
				if(where->color == NONE)
					where->color = RED;
				else if (where->color == BLACK)
					where->color = NONE;
				else
					throw InternalException();
			}
			else
			{
				if (where->color == NONE)
					where->color = RED;
				else if (where->color == BLACK)
					where->color = NONE;
				else if(where->color == RED)
				{
					BTN * inode = findCutRightestLeft(where);
					BTN * old = replace(where, inode);
					if (where->black == nullptr)
					{
						where->black = old;
					}
					else
					{
						where->black->setColor();
						insertLeftest(where->black, old);
					}
					where->setColor();
					insertLeftest(where, node);
					return;
				}
				insertLeftest(where->red, node);
			}

		}
		void insertRightest(BTN*&where, BTN*node)
		{
			if (where->black == nullptr)
			{
				node->color = NONE;
				node->black = nullptr;
				node->red = nullptr;
				where->black = node;
				if (where->color == NONE)
					where->color = BLACK;
				else if (where->color == RED)
					where->color = NONE;
				else
					throw InternalException();
			}
			else
			{
				if (where->color == NONE)
				where->color = BLACK;
				else if (where->color == RED)
				where->color = NONE;
				else if (where->color == BLACK)
				{
					BTN * inode = findCutLeftestRight(where);

					BTN * old = replace(where, inode);
					if (where->red == nullptr)
					{
						where->red = old;
					}
					else
					{
						insertRightest(where->red, old);
					}
					insertRightest(where, node);
					return;
				}
				insertRightest(where->black, node);
			}

		}

		BTN * insert(BTN*&where,const KEY &key,const VALUE &value)
		{
			where->setColor();
			if (comp(key, where->key))
			{
				if (where->color == RED)
				{
					BTN * node = findRightestLeft(where);
					if (comp(node->key, key))
					{
						//BTN * oldblack = where->black;
						BTN * ret = new BTN(key, value);
						BTN * old = replace(where, ret);
						if (where->black == nullptr)
						{
							where->black = old;
						}
						else
							insertLeftest(where->black, old);
						ret->calcWeight();
						return ret;
					}
					else if (comp(key, node->key))
					{
						BTN * oldblack = where->black;
						BTN * oldred = where->red;
						node = findCutRightestLeft(where);
						BTN * old = replace(where, node);
						if (where->black == nullptr)
						{
							where->black = old;
						}
						else
						{
							insertLeftest(where->black, old);
						}
						if (where->red == nullptr)
						{
							where->red = new BTN(key, value);
							return where->red;
						}
						return insert(where->red,key, value);
						
					}
					else
					{
						node->value = value;
					}
				}
				if (where->color == NONE)
				{
					where->color = RED;
				}
				else if (where->color == BLACK)
				{
					where->color = NONE;
				}
				if (where->red == nullptr)
				{
					where->red = new BTN(key, value);
					
					return where->red;
				}
				BTN * ret = insert(where->red,key,value);
				
				return ret;
				
			}
			else if (comp(where->key, key))
			{
				if (where->color == BLACK)
				{
					BTN * node = findLeftestRight(where);
					if (comp(key, node->key))
					{
						//BTN * oldblack = where->black;
						BTN * ret = new BTN(key, value);
						BTN * old = replace(where, ret);
						if (where->red == nullptr)
						{
							where->red = old;
						}
						else
						{
							insertRightest(where->red, old);
						}
					
						return ret ;
					}
					else if (comp(node->key,key))
					{
						node = findCutLeftestRight(where);
						BTN * old = replace(where, node);
						if (where->red == nullptr)
						{
							where->red = old;
						}
						else
						{
							insertRightest(where->red, old);
						}
						if (where->black == nullptr)
						{
							where->black = new BTN(key, value);
							return where->black;
						}
						return insert(where->black, key, value);
						
					}
					else
					{
						node->value = value;
						return node;
					}
				}
				if (where->color == NONE)
				{
					where->color = BLACK;
				}
				else if (where->color == RED)
				{
					where->color = NONE;
				}
				if (where->black == nullptr)
				{
					where->black = new BTN(key, value);
					return where->black;
				}
				return insert(where->black, key, value);
				
			}
			else
			{
				where->value = value;
				return where;
			}
		}
		
		BTN * root = nullptr;
	
		BTN * insert(const KEY & key, const VALUE &value)
		{
			if (root == nullptr)
			{
				root = new BTN(key, value);
				return root ;
			}
			BTN * ret = insert(root,key, value);
			root->calcWeight();
			root->setOnlyColorRecursively();
			return ret;
		}
	
		BTN * find(const KEY &key)
		{
			return root->find(key);
		}
		class iterator
		{
		public:
			BTN*&root;
			BTN*pBegin = nullptr;
			Stack<BTree<String, String>::BTN*> arBTN;

			iterator(BTN*&root) :root(root)
			{
				
			}
			iterator begin()
			{
				
				pBegin = root;
				
				while (pBegin->red)
				{
					arBTN.push(pBegin);
					pBegin = pBegin->red;
					
				}
				return *this;

			}
			bool operator==(const iterator&iter)const
			{
				return pBegin == iter.pBegin;
			}
			BTN*operator->()
			{
				return pBegin;
			}
			BTN& operator*()
			{
				return *pBegin;
			}
			operator BTN*()
			{
				return pBegin;
			}
			iterator operator++()
			{
				if (pBegin && pBegin->black)
				{
					pBegin = pBegin->black;
					while (pBegin->red)
					{
						arBTN.push(pBegin);
						pBegin = pBegin->red;
					}
				}
				else if (!arBTN.isEmpty())
					pBegin = arBTN.pop();
				else
					pBegin = nullptr;
				return *this;
			}
		};
		class iterator begin()
		{
			iterator it(this->root);
			it.begin();
			return it;
		}
		class iterator end()
		{
			iterator it(root);
			return it;
		}
	};

}
