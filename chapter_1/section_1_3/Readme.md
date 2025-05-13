### Exercise 1-7.

if (!istty(stdin) && !istty(stdout) && !itty(stderr)) {
	return(0);
}

if (retval == SUCCESS) {
	return(SUCCESS);
} else{
	return(retval)
}

for (k=0; k < 5; k++) {
	scanf("%lf ", &dx);
	x += dx;
}



### Exercise 1-8.

count is incremented after the test for not exceeding the total, 
so get name could be called with count = total if the loop is not exited
early in the condition below. 

The most idiomatic way is probably the "for" loop:

for (int count = 0; count < total; count++) {
	if (this.getName(count) == nametable.userName()) {
		return(true)
	}
}
