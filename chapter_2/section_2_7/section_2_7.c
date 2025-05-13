#include "list.h"
#include <stdio.h>
#include <stdbool.h>



int main() 
{

	/*------------Copy------------*/

	// test 1

	Nameval *listp, *listp_copy;

	printf("Testing the function copy...");

	listp=list_ops.create_example(0);

	listp_copy = list_ops.copy(listp);

	// test 2

	listp=list_ops.create_example(8);

	listp_copy = list_ops.copy(listp);

	printf("\npass? ----> %d", list_ops.are_equal(listp,listp_copy));


	printf("\npass? ----> %d", list_ops.are_equal(listp,listp_copy));
	printf("\nCompleted testing the function copy.\n\n\n");


	/*------------Merge------------*/

	printf("Testing the function merge...");


	// test 1

	Nameval *listp1=NULL;
	listp1 = list_ops.addend(listp1,list_ops.newitem("name4",4));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name8",8));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name8",8));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name24",24));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name26",26));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name26",26));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name50",50));


	Nameval *listp2=NULL;
	listp2 = list_ops.addend(listp2,list_ops.newitem("name1",1));
	listp2 = list_ops.addend(listp2,list_ops.newitem("name1",1));
	listp2 = list_ops.addend(listp2,list_ops.newitem("name2",2));
	listp2 = list_ops.addend(listp2,list_ops.newitem("name8",8));
	listp2 = list_ops.addend(listp2,list_ops.newitem("name12",12));


	listp = list_ops.merge(listp1,listp2);

	Nameval *testSolution=NULL;
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name1",1));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name1",1));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name2",2));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name4",4));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name8",8));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name8",8));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name8",8));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name12",12));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name24",24));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name26",26));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name26",26));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name50",50));


	printf("\npass? ----> %d", list_ops.are_equal(listp,testSolution));

	// test 2


	listp1=NULL;


	listp2=NULL;
	listp2 = list_ops.addend(listp2,list_ops.newitem("name1",1));
	listp2 = list_ops.addend(listp2,list_ops.newitem("name1",1));
	listp2 = list_ops.addend(listp2,list_ops.newitem("name2",2));


	listp = list_ops.merge(listp1,listp2);


	testSolution=listp2;


	printf("\npass? ----> %d", list_ops.are_equal(listp,testSolution));


	printf("\nCompleted testing the function merge.\n\n\n");


	/*------------Split------------*/

	printf("Testing the function split...");


	// test 1

	listp1=NULL;
	listp1 = list_ops.addend(listp1,list_ops.newitem("name4",4));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name8",8));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name8",8));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name24",24));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name26",26));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name26",26));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name50",50));


	listp2 = list_ops.split(listp1,"name26");


	Nameval *testSolution1 = NULL;
	testSolution1 = list_ops.addend(testSolution1,list_ops.newitem("name4",4));
	testSolution1 = list_ops.addend(testSolution1,list_ops.newitem("name8",8));
	testSolution1 = list_ops.addend(testSolution1,list_ops.newitem("name8",8));
	testSolution1 = list_ops.addend(testSolution1,list_ops.newitem("name24",24));
	testSolution1 = list_ops.addend(testSolution1,list_ops.newitem("name26",26));


	Nameval *testSolution2 = NULL;
	testSolution2 = list_ops.addend(testSolution2,list_ops.newitem("name26",26));
	testSolution2 = list_ops.addend(testSolution2,list_ops.newitem("name50",50));


	bool res1 = list_ops.are_equal(listp1,testSolution1);
	bool res2 = list_ops.are_equal(listp2,testSolution2);


	printf("\npass? ----> %d", res1&&res2);


	// test 2

	listp1 = NULL;
	listp1 = list_ops.addend(listp1,list_ops.newitem("name4",4));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name8",8));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name8",8));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name24",24));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name26",26));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name26",26));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name50",50));


	listp2 = list_ops.split(listp1,"name12345");


	testSolution1 = listp1;

	testSolution2 = NULL;


	res1 = list_ops.are_equal(listp1,testSolution1);
	res2 = list_ops.are_equal(listp2,testSolution2);


	printf("\npass? ----> %d", res1&&res2);


	// test 3

	listp1=NULL;
	listp1 = list_ops.addend(listp1,list_ops.newitem("name4",4));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name8",8));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name8",8));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name24",24));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name26",26));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name26",26));
	listp1 = list_ops.addend(listp1,list_ops.newitem("name50",50));


	listp2 = list_ops.split(listp1,"name4");


	testSolution1 = NULL;
	testSolution1 = list_ops.addend(testSolution1,list_ops.newitem("name4",4));

	testSolution2 = NULL;
	testSolution2 = list_ops.addend(testSolution2,list_ops.newitem("name8",8));
	testSolution2 = list_ops.addend(testSolution2,list_ops.newitem("name8",8));
	testSolution2 = list_ops.addend(testSolution2,list_ops.newitem("name24",24));
	testSolution2 = list_ops.addend(testSolution2,list_ops.newitem("name26",26));
	testSolution2 = list_ops.addend(testSolution2,list_ops.newitem("name26",26));
	testSolution2 = list_ops.addend(testSolution2,list_ops.newitem("name50",50));


	res1 = list_ops.are_equal(listp1,testSolution1);
	res2 = list_ops.are_equal(listp2,testSolution2);


	printf("\npass? ----> %d", res1&&res2);



	printf("\nCompleted testing the function split.\n\n\n");


	/*------------insertbefofe------------*/

	printf("Testing the function insertbefofe...");


	// test 1

	listp=NULL;
	listp = list_ops.addend(listp,list_ops.newitem("name4",4));
	listp = list_ops.addend(listp,list_ops.newitem("name8",8));
	listp = list_ops.addend(listp,list_ops.newitem("name24",24));
	listp = list_ops.addend(listp,list_ops.newitem("name26",26));
	listp = list_ops.addend(listp,list_ops.newitem("name26",26));
	listp = list_ops.addend(listp,list_ops.newitem("name50",50));


	listp2 = list_ops.insertbefore(listp,list_ops.newitem("name1000",1000),"name50");


	testSolution = NULL;
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name4",4));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name8",8));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name24",24));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name26",26));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name26",26));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name1000",1000));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name50",50));



	printf("\npass? ----> %d", list_ops.are_equal(listp2,testSolution));



	// test 2

	listp=NULL;
	listp = list_ops.addend(listp,list_ops.newitem("name4",4));
	listp = list_ops.addend(listp,list_ops.newitem("name8",8));
	listp = list_ops.addend(listp,list_ops.newitem("name24",24));
	listp = list_ops.addend(listp,list_ops.newitem("name26",26));
	listp = list_ops.addend(listp,list_ops.newitem("name26",26));
	listp = list_ops.addend(listp,list_ops.newitem("name50",50));


	listp2 = list_ops.insertbefore(listp,list_ops.newitem("name1000",1000),"name12345");


	testSolution = NULL;
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name4",4));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name8",8));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name24",24));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name26",26));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name26",26));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name50",50));



	printf("\npass? ----> %d", list_ops.are_equal(listp2,testSolution));


	// test 3

	listp=NULL;

	listp2 = list_ops.insertbefore(listp,list_ops.newitem("name1000",1000),"name12345");


	testSolution = NULL;


	printf("\npass? ----> %d", list_ops.are_equal(listp2,testSolution));


	// test 4

	listp=NULL;
	listp = list_ops.addend(listp,list_ops.newitem("name4",4));
	listp = list_ops.addend(listp,list_ops.newitem("name8",8));
	listp = list_ops.addend(listp,list_ops.newitem("name24",24));



	listp2 = list_ops.insertbefore(listp,list_ops.newitem("name4",4),"name4");


	testSolution = NULL;
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name4",4));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name4",4));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name8",8));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name24",24));

	printf("\npass? ----> %d", list_ops.are_equal(listp2,testSolution));


	printf("\nCompleted testing the function insertbefore.\n\n\n");


	/*------------insertafter------------*/

	printf("Testing the function insertafter...");


	// test 1

	listp=NULL;
	listp = list_ops.addend(listp,list_ops.newitem("name4",4));
	listp = list_ops.addend(listp,list_ops.newitem("name8",8));
	listp = list_ops.addend(listp,list_ops.newitem("name24",24));
	listp = list_ops.addend(listp,list_ops.newitem("name26",26));
	listp = list_ops.addend(listp,list_ops.newitem("name26",26));
	listp = list_ops.addend(listp,list_ops.newitem("name50",50));


	listp2 = list_ops.insertafter(listp,list_ops.newitem("name1000",1000),"name50");


	testSolution = NULL;
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name4",4));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name8",8));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name24",24));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name26",26));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name26",26));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name50",50));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name1000",1000));



	printf("\npass? ----> %d", list_ops.are_equal(listp2,testSolution));



	// test 2

	listp=NULL;
	listp = list_ops.addend(listp,list_ops.newitem("name4",4));
	listp = list_ops.addend(listp,list_ops.newitem("name8",8));
	listp = list_ops.addend(listp,list_ops.newitem("name24",24));
	listp = list_ops.addend(listp,list_ops.newitem("name26",26));
	listp = list_ops.addend(listp,list_ops.newitem("name26",26));
	listp = list_ops.addend(listp,list_ops.newitem("name50",50));


	listp2 = list_ops.insertafter(listp,list_ops.newitem("name1000",1000),"name12345");


	testSolution = NULL;
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name4",4));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name8",8));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name24",24));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name26",26));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name26",26));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name50",50));



	printf("\npass? ----> %d", list_ops.are_equal(listp2,testSolution));


	// test 3

	listp=NULL;

	listp2 = list_ops.insertafter(listp,list_ops.newitem("name1000",1000),"name12345");


	testSolution = NULL;


	printf("\npass? ----> %d", list_ops.are_equal(listp2,testSolution));


	// test 4

	listp=NULL;
	listp = list_ops.addend(listp,list_ops.newitem("name4",4));
	listp = list_ops.addend(listp,list_ops.newitem("name8",8));
	listp = list_ops.addend(listp,list_ops.newitem("name24",24));



	listp2 = list_ops.insertafter(listp,list_ops.newitem("name4",4),"name4");


	testSolution = NULL;
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name4",4));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name4",4));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name8",8));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name24",24));

	printf("\npass? ----> %d", list_ops.are_equal(listp2,testSolution));


	printf("\nCompleted testing the function insertafter.\n\n\n");


	/*------------reverse_iteratively------------*/

	printf("Testing the function reverse_iteratively...");


	// test 1

	listp=NULL;
	listp = list_ops.addend(listp,list_ops.newitem("name4",4));
	listp = list_ops.addend(listp,list_ops.newitem("name-1",-1));
	listp = list_ops.addend(listp,list_ops.newitem("name2",2));
	listp = list_ops.addend(listp,list_ops.newitem("name12345678",12345678));
	listp = list_ops.addend(listp,list_ops.newitem("name0",0));
	listp = list_ops.addend(listp,list_ops.newitem("name2",2));

	Nameval *res=list_ops.reverse_iteratively(listp);

	testSolution = NULL;
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name2",2));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name0",0));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name12345678",12345678));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name2",2));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name-1",-1));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name4",4));


	printf("\npass? ----> %d", list_ops.are_equal(res,testSolution));


	// test 2

	listp=NULL;
	listp = list_ops.addend(listp,list_ops.newitem("name4",4));
	listp = list_ops.addend(listp,list_ops.newitem("name-1",-1));
	listp = list_ops.addend(listp,list_ops.newitem("name2",2));


	res=list_ops.reverse_iteratively(listp);

	testSolution = NULL;
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name2",2));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name-1",-1));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name4",4));


	printf("\npass? ----> %d", list_ops.are_equal(res,testSolution));


	// test 3

	listp=NULL;
	listp = list_ops.addend(listp,list_ops.newitem("name4",4));


	res=list_ops.reverse_iteratively(listp);

	testSolution = NULL;
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name4",4));


	printf("\npass? ----> %d", list_ops.are_equal(res,testSolution));

	// test 3

	listp=NULL;


	res=list_ops.reverse_iteratively(listp);

	testSolution = NULL;


	printf("\npass? ----> %d", list_ops.are_equal(res,testSolution));



	printf("\nCompleted testing the function reverse_iteratively.\n\n\n");



	/*------------reverse_recursively------------*/

	printf("Testing the function reverse_recursively...");


	// test 1

	listp=NULL;
	listp = list_ops.addend(listp,list_ops.newitem("name4",4));
	listp = list_ops.addend(listp,list_ops.newitem("name-1",-1));
	listp = list_ops.addend(listp,list_ops.newitem("name2",2));
	listp = list_ops.addend(listp,list_ops.newitem("name12345678",12345678));
	listp = list_ops.addend(listp,list_ops.newitem("name0",0));
	listp = list_ops.addend(listp,list_ops.newitem("name2",2));

	res=list_ops.reverse_recursively(listp);

	testSolution = NULL;
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name2",2));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name0",0));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name12345678",12345678));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name2",2));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name-1",-1));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name4",4));


	printf("\npass? ----> %d", list_ops.are_equal(res,testSolution));


	// test 2

	listp=NULL;
	listp = list_ops.addend(listp,list_ops.newitem("name4",4));
	listp = list_ops.addend(listp,list_ops.newitem("name-1",-1));
	listp = list_ops.addend(listp,list_ops.newitem("name2",2));


	res=list_ops.reverse_recursively(listp);

	testSolution = NULL;
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name2",2));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name-1",-1));
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name4",4));


	printf("\npass? ----> %d", list_ops.are_equal(res,testSolution));


	// test 3

	listp=NULL;
	listp = list_ops.addend(listp,list_ops.newitem("name4",4));


	res=list_ops.reverse_recursively(listp);

	testSolution = NULL;
	testSolution = list_ops.addend(testSolution,list_ops.newitem("name4",4));


	printf("\npass? ----> %d", list_ops.are_equal(res,testSolution));

	// test 3

	listp=NULL;


	res=list_ops.reverse_recursively(listp);

	testSolution = NULL;


	printf("\npass? ----> %d", list_ops.are_equal(res,testSolution));


	printf("\nCompleted testing the function reverse_recursively.\n\n\n");


	return 0;

}
