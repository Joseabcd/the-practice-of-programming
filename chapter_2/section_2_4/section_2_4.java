import java.util.Random;


interface Cmp {
	int cmp(Object x, Object y);
}


// Icmp: Integer comparison
class Icmp implements Cmp {
	public int cmp(Object o1, Object o2)
	{
		int i1 = ((Integer) o1).intValue();
		int i2 =((Integer) o2).intValue();
		if (i1 < i2)
			return -1;
		else if (i1==i2)
			return 0;
		else
			return 1;
	}
}


// Scmp: String comparison
class Scmp implements Cmp {
	public int cmp(Object o1, Object o2)
	{
		String s1 = (String) o1;
		String s2 = (String) o2;
		return s1.compareTo(s2);
	}
}


// Quicksort.sort: quicksort v[left]..v[right]
class Quicksort{

	static void sort(Object[] v, int left, int right, Cmp cmp)
	{
		int i, last;

		if (left >= right) // nothing to do
			return;
		swap(v, left, rand(left,right)); // move pivot elem
		last=left; // to v[left]
		for (i=left+1; i<=right;i++) // partition
			if(cmp.cmp(v[i],v[left])<0)
				swap(v,++last,i);
		swap(v, left, last); // restore pivot elem
		sort(v, left, last-1, cmp); // recursively sort
		sort(v, last+1, right, cmp); // each part
	}

	// Quicksort.swap: swap v[i] and v[j]
	static void swap(Object[] v, int i, int j)
	{
		Object	temp;

		temp=v[i];
		v[i]=v[j];
		v[j]=temp;
	}

	static Random rgen = new Random();

	// Quicksort.rand: return random integer in [left,right]
	static int rand(int left, int right)
	{
		return left + Math.abs(rgen.nextInt())%(right-left+1);
	}

}


class StringQuicksort{

	static void sort(String[] v, int left, int right)
	{
		int i, last;

		if (left >= right) // nothing to do
			return;
		swap(v, left, rand(left,right)); // move pivot elem
		last=left; // to v[left]
		for (i=left+1; i<=right;i++) // partition
			if(v[i].compareTo(v[left])<0)
				swap(v,++last,i);
		swap(v, left, last); // restore pivot elem
		sort(v, left, last-1); // recursively sort
		sort(v, last+1, right); // each part
	}

	// Quicksort.swap: swap v[i] and v[j]
	static void swap(String[] v, int i, int j)
	{
		String	temp;

		temp=v[i];
		v[i]=v[j];
		v[j]=temp;
	}

	static Random rgen = new Random();

	// Quicksort.rand: return random integer in [left,right]
	static int rand(int left, int right)
	{
		return left + Math.abs(rgen.nextInt())%(right-left+1);
	}

}


class IntegerQuicksort{

	static void sort(Integer[] v, int left, int right)
	{
		int i, last;

		if (left >= right) // nothing to do
			return;
		swap(v, left, rand(left,right)); // move pivot elem
		last=left; // to v[left]
		for (i=left+1; i<=right;i++) // partition
			if(Integer.valueOf(v[i])<Integer.valueOf(v[left]))
				swap(v,++last,i);
		swap(v, left, last); // restore pivot elem
		sort(v, left, last-1); // recursively sort
		sort(v, last+1, right); // each part
	}

	// Quicksort.swap: swap v[i] and v[j]
	static void swap(Integer[] v, int i, int j)
	{
		int	temp;

		temp=v[i];
		v[i]=v[j];
		v[j]=temp;
	}

	static Random rgen = new Random();

	// Quicksort.rand: return random integer in [left,right]
	static int rand(int left, int right)
	{
		return left + Math.abs(rgen.nextInt())%(right-left+1);
	}

}


class myClass
{
	public static void main(String[] args)
	{
		
		int n=10000;

		int[] myInts1 = new Random().ints(n, 0, 10000).toArray();

		Integer[] myIntegers1 = new Integer[n];
		Integer[] myIntegers2 = new Integer[n];

		for(int k=0; k < n;k++)
		{
			myIntegers1[k]=Integer.valueOf(myInts1[k]);
			myIntegers2[k]=myIntegers1[k];
		}


		System.out.println("Sorting using Quicksort...");
		final long startTime1 = System.currentTimeMillis();
		Quicksort.sort(myIntegers1,0,myIntegers1.length-1, new Icmp());
		final long endTime1 = System.currentTimeMillis();

		System.out.println("First value: " + myIntegers1[0]);
		System.out.println("Last value: " + myIntegers1[n-1]);

		System.out.println("Sorting execution time: " + (endTime1 - startTime1));


		System.out.println("Sorting using IntegerQuicksort...");
		final long startTime2 = System.currentTimeMillis();
		IntegerQuicksort.sort(myIntegers2,0,myIntegers2.length-1);
		final long endTime2 = System.currentTimeMillis();

		System.out.println("First value: " + myIntegers2[0]);
		System.out.println("Last value: " + myIntegers2[n-1]);

		System.out.println("Sorting execution time: " + (endTime2 - startTime2));

	}
}
