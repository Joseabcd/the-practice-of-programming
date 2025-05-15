
# markov.pl: markov chain algorithm for 2-word prefixes

$MAXGEN = 10000;
$NONWORD = "XXXXXXXXXX";
$w1 = $w2 = $NONWORD;  # initial state
while (<>) {
	foreach (split) {
		push(@{$statetab{$w1}{$w2}}, $_);
		($w1, $w2) = ($w2, $_);  # multiple assignment
	}
}
push(@{$statetab{$w1}{$w2}}, $NONWORD);  # add tail

$w1 = $w2 = $NONWORD;
for ($i = 0; $i < $MAXGEN; $i++) {
	$suf = $statetab{$w1}{$w2};  # array reference
	$r = int(rand @$suf);  # @$suf evaluates to number of elems when used with rand
	exit if (($t = $suf->[$r]) eq $NONWORD);
	print "$t\n";
	($w1, $w2) = ($w2, $t);  #advance chain
}