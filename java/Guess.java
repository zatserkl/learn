// George T. Heineman, Gary Pollice & Stanley Selkow, Algorithms in a Nutshell, 2nd Ed.

import java.util.Scanner;

public class Guess
{
    public static int Turns(int n, int low, int high)
    {
        // Computes the number of turns when n is garantied to in range [low, high]

        int turns = 0;

        // Continue while there is is a potential number to guess
        while (high >= low)
        {
            System.out.printf("turns = %d low = %d high = %d\n", turns, low, high);

            turns++;
            if (turns > 100) return -turns;

            int mid = (high + low) / 2;
            if (mid == n) {
                return turns;
            }
            else if (mid < n) {
                low = mid + 1;
            }
            else high = mid - 1;
        }

        return turns;
    }

    public static void main(String[] args)
    {
        //-- for (int i=0; i<args.length; ++i) System.out.printf("%d\t%s\n", i, args[i]);
        for (String arg: args) System.out.println(arg);

        if (args.length == 0) {
            System.out.println("Usage: java Guess 1 512 127");
        }

        int n = 257;
        // int n = 512;
        int low = 1;
        int high = 512;

        // if (args.length > 0) low = Integer.parseInt(args[0]);
        // if (args.length > 1) high = Integer.parseInt(args[1]);
        // if (args.length > 2) n = Integer.parseInt(args[2]);

        // Example of exception from https://docs.oracle.com/javase/tutorial/essential/environment/cmdLineArgs.html

        int iarg = 0;
        try {
            if (args.length > iarg) low = Integer.parseInt(args[0]);
            ++iarg;
            if (args.length > iarg) high = Integer.parseInt(args[1]);
            ++iarg;
            if (args.length > iarg) n = Integer.parseInt(args[2]);
        } catch (NumberFormatException e) {
            System.err.println("Argument args[" + iarg + "] = " + args[iarg] + " must be an integer.");
            System.exit(1);
        }

        System.out.printf("low = %d high = %d n = %d\n", low, high, n);

        System.out.printf("call Turns(%d, %d, %d)\n", n, low, high);

        int turns = Turns(n, low, high);
        System.out.printf("turns = %d\n", turns);
    }
}
