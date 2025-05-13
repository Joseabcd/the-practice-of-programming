### Exercise 3-5.

The code for this exercise is in file section_3_6.cpp.

To get the running time and max memory consumption I've used here the command /usr/bin/time -l ./a.out to run the program. 

Simply using unordered_map for the prefix (which came out after the book, in 2011), speeds up the run time from 7.77s to 1.73s; this is already close to the running time of the C program (1.23s), so most of the difference was accounted by the lookups in the map container. Max memory consumption is similar.

The choice of double-ended queues for the prefix is the best. There are three requirements for the prefix: fast push_back operation, fast pop_front operation, and random access or ability to traverse them (in order to compute the hash without making an expensive copy). The only containers that meet these requirements are deque and list (note queue allows neither random access to its elements nor provides a way to iterate through them). List is overkill, as it adds unnecessary overhead by adding the ability to insert elements in the middle, which is not needed here, so that leaves the choice to deque.


The choice of vector for the suffix is also the best. There are two requirements for the suffix: fast push_back operation, and random access or ability to traverse them (in order to choose a random element). The only containers that meet these requirements are list, vector and deque. List is overkill, as it adds unnecessary overhead by adding the ability to insert elements in the middle, which is not needed here. Vectors just provide fast push/pop at the back and random access, as required. Deque provide fast push_back and ability to traverse them; they also provide fast push_front (which isn't needed), but they are worth trying. Measuring the max memory consumption shows that vectors take about half of space than deque.



### Exercise 3-6.

The code for this exercise is in files custom_classes.hpp, custom_classes.cpp and section_3_6.cpp.

To get the running time and max memory consumption I've used here the command /usr/bin/time -l ./a.out to run the program. 

The STL version of the program is faster than the custom version (1.6s vs 5s). However, max memory consumption in the custom version is lower (2.1GB vs 100MB).

