#ifndef LIST_HEADER
#define LIST_HEADER

#include <stdbool.h>


typedef struct Nameval Nameval;
struct Nameval {
	char	*name;
	int		value;
	Nameval	*next;
};


/* ListOps holds pointers to list-related functions. By sharing an instance of this
class with other files, they will have access to these functions */
typedef struct {
	// add the prototypes of the functions to be exposed outside
	Nameval * (*create_example)(int length);
	Nameval * (*newitem)(char *name, int value);
	Nameval * (*addend)(Nameval *listp, Nameval *newp);
	Nameval * (*addfront)(Nameval *listp, Nameval *newp);
	Nameval * (*lookup)(Nameval *listp, char *name);
	void	(*apply)(Nameval *listp, void (*fn)(Nameval*, void*), void *arg);
	void	(*freeall)(Nameval *listp);
	Nameval *	(*delitem)(Nameval *listp, char *name);
	Nameval *	(*copy)(Nameval * listp);
	Nameval *	(*merge)(Nameval *listp1, Nameval *listp2);
	Nameval *	(*split)(Nameval *listp, char *name);
	Nameval *	(*insertbefore)(Nameval *listp, Nameval *newp, char *name);
	Nameval *	(*insertafter)(Nameval *listp, Nameval *newp, char *name);
	Nameval *	(*reverse_iteratively)(Nameval *listp);
	Nameval *	(*reverse_recursively)(Nameval *listp);
	bool	(*are_equal)(Nameval *listp1, Nameval *listp2);

} ListOps;


/* Declare the instance list_ops, which is created in an external file. This assumes that an
instance of the class ListOps, named list_ops, is created in list.c. Declaring it will
make it visible to other files that include this header file. */
extern ListOps list_ops; 


#endif