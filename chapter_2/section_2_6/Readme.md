### Exercise 2-5.

It is not worthwhile to resize the array every time that an element is delete, as the space that only 1 element leaves behind is normally negligible.

I would decide to do so based on the number of unused spots in the array; this is, based on (nvtab.max - nvtab.nval) reaching a certain threshold.



### Exercise 2-6.

```cpp
/* delname: remove first matching nameval from nvtab */
int delname(char *name)
{
	int i;
	for (i = 0; i < nvtab.nval; i++)
		if (strcmp(nvtab.nameval[i].name,name) == 0) {
			nvtab.nameval=NULL;
			nvtab.nval--;
			return 1;
		}
	return 0;
}


typedef struct Nameval Nameval;
struct Nameval {
	char	*name;
	int	value;
};

struct NVtab {
	int	nval;	/* current number of values */
	int	max;	/* allocated number of values */
	nameval	*nameval; /* array of name-value pairs */
	int nunused; /* number of unused positions between positions 0 and nval-1 */
} nvtab;

enum { NVINIT = 1, NVGROW = 2 };

/* add name: add new name and value to nvtab */
int addname (Nameval newname)
{
	Nameval *nvp;

	if (nvtab.nameval == NULL) { /* first time */
		nvtab.nameval=
			(Nameval *) malloc(NVINIT * sizeof(Nameval));
		if (nvtab.nameval == NULL)
			return -1;
		nvtab.max=NVINIT;
		nvtab.nval = 0;

	} else if(nunused>0) {
		for(int i=0; i<nval; i++) {
			if(nvtab.nameval[i]==NULL) {
				nvtab.nameval[i]=newname;
				nvtab.nval++;
				nvtab.nunused--;
				return i;
			}
		}
	} else if(nvtab.nval >= nvtab.max) { /* grow */
		nvp = (Nameval*) realloc(nvtab.nameval,
			(NVGROW*nvtab.max)*sizeof(Nameval));
		if(nvp == NULL)
			return -1;
		nvtab.max*=NVGROW;
		nvtab.nameval=nvp;
	}
	nvtab.nameval[nvtab.nval] = newname;
	return nvtab.nval++;

}
```

Apart from these two functions, the rest of the program is only affected by the inclusion of a new attribute in NVtab, to keep track of how
many unused positions we have. This is to prevent searching for them if there're not any. 

It would possibly be better to have instead an array that keeps track of the positions with the unused items, to prevent having to search for them,
but it would be another array that grows.
