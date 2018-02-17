/**
  Snap implementation of the Merge Sort algorithm in Java.
  */

import java.util.Arrays;

public class MergeSort
{
    public void mergeSort(int[] a, int[] b, int[] c)
    {
        int ia = 0;
        int ib = 0;
        int ic = 0;

        while (ia < a.length && ib < b.length)    // lengthMin elements from both a and b
        {
            // System.out.println("        mergeSort: a[ia] = " + a[ia] + " b[ib] = " + b[ib]);
            if (a[ia] <= b[ib]) c[ic++] = a[ia++];
            else c[ic++] = b[ib++];
        }

        while (ia < a.length) c[ic++] = a[ia++];
        while (ib < b.length) c[ic++] = b[ib++];
    }

    /**
      Takes an array as a parameter. Splits it to two parts and call merge to combine them back sorted.
      Performs a recursive call for each part.
      Splits the input array into two parts.
      Has just one parameter: array a. Performs recursive calls for the two parts of the array.
      Allocated space for the output arrays aLow and aHigh
      */
    public void mergeSplit(int a[])
    {
        if (a.length < 2) return;           // stops the recursion

        int n = a.length / 2;
        int[] aLow = new int[n];
        int[] aHigh = new int[a.length - n];

        for (int i=0; i<aLow.length; ++i) aLow[i] = a[i];
        for (int i=0; i<aHigh.length; ++i) aHigh[i] = a[n + i];

        System.out.println("    mergeSplit: aLow: " + Arrays.toString(aLow));
        System.out.println("    mergeSplit: aHigh: " + Arrays.toString(aHigh));

        // recursive calls (occurs then the number of elements is greater than 2)
        mergeSplit(aLow);
        mergeSplit(aHigh);

        // merge the results back into original array
        mergeSort(aLow, aHigh, a);
    }

    public void mergeSort(int[] a)          // like an alias for mergeSplit
    {
        mergeSplit(a);
    }

    public static void main(String[] args)
    {
        int array[] = {40, 10, 20, 50, 30};

        System.out.println("array: " + Arrays.toString(array));

        int a[] = {10, 50};
        int b[] = {20, 30, 40};
        int c[] = new int[a.length + b.length];

        MergeSort mergeSort = new MergeSort();

        // test mergeSort

        System.out.println("\n// test just mergeSort");

        mergeSort.mergeSort(a, b, c);

        System.out.println("a: " + Arrays.toString(a));
        System.out.println("b: " + Arrays.toString(b));
        System.out.println("c: " + Arrays.toString(c));

        // test mergeSplit

        System.out.println("\n// test mergeSplit: this is basically the MergeSort algorithm");

        // mergeSort.mergeSplit(a);
        // System.out.println("a: " + Arrays.toString(a));

        mergeSort.mergeSplit(array);
        System.out.println("array: " + Arrays.toString(array));
    }
}
