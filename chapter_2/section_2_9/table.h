#ifndef TABLE_HEADER
#define TABLE_HEADER

#include "../section_2_7/list.h"


typedef struct NVsymtab NVsymtab;
struct NVsymtab {
	int nval;
	int nhash;
	Nameval **tablep;
};


/* TableOps holds pointers to hash-table-related functions. By sharing an instance of this
class with other files, they will have access to these functions */
typedef struct {
	// add the prototypes of the functions to be exposed outside
	unsigned int (*stringhash)(char *str, int nhash);
	NVsymtab * (*create_example)(int n, int nhash);
	Nameval* (*lookup)(NVsymtab *symtabp, char *name, int create, int value);
	

} TableOps;


/* Declare the instance table_ops, which is created in an external file. This assumes that an
instance of the class TableOps, named table_ops, is created in table.c. Declaring it will
make it visible to other files that include this header file. */
extern TableOps table_ops;


#endif