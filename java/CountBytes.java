// based on http://www.lysator.liu.se/java/progGuide/java/nutsandbolts/main.html

// import java.io.InputStream;
// import java.io.FileInputStream;
// import java.io.IOException;             // to use throws java.io.IOException instead of throw IOException
// import java.io.FileNotFoundException;   // to use throws java.io.FileNotFoundException instead of throws FileNotFoundException

/**
  * Counts bytes in the file provided through the command line argument
  */
class CountBytes {
    public static void main(String args[])
	throws java.io.IOException, java.io.FileNotFoundException    // don't need import statements for the exceptions
	// throws IOException, FileNotFoundException   // needs import statement: import java.io.IOException, java.io.FileNotFoundException;
	// throws IOException  // the same as previous because IOException includes FileNotFoundException
/*
NB: if you don't throw exceptions in the main (comment out the throws line), you'll get:

java$ javac CountBytes.java
CountBytes.java:13: error: unreported exception FileNotFoundException; must be caught or declared to be thrown
	    is = new FileInputStream(args[0]);
	         ^
CountBytes.java:17: error: unreported exception IOException; must be caught or declared to be thrown
        while (is.read() != -1)
                      ^
2 errors
*/
    {
        int count = 0;
	java.io.InputStream is;

        if (args.length == 1)
	    is = new java.io.FileInputStream(args[0]);
	else {
	    System.out.println("Enter the characters to count followed by Ctrl-D twice");
	    is = System.in;
	}
	
        while (is.read() != -1)
            count++;

	if (args.length == 1)
	    System.out.println(args[0] + " has "+ count + " chars.");
	else
	    System.out.println("\nInput has " + count + " chars.");
    }
}
