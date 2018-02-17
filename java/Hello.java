import java.util.Scanner;

public class Hello {

    public static void countdown(int n) {
        if (n==0) {
            System.out.println("Blastoff!");
        }
        else {
            System.out.println(n);
            countdown(n - 1);
        }
    }

    public static void countup(int n)
    {
        if (n==0) {
            System.out.println("Blastoff!");
        }
        else {
            countup(n - 1);
            System.out.println(n);
        }
    }

    public static void displayBinary(int value) {
        // For more background about binary numbers, see http://www.mathsisfun.com/binary-number-system.html
        if (value>0) {
            displayBinary(value / 2);
            System.out.print(value % 2);
        }
    }

    public static long fibonacci(int n)
    {
        // add cache (to store calculated numbers) for efficiency
        // to avoid recalculation of the Fibonacci numbers

        if (n == 1 || n == 2) return 1;
        else return fibonacci(n-1) + fibonacci(n-2);
    }

    /** Fibonacci with Memoization.
     * use cache to avoid recalculation of the Fibonacci numbers.
     */
    public static int fibonacciArrayDim = 0;
    public static long[] fibonacciArray;

    public static long fibonacciMemoization(int n)
    {
        if (n > fibonacciArrayDim) {
            fibonacciArrayDim = n + 1;
            fibonacciArray = new long[fibonacciArrayDim];
        }

        if (n == 1 || n == 2) return 1;
        if (fibonacciArray[n] == 0) {
            fibonacciArray[n] = fibonacciMemoization(n-1) + fibonacciMemoization(n-2);
        }
        return fibonacciArray[n];
    }

    public static void main(String[] args)      // args is an array of String
    {
	System.out.println("Hello, World!");

        System.out.println("args.length = " + args.length);
        // for (String s: args)
        for (int i=0; i<args.length; ++i)
        {
	    System.out.println("arg #" + i + ": " + args[i]);
	}
	System.out.println("Done with command line arguments\n");

        /*
         * There are two ways to define a String:
         * 
         * 1) with the literal:
         * String s = "abc";
         * 
         * 2) with the String object method using operator new:
         * String s = new String("abc");
         *
         * The most important difference is that the literal is placed into memory pool
         * for possible use. You can call method intern() explicitly to place into the pool
         * the string created with new method.
         *
         * Recommendation from http://www.java67.com/2014/08/difference-between-string-literal-and-new-String-object-Java.html
         * 
         * "In general you should use the string literal notation when possible."
         *
         * Also there
         *
         * "it's suggested as always compare two String object using equals() method and never compare them using == operator,
         * because you never know which one is coming from pool and which one is created using new() operator."
         */

	// String fruit1 = "Apple";     // this is a String literal method. It call intern() automatically to cache the literal in memory.
	// String fruit2 = "Orange";
        // String fruit3 = "Apple";

	String fruit1 = new String("Apple");    // this is a String object method. If you want to cache the string content call intern() explicitely.
	String fruit2 = new String("Orange");
        String fruit3 = new String("Apple");
        System.out.println("fruit1 = " + fruit1 + " fruit2 = " + fruit2 + " fruit3 = " + fruit3);
	System.out.println("fruit1.equals(fruit2): " + fruit1.equals(fruit2));
	System.out.println("fruit1.equals(fruit3): " + fruit1.equals(fruit3));
        System.out.println();
	System.out.println("fruit1 == fruit2: " + (fruit1 == fruit2));
	System.out.println("fruit1 == fruit3: " + (fruit1 == fruit3));
        System.out.println();

	// int n = 9;
	int n = 10;
	int reminder = n % 3;
	System.out.printf("reminder = %d\n",reminder);

	String strNumber = "12";
	Scanner scanner = new Scanner(strNumber);

	// System.out.println(scanner);

	int number = scanner.nextInt();
	System.out.println("number = " + number);

	strNumber = "123";
	if (scanner.hasNextInt()) {
	    number = scanner.nextInt();
	    System.out.println("number = " + number);
	}
	else System.out.println("the strNumber does not contain an int");

        System.out.println("\ncountdown");
	countdown(3);

        System.out.println("\ncountup");
	countup(3);

	System.out.println("Binary for 23 is 10111");
	displayBinary(23);
	System.out.println();

	System.out.println("\n1 + 2 is");
	System.out.println(1+2);
	System.out.println("1 + 2 = " + 1+2);

        // int nFibonacci = 6;
        // int nFibonacci = 16;
        int nFibonacci = 46;            // 5353 ms w/o Memoization, fibonacci number for 46 is 1836311903
        // int nFibonacci = 56;         // takes very long time... (for the primitive algorithm without Memoization)

        long preTime=System.currentTimeMillis();
	System.out.println("\nFibonacci");
	System.out.println("Fibonacci number for " + nFibonacci + " is " + fibonacci(nFibonacci));       // NB: fibonacci(5) = 5
        long postTime=System.currentTimeMillis();
        System.out.println("Time taken to compute in milliseconds: "+(postTime-preTime));

        preTime=System.currentTimeMillis();
	System.out.println("\nFibonacci with Memoization");
	System.out.println("Fibonacci number (with Memoization technique) for " + nFibonacci + " is " + fibonacciMemoization(nFibonacci));       // NB: fibonacciMemoization(5) = 5
        postTime=System.currentTimeMillis();
        System.out.println("Time taken to compute in milliseconds: "+(postTime-preTime));

	System.out.println("\nfor loop");
	for (int i=0; i<3; ++i) {
	    System.out.println(i);
	}
    }
}
