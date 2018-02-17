import java.util.Arrays;        // NB: Arrays is plural

/**
 * The Arrays.copyOf(array, length) clones the array.
 * In my case in
 *
 *      a1 = Arrays.copyOf(a);
 *
 * the 4-dimensinal array a1 became a 3-dimentional copy of the array a
 *
 * Conclusion: Do not use copyOf for coping of a smaller array into larger one.
 */
public class ArraysCopyOf       // NB: in the class name: Arrays (plural)
{
    private int[] array;

    private ArraysCopyOf()      // forbid to use w/o parameters. BUT it will be called anyway!?
    {
        // this(0);             // call of the ArraysCopyOf(array) works fine
        System.out.println("private default constructor of ArraysCopyOf");
    }

    public ArraysCopyOf(int... array)   // parameter int... is considered as an array
    {
        System.out.println("constructor ArraysCopyOf: array.length = " + array.length);
        System.out.println("this.array = Arrays.copyOf(array, array.length)");
        this.array = Arrays.copyOf(array, array.length);
    }

    @Override               // @Override is an annotation
    public String toString() {
        return String.format("%s(array=%s)",
                getClass().getSimpleName(), Arrays.toString(array));
    }

    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50};

        System.out.println("--> constructor ArraysCopyOf(array)\n");

        ArraysCopyOf arraysCopyOf = new ArraysCopyOf(array);
        System.out.println("\narraysCopyOf:\n" + arraysCopyOf);

        System.out.println("\n--> Another way to provide arbitrary number of arguments\n");

        ArraysCopyOf arraysCopyOf1 = new ArraysCopyOf(100, 200, 300, 400, 500);
        System.out.println("\narraysCopyOf1:\n" + arraysCopyOf1);

        System.out.println("\n--> Send zero parameters to the constructor ArraysCopyOf\n");

        ArraysCopyOf arraysCopyOf2 = new ArraysCopyOf();
        System.out.println("\narraysCopyOf2:\n" + arraysCopyOf2);
    }
}
