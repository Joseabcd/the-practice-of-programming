#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <libc.h>
#include <string.h>
#include <math.h>


/* newitem: create new item from name and value */
static Nameval *newitem(char *name, int value)
{
	Nameval *newp;

	// newp = (Nameval *) emalloc(sizeof(Nameval));
	newp = (Nameval *) malloc(sizeof(Nameval));
	newp->name = name;
	newp->value = value;
	newp->next = NULL;
	return newp;
}

/* addfront: add newp to front of listp */
static Nameval *addfront(Nameval *listp, Nameval *newp)
{
	newp->next = listp;
	return newp;
}

/* addend: add newp to end of listp */
static Nameval *addend(Nameval *listp, Nameval *newp)
{
	Nameval *p;

	if(listp == NULL)
		return newp;
	for (p = listp ; p->next != NULL; p = p->next)
		;
	p->next = newp;
	return listp;
}

/* lookup: sequential search for name in listp */
static Nameval *lookup(Nameval *listp, char *name)
{

	for( ; listp != NULL; listp = listp->next)
		if(strcmp(listp->name,name) == 0)
			return listp;
	return NULL;	/* no match */

}


/* apply: execute fn for each element of listp */
static void apply(Nameval *listp,
		void (*fn)(Nameval*, void*), void *arg)
	{
		for( ; listp != NULL; listp = listp->next)
			(*fn)(listp, arg); /* call the function */
	}


/* printnv: print name and value using format in arg */
static void printnv(Nameval *p, void *arg)
{
	char *fmt;
	fmt = (char *) arg;
	printf(fmt, p->name, p->value);
}


/* inccounter: increment counter arg */
static void inccounter(Nameval p, void *arg)
{
	int *ip;

	/* p is unused */
	ip = (int *) arg;
	(*ip)++;
}


/* freeall: free all elements of listp */
static void freeall(Nameval *listp)
{
	Nameval *next;

	for ( ; listp != NULL; listp = next) {
		next = listp->next;
		/* assumes name is freed elsewhere */
		free(listp);
	}
}


/* delitem: delete first name from listp */
static Nameval *delitem(Nameval *listp, char *name)
{
	Nameval *p, *prev;

	prev = NULL;
	for(p = listp; p != NULL; p = p->next) {
		if (strcmp(name,p->name) == 0) {
			if (prev == NULL)
				listp = p->next;
			else
				prev->next = p->next; /* bridge the gap left by the deletion*/
			free(p);
			return listp;
		}
		prev = p;
	}
	// eprintf("delitem: %s not in list", name);
	return NULL;	/* if using eprintf, can't get here */
}

/* copy: make a copy of listp and return the pointer to its first element */
static Nameval *copy(Nameval *listp)
{

	if(listp==NULL) return NULL;

	Nameval *newlistp;
	newlistp = NULL;

	newlistp=newitem(listp->name,listp->value);


	for (Nameval *p = listp->next; p != NULL; p = p->next) {
		Nameval *newp;
		newp = newitem(p->name,p->value);
		addend(newlistp,newp);
	}
	return newlistp;
}


/*merge: joins listp1 and listp2 (assumed in order) into one sorted list*/
static Nameval *merge(Nameval *listp1, Nameval *listp2)
{


	Nameval *listp = NULL;

	if (listp1 == NULL && listp2 == NULL) return listp;

	if(listp1 != NULL && listp2 == NULL){
		listp = listp1;
		listp->next = merge(listp1->next,listp2);
		return listp;
	}


	if(listp1 == NULL && listp2 != NULL){
		listp = listp2;
		listp->next=merge(listp1,listp2->next);
		return listp;
	}


	if(listp1->value < listp2->value) {
		listp=listp1;
		listp->next=merge(listp1->next,listp2);
	} else {
		listp = listp2;
		listp->next = merge(listp1,listp2->next);
	}

	return listp;
}


/* split: separate listp into two at the element matching name;
return the pointer to the second list, or NULL if name not found. */
static Nameval *split(Nameval *listp, char *name)
{

	Nameval *newHead = NULL;

	for( ; listp != NULL; listp = listp->next) {
		if(strcmp(listp->name,name) == 0) {
			newHead=listp->next;
			listp->next = NULL;
			return newHead;
		}
	}
	return newHead;	/* no match */
}

/* insertbefore: adds an item to listp placed before the first item matching name */
static Nameval *insertbefore(Nameval *listp, Nameval *newp, char *name) 
{
	Nameval *prev;

	prev = NULL;
	for (Nameval *p = listp; p != NULL; p = p->next) {
		if (strcmp(p->name, name) == 0) {
			if (prev == NULL) {
				return addfront(listp, newp);
			}
			else {
				prev->next = newp;
				newp->next = p;
				return listp;
			}
		}
		prev = p;
	}

	return listp;	/* name not found */
}

/* insertafter: adds an item to listp placed after the first item matching name */
Nameval *insertafter(Nameval *listp, Nameval *newp, char *name) 
{
	Nameval *p;

	p = lookup(listp, name);

	if (p != NULL) {
		newp->next = p->next;
		p->next = newp;
	}

	return listp;
}


Nameval *reverse_iteratively(Nameval *listp) 
{
	if (listp == NULL) return listp;
	
	Nameval *next = listp->next;

	listp->next = NULL; /* the head eventually will become the tail */

	for (Nameval *p = next; p != NULL; p = next){
		next = p->next;
		listp=addfront(listp, p);
	}

	return listp;

}


static Nameval *reverse_recursively(Nameval *listp) 
{	

	if (listp == NULL) return listp;

	if (listp->next == NULL) return listp;

	Nameval *next2 = (listp->next)->next;

	(listp->next)->next = listp;

	if (next2 == NULL) return listp->next;

	Nameval *res;
	res = reverse_recursively(next2);

	next2->next = listp->next;

	listp->next = NULL;

	return res;

}


static Nameval *create_example(int length)
{

	Nameval *listp = NULL;

	int name_length = 
		4 /* chars in "name" */ + 
		(int)log10(length) /* number digits */ + 
		1 /* terminating char */ + 
		1 /* to be safe */;

	for (int i = 0; i < length; i++) {

		char *name = malloc(name_length * sizeof(char));
		sprintf(name, "name%d", i);

		listp = addend(listp,newitem(name,i));

	}

	return listp;

}


bool are_equal(Nameval *listp1, Nameval *listp2)
{
	Nameval *p1 = listp1;
	Nameval *p2 = listp2;

	while (true) {

		if (p1 == NULL) {
			return p2 == NULL;
		}


		if (p2 == NULL) {
			return p1 == NULL;
		}


		if ((p1->name != p2->name) || (p1->value != p2->value)) return false;


		p1 = p1->next;
		p2 = p2->next;

	}

	return true;

}


ListOps list_ops = {
	.create_example=create_example,
	.newitem=newitem,
	.addend=addend,
	.addfront=addfront,
	.lookup=lookup,
	.apply=apply,
	.freeall=freeall,
	.delitem=delitem,
	.copy=copy,
	.merge=merge,
	.split=split,
	.insertbefore=insertbefore,
	.insertafter=insertafter,
	.reverse_iteratively=reverse_iteratively,
	.reverse_recursively=reverse_recursively,
	.are_equal=are_equal
};
