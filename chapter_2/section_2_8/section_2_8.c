#include <stdlib.h>
#include <stdio.h>
#include <libc.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>


typedef struct Nameval Nameval;
struct Nameval {
	char *name;
	int value;
	Nameval *left; /* lesser */
	Nameval *right; /* greater */
};


/* insert: insert newp in treep, return treep */
Nameval *insert(Nameval *treep, Nameval *newp)
{
	int cmp;

	if (treep == NULL)
		return newp;
	cmp = strcmp(newp->name, treep->name);
	if (cmp == 0)
		printf("insert: duplicate entry %s ignored",newp->name);
		// weprintf("insert: duplicate entry %s ignored",newp->name);
	else if (cmp < 0)
		treep->left = insert(treep->left, newp);
	else
		treep->right = insert(treep->right, newp);
	return treep;
}


/* lookup: look up name in tree treep */
Nameval *lookup(Nameval *treep, char* name)
{
	int cmp;

	if (treep == NULL)
		return NULL;
	cmp = strcmp(treep->name, name);
	if (cmp == 0)
		return treep;
	else if (cmp > 0)
		return lookup(treep->left, name);
	else
		return lookup(treep->right, name);
}


/* nrlookup: non-recursively look up name in tree treep */
Nameval *nrlookup(Nameval *treep, char* name)
{
	int cmp;

	while(treep != NULL) {
		cmp = strcmp(treep->name, name);
		if (cmp == 0)
			return treep;
		else if (cmp > 0)
			treep = treep->left;
		else
			treep = treep->right;
	}
	return NULL;
}


/* applyinorder: inorder application of fn to treep */
void applyinorder(Nameval *treep, void (*fn)(Nameval*, void*),void *arg)
{
	if (treep == NULL)
		return;
	applyinorder(treep->left, fn, arg);
	(*fn)(treep, arg);
	applyinorder(treep->right, fn, arg);
}


/* postorder: postorder application of fn to treep */
void applypostorder(Nameval *treep, void (*fn)(Nameval*, void*),void *arg)
{
	if (treep == NULL)
		return;
	applypostorder(treep->left, fn, arg);
	applypostorder(treep->right, fn, arg);
	(*fn)(treep, arg);

}


/* newitem: create new item from name and value */
Nameval *newitem(char *name, int value)
{
	Nameval *newp;

	newp = (Nameval *) malloc(sizeof(Nameval));
	newp->name = name;
	newp->value = value;
	newp->left = NULL;
	newp->right = NULL;
	return newp;
}


/* printnv: print name and value using format in arg */
void printnv(Nameval *p, void *arg)
{
	char *fmt;
	fmt = (char *) arg;
	printf(fmt, p->name, p->value);
}


/* arrayswap: swaps the elements at two positions in an array*/
void arrayswap(Nameval *a, int i, int j) 
{
	Nameval temp = a[i];

	a[i] = a[j];
	a[j] = temp;

}


/* examplearray: create an array of length N of unique items randomly ordered*/
Nameval *examplearray(int N) 
{

	Nameval *a = (Nameval *) malloc(N * sizeof(Nameval));

	for (int i = 0; i < N; i++) {

		int name_length = 
			4 /* chars in "name" */ + 
			(int) log10(N - 1) /* number digits*/ + 
			1 /* terminating char */ + 
			1 /* to be safe*/;
		char *name = malloc(name_length * sizeof(char));
		sprintf(name, "name%d", i);

		a[i].name=name;
		a[i].value=i;


	}

	for (int i = 0; i < N; i++) {
		arrayswap(a, i, rand() % (N - 1)); // randomize array
	}

	return a;

}


/*
treefromarray: constructs a binaru search tree from the elements in an arrat
*/
Nameval *treefromarray(Nameval *a, int N) 
{
	Nameval *treep = NULL;


	for (int i = 0; i < N; i++) {
		Nameval * p = newitem(a[i].name,a[i].value);
		treep = insert(treep, p);
		/*
		avoiding to make a copy of the elements in the array wouldn't be so trivial, 
		because later on while filling the sortnved array, the tree structure
		must be preserved until completely done. 
		*/
	}

	return treep;
}


