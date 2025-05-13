#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../section_2_7/list.h"
#include "../section_2_9/table.h"
// #include <math.h>
#include "time.h"


enum {
	NPREF = 2, /* number of prefix words*/
	DEFAULTNHASH = 4093, /* size to use when creating the state hash table array */
	MAXGEN = 10000, /* maximum words generated */
	MULTIPLIER = 31 /* to use in the function hash*/,
	WORDS_STORED_ONCE = 1 /* Has value of 0 or 1 indicating if words should be stored only once in a separate hash table*/
};

char NONWORD[] = "XXXXXXXXXX";	/* cannot appear as real word */


typedef struct Suffix Suffix;
struct Suffix { /* list of suffixes */
	char	*word;	/* suffix */
	Suffix *next;	/* next in list of suffixes*/
};



typedef struct State State;
struct State { /* prefix + suffix list*/
	char	*pref[NPREF];	/* prefix words*/
	Suffix	*suf;	/* list of suffixes */
	State	*next;	/* next in hash table */
};


typedef struct StateTab StateTab;
struct StateTab {
	int nval;
	int nhash;
	State **tablep;
};


typedef struct Address Address;
struct Address {
	char	*word;
	Address	*next;	/* next in hash table */
};


typedef struct AddressTab AddressTab;
struct AddressTab {
	int nval;
	int nhash;
	Address **tablep;
};


/* hash: compute hash value for array of NPREF strings */
unsigned int hash(char *array[NPREF], int nhash)
{
	unsigned int h;
	unsigned char *p;
	int i;

	h = 0;
	for (i = 0; i < NPREF; i++) {
		for (p = (unsigned char *) array[i]; *p != '\0'; p++) {
			h = MULTIPLIER * h + *p;
		}
	}

	return h % nhash;
}


static StateTab *create_empty(int nhash)
{
	StateTab *statetabp = (StateTab *) malloc(sizeof(StateTab));
	
	statetabp->nval = 0;
	
	statetabp->nhash = nhash;
	
	State **emptytablep = (State **) malloc(nhash*sizeof(State*));
	for (int i = 0; i < nhash; i++) {
		emptytablep[i] = NULL;
	}

	statetabp->tablep = emptytablep;

	return statetabp;
}


static AddressTab *create_empty_addresstab(int nhash)
{
	AddressTab *addresstabp = (AddressTab *) malloc(sizeof(AddressTab));
	
	addresstabp->nval = 0;
	
	addresstabp->nhash = nhash;
	
	Address **emptytablep = (Address **) malloc(nhash*sizeof(Address*));
	for (int i = 0; i < nhash; i++) {
		emptytablep[i] = NULL;
	}

	addresstabp->tablep = emptytablep;

	return addresstabp;
}


/* lookup: search for prefix; create if requested. */
/* returns pointer if present or created; NULL if not. */
/* creation doesn't strdup so strings mustn't change later. */
State *lookup(StateTab *statetabp, char *prefix[NPREF], int create)
{
	int i, h;
	State *sp;

	h = hash(prefix, statetabp->nhash);
	for (sp = (statetabp->tablep)[h]; sp != NULL; sp=sp->next) {
		for (i = 0; i < NPREF; i++) {
			int condition;
			if (WORDS_STORED_ONCE) 
				condition = prefix[i] != (sp->pref)[i]; // pointer address comparison
			else
				condition = strcmp(prefix[i], (sp->pref)[i]) != 0; // character-wise string comparison
			if (condition) 
				break;
		}
		if (i == NPREF)	/* found it */
			return sp;
	}
	if (create) {
		sp = (State *) malloc(sizeof(State));
		for (i = 0; i < NPREF; i++) {
			(sp->pref)[i] = prefix[i];
		}
		sp->suf = NULL;
		sp->next = (statetabp->tablep)[h];
		(statetabp->tablep)[h] = sp;
		(statetabp->nval)++;
	}
	return sp;
}


/* addresslookup: */
Address *addresslookup(AddressTab *addresstabp, char *word, int create)
{
	int i, h;
	Address *ap;

	h = table_ops.stringhash(word, addresstabp->nhash);
	for (ap = (addresstabp->tablep)[h]; ap != NULL; ap=ap->next) {
		if (strcmp(word, ap->word) == 0)	/* found it */
			return ap;
	}
	if (create) {
		ap = (Address *) malloc(sizeof(Address));
		//ap->word=word;
		ap->word=strdup(word);
		ap->next = (addresstabp->tablep)[h];
		(addresstabp->tablep)[h] = ap;
		(addresstabp->nval)++;
	}
	return ap;
}


