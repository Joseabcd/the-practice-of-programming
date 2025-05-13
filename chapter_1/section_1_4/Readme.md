### Exercise 1-9.

#define ISDIGIT(c) ((c >= 'O') && (c <= '9')) ? 1 : 0	

If an argument expression contained side effects, it'd be evaluated twice.

Additionally, if this is inserted in the code within another expression involving
other operations, the result will be dependent on the precedence of the operators 
involved. For example:

ISDIGIT('3') + 5 will get replaced at compile time by ((c >= 'O') && (c <= '9')) ? 1 : 0 + 5, what is equivalent to ((c >= 'O') && (c <= '9')) ? 1 : 5 and the result will be the unexpected
value of 1, instead of 6.

To prevent this, it should be wrapped in parentheses:

#define ISDIGIT(c) (((c >= 'O') && (c <= '9')) ? 1 : 0)
