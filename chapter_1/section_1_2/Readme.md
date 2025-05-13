### Exercise 1-4.

if (c != 'y') && (c != 'Y')
	return;

length = ( (length < BUFSIZE) ? length : BUFSIZE );

flag = ! flag;

isQuote = (*line == '"') ? 1 : 0;

if (val == 1)
	bit = 1;
else
	bit = 0;



### Exercise 1-5.

The function "read" reads an integer from stdin, stores it in a passed variable, and returns the value that has been stored in such variable. This looks ok. 

However, is the order in which the two calls to the function below are made well defined? Possibly not, and this would make it unreliable, making it unclear whether the first value input to stdin is for "val" or for "ch"



### Exercise 1-6.

One possibility is that the second argument gets evaluated before the third argument:
	1 2


another possibility is that the second argument gets evaluated after the third argument:
	2, 1

is it another possibility that they get executed at the same time?, then giving:
	1, 1

I've tried it with clang and with other online compilers and have gotten the first and second possibilities.