/* addsufix: add to state. suffix must not change later */
void addsuffix(State *sp, char *suffix)
{
	Suffix *suf;

	suf = (Suffix *) malloc(sizeof(Suffix));
	suf->word = suffix;
	suf->next = sp->suf;
	sp->suf=suf;
}


/* add: add word to suffix list, and update prefix to next one. */
/* If prefix not already in statetabp, it adds a new state to the table.*/
void add(StateTab *statetabp, char *prefix[NPREF], char *suffix)
{
	State *sp;

	sp = lookup(statetabp, prefix, 1); /* create if not found */

	addsuffix(sp, suffix);
	/* move the words down the prefix */

	memmove(prefix, prefix+1, (NPREF - 1) * sizeof(prefix[0]));
	prefix[NPREF - 1] = suffix;

}


/* build: read input, build prefix table */
StateTab *build(char *prefix[NPREF], FILE *f)
{
	char buf[100], fmt[10];

	StateTab *statetabp = create_empty(DEFAULTNHASH);
	AddressTab *addresstabp;
	if (WORDS_STORED_ONCE)
		addresstabp = create_empty_addresstab(DEFAULTNHASH); // revise this: what nhash to use???

	/* create a format string; %s could overflow buf */
	sprintf(fmt, "%%%ds", sizeof(buf)-1);
	while (fscanf(f, fmt, buf) != EOF) {
		char *suffix;
		if (WORDS_STORED_ONCE)
			suffix = addresslookup(addresstabp, buf, 1)->word; // note buf is strdupped inside addresslookup if new item added to addresstabp
		else
			suffix = strdup(buf);
		add(statetabp, prefix, suffix);
	}

	return statetabp;
}


/* generate: produce output, one word per line */
void generate(StateTab *statetabp, int nwords)
{
	State *sp;
	Suffix *suf;
	char *prefix[NPREF], *w;
	int i, nmatch;

	for (i = 0; i < NPREF; i++)	/* reset initial prefix */
		prefix[i] = NONWORD;

	for (i = 0; i < nwords; i++) {
		sp = lookup(statetabp, prefix, 0);
		nmatch = 0;
		for (suf = sp->suf; suf != NULL; suf = suf->next)
			if (rand() % ++nmatch == 0)	/* prob = 1/nmatch */
				w = suf->word;
		if (strcmp(w, NONWORD) == 0)
			break;
		printf("%s\n",w);
		memmove(prefix,prefix+1, (NPREF - 1) * sizeof(prefix[0]));
		prefix[NPREF - 1] = w;
	}

}


/* markov main: markov-chain random text generation*/
int main()
{
	
	// srand(time(NULL));

	/*---------exercise 3-1 ---------*/
	/* to test the random number generator, check if the distribution of a set of 
	numbers randomly generated in this manner is close to being uniform */
	/*int nmax = 10;
	int nsample = 10000000;

	int counts[nmax];
	for (int i = 0; i < nmax; i++) {
		counts[i] = 0;
	}

	int nmatch, candidate, chosen;
	for (int k = 0; k < nsample; k++) {
		nmatch = 0;
		for (int i = 0; i < nmax; i++){
			if (rand() % ++nmatch == 0)
				candidate = i;
		}
		chosen = candidate;
		counts[chosen]++;
	}

	float absdiffs = 0.;
	int expectedcounts = nsample / nmax;
	for (int i = 0; i < nmax; i++) {
		printf("count: %d\n", counts[i]);
		absdiffs += abs(counts[i] - expectedcounts);
	}

	printf(
		"meanabsdiffs: %f, which should be a small number in comparison to expectedcounts: %d (meanabsdiffs/expectedcounts = %f)\n",
		absdiffs / nmax,
		expectedcounts,
		absdiffs / nmax / expectedcounts
	);
	*/


	int i, nwords = MAXGEN;
	char *prefix[NPREF];	/* current input prefix */


	for (i = 0; i < NPREF; i++)	/* set up initial prefix */
		prefix[i] = NONWORD;

	//FILE *filep=fopen("CompleteWorksOfWilliamShakespeare.txt","r");
	FILE *filep=fopen("InSearchOfLostTime.txt","r");

	clock_t build_start_clock = clock();
	StateTab *statetabp = build(prefix, filep);
	clock_t build_end_clock = clock();

	add(statetabp, prefix, NONWORD);

	clock_t generate_start_clock = clock();
	generate(statetabp, nwords);
	clock_t generate_end_clock = clock();
	
	
	double build_elapsed = (double)(build_end_clock - build_start_clock) / CLOCKS_PER_SEC;
	printf("Building took: %.3f seconds\n", build_elapsed);
	double generate_elapsed = (double)(generate_end_clock - generate_start_clock) / CLOCKS_PER_SEC;
	printf("Generation took: %.3f seconds\n", generate_elapsed);

	return 0;
}