/*
assignelement: takes a memory location arg that holds another memory location whose value will be assigned elem, 
and it moves the memory location held by arg to the next position.
*/
void assignelement(Nameval *elem, void *arg)
{
	Nameval ** p = (Nameval **) arg; // points to a memory location whose value is to be modified

	(**p) = *elem;
	/*here, assigning the element from the tree will have the side effect of having modified the left */

	(*p)++; // move on to the next location whose value will be modified next time


}


/*
sortnv: sorts an array of Namevalue elements
*/
void sortnv(Nameval *a, int N)
{
	Nameval *treep = treefromarray(a, N);

	Nameval ** p = (Nameval **) malloc(sizeof(Nameval **));
	*p = a; // the first value to be modified will be in the address of the first array element

	applyinorder(treep, assignelement, p);
}


/*
nvcmp: compare two Nameval names
*/
int nvcmp(const void *va, const void *vb)
{
	const Nameval *a, *b;

	a = (Nameval *) va;
	b = (Nameval *) vb;

	return strcmp(a->name, b->name);
}



int main() {


	const unsigned int N = 500000;

	srand(123);
	Nameval *randomarray = examplearray(N);


	// printf("Generating example tree with %d nodes...\n", N);
	// Nameval *randomtreep = treefromarray(randomarray, N);
	// printf("Completed generating example tree.\n");


	// applyinorder(randomtreep, printnv, "%s: %d\n");

	Nameval* res;
	clock_t t;


	// printf("------TEST 1------\n");
	// t = clock();
	// res = lookup(randomtreep,randomarray[1000].name);
	// t = clock() - t;
	// double time_taken = ((double) t / CLOCKS_PER_SEC);
	// printf("success? %d\n",res->name==randomarray[1000].name);
	// printf("lookup took %f seconds to execute \n", time_taken);

	// t = clock();
	// res = nrlookup(randomtreep,randomarray[1000].name);
	// t = clock() - t;
	// double time_taken = ((double) t / CLOCKS_PER_SEC);
	// printf("success? %d\n",res->name==randomarray[1000].name);
	// printf("nrlookup took %f seconds to execute \n", time_taken); 

	// printf("\n-------------\n");



	// printf("------TEST 2------\n");
	// t = clock();
	// res = lookup(randomtreep,randomarray[80000].name);
	// t = clock() - t;
	// double time_taken = ((double) t / CLOCKS_PER_SEC);
	// printf("success? %d\n",res->name==randomarray[80000].name);
	// printf("lookup took %f seconds to execute \n", time_taken);

	// t = clock();
	// res = nrlookup(randomtreep,randomarray[80000].name);
	// t = clock() - t;
	// double time_taken = ((double) t / CLOCKS_PER_SEC);
	// printf("success? %d\n",res->name==randomarray[80000].name);
	// printf("nrlookup took %f seconds to execute \n", time_taken); 

	// printf("\n-------------\n");



	// printf("------TEST 3------\n");
	// t = clock();
	// res = lookup(randomtreep,randomarray[N-1].name);
	// t = clock() - t;
	// double time_taken = ((double) t / CLOCKS_PER_SEC);
	// printf("success? %d\n",res->name==randomarray[N-1].name);
	// printf("lookup took %f seconds to execute \n", time_taken);

	// t = clock();
	// res=nrlookup(randomtreep,randomarray[N-1].name);
	// t = clock() - t;
	// double time_taken = ((double) t / CLOCKS_PER_SEC);
	// printf("success? %d\n",res->name==randomarray[N-1].name);
	// printf("rlookup took %f seconds to execute \n", time_taken); 
	// printf("\n-------------\n");


	// printf("\noriginal array:\n");	
	// for (int i = 0; i < N; i++) {
	// 	printf("%d\n",randomarray[i].value);
	// }

	// t = clock();
	// sortnv(randomarray, N);
	// t = clock() - t;
	// double time_taken = ((double) t / CLOCKS_PER_SEC);
	// // printf("success? %d\n",res->name==randomarray[N-1].name);
	// printf("sortnv took %f seconds to execute \n", time_taken); 
	// printf("\n-------------\n");



	t = clock();
	qsort(randomarray, N, sizeof(randomarray[0]), nvcmp);
	t = clock() - t;
	double time_taken = ((double) t / CLOCKS_PER_SEC);
	printf("qsort took %f seconds to execute \n", time_taken); 
	printf("\n-------------\n");



	// printf("\nsorted array:\n");
	// for (int i = 0; i < N; i++) {
	// 	printf("%d\n",randomarray[i].value);
	// }

}
