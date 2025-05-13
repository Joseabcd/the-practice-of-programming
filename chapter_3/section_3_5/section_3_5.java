import java.util.Vector;
import java.util.Hashtable;
import java.util.Random;
import java.io.InputStream;
import java.io.IOException;
import java.io.StreamTokenizer;


class Prefix {
	public String[] pref;
	static final int MULTIPLIER = 31; // for hashCode()

	// constructor: duplicate existing prefix
	Prefix(Prefix p)
	{
		pref = (String[]) p.pref.clone();

	}

	// constructor: n copies of str
	Prefix(int n, String str)
	{
		pref = new String[n];
		for (int i = 0; i < n; i++)
			pref[i] = str;
	}

	// hashCode: generate hash from all prefix words
	public int hashCode()
	{
		int h = 0;
		for (int i = 0; i < pref.length; i++)
			h = MULTIPLIER * h + pref[i].hashCode();
		return h;
	}

	// equals: compare two prefixes for equal words
	public boolean equals(Object o)
	{
		Prefix p = (Prefix) o;
		for (int i = 0; i < pref.length; i++)
			if (!pref[i].equals(p.pref[i]))
				return false;
		return true;
	} 
}


class Chain {
	static final int NPREF = 2; // size of prefix
	static final String NONWORD = "XXXXXXXXXX"; // word that can't appear
	Hashtable statetab = new Hashtable(); // maps prefix arrays to suffix vectors
	Prefix prefix = new Prefix(NPREF, NONWORD); // initial prefix
	Random rand = new Random();

	// build: build State table from input stream
	void build(InputStream in) throws IOException
	{
		StreamTokenizer st = new StreamTokenizer(in);

		st.resetSyntax(); // remove dafault rules
		st.wordChars(0, Character.MAX_VALUE); // turn on all chars
		st.whitespaceChars(0, ' '); // except up to blank
		while (st.nextToken() != st.TT_EOF)
			add(st.sval);
		add(NONWORD);
	}

	// add: add word to suffix list, update prefix
	void add(String word)
	{
		Vector suf = (Vector) statetab.get(prefix);
		if (suf == null) {
			suf = new Vector();
			statetab.put(new Prefix(prefix), suf);
		}
		suf.addElement(word);

		for (int k = 0; k < (prefix.pref.length - 1); k++) {
			prefix.pref[k] = prefix.pref[k + 1];
		}
		prefix.pref[prefix.pref.length - 1] = word;

	}

	// generate: generate output words
	void generate(int nwords) {
		prefix = new Prefix(NPREF, NONWORD);
		for (int i = 0; i < nwords; i++) {
			Vector s = (Vector) statetab.get(prefix);
			int r = Math.abs(rand.nextInt()) % s.size();
			String suf = (String) s.elementAt(r);
			if (suf.equals(NONWORD))
				break;
			System.out.println(suf);

			for (int k = 0; k < (prefix.pref.length - 1); k++) {
				prefix.pref[k] = prefix.pref[k + 1];
			}
			prefix.pref[prefix.pref.length - 1] = suf;

		}
	}

}


class Markov {
	static final int MAXGEN = 10000; // maximum words generated
	public static void main(String[] args) throws IOException
	{
		Chain chain = new Chain();
		int nwords = MAXGEN;

		chain.build(System.in);
		chain.generate(nwords);
	}
}
