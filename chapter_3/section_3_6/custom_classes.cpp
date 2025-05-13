#include "custom_classes.hpp"

enum {MULTIPLIER = 31};


Prefix::Prefix()
{
	first = NULL;
	last = NULL;
	nval = 0;
}

Prefix::Prefix(string s, int n)
{	
	nval = n;
	WordNode *nodep = new WordNode;
	first = nodep;
	for (int i = 1; i < n; i++) {
		WordNode *next_nodep = new WordNode;
		nodep->next = next_nodep;
		nodep = next_nodep;
	}
	last = nodep;
}

Prefix::Prefix(const Prefix& prefix)
{	
		nval = 0;
		WordNode *nodep = prefix.first;
		WordNode *new_nodep;
		if (nodep) {
			new_nodep = new WordNode;
			new_nodep->word = nodep->word;
			new_nodep->next = NULL;
			first = new_nodep;
			nval++;

			while (nodep->next) {
				WordNode *new_next = new WordNode;
				new_next->word = nodep->next->word;
				new_next->next = NULL;
				
				new_nodep->next = new_next;

				nodep = nodep->next;
				new_nodep = new_next;
				nval++;
			}
			last = new_nodep;

		} else {
			first = NULL;
			last = NULL;
		}

	}

void Prefix::push_back(string s)
{
	WordNode *nodep = new WordNode;
	nodep->word = s;
	nodep->next = NULL;
	
	if (last)
		last->next = nodep;
	else 
		first = nodep;

	last = nodep;
	nval++;
}

void Prefix::pop_front()
{
	WordNode *oldFirst = first;
	first = first->next;
	nval--;
	delete oldFirst;
}

bool Prefix::operator==(const Prefix& prefix) const
{
	WordNode *nodep1 = first;
	WordNode *nodep2 = prefix.first;
	for (int i = 0; i < NPREF; i++) {
		if (nodep1->word != nodep2->word)
			return false;
		nodep1 = nodep1->next;
		nodep2 = nodep2->next;
	}
	return true;
}


void SuffixList::push_front(string s)
	{
		WordNode *nodep = new WordNode;
		nodep->word = s;
		nodep->next = first;
		first = nodep;
		nval++;
	}


string SuffixList::operator[](int m) const
{
	WordNode *nodep = first;
	for (int i = 0; i < m; i++)
		nodep = nodep->next;
	return nodep->word;
}


StateTab::StateTab(int nhash)
{
	this->nval = 0;
	this->nhash = nhash;

	State **empty_table = new State*[nhash];
	for (int i = 0; i < nhash; i++) {
		empty_table[i] = NULL;
	}
	this->tablep = empty_table;

}


// note it return a reference to the object in the table, rather than a copy
SuffixList& StateTab::operator[](const Prefix& prefix)
{
	State *sp;

	int h = hash(prefix);
	for (sp = tablep[h]; sp != NULL; sp=sp->next) {
		if (prefix == sp->pref)
			return sp->suf;
	}
	
	// always create if not present
	sp = new State(prefix);
	sp->next = tablep[h];
	tablep[h] = sp;
	nval++;

	return sp->suf;

}


unsigned int StateTab::hash(const Prefix& prefix) const
{
	unsigned int h = 0;
	for (WordNode *nodep = prefix.front(); nodep != NULL; nodep = nodep->next) {
		string s = nodep->word;
		for (int i = 0; i < s.size(); i++) {
			h = h * MULTIPLIER + (unsigned char) s[i];
		}
	}

	return h % nhash;
}

