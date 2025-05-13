### Exercise 1-11.

```cpp
void dict::insert(string& w)
// returns 1 if w in dictionary, otherwise returns 0
```
It explains what the return value of insert is, but judging from the name of the function, this doesn't seem to be the main purpose of the function.


```cpp
if (n > MAX || n % 2 > 0) // test for even number
```
The test is not only for determine if the number is even, but also on whether is
greater than MAX. In any case, both conditions seem to be quite clear.



```cpp
// Write a message
// Add to line counter for each line written

void write_message()
{
	// increment line counter
	line_number = line_number +1; fprintf(fout, "%d %s\n%d %s\n%d %s\n",
	line_number, HEADER, line_number +1, BODY, line_number + 2, TRAILER);
	// increment line counter
	line_number = line_number + 2;
}
```
The description of the function is not too bad, but the second line is a bit imprecise: what is to be added to line counter? (the total lines written?) Also, is this line counter a well-known variable across the code or only in a local portion? If the latter were the case, possibly more context should be given.

The two comments within the function are obvious. However, the middle part of the
definition doesn't look as clear, and has no comments.
