// package com.google.challenges;	//--AZ: commented out to avoid: Error: Could not find or load main class Answer

/*
javac Answer.java
java Answer 12
*/

import java.util.Arrays;

public class Answer {   
    public static int[] answer(int area) { 

	// Your code goes here.

	int[] outlist = new int[100];	// enough room for 1,000,000 range
	int nelements = 0;

	int r = area;
	while (r > 1) {
	    int n = (int) Math.sqrt((double) r);
	    outlist[nelements++] = n*n;
	    r -= n*n;
	}

	if (r > 0) outlist[nelements++] = 1;

	// int[] outlistFinal = new int[nelements];
	// // for (int i=0; i<nelements; ++i) outlistFinal[i] = outlist[i]; // old
	// System.arraycopy(outlist, 0, outlistFinal, 0, nelements); // efficient
	// return outlistFinal;
	
	return Arrays.copyOf(outlist, nelements);
    }

    public static void main(String[] args)
    {
	System.out.println("args.length = " + args.length);
	for (int i=0; i<args.length; ++i) System.out.println("" + i + " " + args[i]);
	System.out.println("");

	int area = args.length > 0? Integer.parseInt(args[0]): 15324;
	
	int[] outlist = answer(area);

	System.out.print("area = " + area + " panels:");
	for (int i=0; i<outlist.length; ++i) System.out.print(" " + outlist[i]);
	System.out.println("");
    }
}
