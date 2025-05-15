### Exercise 3-1.

There are some experiments in the file section_3_4.c.



### Exercise 3-2.

The code for this exercise is in the file section_3_4.c. The version with the 2nd hash table can be enabled by setting the value of  ```WORDS_STORED_ONCE``` to ```1``` inside the ```enum``` at the top of the file.

Running the program with the command /usr/bin/time -l ./a.out, taking as input the book "In Search of Lost Time", reports that the version with hash table of unique words has a lower peak memory consumption (41MB vs 62MB).

Regarding the execution time, the version with the hash table of unique words is also faster (2.55s vs 1.40s on the same book), specially in the part of the program that builds the hash table. While adding the second hash table requires looking up each word of the input text, making a string comparison, this is compensated by the improvement in lookup time in the first hash table. This is because the second hash table will have much fewer elements than the first (there will be many more unique prefixes than unique words), so there will be fewer collisions, and when collisions exist only one word needs to be compared (rather than as many as NPREF).
