#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../section_2_9/table.h"
#include <math.h>


enum { MULTIPLIER = 31, x = 5, y = 2};


/* stringhash: compute the hash value of string */
static unsigned int stringhash(char *str, int nhash)
{
	unsigned int h;
	unsigned char *p;

	h = 0;
	for (p = (unsigned char *) str; *p != '\0'; p++) {
		h = h * MULTIPLIER + *p;
	}
	return h % nhash;
}


/*get: access the i-th element in symtab*/
static Nameval *get(NVsymtab *symtabp, int i)
{	
	int element_position = 0;

	for (int k = 0; k < symtabp->nhash; k++){
		for (Nameval *p = (symtabp->tablep)[k]; p != NULL; p = p->next){
			if (element_position == i) 
				return p;
			element_position++;
		}
	}

	return NULL;

}


/* grow: reallocate the input symtabp into a a new array of buckets of size newnhash */
static NVsymtab *grow(NVsymtab * symtabp, int newnhash)
{

	Nameval* aux[symtabp->nval];
	for (int i = 0; i < symtabp->nval; i++) {
		aux[i]=get(symtabp,i);
	}

	Nameval **p = (Nameval **) malloc((symtabp->nhash * y) * sizeof(Nameval*));
	if (p == NULL) return NULL;
	symtabp->nhash *= y;

	for (int i = 0; i < symtabp->nval; i++) {
		Nameval *sym = aux[i];
		int h = stringhash(sym->name, symtabp->nhash);
		p[h]=list_ops.addfront(p[h],sym);
	}

	free(symtabp->tablep);
	symtabp->tablep = p;

	return symtabp;

}


/* lookup: find name in symbtab, with optional create, growing the array if the
average list length becomes more than x */
static Nameval* lookup(NVsymtab *symtabp, char *name, int create, int value)
{
	int h;
	Nameval *sym;

	h = stringhash(name, symtabp->nhash);
	for(sym = (symtabp->tablep)[h]; sym != NULL; sym = sym->next) {
		if (strcmp(name, sym->name) == 0)
			return sym;
	}

	if (create) {

		sym = (Nameval *) malloc(sizeof(Nameval*)); // revise this: shouldn't it be sizeof(Nameval)???
		sym->name = name; /* assumed allocated elsewhere */
		sym->value = value;
		sym->next = (symtabp->tablep)[h];
		(symtabp->tablep)[h] = sym;
		symtabp->nval++;


		if (((float) symtabp->nval / symtabp->nhash) > x)
			symtabp = grow(symtabp, symtabp->nhash * y);

	}

	return sym;
}


static NVsymtab *create_example(int n, int nhash) 
{

	srand(123);

	Nameval **example_table = (Nameval **) malloc(sizeof(Nameval*) * nhash);

	for (int i = 0; i < nhash; i++) {
		example_table[i] = NULL;
	}

	int count = 0;

	for (int i = 0; i < n; i++) {

		int random_integer = rand();

		int name_length = 
			4 /* chars in "name" */ + 
			(int)log10(random_integer == 0 ? 1 : random_integer) /* number of digits */ + 
			1 /* terminating char */ + 
			1 /* to be safe */;

		char *name = malloc(name_length * sizeof(char));
		sprintf(name, "name%d", random_integer);

		int h = stringhash(name, nhash);

		example_table[h] = list_ops.addend(example_table[h], list_ops.newitem(name, random_integer));

		count++;
	}
	
	NVsymtab * symtabp = (NVsymtab *) malloc(sizeof(NVsymtab));
	symtabp->nval = n;
	symtabp->nhash = nhash;
	symtabp->tablep = example_table;

	return symtabp;

}


TableOps table_ops = {
	.stringhash=stringhash,
	.create_example=create_example,
	.lookup=lookup

};

