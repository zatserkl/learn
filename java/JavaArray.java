import java.util.Arrays;

public class JavaArray {
    public static void main(String[] args)
    {
        int[] a1;
        a1 = new int[5];

        for (int i=0; i<5; ++i) a1[i] = 10*(i+1);
        System.out.print("a1:");
        for (int i=0; i<5; ++i) System.out.print(" " + a1[i]);
        System.out.println();

        System.out.println("Arrays.toString(a1): " + Arrays.toString(a1));

        // two-dim

        System.out.println("\ntwo-dimensional array");

        int[][] a2 = new int[3][4];

        System.out.println("a2.length = " + a2.length + " a2[0].length = " + a2[0].length);

        for (int row=0; row<a2.length; ++row) {
            for (int col=0; col<a2[row].length; ++col) {    // same as a2[0].length
                System.out.print(a2[row][col] + " ");
            }
            System.out.println();
        }

        // ragged array: array with rows of different length

        System.out.println("\nRagged array");

        int[][] aRagged;
        aRagged = new int[3][];     // addresses of rows
        aRagged[0] = new int[4];
        aRagged[1] = new int[3];
        aRagged[2] = new int[5];

        for (int row=0; row<aRagged.length; ++row) {
            for (int col=0; col<aRagged[row].length; ++col) {
                System.out.print(aRagged[row][col] + " ");
            }
            System.out.println();
        }
    }
}
