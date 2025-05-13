// Comment/uncomment the next line to choose whether to use STL functionality
//#define USE_STL

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "constants.h"

using namespace std;



#ifdef USE_STL


// #include <map>
#include <unordered_map>
#include <deque>

typedef deque<string> Prefix;

typedef vector<string> Suffixes;
//typedef deque<string> Suffixes;


class PrefixHashFunction {
public:
	size_t operator()(const Prefix& p) const
	{
		string concatenated_prefix = "";
		for (int i = 0; i < p.size(); i++) {
			concatenated_prefix += p[i];
		}

		std::hash<std::string> hasher;
		return hasher(concatenated_prefix);

	}
};

// map<Prefix, vector<string>> statetab; // maps prefix to suffixes
unordered_map<Prefix, Suffixes, PrefixHashFunction> statetab; // maps prefix to suffixes


#else


#include "custom_classes.hpp"

typedef SuffixList Suffixes;

StateTab statetab(DEFAULTNHASH); // maps prefix to suffixes


#endif



// enum {NPREF= 2, MAXGEN = 10000, MULTIPLIER = 31, DEFAULTNHASH = 4093};


char NONWORD[] = "XXXXXXXXXX";


// add: add word to suffix list, update prefix
void add(Prefix& prefix, const string& s)
{
	if (prefix.size() == NPREF) {
		#ifdef USE_STL
		statetab[prefix].push_back(s);
		#else
		// custom SuffixList objects do not support push_back
		statetab[prefix].push_front(s);
		#endif

		prefix.pop_front();
	}
	prefix.push_back(s);
}


// build: read input words, build state table
void build(Prefix& prefix, istream& in)
{
	string buf;

	while (in >> buf)
		add(prefix, buf);

}


// generate: produce output, one word per line
void generate(int nwords) {
	Prefix prefix;
	int i;
	for (i = 0; i < NPREF; i++) // reset initial prefix
		add(prefix, NONWORD);
	for (i = 0; i < nwords; i++) {
		Suffixes suf = statetab[prefix];
		const string& w = suf[rand() % suf.size()];
		if (w == NONWORD)
			break;
		cout << w << "\n";
		prefix.pop_front();
		prefix.push_back(w);
	}
}


// main: markov-chain random text generation
int main(void)
{
	int nwords = MAXGEN;
	Prefix prefix;

	for (int i = 0; i < NPREF; i++) // set up initial prefix
		add(prefix, NONWORD);


	ifstream file("../section_3_4/InSearchOfLostTime.txt"); // std::ifstream is a derived class of std::istream
	build(prefix, file);

	add(prefix, NONWORD);
	generate(nwords);


	return 0;
}

