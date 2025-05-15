### Exercise 3-7.

Solution in files markov.awk and markov.pl. The approach taken has differed in both languages, for the sake of exploration. The difference is in the way to define and access the elements in the state table using a prefix of arbitrary length. In AWK, the associative array with the states has been kept flat, and the indexes have been constructed by concatenating the prefix strings. In Perl, the state table is a data structure of nested hashes, each of which gets created one after the other in a loop.

The specific 2-prefix version runs slightly faster than the general version with NPREF = 2 (1.3s vs 2.6s on the input ../section_3_4/InSearchOfLostTime.txt). This may be explained by the added overhead from concatenating the prefixes into a string. When NPREF is increased, the timing also increases, as the effort to shift the prefix is larger. Using NPREF = 3 takes 3.5s, using NPREF = 6 takes 5.4s.

With Perl, the specific 2-prefix is roughly twice as fast as the general version with NPREF = 2 (1.2s vs 0.6s on the input ../section_3_4/InSearchOfLostTime.txt). This slowdown is understandable, as Perl must have a more efficient internal way of doing this multi-indexing, which is faster than constructing the nested hashes using top-level code. When NPREF is increased, the timing also increases a bit, as there are more hashes to create at deeper levels. Using NPREF = 3 takes 1.7s, using NPREF = 6 takes 2.8s.

