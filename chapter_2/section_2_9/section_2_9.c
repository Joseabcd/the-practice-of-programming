#include "table.h"
#include<stdio.h>



int main()
{
	int NHASH0 = 37;

	NVsymtab *example_table = table_ops.create_example(100, NHASH0);

	printf("%f\n",((float) example_table->nval)/(example_table->nhash));

	char* printed_name;

	if (table_ops.lookup(example_table, "xxx",1,0)) {
		printed_name=table_ops.lookup(example_table, "xxx",0,0)->name;
	}
	else {
		printed_name="NOT FOUND.";
	}

	printf("%f\n",((float) example_table->nval)/(example_table->nhash));

	printf(
		"%s\n",
		printed_name
	);



	// printf("%s\n\n\n", get(example_table, 20)->name);



	// if (lookup(example_table, "name1155500400",0,0)) {
	// 	printed_name=lookup(example_table, "name1155500400",0,0)->name;
	// }
	// else {
	// 	printed_name="NOT FOUND.";
	// }



	// memcpy(symtab, example_table, NHASH*sizeof(*example_table));


	// printf("%s\n", get(0)->name);
	// printf("%s\n", get(15)->name);
	// printf("%s\n", get(49)->name);




	// unsigned int h;
	// const int k = 16;


	// char s1[3];

	// s1[0] = k + NHASH;
	// s1[1] = k + NHASH;
	// s1[2] = '\0';
	// h = stringhash(s1);
	// printf("%d\n", h);


	// s1[0] = k + 2 * NHASH;
	// s1[1] = k + NHASH;
	// s1[2] = '\0';
	// h = stringhash(s1);
	// printf("%d\n", h);


	// s1[0] = k + 3 * NHASH;
	// s1[1] = k + 2 * NHASH;
	// s1[2] = '\0';	
	// h = stringhash(s1);
	// printf("%d\n", h);


	// char s2[4];

	// s2[0] = k + 3 * NHASH;
	// s2[1] = k + 2 * NHASH;
	// s2[2] = k + 1 * NHASH;
	// s2[3] = '\0';	
	// h = stringhash(s2);
	// printf("%d\n", h);

	// s2[0] = k + 1 * NHASH;
	// s2[1] = k + 1 * NHASH;
	// s2[2] = k + 3 * NHASH;
	// s2[3] = '\0';	
	// h = stringhash(s2);
	// printf("%d\n", h);


	// char s3[4];

	// s3[0] = 12;
	// s3[1] = 18;
	// s3[2] = 5;
	// s3[3] = '\0';
	// h = stringhash(s3);
	// printf("%d\n", h);

	// s3[0] = -120;
	// s3[1] = 118;
	// s3[2] = 5;
	// s3[3] = '\0';	
	// h = stringhash(s3);
	// printf("%d\n", h);



	return 0;

}