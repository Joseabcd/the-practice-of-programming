#include <string>
#include "constants.h"

using namespace std;


class WordNode {
public:
	string word;
	WordNode *next;
};


class Prefix {
private:
	WordNode *first;
	WordNode *last;
	int nval;

public:
	Prefix();

	Prefix(string s, int n);

	Prefix(const Prefix& prefix);


	unsigned int size() const 
	{
		return nval;
	}

	WordNode * front() const 
	{
		return first;
	}

	WordNode * back() const 
	{
		return last;
	}

	void push_back(string s);


	void pop_front();
	

	bool operator==(const Prefix& prefix) const;


};


// for the suffixes can define a list that only supports pushing on one end;
// this spares the need to keep track of its last element, saving a bit of space.
class SuffixList {
private:
	WordNode *first;
	int nval;

public:
	SuffixList()
	{	
		first = NULL;
		nval = 0;
	}

	unsigned int size() const
	{
		return nval;
	}

	WordNode * front() const
	{
		return first;
	}

	void push_front(string s);

	string operator[](int m) const;

};


class State {
public:
	Prefix pref;
	SuffixList suf;
	State *next; // next in its hash table bucket

	State(const Prefix& prefix):pref(prefix)
	{
		next=NULL;
	}
};


class StateTab {
public:
	int nval;
	int nhash;
	State **tablep;

	StateTab(int nhash);

	SuffixList& operator[](const Prefix& prefix);

private:
	unsigned int hash(const Prefix& prefix) const;

};
