// George T. Heineman, Gary Pollice & Stanley Selkow, Algorithms in a Nutshell, 2nd Ed.

import java.util.Scanner;

public class MaxElement
{
    // public class NoSuchElementException extends Exception {
    // }

    public static int maxElement(int[] vals)
    {
        if (vals.length == 0) {
            // throw new NoSuchElementException("No Max Element in Empty Array");
            System.out.println("No Max Element in Empty Array");
        }
        return maxElement(vals, 0, vals.length);
    }

    public static int maxElement(int[] vals, int left, int right)
    {
        System.out.println("maxElement: left = " + left + " right = " + right);

        //-- if (right - left == 1) return vals[left];
        if (right - left == 1) {
            System.out.println("-- maxElement: return element for left = " + left);
            return vals[left];
        }

        int mid = (right + left) / 2;
        // System.out.println("\tleft = " + left + " right = " + right + " mid = " + mid);
        
        int maxLeft = maxElement(vals, left, mid);      // NB: mid element is excluded
        int maxRight = maxElement(vals, mid, right);

        System.out.printf("\t\tCompare maxLeft = %d and maxRight = %d\n", maxLeft, maxRight);
        if (maxLeft >= maxRight) return maxLeft;
        else return maxRight;
    }

    public static void main(String[] args)
    {
        int vals[] = {2, 9, 3, 6, 4, 1, 7, 8, 5, 0};

        for (int i=0; i<10; ++i) System.out.printf("%d ", i);
        System.out.println();
        for (int val: vals) System.out.printf("%d ", val);
        System.out.println();

        // int max = vals[0];
        // max = maxElement(vals);

        int max = vals[0];
        try {
            max = maxElement(vals);
        }
        catch (StackOverflowError e) {                            // used during development
            //System.out.println("***Exception StackOverflowError" + e);
            System.out.println("***Exception thrown: " + e);
            System.exit(1);
        }
        // catch (NoSuchElementException e) {
        //     System.err.println("***Exception thrown: " + e);
        //     System.exit(1);
        // }

        // try {
        //     max = maxElement(vals);
        // } catch (NoSuchElementException e) {
        //     System.err.println("Exception");
        //     System.exit(1);
        // }

        System.out.printf("max element is %d\n", max);
    }
}
