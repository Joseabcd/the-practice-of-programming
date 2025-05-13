### Exercise 1-1.

TRUE has been redefined with 0, which usually indicates the logical value of False. Same thing for FALSE. They're reversed from how they would intuitively be.

not-eof contains a hyphen? Besides normally not being a valid variable name, there is a double negation in there.



### Exercise 1-2.

int isSmaller(char *s, char *t) {
	if (strCompare(s, t) < 1) {
		return 1;
	} else {
		return 0;
	}
}
