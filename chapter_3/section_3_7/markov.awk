
# markov.awk: markov chain algorithm for prefixes of NPREF length

BEGIN {
	NPREF = 2
	MAXGEN = 10000
	NONWORD = "XXXXXXXXXX"

	for (i = 1; i <= NPREF; i++) {
		pref[i] = NONWORD
	}
}

{
	for (i = 1; i <= NF; i++) {  # read all words in the current line
		wstr = prefixtostr(pref)
		statetab[wstr,++nsuffix[wstr]] = $i
		shiftprefix(pref, $i)
	}
}

END {
	wstr = prefixtostr(pref)
	statetab[wstr,++nsuffix[wstr]] = NONWORD  # add tail

	for (i = 1; i <= NPREF; i++) {
		pref[i] = NONWORD
	}
	for (i = 0; i < MAXGEN; i++) {
		wstr = prefixtostr(pref)
		r = int(rand() * nsuffix[wstr]) + 1  # nsuffix >= 1
		p = statetab[wstr,r]
		if (p == NONWORD)
			exit
		print p
		shiftprefix(pref, p)
	}
}


function prefixtostr(pref, ii)
{	
	result = ""
	for (ii = 1; ii <= NPREF; ii++) {
		result = result " " pref[ii]
	}
	return result
}


function shiftprefix(pref, s, ii)
{
	for (ii = 1; ii < NPREF; ii++) {
		pref[ii] = pref[ii + 1]
	}
	pref[NPREF] = s

}
