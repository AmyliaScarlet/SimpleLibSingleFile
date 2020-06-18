#include "pch.h"
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::list;
using std::vector;
using std::remove;
using std::find;
using std::iterator;
using std::nullptr_t;
using std::map;

template<class TK> class KeyCollection : public list<TK>
{
private:
	typename KeyCollection<TK>::iterator itor;
public:
	KeyCollection() 
	{
	}
	bool Contains(TK key)
	{	
		for (itor = this->begin(); itor != this->end(); itor++)
		{
			if (*itor == key)
			{
				return true;
			}
		}
		return false;
	}
	typename KeyCollection<TK>::iterator Iterator() {
		return this->itor;
	}
	~KeyCollection() {
		this->clear();
	}
};

template<class TV> class ValueCollection : public list<TV>
{
private:
	typename ValueCollection::iterator itor;
public:
	ValueCollection(){	
	}
	bool Contains(TV value)
	{
		for (itor = this->begin(); itor != this->end(); itor++)
		{
			if (*itor == value)
			{
				return true;
			}
		}
		return false;
	}
	typename ValueCollection::iterator Iterator() {
		return this->itor;
	}
	~ValueCollection() {
		this->clear();
	}
};

template<class TK, class TV> class KeyValuePair 
{
private:
	TK key;
	TV value;
public:
	KeyValuePair(TK k, TV v)
	{
		this->key = k;
		this->value = v;
	}
	KeyValuePair()
	{
	}
	void setKey(TK k) {
		this->key = k;
	}
	void setValue(TV v) {
		this->value = v;
	}

	TK getKey() {
		return this->key;
	}
	TV getValue() {
		return this->value;
	}
	void Print()
	{
		cout << this->key << " -> " << this->value << endl;
	}
	~KeyValuePair()
	{
		key = TK();
		value = TV();
	}
};

template<class TK, class TV> class Dictionary : public map<TK, TV>
{
private:
	list<KeyValuePair<TK, TV>> dic;
	typename list<KeyValuePair<TK, TV>>::iterator itor;
	int length;
	KeyCollection<TK> kcollect;
	ValueCollection<TV> vcollect;

public:
	Dictionary(int length = 0)
	{
		if (length < 0)
			length = 0;
		this->dic.resize(length);
		this->length = length;
	}
	typename list<KeyValuePair<TK, TV>>::iterator Iterator() {
		return itor;
	}
	void ForEachPrint()
	{
		for (itor = dic.begin(); itor != dic.end(); itor++)
		{
			TK key = itor->getKey();
			if (key != TK() && &key != nullptr)
				cout << itor->getKey() << " -> " << itor->getValue() << endl;
		}
	}
	void Add(KeyValuePair<TK, TV> kvp)
	{
		this->length++;
		this->dic.resize(this->length);
		this->dic.push_back(kvp);
		kcollect.push_back(kvp.getKey());
		vcollect.push_back(kvp.getValue());
	}
	void Remove(KeyValuePair<TK, TV> kvp)
	{
		for (itor = dic.begin(); itor != dic.end(); itor++)
		{
			if (itor->getKey() == kvp.getKey()) {
				kcollect.remove(kvp.getKey());
				vcollect.remove(kvp.getValue());
				itor = dic.erase(itor);
				this->length--;
				break;
			}
		}
	}
	bool ContainsKey(TK key) 
	{
		return kcollect.Contains(key);
	}
	bool ContainsValue(TV value)
	{
		return vcollect.Contains(value);
	}
	KeyCollection<TK> KeyCollection()
	{
		return kcollect;
	}
	ValueCollection<TV> ValueCollection()
	{
		return vcollect;
	}
	TV operator[](TK key)
	{
		for (itor = dic.begin(); itor != dic.end(); itor++)
		{
			if (itor->getKey() == key)
				return itor->getValue();
		}
		return TV();
	}
	TV GetValue(TK key)
	{
		for (itor = dic.begin(); itor != dic.end(); itor++)
		{
			if (itor->getKey() == key)
				return itor->getValue();
		}
		return TV();
	}
	int Count()
	{
		return this->length;
	}
	~Dictionary()
	{
		dic.clear();
		this->length = 0;
	}
};
