// Andriy Zatserklyniy <zatserkl@gmail.com> 

import java.util.Arrays;

/**
 * The Arrays.copyOf(array, length) clones the array.
 * In my case in
 *
 *      a1 = Arrays.copyOf(a);
 *
 * the 4-dimensinal array a1 became a 3-dimentional copy of the array a.
 *
 * Conclusion: Do not use copyOf for coping of a smaller array into larger one.
 */
public class AddToArray {
    public static void main(String[] args)
    {
        int[] a = {10, 20, 30};
        
        System.out.println("a orig:\t" + a.toString() + " " + Arrays.toString(a));

        int[] a1 = new int[a.length + 1];       // one element more than a

        System.out.println("a.length = " + a.length + " a1.length = " + a1.length);

        // Copy old array into new

        //
        // Do NOT use Arrays.copyOf to copy small array into large:
        // the dimension of the tagred array will be reduced to source one
        // 
        // a1 = Arrays.copyOf(a, a.length); // NB: it makes a1.length == a.length

        // use element-by-element copy
        
        for (int i=0; i<a.length; ++i) {
            a1[i] = a[i];
        }

        a1[a1.length - 1] = 400;        // assign the last, 4th element of a1
        
        System.out.println("a1:\t" + a1.toString() + " " + Arrays.toString(a1));

        // swap the arrays

        int[] aOld = a; // keep a reference to the old array

        a = a1;         // now both a and a1 point to the same memory location
        
        // System.out.println("aOld: " + Arrays.toString(aOld));
        // System.out.println("a: " + Arrays.toString(a));
        System.out.println("aOld:\t" + aOld.toString() + " " + Arrays.toString(aOld));
        System.out.println("a1:\t" + a1.toString() + " " + Arrays.toString(a1));
        System.out.println("a:\t" + a.toString() + " " + Arrays.toString(a));
    }
}
