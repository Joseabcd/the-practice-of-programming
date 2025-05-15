
# markov.pl: markov chain algorithm for 2-word prefixes

$NPREF = 2;
$MAXGEN = 10000;
$NONWORD = "XXXXXXXXXX";
@pref = ($NONWORD) x $NPREF;  # initial state
$statetab = {};
while (<>) {
	foreach (split) {
		$suf = lookup($statetab, @pref);
		push(@{$suf}, $_);
		@pref = (@pref[1..$#pref], $_); # shift the prefix
	}
}
$suf = lookup($statetab, @pref);
push(@{$suf}, $NONWORD);  # add tail

@pref = ($NONWORD) x $NPREF;
for ($i = 0; $i < $MAXGEN; $i++) {
	$suf = lookup($statetab, @pref);  # array reference
	$r = int(rand @$suf);  # @$suf evaluates to number of elems when used with rand
	exit if (($t = $suf->[$r]) eq $NONWORD);
	print "$t\n";
	@pref = (@pref[1..$#pref], $t); #advance chain
}


# lookup: takes a reference to a hash as first argument,
# and an array of keys as second argument. Returns a
# reference to the element in the hash indexed by the keys.
# If not found, it creates an empty array in that position
# and returns a reference to it.
sub lookup {

	my ($rt0, @keys) = @_;

	my $rt;
	my $n = $#keys + 1; # number of keys

	$rt0->{$keys[0]} = {} if !defined $rt0->{$keys[0]};
	$rt = $rt0->{$keys[0]};
	my $i;
	for ($i = 1; $i < $n - 1; $i++) {
		$rt->{$keys[$i]} = {} if ! defined $rt->{$keys[$i]};
		$rt = $rt->{$keys[$i]};
	}

	# create an empty list if no element exists yet at the position indexed by keys
	$rt->{$keys[$n - 1]} = [] if !defined $rt->{$keys[$n - 1]};

	return $rt->{$keys[$n - 1]};
}
